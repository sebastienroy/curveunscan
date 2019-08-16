#if !defined(AFX_ZOOMDIALOG_H__CF79B103_8C9D_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_ZOOMDIALOG_H__CF79B103_8C9D_11D4_935E_0080C7A4F675__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZoomDialog.h : header file
//

#include "ZoomCombo.h"

class CUnscanView;

/////////////////////////////////////////////////////////////////////////////
// CZoomDialog dialog

class CZoomDialog : public CDialog
{
// Construction
public:
	void SetZoomValue(int nZoom);
	CZoomDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CZoomDialog)
	enum { IDD = IDD_ZOOM_DIALOG };
	CZoomCombo	m_ZoomCombo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoomDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CUnscanView* m_pView;

	// Generated message map functions
	//{{AFX_MSG(CZoomDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeComboZoom();
	afx_msg void OnSelchangeComboZoom();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZOOMDIALOG_H__CF79B103_8C9D_11D4_935E_0080C7A4F675__INCLUDED_)
