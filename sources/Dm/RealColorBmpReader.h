// RealColorBmpReader.h: interface for the CRealColorBmpReader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REALCOLORBMPREADER_H__5269E022_3BFE_11D5_935E_961BFEB55F79__INCLUDED_)
#define AFX_REALCOLORBMPREADER_H__5269E022_3BFE_11D5_935E_961BFEB55F79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AbstractBmpReader.h"

class CRealColorBmpReader : public CAbstractBmpReader  
{
public:
	CRealColorBmpReader(PLWinBmp* pBmp);
	virtual ~CRealColorBmpReader();

public:
	virtual PLPixel32 GetPixel(CPoint point);
	virtual bool PixelIsBlack(const CPoint& point,const PLPixel32& blackLevel);

};

#endif // !defined(AFX_REALCOLORBMPREADER_H__5269E022_3BFE_11D5_935E_961BFEB55F79__INCLUDED_)
