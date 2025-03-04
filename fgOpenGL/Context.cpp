// Copyright (c)2022 Fundament Software
// For conditions of distribution and use, see copyright notice in "BackendGL.hpp"

#include "BackendGL.hpp"
#include "VertexArrayObject.hpp"
#include "ProgramObject.hpp"
#include "EnumMapping.hpp"
#include <algorithm>
#include <cassert>
#include <cfloat>
#include <cstring>

#define kh_pair_hash_func(key) \
  kh_int64_hash_func((static_cast<uint64_t>(kh_ptr_hash_func(key.first)) << 32) | kh_int_hash_func(key.second))

using namespace GL;

// Feather uses a premultiplied compositing pipeline:
// https://apoorvaj.io/alpha-compositing-opengl-blending-and-premultiplied-alpha/
const FG_Blend Context::Premultiply_Blend = {
  FG_Blend_Operand_One,
  FG_Blend_Operand_Inv_Src_Alpha,
  FG_Blend_Op_Add,
  FG_Blend_Operand_One,
  FG_Blend_Operand_Inv_Src_Alpha,
  FG_Blend_Op_Add,
  0b1111,
};

const FG_Blend Context::Normal_Blend = {
  FG_Blend_Operand_Src_Alpha,
  FG_Blend_Operand_Inv_Src_Alpha,
  FG_Blend_Op_Add,
  FG_Blend_Operand_One,
  FG_Blend_Operand_Inv_Src_Alpha,
  FG_Blend_Op_Add,
  0b1111,
};

const FG_Blend Context::Default_Blend = {
  FG_Blend_Operand_One,  FG_Blend_Operand_Zero, FG_Blend_Op_Add, FG_Blend_Operand_One,
  FG_Blend_Operand_Zero, FG_Blend_Op_Add,       0b1111,
};

Context::Context(Backend* backend, FG_Element* element, FG_Vec2 dim) :
  _backend(backend), _window(nullptr), _lastblend(Default_Blend), _program(nullptr), _dim(dim)
{
  this->element = element;
  this->context = this;
}
Context::~Context() {}

GLExpected<void> Context::BeginDraw(const FG_Rect* area)
{
  if(_window)
  {
    glfwMakeContextCurrent(_window);
  }
  else
  {
    glEnable(GL_SCISSOR_TEST);
    GL_ERROR("glEnable");
    glScissor(0, 0, _dim.x, _dim.y);
    GL_ERROR("glScissor");
  }

  return {};
}

GLExpected<void> Context::EndDraw()
{
  if(_window)
    glfwSwapBuffers(_window);
  return {};
}

void Context::Draw(const FG_Rect* area)
{
  FG_Msg msg = { FG_Event_Kind_Draw };
  if(area)
    msg.draw.area = *area;
  else
  {
    if(_window)
    {
      int x, y;
      glfwGetFramebufferSize(_window, &x, &y);
      _dim.x = static_cast<float>(x);
      _dim.y = static_cast<float>(y);
    }
    msg.draw.area.right  = _dim.x;
    msg.draw.area.bottom = _dim.y;
  }

  _backend->BeginDraw(_backend, this, &msg.draw.area);
  _backend->Behavior(this, msg);
  _backend->EndDraw(_backend, this);
}

GLExpected<void> Context::Dispatch()
{
  glDispatchCompute(_workgroup.x, _workgroup.y, _workgroup.z);
  GL_ERROR("glDispatchCompute");
  return {};
}

GLExpected<void> Context::Barrier(GLbitfield barrier_flags)
{
  glMemoryBarrier(barrier_flags);
  GL_ERROR("glMemoryBarrier");
  return {};
}

GLExpected<void> Context::ApplyProgram(const ProgramObject& program)
{
  glUseProgram(program);
  GL_ERROR("glUseProgram");
  _program = &program;
  return {};
}

GLExpected<void> Context::SetShaderUniforms(const FG_ShaderParameter* uniforms, const FG_ShaderValue* values,
                                            uint32_t count)
{
  for(uint32_t i = 0; i < count; ++i)
  {
    if(uniforms[i].type == FG_Shader_Type_Buffer)
    {
      RETURN_ERROR(_program->set_buffer(values[i].resource, uniforms[i].count, uniforms[i].width, uniforms[i].length));
      continue;
    }

    auto type      = ShaderObject::get_type(uniforms[i]);
    uint32_t count = !uniforms[i].count ? 1 : uniforms[i].count;

    switch(type)
    {
    case GL_DOUBLE:
    case GL_HALF_FLOAT: // we assume you pass in a proper float to fill this
    case GL_FLOAT:
    case GL_INT:
    case GL_UNSIGNED_INT:
      if(count == 1)
      {
        RETURN_ERROR(_program->set_uniform(uniforms[i].name, type, &values[i].f32, count));
        break;
      }
      // Otherwise fallthrough because the value couldn't be stored directly
    default:
      if(type >= GL_TEXTURE0 && type <= GL_TEXTURE31)
      {
        RETURN_ERROR(_program->set_texture(uniforms[i].name, type, static_cast<GLuint>(values[i].resource)));
      }
      else
      {
        RETURN_ERROR(_program->set_uniform(uniforms[i].name, type, values[i].pf32, count));
      }
      break;
    }
  }
  return {};
}

