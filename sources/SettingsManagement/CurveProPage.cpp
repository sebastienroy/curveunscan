// CurveProPage.cpp : implementation file
//

#include "stdafx.h"
#include "settingsmanagement.h"
#include "CurveProPage.h"
#include "../Utilities/ColorChooseDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurveProPage property page

IMPLEMENT_DYNCREATE(CCurveProPage, CPropertyPage)

CCurveProPage::CCurveProPage() : CPropertyPage(CCurveProPage::IDD)
{
	//{{AFX_DATA_INIT(CCurveProPage)
	m_nThicknessAlgo = 0;
	m_nSmartAlgoRange = 0;
	m_nFollow = 0;
	m_nDashMaxDist = 0;
	m_nDashed = -1;
	//}}AFX_DATA_INIT
}

CCurveProPage::~CCurveProPage()
{
}

void CCurveProPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCurveProPage)
	DDX_Control(pDX, IDC_SPIN_THICKRANGE, m_SpinThickRange);
	DDX_Control(pDX, IDC_SPIN_DASHMAX, m_SpinDashMax);
	DDX_Control(pDX, IDC_BUTTON_SETTING_BLACKCOLOR, m_BlackLevelButton);
	DDX_Radio(pDX, IDC_RADIO_SETTING_SMART, m_nThicknessAlgo);
	DDX_Text(pDX, IDC_EDIT_SETTING_THICKWIDTH, m_nSmartAlgoRange);
	DDV_MinMaxInt(pDX, m_nSmartAlgoRange, 1, 32);
	DDX_Radio(pDX, IDC_RADIO_SETTING_TOPFOLLOW, m_nFollow);
	DDX_Text(pDX, IDC_EDIT_SETTING_DASHMAX, m_nDashMaxDist);
	DDV_MinMaxInt(pDX, m_nDashMaxDist, 1, 1000);
	DDX_Radio(pDX, IDC_RADIO_SETTING_DASHED, m_nDashed);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CCurveProPage, CPropertyPage)
	//{{AFX_MSG_MAP(CCurveProPage)
	ON_BN_CLICKED(IDC_BUTTON_SETTING_BLACKCOLOR, OnButtonBlackcolor)
	ON_BN_CLICKED(IDC_BUTTON_SETTING_CURVEDEFAULTS, OnButtonCurveDefaults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurveProPage message handlers

BOOL CCurveProPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_BlackLevelButton.SetColor(m_BlackColor);
	m_SpinDashMax.SetRange(1,1000);
	m_SpinThickRange.SetRange(1,32);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCurveProPage::OnButtonBlackcolor() 
{
	// TODO: Add your control notification handler code here
	CColorChooseDialog dlg;
	dlg.SetColor(m_BlackLevelButton.GetColor());
	if(IDOK==dlg.DoModal())
	{
		m_BlackLevelButton.SetColor(dlg.GetColor());
	}
	
}

void CCurveProPage::OnButtonCurveDefaults() 
{
	// TODO: Add your control notification handler code here
	m_BlackLevelButton.SetColor(m_DefaultBlackColor);
	m_nDashed=m_nDefaultDashed;
	m_nDashMaxDist=m_nDefaultDashMaxDist;
	m_nFollow=m_nDefaultFollow;
	m_nSmartAlgoRange=m_nDefaultSmartAlgoRange;
	m_nThicknessAlgo=m_nDefaultThicknessAlgo;
	UpdateData(FALSE);
}

void CCurveProPage::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_BlackColor=m_BlackLevelButton.GetColor();
	
	CPropertyPage::OnOK();
}
