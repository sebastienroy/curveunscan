#if !defined(AFX_LICENCEDLG_H__3E6E54A3_375A_11D5_935E_BAB3637C2579__INCLUDED_)
#define AFX_LICENCEDLG_H__3E6E54A3_375A_11D5_935E_BAB3637C2579__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LicenceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLicenceDlg dialog

class CLicenceDlg : public CDialog
{
// Construction
public:
	CLicenceDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLicenceDlg)
	enum { IDD = IDD_LICENCE_DIALOG };
	CString	m_strLicence;
	CString	m_strCompanyName;
	CString	m_strName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLicenceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLicenceDlg)
	virtual void OnOK();
	afx_msg void OnOpenFormButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LICENCEDLG_H__3E6E54A3_375A_11D5_935E_BAB3637C2579__INCLUDED_)
