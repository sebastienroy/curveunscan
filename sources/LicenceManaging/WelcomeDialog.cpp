// WelcomeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "licencemanaging.h"
#include "WelcomeDialog.h"
#include "../main/resource.h"

#include "StringInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWelcomeDialog dialog


CWelcomeDialog::CWelcomeDialog(int nDay,
							   CString strProductID,
							   int ntotalExportNb,
							   int nExportLeft,
							   CWnd* pParent /*=NULL*/)
	: CDialog(CWelcomeDialog::IDD, pParent),
	m_nDay(nDay),
	m_nTotalExportNb(ntotalExportNb),
	m_nExportLeft(nExportLeft)
{
	//{{AFX_DATA_INIT(CWelcomeDialog)
	m_WelcomeString = _T("");
	m_strProductID = _T("");
	//}}AFX_DATA_INIT

	m_strProductID.LoadString(IDS_PRODUCTID);
	m_strProductID+=strProductID;
}


void CWelcomeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWelcomeDialog)
	DDX_Text(pDX, IDC_WELCOME_STATIC_TEXT, m_WelcomeString);
	DDV_MaxChars(pDX, m_WelcomeString, 256);
	DDX_Text(pDX, IDC_STATIC_PRODUCTID, m_strProductID);
	DDV_MaxChars(pDX, m_strProductID, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWelcomeDialog, CDialog)
	//{{AFX_MSG_MAP(CWelcomeDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWelcomeDialog message handlers

BOOL CWelcomeDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	//--- Number of days
	CStringInterface::LicenseStringEnum nPostfixID=CStringInterface::kPostFixIdN;
//	int nPostfixID;
	switch(m_nDay)
		{
		case 1:
			nPostfixID=CStringInterface::kPostFixId1;
			break;
		case 2:
			nPostfixID=CStringInterface::kPostFixId2;
			break;
		case 3:
			nPostfixID=CStringInterface::kPostFixId3;
			break;
		default:
			nPostfixID=CStringInterface::kPostFixIdN;
			break;
		}
	CString postFix;
	postFix.LoadString(CStringInterface::GetInstance()->GetStringID(nPostfixID));
	CString strFormat;
	strFormat.LoadString(GET_STRING_ID(kWelcomeFormat));
	m_WelcomeString.Format(strFormat,m_nDay,postFix);

	//--- Number of exports
	CString strNewText;
	// total nb
	CWnd *pWnd=GetDlgItem(IDC_STATIC_EXPORT_NB);
	CString strExportFormat;
	pWnd->GetWindowText(strExportFormat);
	strNewText.Format(strExportFormat,m_nTotalExportNb);
	pWnd->SetWindowText(strNewText);
	// nb left
	pWnd=GetDlgItem(IDC_STATIC_EXPORT_LEFT);
	pWnd->GetWindowText(strExportFormat);
	strNewText.Format(strExportFormat,m_nExportLeft);
	pWnd->SetWindowText(strNewText);

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
