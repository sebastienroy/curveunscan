// DensitoDlgDrawState.h: interface for the CDensitoDlgDrawState class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DENSITODLGDRAWSTATE_H__B948C7F9_8805_4DAD_B920_6B2E3A215233__INCLUDED_)
#define AFX_DENSITODLGDRAWSTATE_H__B948C7F9_8805_4DAD_B920_6B2E3A215233__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DensitoDlgAbstractState.h"

class CDensitoDlgDrawState : public CDensitoDlgAbstractState  
{
public:
	CDensitoDlgDrawState(CDensitometryDialog* pDlg);
	virtual ~CDensitoDlgDrawState();

public:
	virtual LONG StartPick(UINT wParam, LONG lParam);
	virtual LONG MovePick(UINT wParam, LONG lParam);
	virtual LONG EndPick(UINT wParam, LONG lParam);
	virtual LONG ScrollOff(UINT wParam, LONG lParam);

	virtual void CheckPickColorButton(bool bIsTop);
	virtual void CheckDrawButton();

protected:
	void InvertLine(CDC *pDC, CPoint from, CPoint to);
	void SetStraightLine(const CPoint *ptA, CPoint *ptB);

protected:
	CPoint m_ptTo;
	CPoint m_ptFrom;
};

#endif // !defined(AFX_DENSITODLGDRAWSTATE_H__B948C7F9_8805_4DAD_B920_6B2E3A215233__INCLUDED_)
