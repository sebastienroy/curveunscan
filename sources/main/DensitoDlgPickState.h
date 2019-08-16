// DensitoDlgPickState.h: interface for the CDensitoDlgPickState class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DENSITODLGPICKSTATE_H__EE4768BE_23E1_4C20_A51B_0937428831EF__INCLUDED_)
#define AFX_DENSITODLGPICKSTATE_H__EE4768BE_23E1_4C20_A51B_0937428831EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DensitoDlgAbstractState.h"

class CDensitoDlgPickState : public CDensitoDlgAbstractState  
{
public:
	CDensitoDlgPickState(CDensitometryDialog* pDlg, bool bIsTopColor);
	virtual ~CDensitoDlgPickState();

public:
	virtual void CheckPickColorButton(bool bIsTop);
	virtual void CheckDrawButton();
	virtual LONG EndPick(UINT wParam, LONG lParam);


protected:
	bool m_bIsTopColor;
};

#endif // !defined(AFX_DENSITODLGPICKSTATE_H__EE4768BE_23E1_4C20_A51B_0937428831EF__INCLUDED_)
