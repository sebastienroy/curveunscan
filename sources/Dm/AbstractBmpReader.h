// AbstractBmpReader.h: interface for the CAbstractBmpReader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABSTRACTBMPREADER_H__5269E021_3BFE_11D5_935E_961BFEB55F79__INCLUDED_)
#define AFX_ABSTRACTBMPREADER_H__5269E021_3BFE_11D5_935E_961BFEB55F79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class PLPixel32;
class PLWinBmp;

class CAbstractBmpReader  
{
public:
	CAbstractBmpReader(PLWinBmp* pBmp);
	virtual ~CAbstractBmpReader();

public:
	virtual PLPixel32 GetPixel(CPoint point)=0;
	virtual bool PixelIsBlack(const CPoint& point,const PLPixel32& blackLevel)=0;

protected:
	int m_nBytesPerLine;
	BYTE* m_pBits;
	PLWinBmp* m_pBmp;
};

#endif // !defined(AFX_ABSTRACTBMPREADER_H__5269E021_3BFE_11D5_935E_961BFEB55F79__INCLUDED_)
