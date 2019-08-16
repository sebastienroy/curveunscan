// PromptProPage.cpp : implementation file
//

#include "stdafx.h"
#include "settingsmanagement.h"
#include "PromptProPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPromptProPage property page

IMPLEMENT_DYNCREATE(CPromptProPage, CPropertyPage)

CPromptProPage::CPromptProPage() : CPropertyPage(CPromptProPage::IDD)
{
	//{{AFX_DATA_INIT(CPromptProPage)
	m_nPromptExport = -1;
	m_nHowToStart = -1;
	//}}AFX_DATA_INIT
}

CPromptProPage::~CPromptProPage()
{
}

void CPromptProPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPromptProPage)
	DDX_Radio(pDX, IDC_RADIO_EXPORT_NOPROMPT, m_nPromptExport);
	DDX_Radio(pDX, IDC_RADIO_START_OPENGRAPHIC, m_nHowToStart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPromptProPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPromptProPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPromptProPage message handlers
