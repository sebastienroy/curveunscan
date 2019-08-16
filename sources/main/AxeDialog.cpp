// AxeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CurveUnscan.h"
#include "AxeDialog.h"

#include "AxeDrawingState.h"
#include "AxePointPickingState.h"
#include "AxeWaitState.h"

#include <Dm/Axe.h>
#include <Dm/CoordSyst.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAxeDialog dialog


CAxeDialog::CAxeDialog(UINT ID, CUnscanView *pParent, CSequence *pSequence,
							   CAxe *pMainAxe, CAxe *pOtherAxe)
	: CConstructionDialog(ID,pParent,pSequence),
	m_pAxe(pMainAxe),
	m_pOtherAxe(pOtherAxe),
	m_pState(NULL),
	m_pScalePoint1(pMainAxe->GetScalePoint(1)),
	m_pScalePoint2(pMainAxe->GetScalePoint(2)),
	m_strAxeName(pMainAxe->GetName()),
	m_nLinear((pMainAxe->GetLogarithmic())?1:0)
	{
	}


void CAxeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAxeDialog)
	DDX_Control(pDX, IDC_EDIT_2NDVALUE, m_ValueEditPt2);
	DDX_Control(pDX, IDC_EDIT_1STVALUE, m_ValueEditPt1);
	DDX_Check(pDX, IDC_CHECK_1ST, m_bCheckPt1);
	DDX_Check(pDX, IDC_CHECK_2ND, m_bCheckPt2);
	DDX_Check(pDX, IDC_CHECK_AXE, m_bCheckAxe);
	DDX_Text(pDX, IDC_EDIT_AXENAME, m_strAxeName);
	DDX_Radio(pDX, IDC_RADIO_LINEAR, m_nLinear);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAxeDialog, CDialog)
	//{{AFX_MSG_MAP(CAxeDialog)
	ON_BN_CLICKED(IDC_CHECK_1ST, OnCheck1st)
	ON_BN_CLICKED(IDC_CHECK_2ND, OnCheck2nd)
	ON_BN_CLICKED(IDC_CHECK_AXE, OnCheckAxe)
	ON_EN_CHANGE(IDC_EDIT_1STVALUE, OnChangeEdit1stvalue)
	ON_EN_CHANGE(IDC_EDIT_2NDVALUE, OnChangeEdit2ndvalue)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_PREVIOUS, OnPrevious)
	ON_EN_KILLFOCUS(IDC_EDIT_1STVALUE, OnKillfocusEdit1stvalue)
	ON_EN_SETFOCUS(IDC_EDIT_1STVALUE, OnSetfocusEdit1stvalue)
	ON_EN_KILLFOCUS(IDC_EDIT_2NDVALUE, OnKillfocusEdit2ndvalue)
	ON_EN_SETFOCUS(IDC_EDIT_2NDVALUE, OnSetfocusEdit2ndvalue)
	ON_BN_CLICKED(IDC_RADIO_LINEAR, OnRadioLinear)
	ON_MESSAGE(WM_END_PICK,OnEndPick)
	ON_MESSAGE(WM_MOVE_PICK,OnMovePick)
	ON_MESSAGE(WM_START_PICK,OnStartPick)
	ON_MESSAGE(WM_SCROLL_OFF,OnScrollOff)
	ON_MESSAGE(WM_SCROLL_ON,OnScrollOn)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAxeDialog message handlers

BOOL CAxeDialog::OnInitDialog() 
{
	CConstructionDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	BOOL bFocusSet=FALSE;

	BOOL bAxeDefined=m_pAxe->IsDefined();
	if(!bAxeDefined)	// axe not defined
		{
		EnablePoint(1,FALSE);
		EnablePoint(2,FALSE);
		m_bCheckAxe=TRUE;
		new CAxeDrawingState(this);
		}
	else				// axe defined
		{
		if(m_pScalePoint1->ValueIsDefined())
			{
			m_ValueEditPt1.SetValue(m_pScalePoint1->GetValue());
			}
		if(m_pScalePoint2->ValueIsDefined())
			{
			m_ValueEditPt2.SetValue(m_pScalePoint2->GetValue());
			}

		if(!m_pScalePoint1->PositionIsDefined())
			{
			EnablePoint(2,FALSE);
			m_bCheckPt1=TRUE;
			new CAxePointPickingState(this,1);
			}
		else if(!m_pScalePoint2->IsDefined())
			{
			m_bCheckPt2=TRUE;
			new CAxePointPickingState(this,2);
			}
		else	// Axe defined, 2 scale positions defined
			{
			// set focus if scale values not defined
			if(!m_pScalePoint1->ValueIsDefined())
				{
				m_ValueEditPt1.SetFocus();
				m_ValueEditPt1.SetSel(0,-1);
				bFocusSet=TRUE;
				}
			else if(!m_pScalePoint2->ValueIsDefined())
				{
				m_ValueEditPt2.SetFocus();
				m_ValueEditPt2.SetSel(0,-1);
				bFocusSet=TRUE;
				}

			new CAxeWaitState(this);
			}
		}
#if defined(_DEBUG)
// The state should have been defined now so, if not, throw something
	if (NULL==m_pState)
		{
		MessageBox("State not defined !!!!");
		}
#endif
	
	return !bFocusSet;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAxeDialog::OnCheck1st() 
{
	// TODO: Add your control notification handler code here
	m_pState->CheckPointButton(1);
}

void CAxeDialog::OnCheck2nd() 
{
	// TODO: Add your control notification handler code here
	m_pState->CheckPointButton(2);
}

void CAxeDialog::OnCheckAxe() 
{
	// TODO: Add your control notification handler code here
	m_pState->CheckAxeButton();
}

void CAxeDialog::OnChangeEdit1stvalue() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	ValueEditChanged(1);
}

