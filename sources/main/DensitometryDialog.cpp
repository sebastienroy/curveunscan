// DensitometryDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CurveUnscan.h"
#include "UnscanView.h"
#include "DensitometryDialog.h"
#include "DensitoDlgAbstractState.h"
#include "DensitoDlgDrawState.h"
#include "DensitoDlgPickState.h"
#include "DensitoDlgWaitState.h"
#include "DensitoPreviewWnd.h"

#include <Utilities/ColorChooseDialog.h>
#include <SettingsManagement/SettingsManager.h>

#include <Dm/DensityCurve.h>
#include <Dm/ColorScale.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDensitometryDialog dialog


//CDensitometryDialog::CDensitometryDialog(CWnd* pParent /*=NULL*/)
//	: CConstructionDialog(CDensitometryDialog::IDD, pParent,NULL)
//{
//}


CDensitometryDialog::CDensitometryDialog(UINT ID,CUnscanView *pParent, 
										 CSequence *pSequence, 
										 CDensityCurve *pCurve)
:	CConstructionDialog(ID,pParent,pSequence),
	m_pCurve(pCurve),
	m_pColorScale(pCurve->GetColorScale()),
	m_pState(NULL),
	m_pPreviewWnd(NULL)
{
	//{{AFX_DATA_INIT(CDensitometryDialog)
	m_bPickBottom = FALSE;
	m_bPickTop = FALSE;
	m_bDrawSegment = FALSE;
	m_strCurveName = _T(pCurve->GetName());
	//}}AFX_DATA_INIT
}

void CDensitometryDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDensitometryDialog)
	DDX_Control(pDX, IDC_COLOR_SCALE_BUTTON, m_ColorScaleButton);
	DDX_Control(pDX, IDC_BOTTOM_COLOR_BUTTON, m_BottomColorButton);
	DDX_Control(pDX, IDC_TOP_COLOR_BUTTON, m_TopColorButton);
	DDX_Control(pDX, IDC_EDIT_BOTTOM_COLOR_VALUE, m_BottomValueEdit);
	DDX_Control(pDX, IDC_EDIT_TOP_COLOR_VALUE, m_TopValueEdit);
	DDX_Check(pDX, IDC_CHECK_PICK_BOTTOM_COLOR, m_bPickBottom);
	DDX_Check(pDX, IDC_CHECK_PICK_UP_COLOR, m_bPickTop);
	DDX_Check(pDX, IDC_CHECK_DRAWSEGMENT_DENSITO, m_bDrawSegment);
	DDX_Text(pDX, IDC_EDIT_GRAPHNAME, m_strCurveName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDensitometryDialog, CDialog)
	//{{AFX_MSG_MAP(CDensitometryDialog)
	ON_BN_CLICKED(IDC_TOP_COLOR_BUTTON, OnTopColorButton)
	ON_BN_CLICKED(IDC_BOTTOM_COLOR_BUTTON, OnBottomColorButton)
	ON_BN_CLICKED(IDC_CHECK_DRAWSEGMENT_DENSITO, OnCheckDrawsegmentDensito)
	ON_BN_CLICKED(IDC_CHECK_PICK_BOTTOM_COLOR, OnCheckPickBottomColor)
	ON_BN_CLICKED(IDC_CHECK_PICK_UP_COLOR, OnCheckPickTopColor)
	ON_BN_CLICKED(IDC_DEFAULT_COLOR_SCALE_BUTTON, OnDefaultColorScaleButton)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_PREVIOUS, OnPrevious)
	ON_BN_CLICKED(IDC_DENSITOPREVIEW_BUTTON, OnDensitopreviewButton)
	ON_EN_CHANGE(IDC_EDIT_BOTTOM_COLOR_VALUE, OnChangeEditBottomColorValue)
	ON_MESSAGE(WM_END_PICK,OnEndPick)
	ON_MESSAGE(WM_MOVE_PICK,OnMovePick)
	ON_MESSAGE(WM_START_PICK,OnStartPick)
	ON_MESSAGE(WM_SCROLL_OFF,OnScrollOff)
	ON_MESSAGE(WM_SCROLL_ON,OnScrollOn)
	ON_MESSAGE(WM_PREVIEWCLOSED,OnPreviewClosed)
	ON_EN_CHANGE(IDC_EDIT_TOP_COLOR_VALUE, OnChangeEditTopColorValue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDensitometryDialog message handlers

void CDensitometryDialog::OnTopColorButton() 
{
	// TODO: Add your control notification handler code here
	CColorChooseDialog dlg;
	PLPixel32 oldColor=m_TopColorButton.GetColor();
	dlg.SetColor(oldColor);
	if(( IDOK==dlg.DoModal())&&(dlg.GetColor()!=oldColor) )
	{
		m_TopColorButton.SetColor(dlg.GetColor());
		m_ColorScaleButton.SetTopColor(dlg.GetColor());
		m_pCurve->SetModifiedFlag(TRUE);
	}
	
}

void CDensitometryDialog::OnBottomColorButton() 
{
	// TODO: Add your control notification handler code here
	CColorChooseDialog dlg;
	PLPixel32 oldColor=m_BottomColorButton.GetColor();
	dlg.SetColor(oldColor);
	if(( IDOK==dlg.DoModal())&&(dlg.GetColor()!=oldColor) )
	{
		m_BottomColorButton.SetColor(dlg.GetColor());
		m_ColorScaleButton.SetBottomColor(dlg.GetColor());
		m_pCurve->SetModifiedFlag(TRUE);
	}
	
}

void CDensitometryDialog::OnCheckDrawsegmentDensito() 
{
	// TODO: Add your control notification handler code here
	m_pState->CheckDrawButton();
	
}

void CDensitometryDialog::OnCheckPickBottomColor() 
{
	// TODO: Add your control notification handler code here
	m_pState->CheckPickColorButton(false);
}

void CDensitometryDialog::OnCheckPickTopColor() 
{
	// TODO: Add your control notification handler code here
	m_pState->CheckPickColorButton(true);
}

void CDensitometryDialog::OnDefaultColorScaleButton() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(CheckScaleValidity())
	{
		CSettingsManager *pSettings=CSettingsManager::GetInstance();
		pSettings->SetColorScale(*m_pColorScale);
	}

}

