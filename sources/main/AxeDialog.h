#if !defined(AFX_AXEDIALOG_H__F4BF33C0_D15E_11D5_935E_DE66472DA378__INCLUDED_)
#define AFX_AXEDIALOG_H__F4BF33C0_D15E_11D5_935E_DE66472DA378__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AxeDialog.h : header file
//

#include "ConstructionDialog.h"

#include "ValueEdit.h"

class CAxe;
class CSequence;
class CUnscanView;
class CAxeAbstractState;
class CAxeDrawingState;
class CAxePointPickingState;
class CAxeWaitState;
class CAxeAbstractState;
class CScalePoint;

/////////////////////////////////////////////////////////////////////////////
// CAxeDialog dialog

class CAxeDialog : public CConstructionDialog
{
	friend class CAxeAbstractState;
	friend class CAxeDrawingState;
	friend class CAxePointPickingState;
	friend class CAxeWaitState;

// Construction
public:
	CAxeDialog(UINT ID,CUnscanView* pParent,CSequence* pSequence,CAxe* pMainAxe, CAxe* pOtherAxe);

// Dialog Data
	//{{AFX_DATA(CAxeDialog)
	enum { IDD = IDD_AXE_X };
	CValueEdit	m_ValueEditPt2;
	CValueEdit	m_ValueEditPt1;
	BOOL	m_bCheckPt1;
	BOOL	m_bCheckPt2;
	BOOL	m_bCheckAxe;
	CString	m_strAxeName;
	int		m_nLinear;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAxeDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool IsPositionDefined(int nNumber);
	bool IsValueEditEmpty(int nNumber);
	int GetFocusedEditNb();
	virtual void UpdateObjects();
	void ValueEditChanged(int nPoint);
	mutable CScalePoint* m_pScalePoint2;
	mutable CScalePoint* m_pScalePoint1;
	virtual BOOL OKState();
	CAxeAbstractState* m_pState;
	void EnablePoint(int nPointNumber,BOOL bState);
	virtual BOOL DataValidation();
	LONG OnScrollOff(UINT wParam, LONG lParam);
	LONG OnScrollOn(UINT wParam, LONG lParam);
	LONG OnMovePick(UINT wParam, LONG lParam);
	LONG OnStartPick(UINT wParam, LONG lParam);
	LONG OnEndPick(UINT wParam, LONG lParam);
	CPoint m_ptTo;
	CPoint m_ptFrom;
	CAxe* m_pOtherAxe;
	CAxe* m_pAxe;

	// Generated message map functions
	//{{AFX_MSG(CAxeDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheck1st();
	afx_msg void OnCheck2nd();
	afx_msg void OnCheckAxe();
	afx_msg void OnChangeEdit1stvalue();
	afx_msg void OnChangeEdit2ndvalue();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnPrevious();
	afx_msg void OnKillfocusEdit1stvalue();
	afx_msg void OnSetfocusEdit1stvalue();
	afx_msg void OnKillfocusEdit2ndvalue();
	afx_msg void OnSetfocusEdit2ndvalue();
	afx_msg void OnRadioLinear();
	afx_msg void OnRadio2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AXEDIALOG_H__F4BF33C0_D15E_11D5_935E_DE66472DA378__INCLUDED_)
