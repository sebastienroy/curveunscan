// ScannerManager.cpp : implementation file
//

#include "stdafx.h"
#include "CurveUnscan.h"
#include "ScannerManager.h"
#include "Utilities/VersionInfo.h"
#include "SettingsManagement/SettingsDefs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScannerManager dialog


CScannerManager::CScannerManager(SVersionInfo &version,CWnd* pParent /*=NULL*/)
:	CDialog(CScannerManager::IDD, pParent),
	m_CurveUnscanVersion(version),
	m_pMainFrame(pParent),
	m_bIsScanning(false)
{
	//{{AFX_DATA_INIT(CScannerManager)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

}


void CScannerManager::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScannerManager)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScannerManager, CDialog)
	//{{AFX_MSG_MAP(CScannerManager)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScannerManager message handlers

// Parameters given to the scanner window
void CScannerManager::GetIdentity()
{
	CTwain::GetIdentity();	// default settings

	m_AppId.Version.MajorNum=m_CurveUnscanVersion.m_nMajorVersion;
	m_AppId.Version.MinorNum=m_CurveUnscanVersion.m_nMinorVersion;
	strcpy (m_AppId.Manufacturer, m_CurveUnscanVersion.m_strManufacturer);
	strcpy (m_AppId.ProductFamily, m_CurveUnscanVersion.m_strAppName);
	strcpy (m_AppId.ProductName, m_CurveUnscanVersion.m_strAppName);
	strcpy (m_AppId.Version.Info, m_CurveUnscanVersion.m_strInfo);
	// language
	LanguageType language=(LanguageType)m_CurveUnscanVersion.m_nLanguage;
	TW_UINT16 tLang;
	switch(language)
	{
	case kEnglish:
		tLang=TWCY_USA;
		break;
	case kFrench:
		tLang=TWCY_FRANCE;
		break;
	default:
		tLang=TWCY_USA;
	}
	m_AppId.Version.Language = tLang;
	m_AppId.Version.Country = tLang;

}

BOOL CScannerManager::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if( ProcessMessage(*pMsg) )
	{
		return TRUE;//TWAIN message processed
	}

        // normal windows messages processed
		
	return CDialog::PreTranslateMessage(pMsg);
}

// called when scanning finished
void CScannerManager::CopyImage(HANDLE hBitmap, TW_IMAGEINFO &info)
{
	m_pMainFrame->SendMessage(WM_IMAGE_SCANNED,(WPARAM)hBitmap,(LPARAM)info.BitsPerPixel);
	CloseDS();
}

BOOL CScannerManager::IsReady()
{
	return ( !m_bIsScanning)&&(SourceSelected());
}

void CScannerManager::CloseDS()
{
	CTwain::CloseDS();
	m_pMainFrame->SendMessage(WM_SCANNER_CLOSED,0,0);
	m_bIsScanning=false;
}

BOOL CScannerManager::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitTwain(m_hWnd);
	SelectDefaultSource();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CScannerManager::LaunchImport()
{
	m_bIsScanning=Acquire(1);
	return m_bIsScanning;
}

bool CScannerManager::IsScanning()
{
	return m_bIsScanning;
}