BOOL CDensitometryDialog::DataValidation()
{
	return CheckScaleValidity();
}

BOOL CDensitometryDialog::OnInitDialog() 
{
	CConstructionDialog::OnInitDialog();
	
	CColorScale *pColorScale=m_pCurve->GetColorScale();
	PLPixel32 topColor=pColorScale->GetTopColor();
	PLPixel32 bottomColor=pColorScale->GetBottomColor();

	m_TopColorButton.SetColor(topColor);
	m_BottomColorButton.SetColor(bottomColor);
	m_ColorScaleButton.SetColors(topColor,bottomColor);
	m_TopValueEdit.SetValue(pColorScale->GetTopValue());
	m_BottomValueEdit.SetValue(pColorScale->GetBottomValue());

	HICON dropperIcon=AfxGetApp()->LoadIcon(IDI_DROPPER_ICON);
	CButton* pPickTopButton=static_cast<CButton*>(GetDlgItem(IDC_CHECK_PICK_UP_COLOR));
	pPickTopButton->SetIcon(dropperIcon);
	CButton* pPickBottomButton=static_cast<CButton*>(GetDlgItem(IDC_CHECK_PICK_BOTTOM_COLOR));
	pPickBottomButton->SetIcon(dropperIcon);

	// manage state
	if(m_pCurve->IsPositionDefined())
	{
		new CDensitoDlgWaitState(this);
	}
	else
	{
		new CDensitoDlgDrawState(this);
		CButton *pPreviewButton=static_cast<CButton*>(GetDlgItem(IDC_DENSITOPREVIEW_BUTTON));
		pPreviewButton->EnableWindow(FALSE);
	}


	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CDensitometryDialog::CheckScaleValidity()
{
	// check non-empty fields
	CString strEmptyValueMsg;
	strEmptyValueMsg.LoadString(IDS_MUST_GIVE_VALUE);
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
	m_pColorScale->SetTopColor(m_TopColorButton.GetColor());
	m_pColorScale->SetBottomColor(m_BottomColorButton.GetColor());
	m_pColorScale->SetTopValue(m_TopValueEdit.GetValue());
	m_pColorScale->SetBottomValue(m_BottomValueEdit.GetValue());

	// Check values
	ScaleCoherence result=m_pColorScale->GetCoherence();
	if(VALUES_IDENTICAL==result)
	{
		CString msg;
		msg.LoadString(IDS_SCALE_VALUE_MUST_BE_DIFFERENT);
		MessageBox(msg,NULL,MB_OK|MB_ICONSTOP);
		m_TopValueEdit.SetFocus();
		return false;
	}
	else if(COLORS_IDENTICAL==result)
	{
		CString msg;
		msg.LoadString(IDS_SCALE_COLOR_MUST_BE_DIFFERENT);
		MessageBox(msg,NULL,MB_OK|MB_ICONSTOP);
		return false;
	}
	else	// scale ok
	{
		return true;
	}
}

LONG CDensitometryDialog::OnEndPick(UINT wParam, LONG lParam)
{
	return m_pState->EndPick(wParam,lParam);
}

LONG CDensitometryDialog::OnStartPick(UINT wParam, LONG lParam)
{
	return m_pState->StartPick(wParam,lParam);
}

LONG CDensitometryDialog::OnMovePick(UINT wParam, LONG lParam)
{
	return m_pState->MovePick(wParam,lParam);
}

LONG CDensitometryDialog::OnScrollOn(UINT wParam, LONG lParam)
{
	return 0;
}

LONG CDensitometryDialog::OnScrollOff(UINT wParam, LONG lParam)
{
	return m_pState->ScrollOff(wParam,lParam);
}

void CDensitometryDialog::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	if(NULL!=m_pPreviewWnd)
	{
		m_pPreviewWnd->ParentClosed();
		m_pPreviewWnd->DestroyWindow();
//		delete m_pPreviewWnd;
		m_pPreviewWnd=NULL;
	}
	
	delete m_pState;

	CConstructionDialog::PostNcDestroy();
}


