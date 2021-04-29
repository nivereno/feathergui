// Copyright (c)2021 Fundament Software
// For conditions of distribution and use, see copyright notice in "fgDirect2D.h"

#ifndef D2D__IMAGEEFFECTBASE_H
#define D2D__IMAGEEFFECTBASE_H

#include <d2d1effectauthor.h>

namespace D2D {
  class ImageEffectBase : public ID2D1EffectImpl, public ID2D1DrawTransform
  {
  public:
    IFACEMETHODIMP PrepareForRender(D2D1_CHANGE_TYPE changeType);
    IFACEMETHODIMP SetGraph(_In_ ID2D1TransformGraph* pGraph);
    IFACEMETHODIMP_(ULONG) AddRef();
    IFACEMETHODIMP_(ULONG) Release();
    IFACEMETHODIMP QueryInterface(_In_ REFIID riid, _Outptr_ void** ppOutput);

    HRESULT SetColor(UINT color);
    UINT GetColor() const;

    IFACEMETHODIMP MapOutputRectToInputRects(_In_ const D2D1_RECT_L* pOutputRect,
                                             _Out_writes_(inputRectCount) D2D1_RECT_L* pInputRects,
                                             UINT32 inputRectCount) const;
    IFACEMETHODIMP MapInputRectsToOutputRect(_In_reads_(inputRectCount) CONST D2D1_RECT_L* pInputRects,
                                             _In_reads_(inputRectCount) CONST D2D1_RECT_L* pInputOpaqueSubRects,
                                             UINT32 inputRectCount, _Out_ D2D1_RECT_L* pOutputRect,
                                             _Out_ D2D1_RECT_L* pOutputOpaqueSubRect);
    IFACEMETHODIMP MapInvalidRect(UINT32 inputIndex, D2D1_RECT_L invalidInputRect,
                                  _Out_ D2D1_RECT_L* pInvalidOutputRect) const;
    IFACEMETHODIMP_(UINT32) GetInputCount() const;

  protected:
    ImageEffectBase();
    ~ImageEffectBase();
    HRESULT UpdateConstants();

    D2D1_RECT_L _inputRect;
    ID2D1DrawInfo* _drawInfo;
    LONG _ref;
    UINT _color;

    struct
    {
      D2D1_COLOR_F color;
    } _constants;
  };
}

#endif
