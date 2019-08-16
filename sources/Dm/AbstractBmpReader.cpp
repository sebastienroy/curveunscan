// AbstractBmpReader.cpp: implementation of the CAbstractBmpReader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "CurveUnscan.h"
#include "AbstractBmpReader.h"

#include "plwinbmp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAbstractBmpReader::CAbstractBmpReader(PLWinBmp* pBmp)
:m_pBmp(pBmp)
{
	m_pBits=m_pBmp->GetBits();
	m_nBytesPerLine=m_pBmp->GetBytesPerLine();
}

CAbstractBmpReader::~CAbstractBmpReader()
{

}

bool CAbstractBmpReader::PixelIsBlack(const CPoint& point,const PLPixel32& blackLevel)
{
	return false;
}

PLPixel32 CAbstractBmpReader::GetPixel(CPoint point)
{
	return PLPixel32(255,255,255,0);
}
