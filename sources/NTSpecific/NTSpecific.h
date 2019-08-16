// NTSpecific.h : main header file for the NTSPECIFIC DLL
//

#if !defined(AFX_NTSPECIFIC_H__5CDC83D3_B935_4879_9AE5_3F17D69E630E__INCLUDED_)
#define AFX_NTSPECIFIC_H__5CDC83D3_B935_4879_9AE5_3F17D69E630E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNTSpecificApp
// See NTSpecific.cpp for the implementation of this class
//

class CNTSpecificApp : public CWinApp
{
public:
	CNTSpecificApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNTSpecificApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CNTSpecificApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NTSPECIFIC_H__5CDC83D3_B935_4879_9AE5_3F17D69E630E__INCLUDED_)
