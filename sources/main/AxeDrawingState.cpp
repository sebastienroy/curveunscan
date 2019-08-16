// AxeDrawingState.cpp: implementation of the CAxeDrawingState class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "UnscanDoc.h"
#include "AxeDrawingState.h"
#include "AxeDialog.h"
#include "UnscanView.h"
#include "AxePointPickingState.h"
#include "AxeWaitState.h"
#include "Sequence.h"
#include "enums.h"
#include "math.h"

#include <Dm/Axe.h>
#include <Dm/CoordSyst.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAxeDrawingState::CAxeDrawingState(CAxeDialog* theDialog)
:CAxeAbstractState(theDialog),
m_pAxe(theDialog->m_pAxe)
{	
	m_pDialog->m_bCheckAxe=TRUE;
	m_pDialog->m_bCheckPt1=FALSE;
	m_pDialog->m_bCheckPt2=FALSE;
	m_pDialog->UpdateData(FALSE);

	m_pDialog->m_CursorShape=kDrawLineCursor;

	UpdateStateLine();
}

CAxeDrawingState::~CAxeDrawingState()
{

}

LONG CAxeDrawingState::StartPick(UINT wParam, LONG lParam)
{
	m_ptFrom=*((CPoint*)lParam);
	m_ptTo=m_ptFrom;
	return 0;
}

LONG CAxeDrawingState::MovePick(UINT wParam, LONG lParam)
{
	CUnscanView* pView=m_pDialog->m_pSequence->GetView();
	CClientDC dc(pView);
	pView->OnPrepareDC(&dc);

	CPoint* pPoint=(CPoint*)lParam;
	if(MK_SHIFT&wParam)
		{
		SetStraightLine(&m_ptFrom,pPoint);
		}
	InvertLine(&dc,m_ptFrom,m_ptTo);
	InvertLine(&dc,m_ptFrom,*pPoint);
	m_ptTo=*pPoint;

	return 0;
}

LONG CAxeDrawingState::EndPick(UINT wParam, LONG lParam)
{
	CUnscanView* pView=m_pDialog->m_pSequence->GetView();
	CClientDC dc(pView);
	pView->OnPrepareDC(&dc);

	InvertLine(&dc,m_ptFrom,m_ptTo);


	CPoint* pPoint=(CPoint*)lParam;
	if(MK_SHIFT&wParam)
		{
		SetStraightLine(&m_ptFrom,pPoint);
		}
	m_ptTo=*pPoint;
	m_pDialog->SetFocus();

	if(m_ptFrom==m_ptTo)	// single point not valid
		{
		return 0;
		}

	// Si l'autre axe a ete  initialise, verification non ||
	if( m_pDialog->m_pOtherAxe->IsDefined() )
		{
		CPoint otherFrom=m_pDialog->m_pOtherAxe->GetFrom();
		CPoint otherTo=m_pDialog->m_pOtherAxe->GetTo();
		double delta;
		double a1,a2,b1,b2,u1,u2,v1,v2;
		a1=(double)otherFrom.x;
		a2=(double)m_ptFrom.x; 
		b1=(double)otherFrom.y;
		b2=(double)m_ptFrom.y;
		u1=(double)(otherTo.x)-a1;
		u2=(double)(m_ptTo.x)-a2;
		v1=(double)(otherTo.y)-b1;
		v2=(double)(m_ptTo.y)-b2;
		delta=(u2*v1)-(u1*v2);
		if(fabs(delta)<1.0e-5)
			{
			CString msg;
			msg.LoadString(IDS_NOT_PARALLEL);
			m_pDialog->MessageBox(msg,"CurveUnscan",MB_OK|MB_ICONINFORMATION);
			return 0;
			}
		}

	m_pAxe->SetPosition(m_ptFrom,m_ptTo);
	m_pAxe->GetCoordSyst()->CalculateOrigin();

	m_pDialog->UpdateOKButton();
	CUnscanDoc* pDoc=m_pDialog->m_pSequence->GetDocument();
	pDoc->UpdateAllViews(NULL);
	if(!m_pAxe->GetScalePoint(1)->PositionIsDefined())
		{
		m_pDialog->EnablePoint(1,TRUE);
		m_pDialog->m_ValueEditPt1.SetFocus();
		m_pDialog->m_ValueEditPt1.SetSel(0,-1);
		new CAxePointPickingState(m_pDialog,1);
		}
	else if(!m_pAxe->GetScalePoint(2)->PositionIsDefined())
		{
		m_pDialog->EnablePoint(2,TRUE);
		m_pDialog->m_ValueEditPt2.SetFocus();
		m_pDialog->m_ValueEditPt2.SetSel(0,-1);
		new CAxePointPickingState(m_pDialog,2);
		}
	else
		{
		if(!m_pAxe->GetScalePoint(1)->ValueIsDefined())
			{
			m_pDialog->m_ValueEditPt1.SetFocus();
			m_pDialog->m_ValueEditPt1.SetSel(0,-1);
			}
		else if(!m_pAxe->GetScalePoint(2)->ValueIsDefined())
			{
			m_pDialog->m_ValueEditPt2.SetFocus();
			m_pDialog->m_ValueEditPt2.SetSel(0,-1);
			}
		new CAxeWaitState(m_pDialog);
		}
	return 0;
}

LONG CAxeDrawingState::ScrollOff(UINT wParam, LONG lParam)
{
	CUnscanView* pView=m_pDialog->m_pSequence->GetView();
	CClientDC dc(pView);
	pView->OnPrepareDC(&dc);

	m_ptTo=*((CPoint*)lParam);
	InvertLine(&dc,m_ptFrom,m_ptTo);

	return 0;
}

void CAxeDrawingState::SetStraightLine(const CPoint *ptA, CPoint *ptB)
{
	int deltaX=ptB->x-ptA->x;
	deltaX=(deltaX>=0)?deltaX:(-1)*deltaX;
	int deltaY=ptB->y-ptA->y;
	deltaY=(deltaY>=0)?deltaY:(-1)*deltaY;
	if(deltaX>deltaY)
		{
		ptB->y=ptA->y;
		}
	else
		{
		ptB->x=ptA->x;
		}
}

void CAxeDrawingState::InvertLine(CDC *pDC, CPoint from, CPoint to)
{
	int nOldMode=pDC->SetROP2(R2_NOT);
	pDC->MoveTo(from);
	pDC->LineTo(to);
	pDC->SetROP2(nOldMode);
}

void CAxeDrawingState::CheckAxeButton()
{
	m_pDialog->UpdateData(TRUE);
	if(!m_pAxe->IsDefined())
		{
		m_pDialog->m_bCheckAxe=TRUE;
		m_pDialog->UpdateData(FALSE);
		return;
		}
	else
		{
		new CAxeWaitState(m_pDialog);
		}
}

void CAxeDrawingState::CheckPointButton(int nButton)
{
	new CAxePointPickingState(m_pDialog,nButton);
}

void CAxeDrawingState::UpdateStateLine()
{
	CWnd* pStatus=m_pDialog->GetDlgItem(IDC_STATIC_STATUS);

	CAxe* pAxe=m_pDialog->m_pAxe;
	bool bIsX=(pAxe==pAxe->GetCoordSyst()->GetXAxe());

	CString strFormat;
	strFormat.LoadString(IDS_AXE_PLEASE_DRAW);
	CString axeName;
	axeName.LoadString(bIsX?IDS_X_AXIS_NAME:IDS_Y_AXIS_NAME);
	CString msg;
	msg.Format(strFormat,LPCTSTR(axeName));

	pStatus->SetWindowText(msg);
	pStatus->RedrawWindow();

}
