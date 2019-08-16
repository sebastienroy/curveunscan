// SavePromptDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CurveUnscan.h"
#include "SavePromptDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSavePromptDlg dialog


CSavePromptDlg::CSavePromptDlg(CString strPrompt, CWnd* pParent /*=NULL*/)
	: CDialog(CSavePromptDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSavePromptDlg)
	m_strPrompt = _T("");
	m_nSaveKind = 0;
	//}}AFX_DATA_INIT

	m_strPrompt=strPrompt; 
}


void CSavePromptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSavePromptDlg)
	DDX_Text(pDX, IDC_STATIC_QUESTION, m_strPrompt);
	DDX_Radio(pDX, IDC_RADIO_SAVE_EXPORT, m_nSaveKind);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSavePromptDlg, CDialog)
	//{{AFX_MSG_MAP(CSavePromptDlg)
	ON_BN_CLICKED(IDYES, OnYes)
	ON_BN_CLICKED(IDNO, OnNo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSavePromptDlg message handlers


void CSavePromptDlg::OnYes() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	EndDialog(IDYES);
}

void CSavePromptDlg::OnNo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	EndDialog(IDNO);
}
