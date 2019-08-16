// RealColorBmpReader.cpp: implementation of the CRealColorBmpReader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "CurveUnscan.h"
#include "RealColorBmpReader.h"

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

CRealColorBmpReader::CRealColorBmpReader(PLWinBmp* pBmp)
:CAbstractBmpReader(pBmp)
{

}

CRealColorBmpReader::~CRealColorBmpReader()
{

}

bool CRealColorBmpReader::PixelIsBlack(const CPoint &point,const PLPixel32& blackLevel)
{
	PLPixel32 pixel=m_pBmp->GetPixel(point.x,point.y);

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

PLPixel32 CRealColorBmpReader::GetPixel(CPoint point)
{
	return m_pBmp->GetPixel(point.x,point.y);
}
