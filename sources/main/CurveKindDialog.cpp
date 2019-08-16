// CurveKindDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CurveKindDialog.h"
#include "CurveUnscan.h"
#include "Sequence.h"

#include "HelpSystem/HelpFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurveKindDialog dialog


CCurveKindDialog::CCurveKindDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCurveKindDialog::IDD, pParent)
	{
	//{{AFX_DATA_INIT(CCurveKindDialog)
	m_Kind = 0;
	//}}AFX_DATA_INIT
	}


CCurveKindDialog::CCurveKindDialog(CSequence *pSequence)
	: CDialog(CCurveKindDialog::IDD, NULL)
	{
	m_pSequence=pSequence;
	m_Kind=0;
	}

void CCurveKindDialog::DoDataExchange(CDataExchange* pDX)
	{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCurveKindDialog)
	DDX_Radio(pDX, IDC_RADIO_CONTINUOUS, m_Kind);
	//}}AFX_DATA_MAP
	}


BEGIN_MESSAGE_MAP(CCurveKindDialog, CDialog)
	//{{AFX_MSG_MAP(CCurveKindDialog)
	ON_BN_CLICKED(IDC_PREVIOUS, OnPrevious)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurveKindDialog message handlers

void CCurveKindDialog::OnOK() 
	{
	// TODO: Add extra validation here
	m_Next=+1;
	CRect rect;
	GetWindowRect(&rect);
	m_pSequence->SetActWndPosition(rect.TopLeft());
	CDialog::OnOK();
	}

void CCurveKindDialog::OnPrevious() 
	{
	// TODO: Add your control notification handler code here
	m_Next=-1;
	CRect rect;
	GetWindowRect(&rect);
	m_pSequence->SetActWndPosition(rect.TopLeft());
	CDialog::OnOK();	
	}

BOOL CCurveKindDialog::OnInitDialog() 
	{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CPoint position=m_pSequence->GetPrevWndPosition();
	CRect rect;
	GetWindowRect(&rect);
	MoveWindow(position.x,position.y,rect.Width(),rect.Height());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
	}

BOOL CCurveKindDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	CHelpFunctions::DisplayCtrlPopup(FromHandle((HWND)pHelpInfo->hItemHandle),
									pHelpInfo->MousePos,
									pHelpInfo->iCtrlId);
	return TRUE;
}
