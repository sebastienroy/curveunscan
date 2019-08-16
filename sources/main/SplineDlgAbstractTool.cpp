// SplineDlgAbstractTool.cpp: implementation of the CSplineDlgAbstractTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "SplineDlgAbstractTool.h"
#include "SplineDialog.h"
#include "UnscanView.h"

#include <Dm/SplineCurve.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSplineDlgAbstractTool::CSplineDlgAbstractTool(CSplineDialog* pDialog, CSplineCurve* pCurve)
:	m_pDialog(pDialog),
	m_pCurve(pCurve)
{
}

CSplineDlgAbstractTool::~CSplineDlgAbstractTool()
{

}

void CSplineDlgAbstractTool::StartPick(const CPoint &pt, bool bModif1, bool bModif2)
{
	// default implementation do nothing	
}

void CSplineDlgAbstractTool::MovePick(const CPoint &pt, bool bModif1, bool bModif2)
{
	m_pCurve->MoveSelection(pt,bModif1,bModif2);
	
	// draw
	CUnscanView* pView=m_pDialog->GetView();
	CClientDC dc(pView);
	pView->OnPrepareDC(&dc);

	m_pCurve->MoveQuickDraw(&dc,pt);
}

void CSplineDlgAbstractTool::EndPick(const CPoint &pt, bool bModif1, bool bModif2)
{
	m_pCurve->EndModification();
	
	// draw
	CUnscanView* pView=m_pDialog->GetView();
	CClientDC dc(pView);
	pView->OnPrepareDC(&dc);

	m_pCurve->EndQuickDraw(&dc,pt);
}

CString CSplineDlgAbstractTool::getToolComment()
{
	return CString();
}
