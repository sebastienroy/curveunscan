// CurveUnscan.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CurveUnscan.h"

#include "MainFrm.h"
#include "UnscanDoc.h"
#include "UnscanView.h"
#include "LicenceManaging/LicenceManager.h"
#include "LicenceManaging/IntegrityCheck.h"
#include "SettingsManagement/SettingsManager.h"
#include "SettingsManagement/SettingsDefs.h"

#include <Utilities/Tools.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUnscanApp

BEGIN_MESSAGE_MAP(CUnscanApp, CWinApp)
	//{{AFX_MSG_MAP(CUnscanApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_VIEW_OPTIONS, OnViewOptions)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUnscanApp construction

CUnscanApp::CUnscanApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CUnscanApp object

CUnscanApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CUnscanApp initialization

BOOL CUnscanApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	// resource language specification
	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("SquarePoint Software"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	CSettingsManager *pSettings=CSettingsManager::GetInstance();
	ASSERT(NULL!=pSettings);

	HINSTANCE hResource=LoadLibrary(pSettings->GetResourceDllName());
	if(NULL!=hResource)
	{
		AfxSetResourceHandle(hResource);
	}

	//--- Check program integrity
	CIntegrityCheck* chk=CIntegrityCheck::Init(__targv[0]);
	if(!chk->IsInstallOk())
	{
		return FALSE;
	}
	chk->LaunchCheck();

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif


	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CUnscanDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CUnscanView));
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Modify WinHelp file name in order to use HTMLHelp
	try
	{
		CString helpFileName=CString(m_pszHelpFilePath);
		free((void*)m_pszHelpFilePath);
		helpFileName=CTools::GetFullDirFromPath(helpFileName);

		LanguageType language=pSettings->GetCurrentLanguage();
		switch(language)
		{
		case kFrench:
			helpFileName+="CurveUnscan.chm";
			break;
		case kEnglish:
		default:
			helpFileName+="CurveUnscanUs.chm";
		}
		m_pszHelpFilePath = _tcsdup(helpFileName);

	}
	catch(...)
	{
	}

	CLicenceManager& mngr=CLicenceManager::GetInstance();
	RegistrationStateEnum licenceState=mngr.CheckLicence();
	// achtung the check in the end of the method should be complient with the following
	if((kNoRight==licenceState)||(kInstallPb==licenceState))
	{
		return FALSE;
	}

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(/*SW_SHOW|*/SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();

	CMainFrame* pMainFrame=static_cast<CMainFrame*>(m_pMainWnd);
	pMainFrame->InitSequence();
	
	// should return TRUE (a further licence test)
	return ((kRegistered==licenceState)||(kUnderEvaluation==licenceState));
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	bool m_bRegistered;
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_strID;
	CString m_strBuildNb;
	CString	m_strRegistered;
	CString	m_strName;
	CString	m_strCompName;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void Update();
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRegisterButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_strID = _T("");
	m_strBuildNb = _T("");
	m_strRegistered = _T("");
	m_strName = _T("");
	m_strCompName = _T("");
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_STATIC_PRODID, m_strID);
	DDV_MaxChars(pDX, m_strID, 255);
	DDX_Text(pDX, IDC_STATIC_REGISTERED, m_strRegistered);
	DDX_Text(pDX, IDC_STATIC_LICENCEDNAME, m_strName);
	DDX_Text(pDX, IDC_STATIC_LICENCEDCOMPNAME, m_strCompName);
	DDX_Text(pDX, IDC_STATIC_BUILD_NB, m_strBuildNb);

	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_REGISTER_BUTTON, OnRegisterButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CUnscanApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
//	aboutDlg.m_strID="Product ID : ";
	aboutDlg.m_strID.LoadString(IDS_PRODUCTID);
	aboutDlg.m_strID+=CLicenceManager::GetInstance().GetProductID();
	bool bRegistered=CLicenceManager::GetInstance().IsRegistered();
	aboutDlg.m_strBuildNb=CLicenceManager::GetInstance().GetStrBuildNb();
	aboutDlg.m_bRegistered=bRegistered;
	if(bRegistered)
		{
//		aboutDlg.m_strRegistered="This product is licenced to :";
		aboutDlg.m_strRegistered.LoadString(IDS_PRODUCT_LICENCED);
		aboutDlg.m_strName=CLicenceManager::GetInstance().GetName();
		aboutDlg.m_strCompName=CLicenceManager::GetInstance().GetCompanyName();
		}
	else
		{
//		aboutDlg.m_strRegistered="This copy is unregistered";
		aboutDlg.m_strRegistered.LoadString(IDS_PRODUCT_UNREGISTERED);
		aboutDlg.m_strName="";
		aboutDlg.m_strCompName="";
		}
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CUnscanApp message handlers


BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	Update();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAboutDlg::OnRegisterButton() 
{
	// TODO: Add your control notification handler code here
	bool registered=CLicenceManager::GetInstance().Register();
	if(registered)
	{
		Update();
		UpdateData(FALSE);
		CWnd* pOkButton=GetDlgItem(IDOK);
		pOkButton->SetFocus();
	}
}

void CAboutDlg::Update()
{
	// Version label
	CWnd *pVersionLabel=GetDlgItem(IDC_STATIC_VERSION);
	CString strLabel;
	pVersionLabel->GetWindowText(strLabel);
	CString strVersion=CLicenceManager::GetInstance().GetVersion();
	CString strFullVersion;
	strFullVersion.Format((LPCSTR)strLabel,(LPCSTR)strVersion);
	pVersionLabel->SetWindowText(strFullVersion);

	m_strID.LoadString(IDS_PRODUCTID);
	m_strID+=CLicenceManager::GetInstance().GetProductID();
	m_bRegistered=CLicenceManager::GetInstance().IsRegistered();

	CWnd* pRegisterButton=GetDlgItem(IDC_REGISTER_BUTTON);

	if(m_bRegistered)
	{
		pRegisterButton->ModifyStyle(WS_VISIBLE,0);
		pRegisterButton->EnableWindow(FALSE);
		m_strRegistered.LoadString(IDS_PRODUCT_LICENCED);
		m_strName=CLicenceManager::GetInstance().GetName();
		m_strCompName=CLicenceManager::GetInstance().GetCompanyName();
	}
	else
	{
		pRegisterButton->ModifyStyle(0,WS_VISIBLE);
		m_strRegistered.LoadString(IDS_PRODUCT_UNREGISTERED);
		m_strName="";
		m_strCompName="";
	}
	RedrawWindow();

}

int CUnscanApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	CSettingsManager::DeleteInstance();
	CIntegrityCheck::Clear();
	CStringInterface::Clear();
	
	return CWinApp::ExitInstance();
}

void CUnscanApp::OnViewOptions() 
{
	// TODO: Add your command handler code here
	CSettingsManager *pManager=CSettingsManager::GetInstance();
	pManager->ShowOptions();
}

void CUnscanApp::OnFileOpen() 
{
	// TODO: Add your command handler code here

	// get doc template
	CDocTemplate *pDocTemplate=NULL;
	CUnscanDoc *pDoc=NULL;
	POSITION templatePos=GetFirstDocTemplatePosition();
	if(NULL!=templatePos)
	{
		pDocTemplate=GetNextDocTemplate(templatePos);

		// get document
		POSITION docPos=pDocTemplate->GetFirstDocPosition();
		if(NULL!=docPos)
		{
			pDoc=static_cast<CUnscanDoc*>(pDocTemplate->GetNextDoc(docPos));
		}
	}
	
	if(NULL!=pDoc)
	{
	}


	CWinApp::OnFileOpen();
}
