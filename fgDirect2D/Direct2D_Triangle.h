#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
// Buffer Definitions: 
//
// cbuffer constants
// {
//
//   float4 rect;                       // Offset:    0 Size:    16
//   float4 corners;                    // Offset:   16 Size:    16
//   float4 color;                      // Offset:   32 Size:    16
//   float4 outlinecolor;               // Offset:   48 Size:    16
//   float outline;                     // Offset:   64 Size:     4
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim      HLSL Bind  Count
// ------------------------------ ---------- ------- ----------- -------------- ------
// constants                         cbuffer      NA          NA            cb0      1 
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_POSITION              0   xyzw        0      POS   float       
// SCENE_POSITION           0   xyzw        1     NONE   float   xy  
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_TARGET                0   xyzw        0   TARGET   float   xyzw
//
//
// Constant buffer to DX9 shader constant mappings:
//
// Target Reg Buffer  Start Reg # of Regs        Data Conversion
// ---------- ------- --------- --------- ----------------------
// c0         cb0             0         5  ( FLT, FLT, FLT, FLT)
//
//
// Level9 shader bytecode:
//
    ps_2_x
    def c5, 0, 0.5, 1, -1
    def c6, -2, 3, 0, 0
    dcl t0
    mov r0.z, c5.x
    mov r1.y, c5.x
    add r0.xy, -c0, c0.zwzw
    mul r1.x, r0.x, c1.w
    add r2.xy, r0.zyzw, -r1
    mov r2.z, -r2.x
    dp2add r0.z, r2.yzzw, r2.yzzw, c5.x
    rsq r0.z, r0.z
    mul r0.zw, r0.z, r2.xyyz
    add r1.zw, t0.xyxy, -c0.xyxy
    add r2.xy, -r1.zwzw, r1
    add r3.xy, -r1, r0
    add r3.w, -r0.y, r1.w
    mad r0.x, r1.w, c5.y, r1.z
    dp2add r0.y, r0.zwzw, r2, c5.x
    mov r3.z, -r3.x
    dp2add r0.z, r3.yzzw, r3.yzzw, c5.x
    rsq r0.z, r0.z
    mul r0.zw, r0.z, r3.xyyz
    dp2add r0.z, r0.zwzw, r2, c5.x
    max r1.x, r0.y, -r0.z
    max r0.y, r1.x, r3.w
    dsx r0.z, r0.x
    dsy r0.x, r0.x
    abs r0.xz, r0
    add r0.x, r0.x, r0.z
    mov r0.z, c5.z
    add r0.z, r0.z, -c4.x
    add r0.w, -r0.x, r0.z
    rcp r0.x, -r0.x
    add r0.z, -r0.w, r0.z
    add r0.w, -r0.w, r0.y
    add r0.y, r0.y, c5.w
    mul_sat r0.x, r0.x, r0.y
    rcp r0.y, r0.z
    mul_sat r0.y, r0.y, r0.w
    mad r0.z, r0.y, c6.x, c6.y
    mul r0.y, r0.y, r0.y
    mad r0.y, r0.z, -r0.y, c5.z
    mad r0.z, r0.x, c6.x, c6.y
    mul r0.x, r0.x, r0.x
    mad_sat r0.x, r0.z, r0.x, -r0.y
    mul r1.xyz, c3.w, c3
    mov r1.w, c3.w
    mul r1, r0.x, r1
    mul r2.xyz, c2.w, c2
    mov r2.w, c2.w
    mad r0, r2, r0.y, r1
    mov oC0, r0