GLExpected<void> Context::DrawArrays(uint32_t vertexcount, uint32_t instancecount, uint32_t startvertex,
                                     uint32_t startinstance)
{
  if(instancecount > 0)
    return CUSTOM_ERROR(ERR_NOT_IMPLEMENTED, "don't know how to instance things!");
  glDrawArrays(_primitive, startvertex, vertexcount);
  GL_ERROR("glDrawArrays");
  return {};
}
GLExpected<void> Context::DrawIndexed(uint32_t indexcount, uint32_t instancecount, uint32_t startindex, int startvertex,

                                      uint32_t startinstance)
{
  if(instancecount > 0)
    return CUSTOM_ERROR(ERR_NOT_IMPLEMENTED, "don't know how to instance things!");
  glDrawElements(_primitive, indexcount, _indextype, nullptr);
  GL_ERROR("glDrawElements");
  return {};
}

int Context::GetBytes(GLenum type)
{
  switch(type)
  {
  case GL_BYTE:
  case GL_UNSIGNED_BYTE: return 1;
  case GL_SHORT:
  case GL_UNSIGNED_SHORT:
  case GL_HALF_FLOAT: return 2;
  case GL_INT:
  case GL_UNSIGNED_INT:
  case GL_INT_2_10_10_10_REV:
  case GL_UNSIGNED_INT_2_10_10_10_REV:
  case GL_UNSIGNED_INT_10F_11F_11F_REV:
  case GL_FLOAT: return 4;
  case GL_DOUBLE: return 8;
  }
  assert(false);
  return 0;
}

void Context::FlipFlag(int diff, int flags, int flag, int option)
{
  if(diff & flag)
  {
    if(flags & flag)
      glEnable(option);
    else
      glDisable(option);
  }
}

GLExpected<void> Context::ApplyBlendFactor(const std::array<float, 4>& factor)
{
  if(_lastfactor != factor)
  {
    glBlendColor(factor[0], factor[1], factor[2], factor[3]);
    GL_ERROR("glBlendColor");
    _lastfactor = factor;
  }
  return {};
}

GLExpected<void> Context::ApplyBlend(const FG_Blend& blend, bool force)
{
  if(force || memcmp(&blend, &_lastblend, sizeof(FG_Blend)) != 0)
  {
    glBlendFuncSeparate(BlendMapping[blend.src_blend], BlendMapping[blend.dest_blend], BlendMapping[blend.src_blend_alpha],
                        BlendMapping[blend.dest_blend_alpha]);
    GL_ERROR("glBlendFuncSeperate");
    glBlendEquationSeparate(BlendOpMapping[blend.blend_op], BlendOpMapping[blend.blend_op_alpha]);
    GL_ERROR("glBlendEquationSeparate");

    if(_lastblend.rendertarget_write_mask != blend.rendertarget_write_mask)
    {
      glColorMask(blend.rendertarget_write_mask & 0b0001, blend.rendertarget_write_mask & 0b0010,
                  blend.rendertarget_write_mask & 0b0100, blend.rendertarget_write_mask & 0b1000);
      GL_ERROR("glColorMask");
    }

    _lastblend = blend;
  }

  return {};
}

GLExpected<void> Context::ApplyFill(uint8_t fill)
{
  if(_lastfill != fill)
  {
    switch(fill)
    {
    case FG_Fill_Mode_Fill: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
    case FG_Fill_Mode_Line: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
    case FG_Fill_Mode_Point: glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); break;
    }
    GL_ERROR("glPolygonMode");
    _lastfill = fill;
  }
  return {};
}

