// DensitoDlgWaitState.h: interface for the CDensitoDlgWaitState class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DENSITODLGWAITSTATE_H__3F249ADB_E3CD_4BF6_BB35_48CE90EF733E__INCLUDED_)
#define AFX_DENSITODLGWAITSTATE_H__3F249ADB_E3CD_4BF6_BB35_48CE90EF733E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DensitoDlgAbstractState.h"

class CDensitoDlgWaitState : public CDensitoDlgAbstractState  
{
public:
	CDensitoDlgWaitState(CDensitometryDialog* pDlg);
	virtual ~CDensitoDlgWaitState();

public:
	virtual void CheckPickColorButton(bool bIsTop);
	virtual void CheckDrawButton();


};

#endif // !defined(AFX_DENSITODLGWAITSTATE_H__3F249ADB_E3CD_4BF6_BB35_48CE90EF733E__INCLUDED_)
