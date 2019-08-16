#if !defined(AFX_DASHMAXDISTDIALOG_H__21C5BD46_41F8_4D15_B4D7_F40D85E2C1BF__INCLUDED_)
#define AFX_DASHMAXDISTDIALOG_H__21C5BD46_41F8_4D15_B4D7_F40D85E2C1BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DashMaxDistDialog.h : header file
//

class CGenesisDialog;

/////////////////////////////////////////////////////////////////////////////
// CDashMaxDistDialog dialog

class CDashMaxDistDialog : public CDialog
{
// Construction
public:
	CDashMaxDistDialog(CWnd* pParent = NULL,int nDashDist=0);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDashMaxDistDialog)
	enum { IDD = IDD_DASHDIST_DIALOG };
	int		m_nDashDist;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDashMaxDistDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CGenesisDialog* m_pGenesisDlg;
	bool m_bChanged;
	int m_nInitialDist;

	// Generated message map functions
	//{{AFX_MSG(CDashMaxDistDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditDashdist();
	afx_msg void OnButtonApply();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DASHMAXDISTDIALOG_H__21C5BD46_41F8_4D15_B4D7_F40D85E2C1BF__INCLUDED_)