void CAxeDialog::OnChangeEdit2ndvalue() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	ValueEditChanged(2);
}

void CAxeDialog::ValueEditChanged(int nPoint)
{
	CValueEdit* pValueEdit=(1==nPoint)?&m_ValueEditPt1:&m_ValueEditPt2;
	if(GetFocus()!=pValueEdit)
		{
		return;
		}

	m_pState->PointValueEdited(nPoint);
}


BOOL CAxeDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CConstructionDialog::OnHelpInfo(pHelpInfo);
}

LONG CAxeDialog::OnEndPick(UINT wParam, LONG lParam)
{
	return m_pState->EndPick(wParam,lParam);
}

LONG CAxeDialog::OnStartPick(UINT wParam, LONG lParam)
{
	return m_pState->StartPick(wParam,lParam);
}

LONG CAxeDialog::OnMovePick(UINT wParam, LONG lParam)
{
	return m_pState->MovePick(wParam,lParam);
}

LONG CAxeDialog::OnScrollOn(UINT wParam, LONG lParam)
{
	return 0;
}

LONG CAxeDialog::OnScrollOff(UINT wParam, LONG lParam)
{
	return m_pState->ScrollOff(wParam,lParam);
}

BOOL CAxeDialog::DataValidation()
{
	if(m_pScalePoint1->GetAxePosition()==m_pScalePoint2->GetAxePosition())
		{
		CString msg;
		msg.LoadString(IDS_SCALE_POINT_DIFFERENT);
		MessageBox(msg,"CurveUnscan",MB_OK|MB_ICONINFORMATION);
		return FALSE;
		}
	if(m_pScalePoint1->GetValue()==m_pScalePoint2->GetValue())
		{
		CString msg;
		msg.LoadString(IDS_SCALE_VALUES_DIFFERENT);
		MessageBox(msg,"CurveUnscan",MB_OK|MB_ICONINFORMATION);
		return FALSE;
		}
	if (m_nLinear==1)
		{
		if( (m_pScalePoint1->GetValue()<=0)||(m_pScalePoint2->GetValue()<=0) )
			{
			CString msg;
			msg.LoadString(IDS_LOG_GREATER_THAN_ZERO2);
			MessageBox(msg,"CurveUnscan",MB_OK|MB_ICONINFORMATION);
			return FALSE;
			}
		}
	return TRUE;
}

void CAxeDialog::OnPrevious() 
{
	// TODO: Add your control notification handler code here
	CConstructionDialog::OnPrevious();
}

void CAxeDialog::EnablePoint(int nPointNumber, BOOL bState)
{
	int nCheckId=(1==nPointNumber)?IDC_CHECK_1ST:IDC_CHECK_2ND;
	CWnd* pCheck=GetDlgItem(nCheckId);
	pCheck->EnableWindow(bState);

	int nStaticId=(1==nPointNumber)?IDC_STATIC_PT1:IDC_STATIC_PT2;
	CWnd* pStatic=GetDlgItem(nStaticId);
	pStatic->EnableWindow(bState);

	CValueEdit* pValueEdit=(1==nPointNumber)?&m_ValueEditPt1:&m_ValueEditPt2;
	pValueEdit->EnableWindow(bState);
}

void CAxeDialog::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	delete m_pState;
	CConstructionDialog::PostNcDestroy();
}


BOOL CAxeDialog::OKState()
{
	return( m_pAxe->IsDefined()
		&& m_pScalePoint1->IsDefined()
		&& m_pScalePoint2->IsDefined() );
}


void CAxeDialog::UpdateObjects()
{
	m_pAxe->SetName(m_strAxeName);	
	m_pAxe->SetLogarithmic((m_nLinear==1)?TRUE:FALSE);

	BOOL flag=(m_pAxe->GetCoordSyst())->CalculateConversionFactors();
}

int CAxeDialog::GetFocusedEditNb()
{
	int nFocused=0;
	if(GetFocus()==&m_ValueEditPt1)
		{
		nFocused=1;
		}
	else if(GetFocus()==&m_ValueEditPt2)
		{
		nFocused=2;
		}
	return nFocused;
}

bool CAxeDialog::IsValueEditEmpty(int nNumber)
{
	CValueEdit& valueEdit=(1==nNumber)?m_ValueEditPt1:m_ValueEditPt2;
	return valueEdit.IsEmpty();
}

bool CAxeDialog::IsPositionDefined(int nNumber)
{
	CScalePoint* pScalePoint=(1==nNumber)?m_pScalePoint1:m_pScalePoint2;
	return pScalePoint->PositionIsDefined();
}

void CAxeDialog::OnKillfocusEdit1stvalue() 
{
	// TODO: Add your control notification handler code here
	m_pState->UpdateStateLine();
}

void CAxeDialog::OnSetfocusEdit1stvalue() 
{
	// TODO: Add your control notification handler code here
	m_pState->UpdateStateLine();
}

void CAxeDialog::OnKillfocusEdit2ndvalue() 
{
	// TODO: Add your control notification handler code here
	m_pState->UpdateStateLine();
}

void CAxeDialog::OnSetfocusEdit2ndvalue() 
{
	// TODO: Add your control notification handler code here
	m_pState->UpdateStateLine();
}

void CAxeDialog::OnRadioLinear() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_pAxe->SetLogarithmic((m_nLinear==1)?TRUE:FALSE);
	
}

void CAxeDialog::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_pAxe->SetLogarithmic((m_nLinear==1)?TRUE:FALSE);
	
}
