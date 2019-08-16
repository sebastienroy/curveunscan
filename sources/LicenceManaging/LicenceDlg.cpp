// LicenceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "licencemanaging.h"
#include "LicenceDlg.h"
#include "HtmlHelp.h"
#include "..\main\resource.h"
#include "LicenceManager.h"
#include "StringInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLicenceDlg dialog


CLicenceDlg::CLicenceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLicenceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLicenceDlg)
	m_strLicence = _T("");
	m_strCompanyName = _T("");
	m_strName = _T("");
	//}}AFX_DATA_INIT
}


void CLicenceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLicenceDlg)
	DDX_Text(pDX, IDC_EDIT_LICENCEKEY, m_strLicence);
	DDV_MaxChars(pDX, m_strLicence, 256);
	DDX_Text(pDX, IDC_EDIT_COMPANYNAME, m_strCompanyName);
	DDV_MaxChars(pDX, m_strCompanyName, 256);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 256);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLicenceDlg, CDialog)
	//{{AFX_MSG_MAP(CLicenceDlg)
	ON_BN_CLICKED(IDC_OPEN_FORM_BUTTON, OnOpenFormButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLicenceDlg message handlers

void CLicenceDlg::OnOK() 
{
	// TODO: Add extra validation here

	// to do : check not empty fields
	CStringInterface *pStrInt=CStringInterface::GetInstance();
	UpdateData(TRUE);
	if(""==m_strName)
		{
		CString msg;
		msg.LoadString(pStrInt->GetStringID(CStringInterface::kNameFieldEmpty));
		MessageBox(msg);
		return;
		}
	if(""==m_strLicence)
		{
		CString msg;
		msg.LoadString(pStrInt->GetStringID(CStringInterface::kLicenceKeyEmpty));
		MessageBox(msg);
		return;
		}
	
	CDialog::OnOK();
}

void CLicenceDlg::OnOpenFormButton() 
{
	// TODO: Add your control notification handler code here
	CWinApp* theApp=AfxGetApp();
	CString helpPath=theApp->m_pszHelpFilePath;
	helpPath+=">FormWindow";
	HtmlHelp(GetSafeHwnd(),helpPath, HH_DISPLAY_TOPIC, (unsigned long)"html/form.htm");	
}
