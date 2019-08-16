// CodeGenerationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CodeGeneration.h"
#include "CodeGenerationDlg.h"
#include "UnscanException.h"

#include "../Utilities/IniAccess.h"
#include "../Utilities/tokenizer.h"

#include <list>
#include <vector>
#include <fstream>
using namespace std;

#include "..\LicenceManaging\Coder.h"
#include <md5/md5checksum.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCodeGenerationDlg dialog

CCodeGenerationDlg::CCodeGenerationDlg(CString strCodeKey, CWnd* pParent /*=NULL*/)
	: CDialog(CCodeGenerationDlg::IDD, pParent),
	m_strCodeKey(strCodeKey)
{
	//{{AFX_DATA_INIT(CCodeGenerationDlg)
	m_String = _T("");
	m_StrCompany = _T("");
	m_StrName = _T("");
	m_StrRegistration = _T("");
	m_strChecksum = _T("");
	m_strFilename = _T("");
	m_strExtension = _T("chk");
	m_nLanguage = 0;
	m_strLicenceText = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
//	m_pCoder=new CCoder;
}

void CCodeGenerationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCodeGenerationDlg)
	DDX_Control(pDX, IDC_COMBO_VERSIONS, m_Version_ComboBox);
	DDX_Text(pDX, IDC_EDIT_STRING, m_String);
	DDX_Text(pDX, IDC_EDIT_COMPANY, m_StrCompany);
	DDX_Text(pDX, IDC_EDIT_NAME, m_StrName);
	DDX_Text(pDX, IDC_EDIT_REGISTRATION, m_StrRegistration);
	DDX_Text(pDX, IDC_EDIT_CHECKSUM, m_strChecksum);
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_strFilename);
	DDX_Text(pDX, IDC_EDIT_EXTENSION, m_strExtension);
	DDX_Radio(pDX, IDC_RADIO_LANGUAGE_ENG, m_nLanguage);
	DDX_Text(pDX, IDC_EDIT_LICENCE_TEXT, m_strLicenceText);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCodeGenerationDlg, CDialog)
	//{{AFX_MSG_MAP(CCodeGenerationDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DECODE, OnDecode)
	ON_BN_CLICKED(IDC_BUTTON_ENCODE, OnEncode)
	ON_BN_CLICKED(IDC_BUTTON_CHECK, OnButtonCheckRegistration)
	ON_BN_CLICKED(IDC_BUTTON_REGISTRATION, OnButtonGetRegistration)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSEFILE, OnButtonChoosefile)
	ON_BN_CLICKED(IDC_BUTTON_GENERATE, OnButtonGenerate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCodeGenerationDlg message handlers

BOOL CCodeGenerationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	FillComboBox();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCodeGenerationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCodeGenerationDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCodeGenerationDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCodeGenerationDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
//	delete m_pCoder;
	CDialog::PostNcDestroy();
}

void CCodeGenerationDlg::OnDecode() 
{
	// TODO: Add your control notification handler code here
UpdateData(TRUE);
//CString decoded=m_pCoder->DecodeString(m_String);
CString decoded;
try
	{
	decoded=GetCoderInstance()->getDecodedString(m_String,GetCoderInstance()->getCodeKey());
	m_String=decoded;
	}
catch(CUnscanException& err)
	{
	AfxMessageBox(err.GetMessage());
	}
catch(...)
	{
	AfxMessageBox("An error occured.");
	}
UpdateData(FALSE);	

}

void CCodeGenerationDlg::OnEncode() 
{
UpdateData(TRUE);
CString coded;
try
	{
	coded=GetCoderInstance()->getCodedString(m_String,GetCoderInstance()->getCodeKey());
	m_String=coded;
	}
catch(CUnscanException& err)
	{
	AfxMessageBox(err.GetMessage());
	}
UpdateData(FALSE);
}

void CCodeGenerationDlg::OnButtonCheckRegistration() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString strSerial;
	m_Version_ComboBox.GetWindowText(strSerial);
	CString strKey=GetCoderInstance()->Strip(m_StrRegistration);
	CString strMD5CodedKey=CMD5Checksum::GetMD5((BYTE*)(LPCSTR)m_StrRegistration,m_StrRegistration.GetLength());
	bool isCorrect=GetCoderInstance()->isRegistrationCodeCorrect(strSerial,m_StrName,m_StrCompany,strMD5CodedKey);
	CString result=isCorrect?"The code is correct":"The code is not correct";
	AfxMessageBox(result);
}

