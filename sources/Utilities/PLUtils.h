// PLUtils.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PLUTILS_H_)
#define _PLUTILS_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "plpixel32.h"

// convert a pixel to an int 0x00RRGGBB
int PLPixel32ToInt(const PLPixel32 &plPixel);

// convert an int 0x00RRGGBB to a pixel
PLPixel32 IntToPLPixel32(int nValue);

#endif // !dfined(_PLUTILS_H_)