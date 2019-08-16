#if !defined(AFX_GENESISDIALOG_H__CD8BD260_63DA_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_GENESISDIALOG_H__CD8BD260_63DA_11D4_935E_0080C7A4F675__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ConstructionDialog.h"
#include <afxtempl.h>
class CUnscanView;
class CSequence;
class CContinuousCurve;
class CCoordSyst;
class CPartialCurve;
class CContinuousAdvOptDlg;
class CDashMaxDistDialog;

// GenesisDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGenesisDialog dialog

class CGenesisDialog : public CConstructionDialog
{
// Construction
public:
	bool ActionConfirmed();
	BOOL UpdateDeleteButton();
	CGenesisDialog(UINT ID, CUnscanView *pView, CSequence *pSequence, CContinuousCurve *pCurve);

// Dialog Data
	//{{AFX_DATA(CGenesisDialog)
	enum { IDD = IDD_CONTINUOUS_DIALOG };
	CListBox	m_GenesisListBox;
	int		m_Thickness;
	CString	m_CurveName;
	BOOL	m_CheckThick;
	BOOL	m_CheckElement;
	int		m_Follow;
	int		m_nDashMaxDist;
	int		m_Dashed;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGenesisDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void UpdateDashed();
	CDashMaxDistDialog* m_pDashDistDialog;
	CContinuousAdvOptDlg* m_pOptDlg;
	void UpdateObjects();
	BOOL DataValidation();
	BOOL OKState();
	void FillListBox();
	CCoordSyst* m_pCoord;
	void AddPartial(CPartialCurve* pPartial);
	CArray<POSITION,POSITION> m_PosArray;
	CContinuousCurve* m_pCurve;

	// Generated message map functions
	//{{AFX_MSG(CGenesisDialog)
	afx_msg void OnEndPick(UINT wParam, LONG lParam);
	afx_msg void OnOptDlgClosed(UINT wParam, LONG lParam);
	afx_msg void OnApplyDashDist(UINT wParam, LONG lParam);
	afx_msg void OnPrevious();
	afx_msg void OnDelete();
	afx_msg void OnSelchangeGenesisList();
	afx_msg void OnCheckThick();
	afx_msg void OnChangeEditCurvename();
	afx_msg void OnChangeEditThickness();
	afx_msg void OnCheckElement();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioTop();
	afx_msg void OnRadioBottom();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnAdvContinuousButton();
	afx_msg void OnButtonDashdist();
	afx_msg void OnDashDistDlgClosed(UINT wParam, LONG lParam);
	afx_msg void OnRadioDashed();
	afx_msg void OnRadioNotdashed();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENESISDIALOG_H__CD8BD260_63DA_11D4_935E_0080C7A4F675__INCLUDED_)
