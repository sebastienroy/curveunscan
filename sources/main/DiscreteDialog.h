#if !defined(AFX_DISCRETEDIALOG_H__69131784_5BC9_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_DISCRETEDIALOG_H__69131784_5BC9_11D4_935E_0080C7A4F675__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ConstructionDialog.h"
class CUnscanView;
class CSequence;
class CDiscreteCurve;
class CCoordSyst;
// DiscreteDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDiscreteDialog dialog

class CDiscreteDialog : public CConstructionDialog
{
// Construction
public:
	CDiscreteDialog(UINT ID,CUnscanView *pParent, CSequence *pSequence, CDiscreteCurve *pCurve);

// Dialog Data
	//{{AFX_DATA(CDiscreteDialog)
	enum { IDD = IDD_DISCRETE_DIALOG };
	CListBox	m_PointListBox;
	CString	m_GraphName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiscreteDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void FillListBox();
	BOOL UpdateDeleteButton();
	BOOL UpdateSortButton();
	BOOL DataValidation();
	BOOL OKState();
	void UpdateObjects();
	void DeleteListBox();
	void AddPoint(CPoint point,POSITION curvePos);
	CCoordSyst* m_pCoordSyst;
	CDiscreteCurve* m_pCurve;

	// Generated message map functions
	//{{AFX_MSG(CDiscreteDialog)
	afx_msg void OnEndPick(UINT wParam, LONG lParam);
	afx_msg void OnSort();
	afx_msg void OnDelete();
	afx_msg void OnPrevious();
	afx_msg void OnSelchangeListPoints();
	afx_msg void OnChangeEditGraphname();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISCRETEDIALOG_H__69131784_5BC9_11D4_935E_0080C7A4F675__INCLUDED_)
