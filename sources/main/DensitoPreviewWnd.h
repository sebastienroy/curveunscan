#if !defined(AFX_DENSITOPREVIEWWND_H__C32D8030_F284_4D0E_A7C3_19D9319AC6CE__INCLUDED_)
#define AFX_DENSITOPREVIEWWND_H__C32D8030_F284_4D0E_A7C3_19D9319AC6CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DensitoPreviewWnd.h : header file
//

class CDensityCurve;

/////////////////////////////////////////////////////////////////////////////
// CDensitoPreviewWnd window

class CDensitoPreviewWnd : public CWnd
{
// Construction
public:
	CDensitoPreviewWnd(CWnd* pParent,CDensityCurve* pCurve);

// Attributes
public:

protected:
	CDensityCurve* m_pCurve;
	CWnd *m_pParent;
	bool m_bParentClosed;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDensitoPreviewWnd)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	void ParentClosed();
	virtual ~CDensitoPreviewWnd();

	// Generated message map functions
protected:
	int GetPixelOffset(double value, double min, double max, int size) const;
	//{{AFX_MSG(CDensitoPreviewWnd)
	afx_msg void OnPaint();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DENSITOPREVIEWWND_H__C32D8030_F284_4D0E_A7C3_19D9319AC6CE__INCLUDED_)
