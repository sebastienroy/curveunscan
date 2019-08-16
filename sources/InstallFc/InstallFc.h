// InstallFc.h : main header file for the INSTALLFC DLL
//

#if !defined(AFX_INSTALLFC_H__12651D3C_B90E_4FE9_AF57_8210BCBF7BF5__INCLUDED_)
#define AFX_INSTALLFC_H__12651D3C_B90E_4FE9_AF57_8210BCBF7BF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CInstallFcApp
// See InstallFc.cpp for the implementation of this class
//

class CInstallFcApp : public CWinApp
{
public:
	CInstallFcApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInstallFcApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CInstallFcApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSTALLFC_H__12651D3C_B90E_4FE9_AF57_8210BCBF7BF5__INCLUDED_)