// approximately 55 instruction slots used
ps_4_0
dcl_constantbuffer CB0[5], immediateIndexed
dcl_input_ps linear v1.xy
dcl_output o0.xyzw
dcl_temps 4
mov r0.z, l(0)
mov r1.y, l(0)
add r0.xy, -cb0[0].xyxx, cb0[0].zwzz
mul r1.x, r0.x, cb0[1].w
add r2.xy, r0.zyzz, -r1.xyxx
mov r2.z, -r2.x
dp2 r0.z, r2.yzyy, r2.yzyy
rsq r0.z, r0.z
mul r0.zw, r0.zzzz, r2.yyyz
add r1.zw, v1.xxxy, -cb0[0].xxxy
add r2.xy, -r1.zwzz, r1.xyxx
add r3.xy, -r1.xyxx, r0.xyxx
add r0.x, -r0.y, r1.w
mad r0.y, r1.w, l(0.500000), r1.z
dp2 r0.z, r0.zwzz, r2.xyxx
mov r3.z, -r3.x
dp2 r0.w, r3.yzyy, r3.yzyy
rsq r0.w, r0.w
mul r1.xy, r0.wwww, r3.yzyy
dp2 r0.w, r1.xyxx, r2.xyxx
max r0.z, -r0.w, r0.z
max r0.x, r0.x, r0.z
deriv_rtx r0.z, r0.y
deriv_rty r0.y, r0.y
add r0.y, |r0.y|, |r0.z|
add r0.z, l(1.000000), -cb0[4].x
add r0.w, -r0.y, r0.z
div r0.y, l(1.000000, 1.000000, 1.000000, 1.000000), -r0.y
add r0.z, -r0.w, r0.z
add r0.w, -r0.w, r0.x
add r0.x, r0.x, l(-1.000000)
mul_sat r0.x, r0.y, r0.x
div r0.y, l(1.000000, 1.000000, 1.000000, 1.000000), r0.z
mul_sat r0.y, r0.y, r0.w
mad r0.z, r0.y, l(-2.000000), l(3.000000)
mul r0.y, r0.y, r0.y
mad r0.y, -r0.z, r0.y, l(1.000000)
mad r0.z, r0.x, l(-2.000000), l(3.000000)
mul r0.x, r0.x, r0.x
mad_sat r0.x, r0.z, r0.x, -r0.y
mul r1.xyz, cb0[3].wwww, cb0[3].xyzx
mov r1.w, cb0[3].w
mul r1.xyzw, r0.xxxx, r1.xyzw
mul r2.xyz, cb0[2].wwww, cb0[2].xyzx
mov r2.w, cb0[2].w
mad o0.xyzw, r2.xyzw, r0.yyyy, r1.xyzw
ret 
// Approximately 47 instruction slots used
#endif

