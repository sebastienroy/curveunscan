#if !defined(AFX_SAVEPROMPTDLG_H__1657EE85_C447_4A86_A021_D11FDD964A73__INCLUDED_)
#define AFX_SAVEPROMPTDLG_H__1657EE85_C447_4A86_A021_D11FDD964A73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SavePromptDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSavePromptDlg dialog

class CSavePromptDlg : public CDialog
{
// Construction
public:
	CSavePromptDlg(CString strPrompt, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSavePromptDlg)
	enum { IDD = IDD_SAVE_PROMPT };
	CString	m_strPrompt;
	int		m_nSaveKind;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSavePromptDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSavePromptDlg)
	afx_msg void OnYes();
	afx_msg void OnNo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVEPROMPTDLG_H__1657EE85_C447_4A86_A021_D11FDD964A73__INCLUDED_)
