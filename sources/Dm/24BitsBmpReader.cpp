// 24BitsBmpReader.cpp: implementation of the C24BitsBmpReader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "CurveUnscan.h"
#include "24BitsBmpReader.h"

#include "plpixel32.h"
#include "plpixel24.h"
#include "plwinbmp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C24BitsBmpReader::C24BitsBmpReader(PLWinBmp* pBmp)
:CAbstractBmpReader(pBmp)
{

}

C24BitsBmpReader::~C24BitsBmpReader()
{

}

bool C24BitsBmpReader::PixelIsBlack(const CPoint &point, const PLPixel32 &blackLevel)
{
	PLPixel24** lineArray=m_pBmp->GetLineArray24();
	PLPixel24* line=lineArray[point.y];
	PLPixel24 pixel=line[point.x];
//	PLPixel32 pixel=m_pBmp->GetPixel(point.x,point.y);
//	PLPixel32 pixel;

	BYTE red=pixel.GetR();
	BYTE green=pixel.GetG();
	BYTE blue=pixel.GetB();

	PLPixel32& black=const_cast<PLPixel32&>(blackLevel);

	if( (red>black.GetR())||(green>black.GetG())||(blue>black.GetB()) )
		{
		return false;
		}
	else
		{
		return true;
		}
}

PLPixel32 C24BitsBmpReader::GetPixel(CPoint point)
{
	PLPixel24** lineArray=m_pBmp->GetLineArray24();
	PLPixel24* line=lineArray[point.y];
	PLPixel24 pixel=line[point.x];
	return PLPixel32(pixel.GetR(),pixel.GetG(),pixel.GetB());
}
