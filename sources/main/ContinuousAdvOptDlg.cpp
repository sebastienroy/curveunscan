// ContinuousAdvOptDlg.cpp : implementation file
//

#include "stdafx.h"
#include "enums.h"
#include "CurveUnscan.h"
#include "ContinuousAdvOptDlg.h"
#include "plpixel32.h"
#include "UnscanDoc.h"
#include "GenesisDialog.h"
#include <HelpSystem/HelpFunctions.h>

#include <SettingsManagement/SettingsManager.h>

#include <Dm/ContinuousCurve.h>
#include <Dm/FlatThicknessCorrector.h>
#include <Dm/SmartThicknessCorrector.h>
#include <Dm/BmpManager.h>
#include <Dm/CoordSyst.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CContinuousAdvOptDlg dialog


CContinuousAdvOptDlg::CContinuousAdvOptDlg(CContinuousCurve* pCurve,CGenesisDialog* pGenesisDlg,CWnd* pParent /*=NULL*/)
	: CDialog(CContinuousAdvOptDlg::IDD, pParent), m_pCurve(pCurve),m_pParent(pGenesisDlg)
{
	m_bModified=false;
	//{{AFX_DATA_INIT(CContinuousAdvOptDlg)
	m_bPickColor = FALSE;
	m_nBlue = 0;
	m_nGreen = 0;
	m_nRed = 0;
	m_nThickWidth = 0;
	m_ThickKindRadio = -1;
	//}}AFX_DATA_INIT
}


void CContinuousAdvOptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CContinuousAdvOptDlg)
	DDX_Control(pDX, IDC_SLIDER_GREEN, m_GreenSlider);
	DDX_Control(pDX, IDC_SLIDER_RED, m_RedSlider);
	DDX_Control(pDX, IDC_SLIDER_BLUE, m_BlueSlider);
	DDX_Control(pDX, IDC_BLACKCOLOR_BUTTON, m_ColoredButton);
	DDX_Check(pDX, IDC_CHECK_PICKCOLOR, m_bPickColor);
	DDX_Text(pDX, IDC_EDIT_BLUE, m_nBlue);
	DDX_Text(pDX, IDC_EDIT_GREEN, m_nGreen);
	DDX_Text(pDX, IDC_EDIT_RED, m_nRed);
	DDX_Text(pDX, IDC_EDIT_THICK_RANGE, m_nThickWidth);
	DDX_Radio(pDX, IDC_RADIO_FLAT_THICKNESS, m_ThickKindRadio);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CContinuousAdvOptDlg, CDialog)
	//{{AFX_MSG_MAP(CContinuousAdvOptDlg)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_RED, OnReleasedcaptureSliderRed)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_GREEN, OnReleasedcaptureSliderGreen)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_BLUE, OnReleasedcaptureSliderBlue)
	ON_MESSAGE(WM_END_PICK,OnEndPick)
	ON_EN_CHANGE(IDC_EDIT_RED, OnChangeEditRed)
	ON_EN_CHANGE(IDC_EDIT_GREEN, OnChangeEditGreen)
	ON_EN_CHANGE(IDC_EDIT_BLUE, OnChangeEditBlue)
	ON_BN_CLICKED(IDC_RADIO_FLAT_THICKNESS, OnRadioFlatThickness)
	ON_BN_CLICKED(IDC_RADIO_SMART_THICKNESS, OnRadioSmartThickness)
	ON_EN_CHANGE(IDC_EDIT_THICK_RANGE, OnChangeEditThickRange)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_CHECK_PICKCOLOR, OnCheckPickcolor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContinuousAdvOptDlg message handlers

BOOL CContinuousAdvOptDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	//--- colors
	PLPixel32 pixel=m_pCurve->GetBlackLevel();

	m_nRed=pixel.GetR();
	m_RedSlider.SetRange(0,255);
	m_RedSlider.SetPos(255-m_nRed);

	m_nGreen=pixel.GetG();
	m_GreenSlider.SetRange(0,255);
	m_GreenSlider.SetPos(255-m_nGreen);

	m_nBlue=pixel.GetB();
	m_BlueSlider.SetRange(0,255);
	m_BlueSlider.SetPos(255-m_nBlue);

	m_ColoredButton.SetColor(pixel);

	//--- thickness
	CSpinButtonCtrl* spin=static_cast<CSpinButtonCtrl*>(GetDlgItem(IDC_SPIN_RANGE));
	spin->SetRange(1,32);
	CWnd* pEdit=GetDlgItem(IDC_EDIT_THICK_RANGE);
	CAbstractThicknessCorrector* corrector=m_pCurve->GetThicknessCorrector();
	CSmartThicknessCorrector* smart=dynamic_cast<CSmartThicknessCorrector*>(corrector);
	if(NULL==smart)
		{
		m_ThickKindRadio=0;
		m_nThickWidth=(CSettingsManager::GetInstance()->GetContinuousCurveDefaultValues()).m_nSmartAlgoRange;
		pEdit->EnableWindow(FALSE);
		spin->EnableWindow(FALSE);
		}
	else
		{
		m_ThickKindRadio=1;
		m_nThickWidth=smart->GetWidth();
		pEdit->EnableWindow(TRUE);
		spin->EnableWindow(TRUE);
		}

	UpdateData(FALSE);

	m_pParent->SetCursorShape(kDefaultCursor);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CContinuousAdvOptDlg::OnReleasedcaptureSliderRed(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int previousValue=m_nRed;
	int position=m_RedSlider.GetPos();
	m_nRed=255-position;
	if(previousValue!=m_nRed) m_bModified=true;
	UpdateColorButton();
	UpdateData(FALSE);

	*pResult = 0;
}

