#if !defined(AFX_WELCOMEDIALOG_H__68DE40CA_3713_11D5_935E_BAB3637C2579__INCLUDED_)
#define AFX_WELCOMEDIALOG_H__68DE40CA_3713_11D5_935E_BAB3637C2579__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WelcomeDialog.h : header file
//

#include "LicenceManaging.h"

/////////////////////////////////////////////////////////////////////////////
// CWelcomeDialog dialog

class CWelcomeDialog : public CDialog
{
// Construction
public:
	CWelcomeDialog(int nDay, CString strProductID, int ntotalExportNb, int nExportLeft, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWelcomeDialog)
	enum { IDD = IDD_WELCOME };
	CString	m_WelcomeString;
	CString	m_strProductID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWelcomeDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_nDay;
	int m_nTotalExportNb;
	int m_nExportLeft;

	// Generated message map functions
	//{{AFX_MSG(CWelcomeDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WELCOMEDIALOG_H__68DE40CA_3713_11D5_935E_BAB3637C2579__INCLUDED_)
