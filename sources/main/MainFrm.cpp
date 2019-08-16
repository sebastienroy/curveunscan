// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "HtmlHelp.h"
#include "CurveUnscan.h"
#include "MainFrm.h"
#include "UnscanDoc.h"
#include "UnscanView.h"
#include "CompleteSequence.h"
#include "ScannerManager.h"

#include <HelpSystem/HelpFunctions.h>
#include <LicenceManaging/LicenceManager.h>
#include <Utilities/VersionInfo.h>
#include <SettingsManagement/SettingsManager.h>
#include <SettingsManagement/SettingsDefs.h>

#include <Dm/BmpManager.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_HELPINFO()
	ON_UPDATE_COMMAND_UI(ID_SCANNER_IMPORT, OnUpdateScannerImport)
	ON_UPDATE_COMMAND_UI(ID_SCANNER_SELECTSOURCE, OnUpdateScannerSelectsource)
	ON_COMMAND(ID_SCANNER_SELECTSOURCE, OnScannerSelectsource)
	ON_COMMAND(ID_SCANNER_IMPORT, OnScannerImport)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)

	ON_MESSAGE(WM_IMAGE_SCANNED,OnImageScanned)
	ON_MESSAGE(WM_SCANNER_CLOSED,OnScannerClosed)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_XLABEL,			// "X="
	ID_INDICATOR_XVALUE,			// X value
	ID_INDICATOR_YLABEL,			// "Y="
	ID_INDICATOR_YVALUE			// Y value
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
:	m_pScannerManager(NULL)
{
	// TODO: add member initialization code here
	m_bActivated=false;
//	m_bInitialScanning=false;
}

CMainFrame::~CMainFrame()
{
	m_pScannerManager->DestroyWindow();
	delete m_pScannerManager;

	CLicenceManager::Destroy();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}


	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	// Find the width of a character
	int fontWidth=5;
	CFont* pFont;
	if(NULL!=(pFont=m_wndStatusBar.GetFont()))
	{
		LOGFONT logFont;
		pFont->GetLogFont(&logFont);
		if(0!=logFont.lfWidth)
		{
			fontWidth=logFont.lfWidth;
		}
	}
	// set values
	m_wndStatusBar.SetPaneInfo(1,ID_INDICATOR_XLABEL,SBPS_NOBORDERS,fontWidth*4);
	m_wndStatusBar.SetPaneInfo(2,ID_INDICATOR_XVALUE,SBPS_NORMAL,fontWidth*15);
	m_wndStatusBar.SetPaneInfo(3,ID_INDICATOR_YLABEL,SBPS_NOBORDERS,fontWidth*4);
	m_wndStatusBar.SetPaneInfo(4,ID_INDICATOR_YVALUE,SBPS_NORMAL,fontWidth*15);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	// Scanner Manager
	SVersionInfo version;
	CLicenceManager::FillVersionInfo(version);
	version.m_nLanguage=(int)CSettingsManager::GetInstance()->GetCurrentLanguage();
	m_pScannerManager=new CScannerManager(version,this);
	m_pScannerManager->Create(IDD_SCANNER);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	UINT style=cs.style;
	style=style|CS_OWNDC;
	cs.style=style;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers



void CMainFrame::WinHelp(DWORD dwData, UINT nCmd) 
{
	// TODO: Add your specialized code here and/or call the base class

	CWinApp* theApp=AfxGetApp();
	CString helpPath=theApp->m_pszHelpFilePath;
//	HtmlHelp(m_hWnd,helpPath,HH_DISPLAY_TOPIC,dwData);
//	HtmlHelp(m_hWnd,helpPath, HH_HELP_CONTEXT, nCmd==HELP_CONTEXT? dwData : 0);
	CHelpFunctions::OpenTopic(m_hWnd,dwData);
	
//	CFrameWnd::WinHelp(dwData, nCmd);
}

BOOL CMainFrame::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	return TRUE;
//	return CFrameWnd::OnHelpInfo(pHelpInfo);
}

