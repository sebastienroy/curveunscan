// AxePointPickingState.h: interface for the CAxePointPickingState class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AXEPOINTPICKINGSTATE_H__F4BF33C3_D15E_11D5_935E_DE66472DA378__INCLUDED_)
#define AFX_AXEPOINTPICKINGSTATE_H__F4BF33C3_D15E_11D5_935E_DE66472DA378__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AxeAbstractState.h"

class CScalePoint;

class CAxePointPickingState : public CAxeAbstractState  
{
public:
	virtual void UpdateStateLine();
	virtual void CheckPointButton(int nButton);
	virtual void CheckAxeButton();
	virtual LONG EndPick(UINT wParam, LONG lParam);
	CAxePointPickingState(CAxeDialog* theDialog,int nPointNumber);
	virtual ~CAxePointPickingState();

protected:
	mutable CScalePoint* m_pOtherScalePoint;
	mutable CScalePoint* m_pScalePoint;
	int m_nPointNumber;
};

#endif // !defined(AFX_AXEPOINTPICKINGSTATE_H__F4BF33C3_D15E_11D5_935E_DE66472DA378__INCLUDED_)
