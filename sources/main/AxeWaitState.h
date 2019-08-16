// AxeWaitState.h: interface for the CAxeWaitState class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AXEWAITSTATE_H__F4BF33C4_D15E_11D5_935E_DE66472DA378__INCLUDED_)
#define AFX_AXEWAITSTATE_H__F4BF33C4_D15E_11D5_935E_DE66472DA378__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AxeAbstractState.h"

class CAxeWaitState : public CAxeAbstractState  
{
public:
	virtual void UpdateStateLine();
	virtual void CheckPointButton(int nButton);
	virtual void CheckAxeButton();
	CAxeWaitState(CAxeDialog* theDialog);
	virtual ~CAxeWaitState();

};

#endif // !defined(AFX_AXEWAITSTATE_H__F4BF33C4_D15E_11D5_935E_DE66472DA378__INCLUDED_)
