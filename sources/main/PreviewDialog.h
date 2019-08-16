#if !defined(AFX_PREVIEWDIALOG_H__04022140_6B93_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_PREVIEWDIALOG_H__04022140_6B93_11D4_935E_0080C7A4F675__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PreviewDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPreviewDialog dialog

class CPreviewDialog : public CDialog
{
// Construction
public:
	CPreviewDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPreviewDialog)
	enum { IDD = IDD_PREVIEW_DIALOG };
	CString	m_PreviewString;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPreviewDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPreviewDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREVIEWDIALOG_H__04022140_6B93_11D4_935E_0080C7A4F675__INCLUDED_)
