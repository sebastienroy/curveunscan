#if !defined(AFX_SPLINEDIALOG_H__A4A9DAFC_3E3F_48CD_AD14_91F9FA2C1C28__INCLUDED_)
#define AFX_SPLINEDIALOG_H__A4A9DAFC_3E3F_48CD_AD14_91F9FA2C1C28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SplineDialog.h : header file
//

#include "ConstructionDialog.h"

class CUnscanView;
class CSequence;
class CSplineCurve;
class CSplineDlgAbstractTool;

/////////////////////////////////////////////////////////////////////////////
// CSplineDialog dialog

class CSplineDialog : public CConstructionDialog
{
// Construction
public:
	void SetToolComment(CString strComment);
	void RefreshToolButton();
	void SetState(CSplineDlgAbstractTool* pDlgState);
	CSplineDialog(CWnd* pParent = NULL);   // standard constructor
	CSplineDialog(UINT ID, 
				  CUnscanView *pView, 
				  CSequence *pSequence, 
				  CSplineCurve *pCurve);
// Dialog Data
	//{{AFX_DATA(CSplineDialog)
	enum { IDD = IDD_SPLINE_DIALOG };
	int		m_nTool;
	CString	m_strCurveName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplineDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual BOOL OKState();
	virtual BOOL DataValidation();
	virtual void UpdateObjects();

	void UpdateToolState();

protected:
	CSplineCurve* m_pCurve;
	CSplineDlgAbstractTool* m_pState;

	// Generated message map functions
	//{{AFX_MSG(CSplineDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnPrevious();
	afx_msg LONG OnEndPick(UINT wParam, LONG lParam);
	afx_msg LONG OnMovePick(UINT wParam, LONG lParam);
	afx_msg LONG OnStartPick(UINT wParam, LONG lParam);
	afx_msg void OnMinimizeButton();
	afx_msg void OnChangeEditCurvename();
	afx_msg void OnRadioSplineAddback();
	afx_msg void OnRadioSplineAddfront();
	afx_msg void OnRadioSplineAddmiddle();
	afx_msg void OnRadioSplineModify();
	afx_msg void OnRadioSplineRemove();
	afx_msg void OnUndoSplineButton();
	afx_msg void OnRedoSplineButton();
	afx_msg void OnSplineCleanAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLINEDIALOG_H__A4A9DAFC_3E3F_48CD_AD14_91F9FA2C1C28__INCLUDED_)