// Called by the application after the initialization of the frame
void CMainFrame::InitSequence()
{
	
	CUnscanDoc* pDoc=static_cast<CUnscanDoc*>(GetActiveDocument());
	// don't start initial sequence if a document have been opened 
	// (document opened from command line)
	if(pDoc->GetBmpManager()->IsBmpOpened())
	{
		return;
	}

	// what kind of job should we start?
	CSettingsManager *settingsManager=CSettingsManager::GetInstance();
	if(NULL==settingsManager)
	{
		return;
	}

	POSITION pos=pDoc->GetFirstViewPosition();
	CUnscanView* pView=static_cast<CUnscanView*>(pDoc->GetNextView(pos));

	StartingJobType job=settingsManager->GetStartingJob();
	switch(job)
	{
	case kOpenBitmap:
		pDoc->InitialOpenBitmap();
		break;
	case kScanning:
		if( (NULL==m_pScannerManager)
			|| (!m_pScannerManager->IsReady()) )
		{
			AfxMessageBox(IDS_NO_SCANNER_AVAILABLE,MB_OK|MB_ICONEXCLAMATION);
			return;
		}
		m_pScannerManager->LaunchImport();
		break;
	default:
		break;	// do nothing
	}


}


void CMainFrame::ActivateFrame(int nCmdShow) 
{
	// TODO: Add your specialized code here and/or call the base class

    if (!m_bActivated) 
    {
        m_bActivated = true;
        nCmdShow = SW_SHOWMAXIMIZED;
    }
	
	CFrameWnd::ActivateFrame(nCmdShow);
}

void CMainFrame::UpdateCoordStatus(const CString &strX, const CString &strY)
{
	m_wndStatusBar.SetPaneText(2,strX,TRUE);
	m_wndStatusBar.SetPaneText(4,strY,TRUE);
}

void CMainFrame::OnUpdateScannerImport(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CUnscanView* pView=static_cast<CUnscanView*>(GetActiveView());
	BOOL bCanBeActivated=( (NULL!=pView)
							&& (!pView->IsDialogOn()) 
							&& (NULL!=m_pScannerManager)
							&& (m_pScannerManager->IsReady()) );

	pCmdUI->Enable(bCanBeActivated);	
}

void CMainFrame::OnUpdateScannerSelectsource(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CUnscanView* pView=static_cast<CUnscanView*>(GetActiveView());
	BOOL bCanBeActivated=( (NULL!=pView)
							&& (!pView->IsDialogOn()) 
							&& (NULL!=m_pScannerManager)
							&& (m_pScannerManager->IsReady()) );

	pCmdUI->Enable(bCanBeActivated);	
}

void CMainFrame::OnScannerSelectsource() 
{
	// TODO: Add your command handler code here
	if(NULL!=m_pScannerManager)
	{
		m_pScannerManager->SelectSource();
	}

}

void CMainFrame::OnScannerImport() 
{
	// TODO: Add your command handler code here
	CUnscanView* pView=static_cast<CUnscanView*>(GetActiveView());
	CUnscanDoc* pDoc=static_cast<CUnscanDoc*>(pView->GetDocument());
	// ask to save
	if(!pDoc->AskToSave())
		{
		return;
		}

	
	pDoc->DeleteContents();
	pView->OnInitialUpdate();
	m_pScannerManager->LaunchImport();
}

bool CMainFrame::IsScannerActive()
{
	if(NULL!=m_pScannerManager)
	{
		return m_pScannerManager->IsScanning();
	}
	else
	{
		return false;
	}
}

// Message envoyé par le scanner manager -> redispatcher au document
void CMainFrame::OnImageScanned(UINT wParam, LONG lParam)
{
	HANDLE &hBmp=(HANDLE&)wParam;
	int nBitsPerPixel=(int)lParam;

	CUnscanView* pView=static_cast<CUnscanView*>(GetActiveView());
	CUnscanDoc* pDoc=static_cast<CUnscanDoc*>(pView->GetDocument());

	pDoc->SetScannedImage(hBmp,nBitsPerPixel);

	if((pDoc->GetBmpManager())->IsBmpOpened())
	{
		pView->StartInitialSequence();
	}	
}

void CMainFrame::OnScannerClosed(UINT wParam, LONG lParam)
{
//	m_bInitialScanning=false; // can be end of scanning or scanning canceled
}
