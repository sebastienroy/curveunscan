// MonochromaticBmpReader.h: interface for the CMonochromaticBmpReader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MONOCHROMATICBMPREADER_H__5269E024_3BFE_11D5_935E_961BFEB55F79__INCLUDED_)
#define AFX_MONOCHROMATICBMPREADER_H__5269E024_3BFE_11D5_935E_961BFEB55F79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AbstractBmpReader.h"

class CMonochromaticBmpReader : public CAbstractBmpReader  
{
public:
	CMonochromaticBmpReader(PLWinBmp* pBmp);
	virtual ~CMonochromaticBmpReader();

public:
	virtual PLPixel32 GetPixel(CPoint point);
	virtual bool PixelIsBlack(const CPoint &point,const PLPixel32& blackLevel);

};

#endif // !defined(AFX_MONOCHROMATICBMPREADER_H__5269E024_3BFE_11D5_935E_961BFEB55F79__INCLUDED_)
