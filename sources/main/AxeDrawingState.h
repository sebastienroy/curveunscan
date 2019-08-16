// AxeDrawingState.h: interface for the CAxeDrawingState class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AXEDRAWINGSTATE_H__F4BF33C2_D15E_11D5_935E_DE66472DA378__INCLUDED_)
#define AFX_AXEDRAWINGSTATE_H__F4BF33C2_D15E_11D5_935E_DE66472DA378__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AxeAbstractState.h"

class CAxe;

class CAxeDrawingState : public CAxeAbstractState  
{
public:
	virtual void UpdateStateLine();
	virtual void CheckPointButton(int nButton);
	virtual void CheckAxeButton();
	virtual LONG ScrollOff(UINT wParam, LONG lParam);
	virtual LONG EndPick(UINT wParam, LONG lParam);
	virtual LONG MovePick(UINT wParam, LONG lParam);
	virtual LONG StartPick(UINT wParam, LONG lParam);
	CAxeDrawingState(CAxeDialog* theDialog);
	virtual ~CAxeDrawingState();

protected:
	void InvertLine(CDC *pDC, CPoint from, CPoint to);
	void SetStraightLine(const CPoint *ptA, CPoint *ptB);
	CPoint m_ptTo;
	CPoint m_ptFrom;
	mutable CAxe* m_pAxe;
};

#endif // !defined(AFX_AXEDRAWINGSTATE_H__F4BF33C2_D15E_11D5_935E_DE66472DA378__INCLUDED_)
