// Color256BmpReader.h: interface for the CColor256BmpReader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLOR256BMPREADER_H__5269E025_3BFE_11D5_935E_961BFEB55F79__INCLUDED_)
#define AFX_COLOR256BMPREADER_H__5269E025_3BFE_11D5_935E_961BFEB55F79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AbstractBmpReader.h"

class CPixel32;

class CColor256BmpReader : public CAbstractBmpReader  
{
public:
	CColor256BmpReader(PLWinBmp* pBmp);
	virtual ~CColor256BmpReader();

public:
	virtual PLPixel32 GetPixel(CPoint point);
	virtual bool PixelIsBlack(const CPoint& point,const PLPixel32& blackLevel);

protected:
	BYTE** m_LineArray;
	PLPixel32* m_pPalette;
};

#endif // !defined(AFX_COLOR256BMPREADER_H__5269E025_3BFE_11D5_935E_961BFEB55F79__INCLUDED_)
