// MonochromaticBmpReader.cpp: implementation of the CMonochromaticBmpReader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "CurveUnscan.h"
#include "MonochromaticBmpReader.h"

#include "plwinbmp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMonochromaticBmpReader::CMonochromaticBmpReader(PLWinBmp* pBmp)
:CAbstractBmpReader(pBmp)
{

}

CMonochromaticBmpReader::~CMonochromaticBmpReader()
{

}

bool CMonochromaticBmpReader::PixelIsBlack(const CPoint &point,const PLPixel32& blackLevel)
{
	BYTE masque=1<<(7-point.x%8);
	long pbyte=point.x/8;
//	long pligne=(m_pBmp->GetHeight()-1-point.y)*m_nBytesPerLine;

	PLBYTE** lineArray=m_pBmp->GetLineArray();
	BYTE* pLigne=lineArray[point.y];
	BYTE current=pLigne[(point.x)/8];
	int nColorIndex=(masque&current)?1:0;

	PLPixel32* pClrTab=m_pBmp->GetPalette();
	PLPixel32 &pixel=pClrTab[nColorIndex];
	bool bIsBlack=( (0==pixel.GetR())
					&&(0==pixel.GetG())
					&&(0==pixel.GetB()) );

	return bIsBlack;
//	BYTE current=m_pBits[pligne+pbyte];

//	return (masque&current);
}

PLPixel32 CMonochromaticBmpReader::GetPixel(CPoint point)
{
	PLPixel32 pixel;
	bool isBlack=PixelIsBlack(point,pixel);
	if(isBlack)
		{
		return PLPixel32(0,0,0,0);
		}
	else
		{
		return PLPixel32(255,255,255,0);
		}
}
