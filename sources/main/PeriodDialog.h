#if !defined(AFX_PERIODDIALOG_H__E1FACE40_6880_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_PERIODDIALOG_H__E1FACE40_6880_11D4_935E_0080C7A4F675__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ValueEdit.h"
class CContinuousResults;


// PeriodDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPeriodDialog dialog

class CPeriodDialog : public CDialog
{
// Construction
public:
	CPeriodDialog(CContinuousResults* pResults);
	CPeriodDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPeriodDialog)
	enum { IDD = IDD_PERIOD_DIALOG };
	CValueEdit	m_FirstValueEdit;
	CValueEdit	m_FrequencyEdit;
	CValueEdit	m_PeriodEdit;
	CString	m_PeriodLegend;
	CString	m_FrequencyLegend;
	CString	m_FirstValueLegend;
	CString	m_strNSavedPoints;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPeriodDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int GetLinesNb() const;
	void UpdateNbOfSavedPoints();
	double m_dPeriod;
	void HighlightEdit(int nID);
	CContinuousResults* m_pResults;

	// Generated message map functions
	//{{AFX_MSG(CPeriodDialog)
	afx_msg void OnChangeEditPeriod();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditFrequency();
	afx_msg void OnChangeEditFirstvalue();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERIODDIALOG_H__E1FACE40_6880_11D4_935E_0080C7A4F675__INCLUDED_)
