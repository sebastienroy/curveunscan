// LimitDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CurveUnscan.h"
#include "UnscanDoc.h"
#include "Sequence.h"
#include "LimitDialog.h"

#include <Dm/ContinuousCurve.h>
#include <Dm/CurveElement.h>
#include <Dm/Limit.h>
#include <Dm/PartialCurve.h>
#include <Dm/LogicPoint.h>
#include <Dm/CoordSyst.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLimitDialog dialog



CLimitDialog::CLimitDialog(UINT ID, CUnscanView *pView, CSequence *pSequence, CContinuousCurve *pCurve)
	:CConstructionDialog(ID, pView, pSequence)
	{
	m_pCurve=pCurve;
	m_RightCheck=m_LeftCheck=m_Change=FALSE;
	}

void CLimitDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLimitDialog)
	DDX_Control(pDX, IDC_EDIT_RIGHTVALUE, m_RightEdit);
	DDX_Control(pDX, IDC_EDIT_LEFTVALUE, m_LeftEdit);
	DDX_Check(pDX, IDC_CHECK_LEFT, m_LeftCheck);
	DDX_Check(pDX, IDC_CHECK_RIGHT, m_RightCheck);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLimitDialog, CDialog)
	//{{AFX_MSG_MAP(CLimitDialog)
	ON_EN_CHANGE(IDC_EDIT_LEFTVALUE, OnChangeEditLeftvalue)
	ON_EN_CHANGE(IDC_EDIT_RIGHTVALUE, OnChangeEditRightvalue)
	ON_BN_CLICKED(IDC_CHECK_LEFT, OnCheckLeft)
	ON_BN_CLICKED(IDC_CHECK_RIGHT, OnCheckRight)
	ON_MESSAGE(WM_END_PICK,OnEndPick)
	ON_BN_CLICKED(IDC_PREVIOUS, OnPrevious)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLimitDialog message handlers


void CLimitDialog::OnChangeEditLeftvalue() 
	{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if(GetFocus()!=&m_LeftEdit)
		{
		return;
		}
	if(!ActionConfirmed())
		{
		SetFocus();
		m_LeftEdit.SetValue(m_pLeftLimit->GetValue());
		UpdateData(FALSE);
		return;
		}
	if(m_LeftEdit.IsEmpty())
		{
		m_pLeftLimit->EraseValue();
		}
	else
		{
		m_pLeftLimit->SetValue(m_LeftEdit.GetValue());
		}
	m_Change=TRUE;
	UpdateOKButton();
	m_pCurve->SetHandModification(FALSE);
//	UpdateObjects();
	}

void CLimitDialog::OnChangeEditRightvalue() 
	{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if(GetFocus()!=&m_RightEdit)
		{
		return;
		}
	if(!ActionConfirmed())
		{
		SetFocus();
		m_RightEdit.SetValue(m_pRightLimit->GetValue());
		UpdateData(FALSE);
		return;
		}
	if(m_RightEdit.IsEmpty())
		{
		m_pRightLimit->EraseValue();
		}
	else
		{
		m_pRightLimit->SetValue(m_RightEdit.GetValue());
		}
	m_Change=TRUE;
	UpdateOKButton();
	m_pCurve->SetHandModification(FALSE);
//	UpdateObjects();
	}

BOOL CLimitDialog::OKState()
	{
	return ( (m_pLeftLimit->IsDefined())&&(m_pRightLimit->IsDefined()));
	}

void CLimitDialog::OnCheckLeft() 
	{
	// TODO: Add your control notification handler code here
	m_LeftCheck=!m_LeftCheck;
	m_CursorShape=(m_LeftCheck)?kDrawLineCursor:kDefaultCursor;
	m_RightCheck=FALSE;
	UpdateData(FALSE);
	}

void CLimitDialog::OnCheckRight() 
	{
	// TODO: Add your control notification handler code here
	m_RightCheck=!m_RightCheck;
	m_CursorShape=(m_RightCheck)?kDrawLineCursor:kDefaultCursor;
	m_LeftCheck=FALSE;
	UpdateData(FALSE);
	}

