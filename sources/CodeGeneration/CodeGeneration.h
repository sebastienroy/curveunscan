// CodeGeneration.h : main header file for the CODEGENERATION application
//

#if !defined(AFX_CODEGENERATION_H__041728E5_38F4_11D5_935E_C0FE45E14079__INCLUDED_)
#define AFX_CODEGENERATION_H__041728E5_38F4_11D5_935E_C0FE45E14079__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCodeGenerationApp:
// See CodeGeneration.cpp for the implementation of this class
//

class CCodeGenerationApp : public CWinApp
{
public:
	CCodeGenerationApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodeGenerationApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCodeGenerationApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CODEGENERATION_H__041728E5_38F4_11D5_935E_C0FE45E14079__INCLUDED_)
