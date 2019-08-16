#if !defined(AFX_DENSITOPERIODDIALOG_H__F7F83C43_3E19_4251_BA1A_942660A6CB10__INCLUDED_)
#define AFX_DENSITOPERIODDIALOG_H__F7F83C43_3E19_4251_BA1A_942660A6CB10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DensitoPeriodDialog.h : header file
//

#include <ValueEdit.h>

class CDensityResults;

/////////////////////////////////////////////////////////////////////////////
// CDensitoPeriodDialog dialog

class CDensitoPeriodDialog : public CDialog
{
// Construction
public:
	CDensitoPeriodDialog(CDensityResults *pResults,
						CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDensitoPeriodDialog)
	enum { IDD = IDD_DENSITO_PERIOD_DIALOG };
	CValueEdit	m_MinYEdit;
	CValueEdit	m_MinXEdit;
	CValueEdit	m_MaxYEdit;
	CValueEdit	m_MaxXEdit;
	CValueEdit	m_FirstYEdit;
	CValueEdit	m_FirstXEdit;
	CValueEdit	m_PeriodYEdit;
	CValueEdit	m_FreqYEdit;
	CValueEdit	m_PeriodXEdit;
	CValueEdit	m_FreqXEdit;
	int		m_nDisplayedCoord;
	CString	m_strUnitX;
	CString	m_strUnitY;
	CString	m_strSavedNb;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDensitoPeriodDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void UpdateAllValues(CWnd *pCtrl=NULL);
	void UpdateValues(CWnd *pCtrl=NULL);
	void EnableY(BOOL bEnable);
	void EnableX(BOOL bEnable);

protected:
	bool IsRealyGreater(double a, double b) const;
	bool IsRealyLower(double a, double b) const;
	CDensityResults* m_pBackupResults;
	CDensityResults* m_pResults;
	// values for y=ax+b
	mutable double m_dXtoYperiodFactor;
	mutable double m_dMinX;
	mutable double m_dMaxX;
	mutable double m_dMinY;
	mutable double m_dMaxY;

	// Generated message map functions
	//{{AFX_MSG(CDensitoPeriodDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioDispX();
	afx_msg void OnRadioDispY();
	afx_msg void OnRadioDispBoth();
	afx_msg void OnChangeEditXfirst();
	afx_msg void OnChangeEditYfirst();
	afx_msg void OnChangeEditXperiod();
	afx_msg void OnChangeEditYperiod();
	afx_msg void OnChangeEditXfreq();
	afx_msg void OnChangeEditYfreq();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DENSITOPERIODDIALOG_H__F7F83C43_3E19_4251_BA1A_942660A6CB10__INCLUDED_)