const BYTE Triangle_main[] =
{
     68,  88,  66,  67, 209, 204, 
    239,  28,  88, 243, 236, 114, 
    113, 202, 193,  76, 155, 223, 
     28, 249,   1,   0,   0,   0, 
    200,  11,   0,   0,   6,   0, 
      0,   0,  56,   0,   0,   0, 
    176,   3,   0,   0, 104,   9, 
      0,   0, 228,   9,   0,   0, 
     56,  11,   0,   0, 148,  11, 
      0,   0,  65, 111, 110,  57, 
    112,   3,   0,   0, 112,   3, 
      0,   0,   0,   2, 255, 255, 
     64,   3,   0,   0,  48,   0, 
      0,   0,   1,   0,  36,   0, 
      0,   0,  48,   0,   0,   0, 
     48,   0,   0,   0,  36,   0, 
      0,   0,  48,   0,   0,   0, 
      0,   0,   5,   0,   0,   0, 
      0,   0,   0,   0,   1,   2, 
    255, 255,  81,   0,   0,   5, 
      5,   0,  15, 160,   0,   0, 
      0,   0,   0,   0,   0,  63, 
      0,   0, 128,  63,   0,   0, 
    128, 191,  81,   0,   0,   5, 
      6,   0,  15, 160,   0,   0, 
      0, 192,   0,   0,  64,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  31,   0,   0,   2, 
      0,   0,   0, 128,   0,   0, 
     15, 176,   1,   0,   0,   2, 
      0,   0,   4, 128,   5,   0, 
      0, 160,   1,   0,   0,   2, 
      1,   0,   2, 128,   5,   0, 
      0, 160,   2,   0,   0,   3, 
      0,   0,   3, 128,   0,   0, 
    228, 161,   0,   0, 238, 160, 
      5,   0,   0,   3,   1,   0, 
      1, 128,   0,   0,   0, 128, 
      1,   0, 255, 160,   2,   0, 
      0,   3,   2,   0,   3, 128, 
      0,   0, 230, 128,   1,   0, 
    228, 129,   1,   0,   0,   2, 
      2,   0,   4, 128,   2,   0, 
      0, 129,  90,   0,   0,   4, 
      0,   0,   4, 128,   2,   0, 
    233, 128,   2,   0, 233, 128, 
      5,   0,   0, 160,   7,   0, 
      0,   2,   0,   0,   4, 128, 
      0,   0, 170, 128,   5,   0, 
      0,   3,   0,   0,  12, 128, 
      0,   0, 170, 128,   2,   0, 
    148, 128,   2,   0,   0,   3, 
      1,   0,  12, 128,   0,   0, 
     68, 176,   0,   0,  68, 161, 
      2,   0,   0,   3,   2,   0, 
      3, 128,   1,   0, 238, 129, 
      1,   0, 228, 128,   2,   0, 
      0,   3,   3,   0,   3, 128, 
      1,   0, 228, 129,   0,   0, 
    228, 128,   2,   0,   0,   3, 
      3,   0,   8, 128,   0,   0, 
     85, 129,   1,   0, 255, 128, 
      4,   0,   0,   4,   0,   0, 
      1, 128,   1,   0, 255, 128, 
      5,   0,  85, 160,   1,   0, 
    170, 128,  90,   0,   0,   4, 
      0,   0,   2, 128,   0,   0, 
    238, 128,   2,   0, 228, 128, 
      5,   0,   0, 160,   1,   0, 
      0,   2,   3,   0,   4, 128, 
      3,   0,   0, 129,  90,   0, 
      0,   4,   0,   0,   4, 128, 
      3,   0, 233, 128,   3,   0, 
    233, 128,   5,   0,   0, 160, 
      7,   0,   0,   2,   0,   0, 
      4, 128,   0,   0, 170, 128, 
      5,   0,   0,   3,   0,   0, 
     12, 128,   0,   0, 170, 128, 
      3,   0, 148, 128,  90,   0, 
      0,   4,   0,   0,   4, 128, 
      0,   0, 238, 128,   2,   0, 
    228, 128,   5,   0,   0, 160, 
     11,   0,   0,   3,   1,   0, 
      1, 128,   0,   0,  85, 128, 
      0,   0, 170, 129,  11,   0, 
      0,   3,   0,   0,   2, 128, 
      1,   0,   0, 128,   3,   0, 
    255, 128,  91,   0,   0,   2, 
      0,   0,   4, 128,   0,   0, 
      0, 128,  92,   0,   0,   2, 
      0,   0,   1, 128,   0,   0, 
      0, 128,  35,   0,   0,   2, 
      0,   0,   5, 128,   0,   0, 
    228, 128,   2,   0,   0,   3, 
      0,   0,   1, 128,   0,   0, 
      0, 128,   0,   0, 170, 128, 
      1,   0,   0,   2,   0,   0, 
      4, 128,   5,   0, 170, 160, 
      2,   0,   0,   3,   0,   0, 
      4, 128,   0,   0, 170, 128, 
      4,   0,   0, 161,   2,   0, 
      0,   3,   0,   0,   8, 128, 
      0,   0,   0, 129,   0,   0, 
    170, 128,   6,   0,   0,   2, 
      0,   0,   1, 128,   0,   0, 
      0, 129,   2,   0,   0,   3, 
      0,   0,   4, 128,   0,   0, 
    255, 129,   0,   0, 170, 128, 
      2,   0,   0,   3,   0,   0, 
      8, 128,   0,   0, 255, 129, 
      0,   0,  85, 128,   2,   0, 
      0,   3,   0,   0,   2, 128, 
      0,   0,  85, 128,   5,   0, 
    255, 160,   5,   0,   0,   3, 
      0,   0,  17, 128,   0,   0, 
      0, 128,   0,   0,  85, 128, 
      6,   0,   0,   2,   0,   0, 
      2, 128,   0,   0, 170, 128, 
      5,   0,   0,   3,   0,   0, 
     18, 128,   0,   0,  85, 128, 
      0,   0, 255, 128,   4,   0, 
      0,   4,   0,   0,   4, 128, 
      0,   0,  85, 128,   6,   0, 
      0, 160,   6,   0,  85, 160, 
      5,   0,   0,   3,   0,   0, 
      2, 128,   0,   0,  85, 128, 
      0,   0,  85, 128,   4,   0, 
      0,   4,   0,   0,   2, 128, 
      0,   0, 170, 128,   0,   0, 
     85, 129,   5,   0, 170, 160, 
      4,   0,   0,   4,   0,   0, 
      4, 128,   0,   0,   0, 128, 
      6,   0,   0, 160,   6,   0, 
     85, 160,   5,   0,   0,   3, 
      0,   0,   1, 128,   0,   0, 
      0, 128,   0,   0,   0, 128, 
      4,   0,   0,   4,   0,   0, 
     17, 128,   0,   0, 170, 128, 
      0,   0,   0, 128,   0,   0, 
     85, 129,   5,   0,   0,   3, 
      1,   0,   7, 128,   3,   0, 
    255, 160,   3,   0, 228, 160, 
      1,   0,   0,   2,   1,   0, 
      8, 128,   3,   0, 255, 160, 
      5,   0,   0,   3,   1,   0, 
     15, 128,   0,   0,   0, 128, 
      1,   0, 228, 128,   5,   0, 
      0,   3,   2,   0,   7, 128, 
      2,   0, 255, 160,   2,   0, 
    228, 160,   1,   0,   0,   2, 
      2,   0,   8, 128,   2,   0, 
    255, 160,   4,   0,   0,   4, 
      0,   0,  15, 128,   2,   0, 
    228, 128,   0,   0,  85, 128, 
      1,   0, 228, 128,   1,   0, 
      0,   2,   0,   8,  15, 128, 
      0,   0, 228, 128, 255, 255, 
      0,   0,  83,  72,  68,  82, 
    176,   5,   0,   0,  64,   0, 
      0,   0, 108,   1,   0,   0, 
     89,   0,   0,   4,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      5,   0,   0,   0,  98,  16, 
      0,   3,  50,  16,  16,   0, 
      1,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      0,   0,   0,   0, 104,   0, 
      0,   2,   4,   0,   0,   0, 
     54,   0,   0,   5,  66,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,   0,  54,   0,   0,   5, 
     34,   0,  16,   0,   1,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,  10,  50,   0,  16,   0, 
      0,   0,   0,   0,  70, 128, 
     32, 128,  65,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 230, 138,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  56,   0,   0,   8, 
     18,   0,  16,   0,   1,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,  58, 128, 
     32,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   8,  50,   0,  16,   0, 
      2,   0,   0,   0, 102,  10, 
     16,   0,   0,   0,   0,   0, 
     70,   0,  16, 128,  65,   0, 
      0,   0,   1,   0,   0,   0, 
     54,   0,   0,   6,  66,   0, 
     16,   0,   2,   0,   0,   0, 
     10,   0,  16, 128,  65,   0, 
      0,   0,   2,   0,   0,   0, 
     15,   0,   0,   7,  66,   0, 
     16,   0,   0,   0,   0,   0, 
    150,   5,  16,   0,   2,   0, 
      0,   0, 150,   5,  16,   0, 
      2,   0,   0,   0,  68,   0, 
      0,   5,  66,   0,  16,   0, 
      0,   0,   0,   0,  42,   0, 
     16,   0,   0,   0,   0,   0, 
     56,   0,   0,   7, 194,   0, 
     16,   0,   0,   0,   0,   0, 
    166,  10,  16,   0,   0,   0, 
      0,   0,  86,   9,  16,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   9, 194,   0,  16,   0, 
      1,   0,   0,   0,   6,  20, 
     16,   0,   1,   0,   0,   0, 
      6, 132,  32, 128,  65,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   8,  50,   0,  16,   0, 
      2,   0,   0,   0, 230,  10, 
     16, 128,  65,   0,   0,   0, 
      1,   0,   0,   0,  70,   0, 
     16,   0,   1,   0,   0,   0, 
      0,   0,   0,   8,  50,   0, 
     16,   0,   3,   0,   0,   0, 
     70,   0,  16, 128,  65,   0, 
      0,   0,   1,   0,   0,   0, 
     70,   0,  16,   0,   0,   0, 
      0,   0,   0,   0,   0,   8, 
     18,   0,  16,   0,   0,   0, 
      0,   0,  26,   0,  16, 128, 
     65,   0,   0,   0,   0,   0, 
      0,   0,  58,   0,  16,   0, 
      1,   0,   0,   0,  50,   0, 
      0,   9,  34,   0,  16,   0, 
      0,   0,   0,   0,  58,   0, 
     16,   0,   1,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,  63,  42,   0,  16,   0, 
      1,   0,   0,   0,  15,   0, 
      0,   7,  66,   0,  16,   0, 
      0,   0,   0,   0, 230,  10, 
     16,   0,   0,   0,   0,   0, 
     70,   0,  16,   0,   2,   0, 
      0,   0,  54,   0,   0,   6, 
     66,   0,  16,   0,   3,   0, 
      0,   0,  10,   0,  16, 128, 
     65,   0,   0,   0,   3,   0, 
      0,   0,  15,   0,   0,   7, 
    130,   0,  16,   0,   0,   0, 
      0,   0, 150,   5,  16,   0, 
      3,   0,   0,   0, 150,   5, 
     16,   0,   3,   0,   0,   0, 
     68,   0,   0,   5, 130,   0, 
     16,   0,   0,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,  56,   0,   0,   7, 
     50,   0,  16,   0,   1,   0, 
      0,   0, 246,  15,  16,   0, 
      0,   0,   0,   0, 150,   5, 
     16,   0,   3,   0,   0,   0, 
     15,   0,   0,   7, 130,   0, 
     16,   0,   0,   0,   0,   0, 
     70,   0,  16,   0,   1,   0, 
      0,   0,  70,   0,  16,   0, 
      2,   0,   0,   0,  52,   0, 
      0,   8,  66,   0,  16,   0, 
      0,   0,   0,   0,  58,   0, 
     16, 128,  65,   0,   0,   0, 
      0,   0,   0,   0,  42,   0, 
     16,   0,   0,   0,   0,   0, 
     52,   0,   0,   7,  18,   0, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,  42,   0,  16,   0, 
      0,   0,   0,   0,  11,   0, 
      0,   5,  66,   0,  16,   0, 
      0,   0,   0,   0,  26,   0, 
     16,   0,   0,   0,   0,   0, 
     12,   0,   0,   5,  34,   0, 
     16,   0,   0,   0,   0,   0, 
     26,   0,  16,   0,   0,   0, 
      0,   0,   0,   0,   0,   9, 
     34,   0,  16,   0,   0,   0, 
      0,   0,  26,   0,  16, 128, 
    129,   0,   0,   0,   0,   0, 
      0,   0,  42,   0,  16, 128, 
    129,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   9, 
     66,   0,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0, 128,  63,  10, 128, 
     32, 128,  65,   0,   0,   0, 
      0,   0,   0,   0,   4,   0, 
      0,   0,   0,   0,   0,   8, 
    130,   0,  16,   0,   0,   0, 
      0,   0,  26,   0,  16, 128, 
     65,   0,   0,   0,   0,   0, 
      0,   0,  42,   0,  16,   0, 
      0,   0,   0,   0,  14,   0, 
      0,  11,  34,   0,  16,   0, 
      0,   0,   0,   0,   2,  64, 
      0,   0,   0,   0, 128,  63, 
      0,   0, 128,  63,   0,   0, 
    128,  63,   0,   0, 128,  63, 
     26,   0,  16, 128,  65,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   8,  66,   0, 
     16,   0,   0,   0,   0,   0, 
     58,   0,  16, 128,  65,   0, 
      0,   0,   0,   0,   0,   0, 
     42,   0,  16,   0,   0,   0, 
      0,   0,   0,   0,   0,   8, 
    130,   0,  16,   0,   0,   0, 
      0,   0,  58,   0,  16, 128, 
     65,   0,   0,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   7,  18,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
    128, 191,  56,  32,   0,   7, 
     18,   0,  16,   0,   0,   0, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
     14,   0,   0,  10,  34,   0, 
     16,   0,   0,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
    128,  63,   0,   0, 128,  63, 
      0,   0, 128,  63,   0,   0, 
    128,  63,  42,   0,  16,   0, 
      0,   0,   0,   0,  56,  32, 
      0,   7,  34,   0,  16,   0, 
      0,   0,   0,   0,  26,   0, 
     16,   0,   0,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,  50,   0,   0,   9, 
     66,   0,  16,   0,   0,   0, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0, 192, 
      1,  64,   0,   0,   0,   0, 
     64,  64,  56,   0,   0,   7, 
     34,   0,  16,   0,   0,   0, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,  26,   0, 
     16,   0,   0,   0,   0,   0, 
     50,   0,   0,  10,  34,   0, 
     16,   0,   0,   0,   0,   0, 
     42,   0,  16, 128,  65,   0, 
      0,   0,   0,   0,   0,   0, 
     26,   0,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0, 128,  63,  50,   0, 
      0,   9,  66,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0, 192,   1,  64,   0,   0, 
      0,   0,  64,  64,  56,   0, 
      0,   7,  18,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,  50,  32,   0,  10, 
     18,   0,  16,   0,   0,   0, 
      0,   0,  42,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
     26,   0,  16, 128,  65,   0, 
      0,   0,   0,   0,   0,   0, 
     56,   0,   0,   9, 114,   0, 
     16,   0,   1,   0,   0,   0, 
    246, 143,  32,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
     70, 130,  32,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
     54,   0,   0,   6, 130,   0, 
     16,   0,   1,   0,   0,   0, 
     58, 128,  32,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
     56,   0,   0,   7, 242,   0, 
     16,   0,   1,   0,   0,   0, 
      6,   0,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  56,   0, 
      0,   9, 114,   0,  16,   0, 
      2,   0,   0,   0, 246, 143, 
     32,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,  70, 130, 
     32,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,  54,   0, 
      0,   6, 130,   0,  16,   0, 
      2,   0,   0,   0,  58, 128, 
     32,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,  50,   0, 
      0,   9, 242,  32,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
     86,   5,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  62,   0, 
      0,   1,  83,  84,  65,  84, 
    116,   0,   0,   0,  47,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,  42,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     82,  68,  69,  70,  76,   1, 
      0,   0,   1,   0,   0,   0, 
     72,   0,   0,   0,   1,   0, 
      0,   0,  28,   0,   0,   0, 
      0,   4, 255, 255,   0,   1, 
      0,   0,  36,   1,   0,   0, 
     60,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,  99, 111, 110, 115, 
    116,  97, 110, 116, 115,   0, 
    171, 171,  60,   0,   0,   0, 
      5,   0,   0,   0,  96,   0, 
      0,   0,  80,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 216,   0,   0,   0, 
      0,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    224,   0,   0,   0,   0,   0, 
      0,   0, 240,   0,   0,   0, 
     16,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    224,   0,   0,   0,   0,   0, 
      0,   0, 248,   0,   0,   0, 
     32,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    224,   0,   0,   0,   0,   0, 
      0,   0, 254,   0,   0,   0, 
     48,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    224,   0,   0,   0,   0,   0, 
      0,   0,  11,   1,   0,   0, 
     64,   0,   0,   0,   4,   0, 
      0,   0,   2,   0,   0,   0, 
     20,   1,   0,   0,   0,   0, 
      0,   0, 114, 101,  99, 116, 
      0, 171, 171, 171,   1,   0, 
      3,   0,   1,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  99, 111, 114, 110, 
    101, 114, 115,   0,  99, 111, 
    108, 111, 114,   0, 111, 117, 
    116, 108, 105, 110, 101,  99, 
    111, 108, 111, 114,   0, 111, 
    117, 116, 108, 105, 110, 101, 
      0, 171,   0,   0,   3,   0, 
      1,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     77, 105,  99, 114, 111, 115, 
    111, 102, 116,  32,  40,  82, 
     41,  32,  72,  76,  83,  76, 
     32,  83, 104,  97, 100, 101, 
    114,  32,  67, 111, 109, 112, 
    105, 108, 101, 114,  32,  49, 
     48,  46,  49,   0,  73,  83, 
     71,  78,  84,   0,   0,   0, 
      2,   0,   0,   0,   8,   0, 
      0,   0,  56,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,  15,   0, 
      0,   0,  68,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      1,   0,   0,   0,  15,   3, 
      0,   0,  83,  86,  95,  80, 
     79,  83,  73,  84,  73,  79, 
     78,   0,  83,  67,  69,  78, 
     69,  95,  80,  79,  83,  73, 
     84,  73,  79,  78,   0, 171, 
     79,  83,  71,  78,  44,   0, 
      0,   0,   1,   0,   0,   0, 
      8,   0,   0,   0,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
     15,   0,   0,   0,  83,  86, 
     95,  84,  65,  82,  71,  69, 
     84,   0, 171, 171
};
