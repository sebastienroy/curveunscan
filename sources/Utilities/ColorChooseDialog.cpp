// ColorChooseDialog.cpp : implementation file
//

#include "stdafx.h"
#include "..\Utilities\resource.h"
#include "ColorChooseDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorChooseDialog dialog


CColorChooseDialog::CColorChooseDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CColorChooseDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CColorChooseDialog)
	m_nBlue = 0;
	m_nGreen = 0;
	m_nRed = 0;
	m_nBlueSlider = 0;
	m_nGreenSlider = 0;
	m_nRedSlider = 0;
	//}}AFX_DATA_INIT
}


void CColorChooseDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorChooseDialog)
	DDX_Control(pDX, IDC_BUTTON_COLOR, m_ButtonColor);
	DDX_Text(pDX, IDC_EDIT_BLUESETTING, m_nBlue);
	DDV_MinMaxInt(pDX, m_nBlue, 0, 255);
	DDX_Text(pDX, IDC_EDIT_GREENSETTING, m_nGreen);
	DDV_MinMaxInt(pDX, m_nGreen, 0, 255);
	DDX_Text(pDX, IDC_EDIT_REDSETTING, m_nRed);
	DDV_MinMaxInt(pDX, m_nRed, 0, 255);
	DDX_Slider(pDX, IDC_SLIDER_BLUECOMP, m_nBlueSlider);
	DDX_Slider(pDX, IDC_SLIDER_GREENCOMP, m_nGreenSlider);
	DDX_Slider(pDX, IDC_SLIDER_REDCOMP, m_nRedSlider);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CColorChooseDialog, CDialog)
	//{{AFX_MSG_MAP(CColorChooseDialog)
	ON_EN_CHANGE(IDC_EDIT_BLUESETTING, OnChangeEditBlue)
	ON_EN_CHANGE(IDC_EDIT_GREENSETTING, OnChangeEditGreen)
	ON_EN_CHANGE(IDC_EDIT_REDSETTING, OnChangeEditRed)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_BLUECOMP, OnReleasedcaptureSliderBlue)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_GREENCOMP, OnReleasedcaptureSliderGreen)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_REDCOMP, OnReleasedcaptureSliderRed)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorChooseDialog message handlers

BOOL CColorChooseDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ButtonColor.SetColor(m_Color);

	// set range
	CSliderCtrl *pSlider=static_cast<CSliderCtrl*>(GetDlgItem(IDC_SLIDER_REDCOMP));	// red
	pSlider->SetRange(0,255);
	pSlider=static_cast<CSliderCtrl*>(GetDlgItem(IDC_SLIDER_GREENCOMP));	// green
	pSlider->SetRange(0,255);
	pSlider=static_cast<CSliderCtrl*>(GetDlgItem(IDC_SLIDER_BLUECOMP));	// blue
	pSlider->SetRange(0,255);

	m_nRed=m_Color.GetR();
	m_nRedSlider=255-m_nRed;
	m_nGreen=m_Color.GetG();
	m_nGreenSlider=255-m_nGreen;
	m_nBlue=m_Color.GetB();
	m_nBlueSlider=255-m_nBlue;
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CColorChooseDialog::OnChangeEditBlue() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int nValue=IntoRange(m_nBlue);
	m_nBlueSlider=255-nValue;
	m_Color.SetG(nValue);
	m_ButtonColor.SetColor(m_Color);
	UpdateData(FALSE);
	
} 

void CColorChooseDialog::OnChangeEditGreen() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int nValue=IntoRange(m_nGreen);
	m_nGreenSlider=255-nValue;
	m_Color.SetG(nValue);
	m_ButtonColor.SetColor(m_Color);
	UpdateData(FALSE);

	
}

void CColorChooseDialog::OnChangeEditRed() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int nValue=IntoRange(m_nRed);
	m_nRedSlider=255-nValue;
	m_Color.SetR(nValue);
	m_ButtonColor.SetColor(m_Color);
	UpdateData(FALSE);
	
}

void CColorChooseDialog::OnReleasedcaptureSliderBlue(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_Color.SetB(255-m_nBlueSlider);
	m_ButtonColor.SetColor(m_Color);
	m_nBlue=255-m_nBlueSlider;
	UpdateData(FALSE);
	
	*pResult = 0;
}

void CColorChooseDialog::OnReleasedcaptureSliderGreen(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_Color.SetG(255-m_nGreenSlider);
	m_ButtonColor.SetColor(m_Color);
	m_nGreen=255-m_nGreenSlider;
	UpdateData(FALSE);
	
	*pResult = 0;
}

void CColorChooseDialog::OnReleasedcaptureSliderRed(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_Color.SetR(255-m_nRedSlider);
	m_ButtonColor.SetColor(m_Color);
	m_nRed=255-m_nRedSlider;
	UpdateData(FALSE);
	
	*pResult = 0;
}

void CColorChooseDialog::SetColor(const PLPixel32 &color)
{
	m_Color=color;
}

PLPixel32 CColorChooseDialog::GetColor() const
{
	return m_Color;
}

int CColorChooseDialog::IntoRange(int nValue) const
{
	if(nValue<0)
	{
		nValue=0;
	}
	else if(nValue>255)
	{
		nValue=255;
	}
	return nValue;
}
