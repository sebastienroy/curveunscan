// 24BitsBmpReader.h: interface for the C24BitsBmpReader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_24BITSBMPREADER_H__CBA854F9_4BA6_413C_B7C6_77A6FC66CC5F__INCLUDED_)
#define AFX_24BITSBMPREADER_H__CBA854F9_4BA6_413C_B7C6_77A6FC66CC5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AbstractBmpReader.h"

class C24BitsBmpReader : public CAbstractBmpReader  
{
public:
	PLPixel32 GetPixel(CPoint point);
	bool PixelIsBlack(const CPoint &point,const PLPixel32& blackLevel);
	C24BitsBmpReader(PLWinBmp* pBmp);
	virtual ~C24BitsBmpReader();

};

#endif // !defined(AFX_24BITSBMPREADER_H__CBA854F9_4BA6_413C_B7C6_77A6FC66CC5F__INCLUDED_)