void CCodeGenerationDlg::OnButtonGetRegistration() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString strSerial;
	m_Version_ComboBox.GetWindowText(strSerial);
	m_StrRegistration=GetCoderInstance()->getRegistrationNumber(strSerial,m_StrName,m_StrCompany);
	fillLicenceText();
	UpdateData(FALSE);
	
	// test
//	CString strTest;
//	strTest=IniAccess::GetString("Section","entree","defaut","c:\\test.ini");
}

void CCodeGenerationDlg::OnButtonChoosefile() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE);
	if(dlg.DoModal()!=IDOK)
	{
		return;
	}
	m_strFilename=dlg.GetPathName();
	m_strChecksum=GetCoderInstance()->GetCheckSumValue(m_strFilename);
	UpdateData(FALSE);

}

void CCodeGenerationDlg::OnButtonGenerate() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(m_strFilename.IsEmpty())
	{
		MessageBox("You must choose a file!");
		return;
	}
	m_strChecksum=GetCoderInstance()->GetCheckSumValue(m_strFilename);

	CString strChkFile=m_strFilename;
	int nPointPos=strChkFile.ReverseFind('.');
	if(nPointPos>0)
	{
		strChkFile=strChkFile.Left(nPointPos);
	}
	strChkFile+=CString(".")+m_strExtension;

	try
	{
		ofstream chkFile(strChkFile);
		chkFile << (LPCSTR)m_strChecksum;
	}
	catch(...)
	{
		MessageBox("Error while trying to create check file!");
		return;
	}
}

CCoder* CCodeGenerationDlg::GetCoderInstance()
{
	CString strSerial;
	m_Version_ComboBox.GetWindowText(strSerial);
	if(m_V1Serials.find(strSerial)!=m_V1Serials.end())
	{
		return CCoder::GetInstanceV1(m_strCodeKey);
	}
	else if(m_V2Serials.find(strSerial)!=m_V2Serials.end())
	{
		return CCoder::GetInstanceV2(m_strCodeKey);
	}
	else
	{
		CString msg=CString("Warning : unknown version \"");
		msg+=strSerial;
		msg+="\". V2 Coder is assumed.";
		AfxMessageBox(msg);
		return CCoder::GetInstanceV2(m_strCodeKey);
	}
}

void CCodeGenerationDlg::FillComboBox()
{
	const CString strSection=CString("coderversion");
	const CString strV1Entry=CString("v1");
	const CString strV2Entry=CString("v2");

	//	check inifile
	list<CString> sections;
	CString strV1versions=IniAccess::GetString(strSection,strV1Entry,"",".\\versions.ini");
	CString strV2versions=IniAccess::GetString(strSection,strV2Entry,"",".\\versions.ini");

	m_Version_ComboBox.ResetContent();

	if( (strV1versions.IsEmpty())&&(strV2versions.IsEmpty()))
	{
		ShowUsage();
		FillDefaultComboBox();
		return;
	}
	CTokenizer token1(strV1versions);
	CString strVersion1;
	while(!(strVersion1=token1(",")).IsEmpty())
	{
		m_V1Serials.insert(strVersion1);
		m_Version_ComboBox.AddString(strVersion1);
	}

	CTokenizer token2(strV2versions);
	CString strVersion2;
	while(!(strVersion2=token2(",")).IsEmpty())
	{
		m_V2Serials.insert(strVersion2);
		m_Version_ComboBox.AddString(strVersion2);
	}

	if(m_Version_ComboBox.GetCount()>0)
	{
		m_Version_ComboBox.SetCurSel(m_Version_ComboBox.GetCount()-1);
	}
	


}

void CCodeGenerationDlg::FillDefaultComboBox()
{
	
}

void CCodeGenerationDlg::ShowUsage()
{

}

void CCodeGenerationDlg::fillLicenceText()
{

	CString strText;
	if(0==m_nLanguage)
	{
		strText="Name:\r\n%s\r\n\r\nCompany name:\r\n%s\r\n\r\nLicence key:\r\n%s\r\n\r\n";
	}
	else
	{
		strText="Nom:\r\n%s\r\n\r\nEntreprise:\r\n%s\r\n\r\nClé:\r\n%s\r\n\r\n";
	}

	m_strLicenceText.Format((LPCSTR)strText,(LPCSTR)m_StrName,(LPCSTR)m_StrCompany,m_StrRegistration);
}
