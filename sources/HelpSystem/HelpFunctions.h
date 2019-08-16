// HelpFunctions.h: interface for the CHelpFunctions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HELPFUNCTIONS_H__28AD9A46_0005_11D5_935E_C5C2266FCC78__INCLUDED_)
#define AFX_HELPFUNCTIONS_H__28AD9A46_0005_11D5_935E_C5C2266FCC78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHelpFunctions  
{
public:
	static void OpenTopic(HWND hwndApp, DWORD topic);
	static void DisplayCtrlPopup(CWnd* pWnd, POINT pt, int iCtrlID);
	CHelpFunctions();
	virtual ~CHelpFunctions();

};

#endif // !defined(AFX_HELPFUNCTIONS_H__28AD9A46_0005_11D5_935E_C5C2266FCC78__INCLUDED_)
