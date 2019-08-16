// CurveUnscan.h : main header file for the CURVEUNSCAN application
//

#if !defined(AFX_CURVEUNSCAN_H__4D12A6B9_6750_4824_8DE6_05A5ECA628FA__INCLUDED_)
#define AFX_CURVEUNSCAN_H__4D12A6B9_6750_4824_8DE6_05A5ECA628FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
//#include "stdafx.h"


/////////////////////////////////////////////////////////////////////////////
// CUnscanApp:
// See CurveUnscan.cpp for the implementation of this class
//

class CUnscanApp : public CWinApp
{
public:
	CUnscanApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUnscanApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CUnscanApp)
	afx_msg void OnAppAbout();
	afx_msg void OnViewOptions();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURVEUNSCAN_H__4D12A6B9_6750_4824_8DE6_05A5ECA628FA__INCLUDED_)
