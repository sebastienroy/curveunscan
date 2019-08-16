#if !defined(AFX_PASSWORDDIALOG_H__A510B302_4ABE_44E0_A1CC_E15EB004B92D__INCLUDED_)
#define AFX_PASSWORDDIALOG_H__A510B302_4ABE_44E0_A1CC_E15EB004B92D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PasswordDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPasswordDialog dialog

class CPasswordDialog : public CDialog
{
// Construction
public:
	CPasswordDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPasswordDialog)
	enum { IDD = IDD_PWD_DIALOG };
	CString	m_strPassword;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPasswordDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPasswordDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PASSWORDDIALOG_H__A510B302_4ABE_44E0_A1CC_E15EB004B92D__INCLUDED_)