GLExpected<void> Context::ApplyCull(uint8_t cull)
{
  if(_lastcull != cull)
  {
    if(cull == FG_Cull_Mode_None)
    {
      glDisable(GL_CULL_FACE);
      GL_ERROR("glDisable");
    }
    else
    {
      glEnable(GL_CULL_FACE);
      GL_ERROR("glEnable");

      glCullFace(cull == FG_Cull_Mode_Back ? GL_BACK : GL_FRONT);
      GL_ERROR("glCullFace");
    }

    _lastcull = cull;
  }
  return {};
}
GLExpected<void> Context::ApplyFlags(uint16_t flags)
{
  auto diff = _lastflags ^ flags;
  FlipFlag(diff, flags, FG_Pipeline_Flag_RenderTarget_SRGB_Enable, GL_FRAMEBUFFER_SRGB);
  GL_ERROR("glEnable/glDisable");
  FlipFlag(diff, flags, FG_Pipeline_Flag_Depth_Enable, GL_DEPTH_TEST);
  GL_ERROR("glEnable/glDisable");
  FlipFlag(diff, flags, FG_Pipeline_Flag_Stencil_Enable, GL_STENCIL_TEST);
  GL_ERROR("glEnable/glDisable");
  FlipFlag(diff, flags, FG_Pipeline_Flag_Alpha_To_Coverage_Enable, GL_SAMPLE_ALPHA_TO_COVERAGE);
  GL_ERROR("glEnable/glDisable");
  FlipFlag(diff, flags, FG_Pipeline_Flag_Antialiased_Line_Enable, GL_LINE_SMOOTH);
  GL_ERROR("glEnable/glDisable");
  FlipFlag(diff, flags, FG_Pipeline_Flag_Multisample_Enable, GL_MULTISAMPLE);
  GL_ERROR("glEnable/glDisable");
  FlipFlag(diff, flags, FG_Pipeline_Flag_Blend_Enable, GL_BLEND);
  GL_ERROR("glEnable/glDisable");

  if(diff & FG_Pipeline_Flag_Depth_Write_Enable)
  {
    glDepthMask((flags & FG_Pipeline_Flag_Depth_Write_Enable) ? GL_TRUE : GL_FALSE);
    GL_ERROR("glDepthMask");
  }
  if(diff & FG_Pipeline_Flag_Front_Counter_Clockwise)
  {
    glFrontFace((flags & FG_Pipeline_Flag_Front_Counter_Clockwise) ? GL_CCW : GL_CW);
    GL_ERROR("glFrontFace");
  }

  _lastflags = flags;
  return {};
}

