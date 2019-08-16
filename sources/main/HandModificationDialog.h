#if !defined(AFX_HANDMODIFICATIONDIALOG_H__39597C40_67BE_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_HANDMODIFICATIONDIALOG_H__39597C40_67BE_11D4_935E_0080C7A4F675__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ConstructionDialog.h"
#include <vector>
#include <list>
using namespace std;

class CUnscanView;
class CSequence;
class CContinuousCurve;
class CUnscanDoc;
class CAbstractModificationTool;
// HandModificationDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHandModificationDialog dialog

class CHandModificationDialog : public CConstructionDialog
{
// Construction
public:
	CHandModificationDialog(UINT ID, CUnscanView *pView, CSequence *pSequence, CContinuousCurve *pCurve);

// Dialog Data
	//{{AFX_DATA(CHandModificationDialog)
	enum { IDD = IDD_HAND_DIALOG };
	int		m_ChosenTool;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHandModificationDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation

	//--- Methods 
protected:
	void UpdateUndoRedoButtons();
	void UpdateObjects();
	BOOL OKState();
	BOOL DataValidation();

	//--- Attributes
protected:
	// delay between two redraws
	UINT m_DelayTimer;
	// previous point when "OnMouseMove()"
	CPoint m_PrevPoint;
	// memento of the curve points
	vector<list<CPoint>*> m_MementoVector;
	// index of the current state. Cannot be less than zero
	int m_nMementoIndex;

	//--- Relations
protected:
//	void UpdateRedraw(CRect& rect);
	CRect* m_pRedrawRect;
	CUnscanDoc* m_pDoc;
	CContinuousCurve* m_pCurve;
	CBitmap* m_pBmpPen;
	CBitmap* m_pBmpRubber;
	CAbstractModificationTool* m_pModificationTool;

	// Generated message map functions
	//{{AFX_MSG(CHandModificationDialog)
	afx_msg void OnPrevious();
	afx_msg LONG OnEndPick(UINT wParam, LONG lParam);
	afx_msg LONG OnMovePick(UINT wParam, LONG lParam);
	afx_msg LONG OnStartPick(UINT wParam, LONG lParam);
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRedo();
	afx_msg void OnUndo();
	afx_msg void OnResetModification();
	afx_msg void OnToolChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HANDMODIFICATIONDIALOG_H__39597C40_67BE_11D4_935E_0080C7A4F675__INCLUDED_)
