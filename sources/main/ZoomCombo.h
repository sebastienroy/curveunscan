#if !defined(AFX_ZOOMCOMBO_H__CF79B104_8C9D_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_ZOOMCOMBO_H__CF79B104_8C9D_11D4_935E_0080C7A4F675__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZoomCombo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZoomCombo window

class CZoomCombo : public CComboBox
{
// Construction
public:
	CZoomCombo();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoomCombo)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CZoomCombo();

	// Generated message map functions
protected:
	//{{AFX_MSG(CZoomCombo)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZOOMCOMBO_H__CF79B104_8C9D_11D4_935E_0080C7A4F675__INCLUDED_)
