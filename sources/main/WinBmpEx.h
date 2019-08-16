// WinBmpEx.h: interface for the CWinBmpEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINBMPEX_H__C2CEE603_457F_11D5_935E_FD7B9C4DC578__INCLUDED_)
#define AFX_WINBMPEX_H__C2CEE603_457F_11D5_935E_FD7B9C4DC578__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "pldibsect.h"

class CWinBmpEx : public PLDIBSection  
{
public:
	virtual void DrawRect(HDC hDC,const CRect& rect, DWORD rop = SRCCOPY);
	CWinBmpEx();
	CWinBmpEx(const PLBmp &Orig);
	CWinBmpEx(const PLDIBSection &Orig);
	 
	virtual ~CWinBmpEx();

protected:
	void internalCreate(BITMAPINFOHEADER* pBMI);
};


inline CWinBmpEx::CWinBmpEx(const PLDIBSection &Orig)
:PLDIBSection(Orig)
	{}

inline CWinBmpEx::CWinBmpEx(const PLBmp &Orig)
:PLDIBSection(Orig)
	{}

#endif // !defined(AFX_WINBMPEX_H__C2CEE603_457F_11D5_935E_FD7B9C4DC578__INCLUDED_)
