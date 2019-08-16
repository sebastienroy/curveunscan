// CodeGeneration.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CodeGeneration.h"
#include "CodeGenerationDlg.h"
#include "PasswordDialog.h"

#include <md5/md5checksum.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCodeGenerationApp

BEGIN_MESSAGE_MAP(CCodeGenerationApp, CWinApp)
	//{{AFX_MSG_MAP(CCodeGenerationApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCodeGenerationApp construction

CCodeGenerationApp::CCodeGenerationApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCodeGenerationApp object

CCodeGenerationApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCodeGenerationApp initialization

BOOL CCodeGenerationApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// check password
	bool bGoodCode=false;
	CString password;
	while(!bGoodCode)
	{
		CPasswordDialog pwdDlg;
		if(IDOK==pwdDlg.DoModal())
		{
			password=pwdDlg.m_strPassword;
			CString strCodedPwd=CMD5Checksum::GetMD5((BYTE*)(LPCSTR)password,password.GetLength());
			if(CString("7a9be396ae54b5365dbb2496c56932e3")==strCodedPwd)
			{
				bGoodCode=true;
			}
			else
			{
				AfxMessageBox("Wrong password!",MB_ICONEXCLAMATION);
			}
		}
		else
		{
			return FALSE;
		}
	}

	
	password.MakeUpper();
	CCodeGenerationDlg dlg(password);
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