BOOL CDensitometryDialog::OKState()
{
	return m_pCurve->IsPositionDefined();
}

void CDensitometryDialog::UpdateButtons()
{
	BOOL result=UpdateOKButton();
	if(TRUE==result)
	{
		CButton *pPreviewButton=static_cast<CButton*>(GetDlgItem(IDC_DENSITOPREVIEW_BUTTON));
		pPreviewButton->EnableWindow(TRUE);
	}

}

void CDensitometryDialog::UpdateObjects()
{
	// nothing to do...
	m_pCurve->Compute();
}


void CDensitometryDialog::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if(NULL!=m_pPreviewWnd)
	{
		m_pPreviewWnd->ParentClosed();
		m_pPreviewWnd->DestroyWindow();
		m_pPreviewWnd=NULL;
	}
	
	CConstructionDialog::OnClose();
}

void CDensitometryDialog::OnPrevious() 
{
	// TODO: Add your control notification handler code here
	CConstructionDialog::OnPrevious();
}

void CDensitometryDialog::OnDensitopreviewButton() 
{
	// TODO: Add your control notification handler code here
	if(!CheckScaleValidity())
	{
		return;
	}

	m_pCurve->Compute();

	if(NULL==m_pPreviewWnd)
	{
		m_pPreviewWnd=new CDensitoPreviewWnd(this,m_pCurve);
	}
	
	m_pPreviewWnd->ShowWindow(SW_SHOWNORMAL);
	m_pPreviewWnd->UpdateWindow();
	m_pPreviewWnd->BringWindowToTop();
}

LONG CDensitometryDialog::OnPreviewClosed(UINT wParam, LONG lParam)
{
	m_pPreviewWnd=NULL;

	return 0;
}

void CDensitometryDialog::OnChangeEditBottomColorValue() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if(GetFocus()==&m_BottomValueEdit)
	{
		m_pCurve->SetModifiedFlag();
	}
}

void CDensitometryDialog::OnChangeEditTopColorValue() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if(GetFocus()==&m_TopValueEdit)
	{
		m_pCurve->SetModifiedFlag();
	}
	
}
