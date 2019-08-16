// DensitoProPage.cpp : implementation file
//

#include "stdafx.h"
#include "settingsmanagement.h"
#include "DensitoProPage.h"

#include "Utilities/ColorChooseDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDensitoProPage property page

IMPLEMENT_DYNCREATE(CDensitoProPage, CPropertyPage)

CDensitoProPage::CDensitoProPage()
:	CPropertyPage(CDensitoProPage::IDD)
{
	//{{AFX_DATA_INIT(CDensitoProPage)
	//}}AFX_DATA_INIT
}

CDensitoProPage::~CDensitoProPage()
{
}

void CDensitoProPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDensitoProPage)
	DDX_Control(pDX, IDC_SETTINGS_TOPVALUE, m_TopValueEdit);
	DDX_Control(pDX, IDC_SETTINGS_BOTTOMVALUE, m_BottomValueEdit);
	DDX_Control(pDX, IDC_SETTINGS_TOPCOLOR, m_TopColorButton);
	DDX_Control(pDX, IDC_SETTINGS_COLORSCALE, m_ColorScaleCtrl);
	DDX_Control(pDX, IDC_SETTINGS_BOTTOMCOLOR, m_BottomColorButton);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDensitoProPage, CPropertyPage)
	//{{AFX_MSG_MAP(CDensitoProPage)
	ON_BN_CLICKED(IDC_SETTINGS_TOPCOLOR, OnTopcolorButton)
	ON_BN_CLICKED(IDC_SETTINGS_BOTTOMCOLOR, OnBottomcolorButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDensitoProPage message handlers

void CDensitoProPage::SetColorScale(const CColorScale &colorScale)
{
	m_ColorScale=colorScale;
}

const CColorScale& CDensitoProPage::GetColorScale() const
{
	return m_ColorScale;
}

BOOL CDensitoProPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_TopColorButton.SetColor(m_ColorScale.GetTopColor());
	m_BottomColorButton.SetColor(m_ColorScale.GetBottomColor());
	m_TopValueEdit.SetValue(m_ColorScale.GetTopValue());
	m_BottomValueEdit.SetValue(m_ColorScale.GetBottomValue());

	m_ColorScaleCtrl.SetColors(m_ColorScale.GetTopColor(),m_ColorScale.GetBottomColor());

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDensitoProPage::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	if(!CheckScaleValidity())
	{
		return FALSE;
	}
	
	return CPropertyPage::OnKillActive();
}

void CDensitoProPage::OnTopcolorButton() 
{
	// TODO: Add your control notification handler code here
	CColorChooseDialog dlg;
	PLPixel32 oldColor=m_TopColorButton.GetColor();
	dlg.SetColor(oldColor);
	if(( IDOK==dlg.DoModal())&&(dlg.GetColor()!=oldColor) )
	{
		m_TopColorButton.SetColor(dlg.GetColor());
		m_ColorScaleCtrl.SetTopColor(dlg.GetColor());
	}
		
}

void CDensitoProPage::OnBottomcolorButton() 
{
	// TODO: Add your control notification handler code here
	CColorChooseDialog dlg;
	PLPixel32 oldColor=m_BottomColorButton.GetColor();
	dlg.SetColor(oldColor);
	if(( IDOK==dlg.DoModal())&&(dlg.GetColor()!=oldColor) )
	{
		m_BottomColorButton.SetColor(dlg.GetColor());
		m_ColorScaleCtrl.SetBottomColor(dlg.GetColor());
	}	
}

bool CDensitoProPage::CheckScaleValidity()
{
	// check non-empty fields
	CString strEmptyValueMsg;
	strEmptyValueMsg.LoadString(IDS_SETT_MUST_GIVE_VALUE);
	if(m_TopValueEdit.IsEmpty())
	{
		MessageBox(strEmptyValueMsg,NULL,MB_OK|MB_ICONSTOP);
		m_TopValueEdit.SetFocus();
		return false;
	}
	else if(m_BottomValueEdit.IsEmpty())
	{
		MessageBox(strEmptyValueMsg,NULL,MB_OK|MB_ICONSTOP);
		m_BottomValueEdit.SetFocus();
		return false;
	}
		
	// Copy the items values into the scale object
	m_ColorScale.SetTopColor(m_TopColorButton.GetColor());
	m_ColorScale.SetBottomColor(m_BottomColorButton.GetColor());
	m_ColorScale.SetTopValue(m_TopValueEdit.GetValue());
	m_ColorScale.SetBottomValue(m_BottomValueEdit.GetValue());

	// Check values
	ScaleCoherence result=m_ColorScale.GetCoherence();
	if(VALUES_IDENTICAL==result)
	{
		CString msg;
		msg.LoadString(IDS_SETT_SCALE_VALUE_MUST_BE_DIFFERENT);
		MessageBox(msg,NULL,MB_OK|MB_ICONSTOP);
		m_TopValueEdit.SetFocus();
		return false;
	}
	else if(COLORS_IDENTICAL==result)
	{
		CString msg;
		msg.LoadString(IDS_SETT_SCALE_COLOR_MUST_BE_DIFFERENT);
		MessageBox(msg,NULL,MB_OK|MB_ICONSTOP);
		return false;
	}
	else	// scale ok
	{
		return true;
	}
}