void CLimitDialog::OnEndPick(UINT wParam, LONG lParam)
	{
	if( (m_LeftCheck||m_RightCheck)
		&&(!ActionConfirmed()) )
		{
		return;
		}
	CPoint* point=(CPoint*)lParam;
	CLogicPoint lPoint=(m_pCurve->GetCoordSyst())->ToLogic(*point);
	UpdateData(TRUE);
	if(m_LeftCheck)
		{
		m_LeftEdit.SetValue(lPoint.x);
		m_pLeftLimit->SetValue(lPoint.x);
		m_Change=TRUE;
		m_LeftEdit.SetFocus();
		m_LeftEdit.SetSel(0,-1);
		}
	if(m_RightCheck)
		{
		m_RightEdit.SetValue(lPoint.x);
		m_pRightLimit->SetValue(lPoint.x);
		m_Change=TRUE;
		m_RightEdit.SetFocus();
		m_RightEdit.SetSel(0,-1);
		}
	m_LeftCheck=m_RightCheck=FALSE;
	m_CursorShape=kDefaultCursor;
	UpdateObjects();
	UpdateData(FALSE);
	UpdateOKButton();
	}

// Vérifie que la limite droite est supérieure à la limite gauche
BOOL CLimitDialog::DataValidation()
	{
	// check that values are greater than 0 in the case of a logarithmic axe	
	BOOL bLog=m_pCurve->GetCoordSyst()->GetXAxe()->GetLogarithmic();
	if(bLog)
		{
		if( (m_pRightLimit->GetValue()<=0)||(m_pLeftLimit->GetValue()<=0) )
			{
			CString msg;
			msg.LoadString(IDS_LOG_GREATER_THAN_ZERO3);
			MessageBox(msg,"CurveUnscan",MB_OK|MB_ICONINFORMATION);
			return FALSE;
			}
		}


	BOOL reverse=(m_pCurve->GetCoordSyst())->XAxeIsReverse();
	if( (!reverse)&&(m_pRightLimit->GetValue()<=m_pLeftLimit->GetValue()) )
		{
		CString msg;
		msg.LoadString(IDS_RIGHT_GREATER_THAN_LEFT);
		MessageBox(msg,"CurveUnscan",MB_OK|MB_ICONINFORMATION);
		return FALSE;
		}
	if( (reverse)&&(m_pRightLimit->GetValue()>=m_pLeftLimit->GetValue()) )
		{
		CString msg;
		msg.LoadString(IDS_LEFT_GREATER_THAN_RIGHT);
		MessageBox(msg,"CurveUnscan",MB_OK|MB_ICONINFORMATION);
		return FALSE;
		}
	return TRUE;
	}

void CLimitDialog::UpdateObjects()
	{
	if (!m_Change)
		{
		return;
		}
	POSITION pos=m_pCurve->GetHeadElementPosition();
	CCurveElement* pElement;
	CPoint point;
	while(pos!=NULL)
		{
		pElement=m_pCurve->GetNextElement(pos);
		if(pElement->IsPartialCurve())
			{
			point=((CPartialCurve*)pElement)->GetPosition();
			if( (m_pLeftLimit->HaveIncluded(point))||(m_pRightLimit->HaveIncluded(point)) )
				{
				m_pCurve->RemoveElement(pElement);
				delete pElement;
				}
			}
		}
	m_pCurve->Construct();
	CUnscanDoc* pDoc=m_pSequence->GetDocument();
	pDoc->UpdateAllViews(NULL);
	}

void CLimitDialog::OnPrevious() 
	{
	// TODO: Add your control notification handler code here
	CConstructionDialog::OnPrevious();		
	}

BOOL CLimitDialog::OnInitDialog() 
{
	CConstructionDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_pLeftLimit=m_pCurve->GetLeftLimit();
	m_pRightLimit=m_pCurve->GetRightLimit();
	if(m_pLeftLimit->IsDefined())
		{
		m_LeftEdit.SetValue(m_pLeftLimit->GetValue());
		}
	if(m_pRightLimit->IsDefined())
		{
		m_RightEdit.SetValue(m_pRightLimit->GetValue());
		}
	UpdateData(FALSE);
	m_LeftEdit.SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CLimitDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CConstructionDialog::OnHelpInfo(pHelpInfo);
}

bool CLimitDialog::ActionConfirmed()
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
