/*
/--------------------------------------------------------------------
|
|      $Id: testdec.cpp,v 1.4 2001/09/16 19:03:23 uzadow Exp $
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
--------------------------------------------------------------------
*/

#include "stdafx.h"
#include "testdec.h"
#include "MainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDibtestApp

BEGIN_MESSAGE_MAP(CDibtestApp, CWinApp)
//{{AFX_MSG_MAP(CDibtestApp)
// NOTE - the ClassWizard will add and remove mapping macros here.
//    DO NOT EDIT what you see in these blocks of generated code!
//}}AFX_MSG
ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDibtestApp construction

CDibtestApp::CDibtestApp()
{
  // TODO: add construction code here,
  // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDibtestApp object


CDibtestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDibtestApp initialization

BOOL CDibtestApp::InitInstance()
{
  // Standard initialization
  // If you are not using these features and wish to reduce the size
  //  of your final executable, you should remove from the following
  //  the specific initialization routines you do not need.

#ifdef _AFXDLL
  Enable3dControls();      // Call this when using MFC in a shared DLL
#else
Enable3dControlsStatic();  // Call this when linking to MFC statically
#endif

  CDibtestDlg dlg (m_lpCmdLine);
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

  // Since the dialog has been closed, return false so that we exit the
  //  application, rather than start the application's message pump.

  return false;
}
/*
/--------------------------------------------------------------------
|
|      $Log: testdec.cpp,v $
|      Revision 1.4  2001/09/16 19:03:23  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.3  2000/01/10 23:53:03  Ulrich von Zadow
|      Changed formatting & removed tabs.
|
|
--------------------------------------------------------------------
*/
