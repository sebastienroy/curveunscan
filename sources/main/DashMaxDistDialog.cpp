// DashMaxDistDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CurveUnscan.h"
#include "DashMaxDistDialog.h"
#include "GenesisDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDashMaxDistDialog dialog


CDashMaxDistDialog::CDashMaxDistDialog(CWnd* pParent /*=NULL*/,int nDashDist)
	: CDialog(CDashMaxDistDialog::IDD, pParent),
	  m_pGenesisDlg(static_cast<CGenesisDialog*>(pParent)),
	  m_nDashDist(nDashDist),
	  m_nInitialDist(nDashDist),
	  m_bChanged(false)
{
	//{{AFX_DATA_INIT(CDashMaxDistDialog)
//	m_nDashDist = 0;
	//}}AFX_DATA_INIT
}


void CDashMaxDistDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDashMaxDistDialog)
	DDX_Text(pDX, IDC_EDIT_DASHDIST, m_nDashDist);
	DDV_MinMaxInt(pDX, m_nDashDist, 0, 1000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDashMaxDistDialog, CDialog)
	//{{AFX_MSG_MAP(CDashMaxDistDialog)
	ON_EN_CHANGE(IDC_EDIT_DASHDIST, OnChangeEditDashdist)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDashMaxDistDialog message handlers

BOOL CDashMaxDistDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_DIST))->SetRange(0,1000);
	CButton* applyButton=static_cast<CButton*>(GetDlgItem(IDC_BUTTON_APPLY));
	applyButton->EnableWindow(false);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDashMaxDistDialog::OnChangeEditDashdist() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_DIST))->SetRange(0,1000);
	CButton* applyButton=static_cast<CButton*>(GetDlgItem(IDC_BUTTON_APPLY));
	applyButton->EnableWindow(true);
	m_bChanged=true;
}

void CDashMaxDistDialog::OnButtonApply() 
{
	// TODO: Add your control notification handler code here

	if(FALSE==UpdateData(TRUE))
	{
		return;
	}
	m_pGenesisDlg->SendMessage(WM_APPLY_DASHDIST,(WPARAM)m_nDashDist);
	m_bChanged=false;
}

void CDashMaxDistDialog::OnOK() 
{
	// TODO: Add extra validation here
	BOOL bDataOk=UpdateData(TRUE);
	if(bDataOk)
	{
		if( m_bChanged )
		{
			m_pGenesisDlg->SendMessage(WM_APPLY_DASHDIST,(WPARAM)m_nDashDist);
		}
		m_pGenesisDlg->SendMessage(WM_OPTDLG_CLOSED);
		CDialog::OnOK();
	}
	
}

void CDashMaxDistDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	if(m_nDashDist!=m_nInitialDist)
	{
		m_pGenesisDlg->SendMessage(WM_APPLY_DASHDIST,(WPARAM)m_nInitialDist);
	}
	m_pGenesisDlg->SendMessage(WM_OPTDLG_CLOSED);
	CDialog::OnCancel();
}

void CDashMaxDistDialog::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	delete this;
}

