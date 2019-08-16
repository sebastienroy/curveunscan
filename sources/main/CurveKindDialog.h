#if !defined(AFX_CURVEKINDDIALOG_H__C7D5DD85_4C55_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_CURVEKINDDIALOG_H__C7D5DD85_4C55_11D4_935E_0080C7A4F675__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

class CSequence;

// CurveKindDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCurveKindDialog dialog

class CCurveKindDialog : public CDialog
{
// Construction
public:
	CCurveKindDialog(CSequence* pSequence);
	int m_Next;
	CCurveKindDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCurveKindDialog)
	enum { IDD = IDD_CURVEKIND_DIALOG };
	int		m_Kind;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurveKindDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CSequence* m_pSequence;

	// Generated message map functions
	//{{AFX_MSG(CCurveKindDialog)
	virtual void OnOK();
	afx_msg void OnPrevious();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURVEKINDDIALOG_H__C7D5DD85_4C55_11D4_935E_0080C7A4F675__INCLUDED_)
