// SplineDlgAddFrontTool.cpp: implementation of the CSplineDlgAddFrontTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "SplineDlgAddFrontTool.h"
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

CSplineDlgAddFrontTool::CSplineDlgAddFrontTool(CSplineDialog* pDialog, CSplineCurve* pCurve)
:	CSplineDlgAbstractTool(pDialog,pCurve)
{
}

CSplineDlgAddFrontTool::~CSplineDlgAddFrontTool()
{

}

void CSplineDlgAddFrontTool::StartPick(const CPoint &pt, bool bModif1, bool bModif2)
{
	if(!m_pCurve->AddNodeFront(pt))
	{	
		// should not go here...
		CString msg;
		msg.LoadString(IDS_SPLINE_CANNOT_ADD_NEW_ONE);
		m_pDialog->MessageBox(msg,NULL,MB_ICONINFORMATION|MB_OK);
	}

	// draw
	CUnscanView* pView=m_pDialog->GetView();
	CClientDC dc(pView);
	pView->OnPrepareDC(&dc);

	m_pCurve->MoveQuickDraw(&dc,pt);
}

CSplineDlgAbstractTool::ToolKind CSplineDlgAddFrontTool::GetKind()
{
	return kAddFront;
}

CString CSplineDlgAddFrontTool::getToolComment()
{
	CString strComment;
	strComment.LoadString(IDS_SPLINE_TOOL_ADD_FRONT);
	return strComment;

}
