#if !defined(AFX_LIMITDIALOG_H__374046E0_63A5_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_LIMITDIALOG_H__374046E0_63A5_11D4_935E_0080C7A4F675__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ConstructionDialog.h"
#include "ValueEdit.h"
class CUnscanView;
class CSequence;
class CContinuousCurve;
class CLimit;
// LimitDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLimitDialog dialog

class CLimitDialog : public CConstructionDialog
{
// Construction
public:
	virtual BOOL DataValidation();
	CLimitDialog(UINT ID, CUnscanView* pView, CSequence* pSequence, CContinuousCurve* pCurve);

// Dialog Data
	//{{AFX_DATA(CLimitDialog)
	enum { IDD = IDD_CURVELIMITS_DIALOG };
	CValueEdit	m_RightEdit;
	CValueEdit	m_LeftEdit;
	BOOL	m_LeftCheck;
	BOOL	m_RightCheck;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLimitDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool ActionConfirmed();
	virtual void UpdateObjects();
	BOOL m_Change;
	virtual BOOL OKState();
	CLimit* m_pRightLimit;
	CLimit* m_pLeftLimit;
	CContinuousCurve* m_pCurve;

	// Generated message map functions
	//{{AFX_MSG(CLimitDialog)
	afx_msg void OnChangeEditLeftvalue();
	afx_msg void OnChangeEditRightvalue();
	afx_msg void OnCheckLeft();
	afx_msg void OnCheckRight();
	afx_msg void OnEndPick(UINT wParam, LONG lParam);
	afx_msg void OnPrevious();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIMITDIALOG_H__374046E0_63A5_11D4_935E_0080C7A4F675__INCLUDED_)