void CContinuousAdvOptDlg::OnReleasedcaptureSliderGreen(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int previousValue=m_nGreen;
	int position=m_GreenSlider.GetPos();
	m_nGreen=255-position;
	if(previousValue!=m_nGreen) m_bModified=true;
	UpdateColorButton();
	UpdateData(FALSE);
	
	*pResult = 0;
}

void CContinuousAdvOptDlg::OnReleasedcaptureSliderBlue(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int previousValue=m_nBlue;
	int position=m_BlueSlider.GetPos();
	m_nBlue=255-position;
	if(previousValue!=m_nBlue) m_bModified=true;
	UpdateColorButton();
	UpdateData(FALSE);
	
	*pResult = 0;
}

void CContinuousAdvOptDlg::UpdateColorButton()
{
	PLPixel32 pixel(m_nRed,m_nGreen,m_nBlue,0);
	m_ColoredButton.SetColor(pixel);
//	m_ColoredButton.RedrawWindow();
}

void CContinuousAdvOptDlg::OnChangeEditRed() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_bModified=true;
	UpdateData(TRUE);
	int value=m_nRed;
	if(value>255) value=255;
	if(value<0) value=0;
	m_RedSlider.SetPos(255-value);
	UpdateColorButton();
	UpdateData(FALSE);	
}

void CContinuousAdvOptDlg::OnChangeEditGreen() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_bModified=true;
	UpdateData(TRUE);
	int value=m_nGreen;
	if(value>255) value=255;
	if(value<0) value=0;
	m_GreenSlider.SetPos(255-value);
	UpdateColorButton();
	UpdateData(FALSE);	
	
}

void CContinuousAdvOptDlg::OnChangeEditBlue() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_bModified=true;
	UpdateData(TRUE);
	int value=m_nBlue;
	if(value>255) value=255;
	if(value<0) value=0;
	m_BlueSlider.SetPos(255-value);
	UpdateColorButton();
	UpdateData(FALSE);	
}

void CContinuousAdvOptDlg::OnRadioFlatThickness() 
{
	// TODO: Add your control notification handler code here
	int previousSelect=m_ThickKindRadio;
	UpdateData(TRUE);
	if(previousSelect!=m_ThickKindRadio) m_bModified=true;
	CEdit* pEdit=static_cast<CEdit*>(GetDlgItem(IDC_EDIT_THICK_RANGE));
	pEdit->EnableWindow(FALSE);	
	CSpinButtonCtrl* spin=static_cast<CSpinButtonCtrl*>(GetDlgItem(IDC_SPIN_RANGE));
	spin->EnableWindow(FALSE);
	UpdateData(FALSE);	
}

void CContinuousAdvOptDlg::OnRadioSmartThickness() 
{
	// TODO: Add your control notification handler code here
	int previousSelect=m_ThickKindRadio;
	UpdateData(TRUE);
	if(previousSelect!=m_ThickKindRadio) m_bModified=true;
	CEdit* pEdit=static_cast<CEdit*>(GetDlgItem(IDC_EDIT_THICK_RANGE));
	pEdit->EnableWindow(TRUE);	
	CSpinButtonCtrl* spin=static_cast<CSpinButtonCtrl*>(GetDlgItem(IDC_SPIN_RANGE));
	spin->EnableWindow(TRUE);
	UpdateData(FALSE);		
}

void CContinuousAdvOptDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if(!m_bModified)
		{
		m_pParent->SendMessage(WM_OPTDLG_CLOSED);
		DestroyWindow();
		return;
		}

	if(!ActionConfirmed())
		{
		return;
		}
	else if(!DataValidation())
		{
		return;
		}

	//--- Color
	m_pCurve->SetBlackLevel(PLPixel32(m_nRed,m_nGreen,m_nBlue,0));
	//--- Corrector
	CAbstractThicknessCorrector* corrector;
	if(0==m_ThickKindRadio)
		{
		corrector=new CFlatThicknessCorrector(m_pCurve);
		}
	else
		{
		CSmartThicknessCorrector* smart=new CSmartThicknessCorrector(m_pCurve);
		smart->SetWidth(m_nThickWidth);
		corrector=smart;
		}
	int currentThickness=m_pCurve->GetTickness();
	corrector->SetThickness(currentThickness);
	m_pCurve->SetThicknessCorrector(corrector);	// the old is destroyed

	//--- Redraw
	m_pCurve->Construct();
	CUnscanDoc* pDoc=m_pCurve->GetCoordSyst()->GetDocument();
	pDoc->UpdateAllViews(NULL);

	//---Terminate
	m_pParent->SendMessage(WM_OPTDLG_CLOSED);
	DestroyWindow();
	
}

