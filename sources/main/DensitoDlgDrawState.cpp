// DensitoDlgDrawState.cpp: implementation of the CDensitoDlgDrawState class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "DensitoDlgDrawState.h"
#include "DensitoDlgWaitState.h"
#include "DensitoDlgPickState.h"
#include "UnscanView.h"
#include "UnscanDoc.h"
#include "enums.h"

#include "DensitometryDialog.h"

#include <Dm/DensityCurve.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDensitoDlgDrawState::CDensitoDlgDrawState(CDensitometryDialog* pDlg)
:	CDensitoDlgAbstractState(pDlg)
{

	m_pDlg->UpdateData(TRUE);
	m_pDlg->m_bDrawSegment=TRUE;
	m_pDlg->m_bPickTop=FALSE;
	m_pDlg->m_bPickBottom=FALSE;
	m_pDlg->UpdateData(FALSE);

	m_pDlg->m_CursorShape=kDrawLineCursor;
}

CDensitoDlgDrawState::~CDensitoDlgDrawState()
{

}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

void CDensitoDlgDrawState::CheckDrawButton()
{
	m_pDlg->UpdateData(TRUE);
	new CDensitoDlgWaitState(m_pDlg);
}

void CDensitoDlgDrawState::CheckPickColorButton(bool bIsTop)
{
	m_pDlg->UpdateData(TRUE);
	new CDensitoDlgPickState(m_pDlg,bIsTop);	
}

LONG CDensitoDlgDrawState::StartPick(UINT wParam, LONG lParam)
{
	m_ptFrom=*((CPoint*)lParam);
	m_ptTo=m_ptFrom;
	return 0;
}

LONG CDensitoDlgDrawState::MovePick(UINT wParam, LONG lParam)
{
	CUnscanView* pView=m_pDlg->GetView();
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

LONG CDensitoDlgDrawState::EndPick(UINT wParam, LONG lParam)
{
	CUnscanView* pView=m_pDlg->GetView();
	CClientDC dc(pView);
	pView->OnPrepareDC(&dc);

	InvertLine(&dc,m_ptFrom,m_ptTo);


	CPoint* pPoint=(CPoint*)lParam;
	if(MK_SHIFT&wParam)
	{
		SetStraightLine(&m_ptFrom,pPoint);
	}
	m_ptTo=*pPoint;
	m_pDlg->SetFocus();

	if(m_ptFrom==m_ptTo)	// single point not valid
	{
		return 0;
	}

	m_pDlg->m_pCurve->SetPosition(m_ptFrom,m_ptTo);

	m_pDlg->UpdateButtons();

	CUnscanDoc* pDoc=m_pDlg->GetDocument();
	pDoc->UpdateAllViews(NULL);


	new CDensitoDlgWaitState(m_pDlg);

	return 0;
}

LONG CDensitoDlgDrawState::ScrollOff(UINT wParam, LONG lParam)
{
	CUnscanView* pView=m_pDlg->GetView();
	CClientDC dc(pView);
	pView->OnPrepareDC(&dc);

	m_ptTo=*((CPoint*)lParam);
	InvertLine(&dc,m_ptFrom,m_ptTo);

	return 0;
}


void CDensitoDlgDrawState::InvertLine(CDC *pDC, CPoint from, CPoint to)
{
	int nOldMode=pDC->SetROP2(R2_NOT);
	pDC->MoveTo(from);
	pDC->LineTo(to);
	pDC->SetROP2(nOldMode);
}

void CDensitoDlgDrawState::SetStraightLine(const CPoint *ptA, CPoint *ptB)
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
