/*
   Game Name:  Stranded
      Author:  Allen Sherrod
     Chapter:  Chapter 16
*/


#ifndef _UGP_DEFINES_H_
#define _UGP_DEFINES_H_

#include<windows.h>

#define PERCENT_OF(a, b) (int)(a * b)

// Keyboard keys size.
#define KEYS_SIZE          256

// Flags.
#define UGP_INFINITE       -1
#define UGP_INVALID        -1
#define UGP_OK             1
#define UGP_FAIL           0

// Vertex formats.
#define GUI_FVF            2
#define MV_FVF             3

// Types of controls we support.
#define UGP_GUI_STATICTEXT 1
#define UGP_GUI_BUTTON     2
#define UGP_GUI_BACKDROP   3

// Mouse button states.
#define UGP_BUTTON_UP      1
#define UGP_BUTTON_OVER    2
#define UGP_BUTTON_DOWN    3
#define UGP_LEFT_BUTTON    0
#define UGP_RIGHT_BUTTON   1

// Light type defines.
#define LIGHT_POINT        1
#define LIGHT_DIRECTIONAL  2
#define LIGHT_SPOT         3

// Window handle (need new way if porting to Mac and OpenGL).
#define WinHWND HWND

// Typedefs and enumerations.
typedef long VertexType;

// Primitive types.
enum PrimType
{
   NULL_TYPE,
   POINT_LIST,
   TRIANGLE_LIST,
   TRIANGLE_STRIP,
   TRIANGLE_FAN,
   LINE_LIST,
   LINE_STRIP
};

// Rendering states.
enum RenderState
{
   CULL_NONE,
   CULL_CW,
   CULL_CCW,
   DEPTH_NONE,
   DEPTH_READONLY,
   DEPTH_READWRITE,
   SHADE_POINTS,
   SHADE_SOLIDTRI,
   SHADE_WIRETRI,
   SHADE_WIREPOLY,
   TRANSPARENCY_NONE,
   TRANSPARENCY_ENABLE
};

// Transparency states.
enum TransState
{
   TRANS_ZERO = 1,
   TRANS_ONE,
   TRANS_SRCCOLOR,
   TRANS_INVSRCCOLOR,
   TRANS_SRCALPHA,
   TRANS_INVSRCALPHA,
   TRANS_DSTALPHA,
   TRANS_INVDSTALPHA,
   TRANS_DSTCOLOR,
   TRANS_INVDSTCOLOR,
   TRANS_SRCALPHASAT,
   TRANS_BOTHSRCALPHA,
   TRANS_INVBOTHSRCALPHA,
   TRANS_BLENDFACTOR,
   TRANS_INVBLENDFACTOR
};

// Texture states.
enum TextureState
{
   MIN_FILTER,
   MAG_FILTER,
   MIP_FILTER
};

// Texture filtering.
enum FilterType
{
   POINT_TYPE,
   LINEAR_TYPE,
   ANISOTROPIC_TYPE
};

// Multi-sampling.
enum UGP_MS_TYPE
{
   UGP_MS_NONE,
   UGP_MS_SAMPLES_2,
   UGP_MS_SAMPLES_4,
   UGP_MS_SAMPLES_8,
   UGP_MS_SAMPLES_16
};

// Fog.
enum UGP_FOG_TYPE
{
   UGP_VERTEX_FOG,
   UGP_PIXEL_FOG
};

// Color defines.
#define UGPCOLOR_ARGB(a,r,g,b) ((unsigned long)((((a)&0xff)<<24)|\
                               (((r)&0xff)<<16)|(((g)&0xff)<<8)|\
                               ((b)&0xff)))

#endif