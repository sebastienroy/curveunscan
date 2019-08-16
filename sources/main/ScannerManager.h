#if !defined(AFX_SCANNERMANAGER_H__DB984075_B3D6_49EA_B60D_B0DCFE50DA5F__INCLUDED_)
#define AFX_SCANNERMANAGER_H__DB984075_B3D6_49EA_B60D_B0DCFE50DA5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScannerManager.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScannerManager dialog

#include "Utilities/TwainCpp.h"
#include "Utilities/VersionInfo.h"


class CScannerManager : public CDialog, public CTwain
{
// Construction
public:
	bool IsScanning();
	BOOL LaunchImport();
	BOOL IsReady();
	virtual void GetIdentity();
	CScannerManager(SVersionInfo &version, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScannerManager)
	enum { IDD = IDD_SCANNER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScannerManager)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	SVersionInfo m_CurveUnscanVersion;
	virtual void CloseDS();
	CWnd* m_pMainFrame;
	bool m_bIsScanning;
	virtual void CopyImage(HANDLE hBitmap, TW_IMAGEINFO &info);

	// Generated message map functions
	//{{AFX_MSG(CScannerManager)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCANNERMANAGER_H__DB984075_B3D6_49EA_B60D_B0DCFE50DA5F__INCLUDED_)