/*
void Context::_flushbatchdraw(Font* font)
{
  glActiveTexture(GL_TEXTURE0);
  GL_ERROR("glActiveTexture");
  glBindTexture(GL_TEXTURE_2D, GetFontTexture(font));
  GL_ERROR("glBindTexture");

  // We've already set up our batch indices so we can just use them
  glDrawElements(GL_TRIANGLES, FlushBatch() * 6, GL_UNSIGNED_INT, nullptr);
  GL_ERROR("glDrawElements");
  glBindVertexArray(0);
  GL_ERROR("glBindVertexArray");
}

int mipmapImageGamma(const unsigned char* const orig, int width, int height, int channels, unsigned char* resampled,
                     int block_size_x, int block_size_y)
{
  if((width < 1) || (height < 1) || (channels < 1) || (orig == NULL) || (resampled == NULL) || (block_size_x < 1) ||
     (block_size_y < 1))
  {
    return 0;
  }
  int mip_width  = std::max(width / block_size_x, 1);
  int mip_height = std::max(height / block_size_y, 1);

  for(int j = 0; j < mip_height; ++j)
  {
    for(int i = 0; i < mip_width; ++i)
    {
      for(int c = 0; c < channels; ++c)
      {
        const int index = (j * block_size_y) * width * channels + (i * block_size_x) * channels + c;
        int u_block     = block_size_x;
        int v_block     = block_size_y;
        // do a bit of checking so we don't over-run the boundaries (necessary for non-square textures!)
        if(block_size_x * (i + 1) > width)
        {
          u_block = width - i * block_size_y;
        }
        if(block_size_y * (j + 1) > height)
        {
          v_block = height - j * block_size_y;
        }
        int block_area  = u_block * v_block;
        float sum_value = 0.0f;
        for(int v = 0; v < v_block; ++v)
          for(int u = 0; u < u_block; ++u)
          {
            sum_value += Context::ToLinearRGB(orig[index + v * width * channels + u * channels] / 255.0f); // Linearize
          }
        resampled[j * mip_width * channels + i * channels + c] =
          (unsigned char)roundf(Context::ToSRGB(sum_value / block_area) * 255.0f); // De-linearize
      }
    }
  }
  return 1;
}

unsigned int Context::_createTexture(const unsigned char* const data, int width, int height, int channels,
                                     unsigned int reuse_texture_ID, unsigned int flags, unsigned int opengl_texture_type,
                                     unsigned int opengl_texture_target, unsigned int texture_check_size_enum)
{
  //	variables
  unsigned char* img;
  unsigned int tex_id;
  unsigned int internal_texture_format = 0, original_texture_format = 0;
  int max_supported_size;

  //	create a copy the image data
  img = (unsigned char*)malloc(width * height * channels);
  memcpy(img, data, width * height * channels);

  //	does the user want me to convert from straight to pre-multiplied alpha?
  if(flags & SOIL_FLAG_MULTIPLY_ALPHA)
  {
    // Only calculate mipmap without linearizing if the user says so
    if(flags & SOIL_FLAG_LINEAR_RGB)
    {
      switch(channels)
      {
      case 2:
        for(int i = 0; i < 2 * width * height; i += 2)
        {
          img[i] = (img[i] * img[i + 1] + 128) >> 8;
        }
        break;
      case 4:
        for(int i = 0; i < 4 * width * height; i += 4)
        {
          img[i + 0] = (img[i + 0] * img[i + 3] + 128) >> 8;
          img[i + 1] = (img[i + 1] * img[i + 3] + 128) >> 8;
          img[i + 2] = (img[i + 2] * img[i + 3] + 128) >> 8;
        }
        break;
      }
    }
    else
    {
      switch(channels)
      {
      case 2:
        for(int i = 0; i < 2 * width * height; i += 2)
        {
          // TODO: It is not clear if 2 channel images can be meaningfully linearized.
          img[i] = (img[i] * img[i + 1] + 128) >> 8;
        }
        break;
      case 4:
        for(int i = 0; i < 4 * width * height; i += 4)
        {
          // TODO: This can be SSE optimized, but needs a non-SSE implementation for other architectures
          float alpha = ToSRGB(img[i + 3] / 255.0f);
          img[i + 0]  = (unsigned char)roundf(((img[i + 0] / 255.0f) * alpha) * 255.0f);
          img[i + 1]  = (unsigned char)roundf(((img[i + 1] / 255.0f) * alpha) * 255.0f);
          img[i + 2]  = (unsigned char)roundf(((img[i + 2] / 255.0f) * alpha) * 255.0f);
        }
        break;
      }
    }
  }
  //	how large of a texture can this OpenGL implementation handle?
  //	texture_check_size_enum will be GL_MAX_TEXTURE_SIZE or SOIL_MAX_CUBE_MAP_TEXTURE_SIZE
  glGetIntegerv(texture_check_size_enum, &max_supported_size);
  //	do I need to make it a power of 2?
  if((flags & SOIL_FLAG_MIPMAPS) ||  //	mipmaps
     (width > max_supported_size) || //	it's too big, (make sure it's
     (height > max_supported_size))  //	2^n for later down-sampling)
  {
    int new_width  = 1;
    int new_height = 1;
    while(new_width < width)
    {
      new_width *= 2;
    }
    while(new_height < height)
    {
      new_height *= 2;
    }
    //	still?
    if((new_width != width) || (new_height != height))
    {
      //	yep, resize
      unsigned char* resampled = (unsigned char*)malloc(channels * new_width * new_height);
      up_scale_image(img, width, height, channels, resampled, new_width, new_height);
      //	nuke the old guy, then point it at the new guy
      SOIL_free_image_data(img);
      img    = resampled;
      width  = new_width;
      height = new_height;
    }
  }
  //	now, if it is too large...
  if((width > max_supported_size) || (height > max_supported_size))
  {
    //	I've already made it a power of two, so simply use the MIPmapping
    //  code to reduce its size to the allowable maximum.
    unsigned char* resampled;
    int reduce_block_x = 1, reduce_block_y = 1;
    int new_width, new_height;
    if(width > max_supported_size)
    {
      reduce_block_x = width / max_supported_size;
    }
    if(height > max_supported_size)
    {
      reduce_block_y = height / max_supported_size;
    }
    new_width  = width / reduce_block_x;
    new_height = height / reduce_block_y;
    resampled  = (unsigned char*)malloc(channels * new_width * new_height);
    //	perform the actual reduction
    if(SOIL_FLAG_LINEAR_RGB)
      mipmap_image(img, width, height, channels, resampled, reduce_block_x, reduce_block_y);
    else
      mipmapImageGamma(img, width, height, channels, resampled, reduce_block_x, reduce_block_y);

    //	nuke the old guy, then point it at the new guy
    SOIL_free_image_data(img);
    img    = resampled;
    width  = new_width;
    height = new_height;
  }
  //	create the OpenGL texture ID handle  (note: allowing a forced texture ID lets me reload a texture)
  tex_id = reuse_texture_ID;
  if(tex_id == 0)
  {
    glGenTextures(1, &tex_id);
  }
  GL_ERROR("glGenTextures");

  // Note: sometimes glGenTextures fails (usually no OpenGL context)
  if(tex_id)
  {
    //	and what type am I using as the internal texture format?
    switch(channels)
    {
    case 1: original_texture_format = GL_LUMINANCE; break;
    case 2: original_texture_format = GL_LUMINANCE_ALPHA; break;
    case 3: original_texture_format = GL_RGB; break;
    case 4: original_texture_format = GL_RGBA; break;
    }
    internal_texture_format = original_texture_format;
    if(!(flags & SOIL_FLAG_LINEAR_RGB))
    {
      switch(channels)
      {
      case 3: internal_texture_format = GL_SRGB8;
      case 4: internal_texture_format = GL_SRGB8_ALPHA8;
      }
    }

    //  bind an OpenGL texture ID
    glBindTexture(opengl_texture_type, tex_id);
    GL_ERROR("glBindTexture");

    //	user want OpenGL to do all the work!
    glTexImage2D(opengl_texture_target, 0, internal_texture_format, width, height, 0, original_texture_format,
                 GL_UNSIGNED_BYTE, img);
    GL_ERROR("glTexImage2D");
    //printf( "OpenGL DXT compressor\n" );

    //	are any MIPmaps desired?
    if(flags & SOIL_FLAG_MIPMAPS)
    {
      int MIPlevel             = 1;
      int MIPwidth             = (width + 1) / 2;
      int MIPheight            = (height + 1) / 2;
      unsigned char* resampled = (unsigned char*)malloc(channels * MIPwidth * MIPheight);
      while(((1 << MIPlevel) <= width) || ((1 << MIPlevel) <= height))
      {
        //	do this MIPmap level
        if(SOIL_FLAG_LINEAR_RGB)
          mipmap_image(img, width, height, channels, resampled, (1 << MIPlevel), (1 << MIPlevel));
        else
          mipmapImageGamma(img, width, height, channels, resampled, (1 << MIPlevel), (1 << MIPlevel));

        //  upload the MIPmaps
        glTexImage2D(opengl_texture_target, MIPlevel, internal_texture_format, MIPwidth, MIPheight, 0,
                     original_texture_format, GL_UNSIGNED_BYTE, resampled);
        GL_ERROR("glTexImage2D");

        //	prep for the next level
        ++MIPlevel;
        MIPwidth  = (MIPwidth + 1) / 2;
        MIPheight = (MIPheight + 1) / 2;
      }
      SOIL_free_image_data(resampled);
      //	instruct OpenGL to use the MIPmaps
      glTexParameteri(opengl_texture_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      GL_ERROR("glTexParameteri");
      glTexParameteri(opengl_texture_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      GL_ERROR("glTexParameteri");
    }
    else
    {
      //	instruct OpenGL _NOT_ to use the MIPmaps
      glTexParameteri(opengl_texture_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      GL_ERROR("glTexParameteri");
      glTexParameteri(opengl_texture_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      GL_ERROR("glTexParameteri");
    }
    //	does the user want clamping, or wrapping?
    if(flags & SOIL_FLAG_TEXTURE_REPEATS)
    {
      glTexParameteri(opengl_texture_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
      GL_ERROR("glTexParameteri");
      glTexParameteri(opengl_texture_type, GL_TEXTURE_WRAP_T, GL_REPEAT);
      GL_ERROR("glTexParameteri");
      if(opengl_texture_type == GL_TEXTURE_CUBE_MAP)
      {
        //	SOIL_TEXTURE_WRAP_R is invalid if cubemaps aren't supported
        glTexParameteri(opengl_texture_type, GL_TEXTURE_WRAP_R, GL_REPEAT);
        GL_ERROR("glTexParameteri");
      }
    }
    else
    {
      unsigned int clamp_mode = GL_CLAMP_TO_EDGE;
      glTexParameteri(opengl_texture_type, GL_TEXTURE_WRAP_S, clamp_mode);
      GL_ERROR("glTexParameteri");
      glTexParameteri(opengl_texture_type, GL_TEXTURE_WRAP_T, clamp_mode);
      GL_ERROR("glTexParameteri");
      if(opengl_texture_type == GL_TEXTURE_CUBE_MAP)
      {
        //	SOIL_TEXTURE_WRAP_R is invalid if cubemaps aren't supported
        glTexParameteri(opengl_texture_type, GL_TEXTURE_WRAP_R, clamp_mode);
        GL_ERROR("glTexParameteri");
      }
    }
  }
  SOIL_free_image_data(img);
  return tex_id;
}
*/