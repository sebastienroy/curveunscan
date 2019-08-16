#if !defined(AFX_SEPARATORDIALOG_H__664C4BD1_0768_4482_A77A_4D44ED684473__INCLUDED_)
#define AFX_SEPARATORDIALOG_H__664C4BD1_0768_4482_A77A_4D44ED684473__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SeparatorDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSeparatorDialog dialog

class CSeparatorDialog : public CDialog
{
// Construction
public:
	char GetSeparator() const;
	CSeparatorDialog(char cSeparator, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSeparatorDialog)
	enum { IDD = IDD_EXPORT_FORMAT_DIALOG };
	CString	m_strOtherSeparator;
	int		m_nSeparatorRadio;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeparatorDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	char m_cSeparator;

	// Generated message map functions
	//{{AFX_MSG(CSeparatorDialog)
	virtual void OnOK();
	afx_msg void OnChangeEditSepOther();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEPARATORDIALOG_H__664C4BD1_0768_4482_A77A_4D44ED684473__INCLUDED_)
