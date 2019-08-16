// PLUtils.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"


#include "PLUtils.h"

// convert a pixel to an int 0x00RRGGBB
int PLPixel32ToInt(const PLPixel32 &plPixel)
{
	DWORD nValue=plPixel.GetR();
	nValue<<=8;
	nValue+=plPixel.GetG();
	nValue<<=8;
	nValue+=plPixel.GetB();
	return (int)nValue;
}

// convert an int 0x00RRGGBB to a pixel
PLPixel32 IntToPLPixel32(int nValue)
{
#pragma warning (disable : 4244)	// possible loss of data

	PLPixel32 pixel;
	DWORD nMask=0x000000FF;
	pixel.SetB(nValue&nMask);
	nValue>>=8;
	pixel.SetG(nValue&nMask);
	nValue>>=8;
	pixel.SetR(nValue&nMask);
	return pixel;
}
