// DensitoDlgAbstractState.h: interface for the CDensitoDlgAbstractState class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DENSITODLGABSTRACTSTATE_H__905EAA8F_1007_4B8A_B5BA_1A77DA03B620__INCLUDED_)
#define AFX_DENSITODLGABSTRACTSTATE_H__905EAA8F_1007_4B8A_B5BA_1A77DA03B620__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDensitometryDialog;

class CDensitoDlgAbstractState  
{
public:
	CDensitoDlgAbstractState(CDensitometryDialog* pDlg);
	virtual ~CDensitoDlgAbstractState();

public:
	virtual void CheckPickColorButton(bool bIsTop);
	virtual void CheckDrawButton();
	virtual LONG ScrollOff(UINT wParam, LONG lParam);
	virtual LONG EndPick(UINT wParam, LONG lParam);
	virtual LONG MovePick(UINT wParam, LONG lParam);
	virtual LONG StartPick(UINT wParam, LONG lParam);


protected:
	CDensitometryDialog* m_pDlg;
};

#endif // !defined(AFX_DENSITODLGABSTRACTSTATE_H__905EAA8F_1007_4B8A_B5BA_1A77DA03B620__INCLUDED_)
