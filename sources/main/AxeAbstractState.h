// AxeAbstractState.h: interface for the CAxeAbstractSate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AXEABSTRACTSATE_H__F4BF33C1_D15E_11D5_935E_DE66472DA378__INCLUDED_)
#define AFX_AXEABSTRACTSATE_H__F4BF33C1_D15E_11D5_935E_DE66472DA378__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAxeDialog;

class CAxeAbstractState  
{
public:
	virtual void UpdateStateLine();
	virtual LONG ScrollOff(UINT wParam, LONG lParam);
	virtual void PointValueEdited(int nControl);
	virtual LONG EndPick(UINT wParam, LONG lParam);
	virtual LONG MovePick(UINT wParam, LONG lParam);
	virtual LONG StartPick(UINT wParam, LONG lParam);
	virtual void CheckAxeButton()=0;
	virtual void CheckPointButton(int nButton)=0;
	CAxeAbstractState(CAxeDialog* theDialog);
	virtual ~CAxeAbstractState();

protected:
	CAxeDialog* m_pDialog;
};

#endif // !defined(AFX_AXEABSTRACTSATE_H__F4BF33C1_D15E_11D5_935E_DE66472DA378__INCLUDED_)
