// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__D5DFF631_8656_421F_9282_A81EB5A3D7E6__INCLUDED_)
#define AFX_MAINFRM_H__D5DFF631_8656_421F_9282_A81EB5A3D7E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CScannerManager;

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	virtual void ActivateFrame(int nCmdShow = -1);
	//}}AFX_VIRTUAL

// Implementation
public:
	bool IsScannerActive();
	void UpdateCoordStatus(const CString& strX, const CString& strY);
	void InitSequence();
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
//	bool m_bInitialScanning;
	CScannerManager* m_pScannerManager;
	bool m_bActivated;
	//{{AFX_MSG(CMainFrame)
	afx_msg void OnScannerClosed(UINT wParam, LONG lParam);
	afx_msg void OnImageScanned(UINT wParam, LONG lParam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnUpdateScannerImport(CCmdUI* pCmdUI);
	afx_msg void OnUpdateScannerSelectsource(CCmdUI* pCmdUI);
	afx_msg void OnScannerSelectsource();
	afx_msg void OnScannerImport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__D5DFF631_8656_421F_9282_A81EB5A3D7E6__INCLUDED_)
