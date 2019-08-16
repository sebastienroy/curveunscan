// Color256BmpReader.cpp: implementation of the CColor256BmpReader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "CurveUnscan.h"
#include "Color256BmpReader.h"

#include "plwinbmp.h"
#include "plpixel32.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CColor256BmpReader::CColor256BmpReader(PLWinBmp* pBmp)
:CAbstractBmpReader(pBmp)
{
	m_pPalette=m_pBmp->GetPalette();
	m_LineArray=m_pBmp->GetLineArray();
}

CColor256BmpReader::~CColor256BmpReader()
{

}

bool CColor256BmpReader::PixelIsBlack(const CPoint &point,const PLPixel32& blackLevel)
{
	BYTE* line=m_LineArray[point.y];
	BYTE nColor=line[point.x];

	PLPixel32 pixel=m_pPalette[nColor];
	
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

PLPixel32 CColor256BmpReader::GetPixel(CPoint point)
{
	BYTE* line=m_LineArray[point.y];
	BYTE nColor=line[point.x];

	return m_pPalette[nColor];
}
