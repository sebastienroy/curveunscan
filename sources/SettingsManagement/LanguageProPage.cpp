// LanguageProPage.cpp : implementation file
//

#include "stdafx.h"
#include "settingsmanagement.h"
#include "LanguageProPage.h"

#include <list>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLanguageProPage property page

IMPLEMENT_DYNCREATE(CLanguageProPage, CPropertyPage)

CLanguageProPage::CLanguageProPage() 
: CPropertyPage(CLanguageProPage::IDD)
{
}

CLanguageProPage::CLanguageProPage(int nDefault,const list<CString> &languageList) 
:	CPropertyPage(CLanguageProPage::IDD),
	m_nInitialLanguage(nDefault),
	m_languageList(languageList)
{
	//{{AFX_DATA_INIT(CLanguageProPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

}

CLanguageProPage::~CLanguageProPage()
{
}

void CLanguageProPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLanguageProPage)
	DDX_Control(pDX, IDC_LANG_COMBO, m_LanguageCombo);
	//}}AFX_DATA_MAP

	m_nSelectedLanguage=m_LanguageCombo.GetCurSel();
}


BEGIN_MESSAGE_MAP(CLanguageProPage, CPropertyPage)
	//{{AFX_MSG_MAP(CLanguageProPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLanguageProPage message handlers

int CLanguageProPage::GetSelectedLanguage() const
{
	return m_nSelectedLanguage;
}

BOOL CLanguageProPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	for(list<CString>::const_iterator iter=m_languageList.begin();iter!=m_languageList.end();iter++)
	{
		CString strLanguage=*iter;
		m_LanguageCombo.AddString(strLanguage);
	}
	m_LanguageCombo.SetCurSel(m_nInitialLanguage);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
