#if !defined(AFX_SORRYDLG_H__668B79A1_3830_11D5_935E_E536AE066879__INCLUDED_)
#define AFX_SORRYDLG_H__668B79A1_3830_11D5_935E_E536AE066879__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SorryDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSorryDlg dialog

class CSorryDlg : public CDialog
{
// Construction
public:
	CSorryDlg(CString strID, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSorryDlg)
	enum { IDD = IDD_SORRY };
	CString	m_strProductID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSorryDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSorryDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SORRYDLG_H__668B79A1_3830_11D5_935E_E536AE066879__INCLUDED_)
