#if !defined(AFX_SPLINEPERIODDIALOG_H__8783B2CB_2C38_4463_BAC2_FC047D31A681__INCLUDED_)
#define AFX_SPLINEPERIODDIALOG_H__8783B2CB_2C38_4463_BAC2_FC047D31A681__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SplinePeriodDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSplinePeriodDialog dialog

class CSplineResults;

class CSplinePeriodDialog : public CDialog
{
// Construction
public:
	CSplinePeriodDialog(CSplineResults* pResults, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSplinePeriodDialog)
	enum { IDD = IDD_SPLINE_PERIOD_DIALOG };
	int		m_SavedPointsNb;
	CString	m_strTotalNb;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplinePeriodDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void UpdateTotalNb();
	CSplineResults *m_pResults;

	// Generated message map functions
	//{{AFX_MSG(CSplinePeriodDialog)
	virtual void OnOK();
	afx_msg void OnChangeSplineSavedPointsNbEdit();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLINEPERIODDIALOG_H__8783B2CB_2C38_4463_BAC2_FC047D31A681__INCLUDED_)
