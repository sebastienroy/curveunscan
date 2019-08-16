// ExportProPage.cpp : implementation file
//

#include "stdafx.h"
#include "settingsmanagement.h"
#include "ExportProPage.h"
#include "../Utilities/RegularExpressions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExportProPage property page

IMPLEMENT_DYNCREATE(CExportProPage, CPropertyPage)

CExportProPage::CExportProPage() 
:	CPropertyPage(CExportProPage::IDD),
	m_cSeparator('\t')
{
	//{{AFX_DATA_INIT(CExportProPage)
	m_nSepRadio = 0;
	m_strOtherSeparator = _T("");
	m_strExtension = _T("");
	//}}AFX_DATA_INIT

}

CExportProPage::~CExportProPage()
{
}

void CExportProPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExportProPage)
	DDX_Radio(pDX, IDC_RADIO_SETT_SEP_TAB, m_nSepRadio);
	DDX_Text(pDX, IDC_EDIT_SETT_SEP_OTHER, m_strOtherSeparator);
	DDV_MaxChars(pDX, m_strOtherSeparator, 1);
	DDX_Text(pDX, IDC_EDIT_SETT_FILEEXTENSION, m_strExtension);
	DDV_MaxChars(pDX, m_strExtension, 3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExportProPage, CPropertyPage)
	//{{AFX_MSG_MAP(CExportProPage)
	ON_EN_CHANGE(IDC_EDIT_SETT_SEP_OTHER, OnChangeEditSettSepOther)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExportProPage message handlers

void CExportProPage::OnChangeEditSettSepOther() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_nSepRadio=4;
	UpdateData(FALSE);	
}

char CExportProPage::GetSeparator() const
{
	return m_cSeparator;
}

void CExportProPage::SetSeparator(char cSeparator)
{
	switch(cSeparator)
	{
	case '\t':
		m_nSepRadio=0;
		break;
	case ';':
		m_nSepRadio=1;
		break;
	case ',':
		m_nSepRadio=2;
		break;
	case ' ':
		m_nSepRadio=3;
		break;
	default:
		m_nSepRadio=4;
		m_strOtherSeparator=CString(cSeparator);
	}
}

BOOL CExportProPage::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	if(!UpdateData(TRUE))	// check that not more than one character in edit ctrl
	{
		return FALSE;
	}
	switch(m_nSepRadio)
	{
	case 0:
		m_cSeparator='\t';
		break;
	case 1:
		m_cSeparator=';';
		break;
	case 2:
		m_cSeparator=',';
		break;
	case 3:
		m_cSeparator=' ';
		break;
	case 4:
		if(m_strOtherSeparator.GetLength()<1)
		{
			AfxMessageBox(IDS_SETT_SEPARATOR_ISEMPTY,MB_OK|MB_ICONSTOP);
			CEdit *pEdit=static_cast<CEdit*>(GetDlgItem(IDC_EDIT_SETT_SEP_OTHER));
			pEdit->SetFocus();
			return FALSE;
		}
		m_cSeparator=m_strOtherSeparator[0];
		break;
	default:
		m_cSeparator='\t';
	}
	
	// check extension
	if(m_strExtension.GetLength()<1)
	{
		AfxMessageBox(IDS_SETT_EXTENSION_ISEMPTY,MB_OK|MB_ICONSTOP);
		CEdit *pEdit=static_cast<CEdit*>(GetDlgItem(IDC_EDIT_SETT_FILEEXTENSION));
		pEdit->SetFocus();
		return FALSE;
	}
	if(!RegIsMatching(m_strExtension,"^[a-zA-Z0-9]+$"))	// sizemax is controled by the edit field
	{
		AfxMessageBox(IDS_SETT_ALPHANUMERIC_EXTENSION,MB_OK|MB_ICONSTOP);
		CEdit *pEdit=static_cast<CEdit*>(GetDlgItem(IDC_EDIT_SETT_FILEEXTENSION));
		pEdit->SetFocus();
		pEdit->SetSel(0,-1);
		return FALSE;
	}	

	return CPropertyPage::OnKillActive();
}
