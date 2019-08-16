// UnscanView.h : interface of the CUnscanView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNSCANVIEW_H__89299EA6_C815_401B_8137_0AD46F27A470__INCLUDED_)
#define AFX_UNSCANVIEW_H__89299EA6_C815_401B_8137_0AD46F27A470__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "plpixel32.h"

class CZoomDialog;
class CUnscanDoc;
class CSequence;

enum ViewState
	{
	WaitState,
	WaitDialogState,
	PickingState,
	ScrollingState
	};


class CUnscanView : public CScrollView
{
protected: // create from serialization only
	CUnscanView();
	DECLARE_DYNCREATE(CUnscanView)

// Attributes
public:
	CUnscanDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUnscanView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	void PickingStopped();
	PLPixel32 GetPixelColor(const CPoint& point) const;
	void StartInitialSequence();
	void EndSequence();
	int SetZoomValue(int value);
	void RemoveZoomDialog();
	int GetZoom();
	BOOL IsDialogOn();
	BOOL CancelActiveDialog(CDialog *pDialogue);
	BOOL SetActiveDialog(CDialog* dialogue);
	virtual ~CUnscanView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:

	CSequence* m_pSequence;
	void UpdateCoordStatus(const CPoint& ptCursor);
	BOOL m_FirstAppears;
	UINT m_TimerID;
	CPoint ScrollDirection(CPoint point);
	CPoint m_ScrollDirection;
	enum ViewState m_CurrentState;
	CDialog* m_pActiveDialog;
	//{{AFX_MSG(CUnscanView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnGraphNewsystem();
	afx_msg void OnUpdateGraphNewsystem(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnGraphNewdiscrete();
	afx_msg void OnGraphNewcontinuous();
	afx_msg void OnGraphNewdensito();
	afx_msg void OnUpdateGraphNewcontinuous(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGraphNewdiscrete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGraphNewdensito(CCmdUI* pCmdUI);
	afx_msg void OnGraphModify();
	afx_msg void OnUpdateGraphModify(CCmdUI* pCmdUI);
	afx_msg void OnGraphDeleteobject();
	afx_msg void OnUpdateGraphDeleteobject(CCmdUI* pCmdUI);
	afx_msg void OnGraphNewCoordandcurve();
	afx_msg void OnUpdateGraphNewCoordandcurve(CCmdUI* pCmdUI);
	afx_msg void OnViewZoom();
	afx_msg void OnUpdateViewZoom(CCmdUI* pCmdUI);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnHelpFinder();
	afx_msg void OnUpdateViewOptions(CCmdUI* pCmdUI);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnGraphNewsplinecurve();
	afx_msg void OnUpdateGraphNewsplinecurve(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int GetFittedZoom();
	int m_nZoom;
	CZoomDialog* m_pZoomDialog;
};

#ifndef _DEBUG  // debug version in UnscanView.cpp
inline CUnscanDoc* CUnscanView::GetDocument()
   { return (CUnscanDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNSCANVIEW_H__89299EA6_C815_401B_8137_0AD46F27A470__INCLUDED_)