bool CContinuousAdvOptDlg::DataValidation()
{
	//--- check colors
	UpdateData(TRUE);
	CString msg;
	msg.LoadString(IDS_COLOR_RANGE);
	if( (m_nRed<0)||(m_nRed>255) )
		{
		AfxMessageBox(msg,MB_OK|MB_ICONEXCLAMATION);
		CEdit* pEdit=static_cast<CEdit*>(GetDlgItem(IDC_EDIT_RED));
		pEdit->SetFocus();
		pEdit->SetSel(0,-1);
		return false;
		}
	if( (m_nGreen<0)||(m_nGreen>255) )
		{
		AfxMessageBox(msg,MB_OK|MB_ICONEXCLAMATION);
		CEdit* pEdit=static_cast<CEdit*>(GetDlgItem(IDC_EDIT_GREEN));
		pEdit->SetFocus();
		pEdit->SetSel(0,-1);
		return false;
		}
	if( (m_nBlue<0)||(m_nBlue>255) )
		{
		AfxMessageBox(msg,MB_OK|MB_ICONEXCLAMATION);
		CEdit* pEdit=static_cast<CEdit*>(GetDlgItem(IDC_EDIT_BLUE));
		pEdit->SetFocus();
		pEdit->SetSel(0,-1);
		return false;
		}

	//--- thickness
	if( (1==m_ThickKindRadio)&&( (m_nThickWidth<1)||(m_nThickWidth>32) ) )
		{
		CString msgThick;
		msgThick.LoadString(IDS_THICK_WHIDTH_RANGE);
		AfxMessageBox(msgThick,MB_OK|MB_ICONEXCLAMATION);
		CEdit* pEdit=static_cast<CEdit*>(GetDlgItem(IDC_EDIT_THICK_RANGE));
		pEdit->SetFocus();
		pEdit->SetSel(0,-1);
		return false;
		}
	return true;
}

void CContinuousAdvOptDlg::OnChangeEditThickRange() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if( (GetFocus()!=GetDlgItem(IDC_EDIT_THICK_RANGE))
		&& (GetFocus()!=GetDlgItem(IDC_SPIN_RANGE)) )
		{
		return;
		}
	m_bModified=true;
}

void CContinuousAdvOptDlg::OnEndPick(UINT wParam, LONG lParam)
	{
	UpdateData(TRUE);
	if(!m_bPickColor)
		{
		return;
		}

	m_bModified=true;
	CPoint* point=reinterpret_cast<CPoint*>(lParam);
	CBmpManager* pBmpManager=m_pCurve->GetCoordSyst()->GetDocument()->GetBmpManager();
	PLPixel32 pixel=pBmpManager->GetPointColor(*point);
	m_ColoredButton.SetColor(pixel);
	m_nRed=pixel.GetR();
	m_nGreen=pixel.GetG();
	m_nBlue=pixel.GetB();
	m_RedSlider.SetPos(255-m_nRed);
	m_GreenSlider.SetPos(255-m_nGreen);
	m_BlueSlider.SetPos(255-m_nBlue);
	m_bPickColor=FALSE;

	m_pParent->SetCursorShape(kDefaultCursor);

	UpdateData(FALSE);
	}


void CContinuousAdvOptDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
//	m_pParent->SetCursorShape(kDefaultCursor);

	delete this;
}

void CContinuousAdvOptDlg::OnCancel() 
{
	// TODO: Add extra cleanup here

	m_pParent->SendMessage(WM_OPTDLG_CLOSED);
	DestroyWindow();
}

bool CContinuousAdvOptDlg::ActionConfirmed()
{
	bool result=true;
	if(m_pCurve->GetHandModification())
		{
		CString caption("CurveUnscan");
		CString text;
		text.LoadString(IDS_HAND_MODIFICATION_LOST);
		int reponse=MessageBox(text,caption,MB_YESNO);
		if(reponse!=IDYES)
			{
			result=false;
			}
		}
	return result;
}

BOOL CContinuousAdvOptDlg::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	CHelpFunctions::DisplayCtrlPopup(FromHandle((HWND)pHelpInfo->hItemHandle),
									pHelpInfo->MousePos,
									pHelpInfo->iCtrlId);
	return TRUE;
	}

void CContinuousAdvOptDlg::OnCheckPickcolor() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_bPickColor)
	{
		m_pParent->SetCursorShape(kPickColorCursor);
	}
	else
	{
		m_pParent->SetCursorShape(kDefaultCursor);
	}
	
}
