// SplineDlgRemoveTool.cpp: implementation of the CSplineDlgRemoveTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "UnscanView.h"
#include "SplineDlgRemoveTool.h"
#include "SplineDlgAddBackTool.h"
#include "SplineDialog.h"

#include <Dm/SplineCurve.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSplineDlgRemoveTool::CSplineDlgRemoveTool(CSplineDialog* pDialog, CSplineCurve* pCurve)
:	CSplineDlgAbstractTool(pDialog,pCurve)
{
}

CSplineDlgRemoveTool::~CSplineDlgRemoveTool()
{

}

void CSplineDlgRemoveTool::StartPick(const CPoint &pt, bool bModif1, bool bModif2)
{
	if(!m_pCurve->RemoveNodeAt(pt))
	{	
		// should not go here...
		CString msg;
		msg.LoadString(IDS_SPLINE_CANNOT_REMOVE_NODE);
		m_pDialog->MessageBox(msg,NULL,MB_ICONINFORMATION|MB_OK);
		m_pDialog->GetView()->PickingStopped();
	}
	if(0==m_pCurve->GetNodeCount())
	{
		CSplineDialog* pDialog=m_pDialog;
		CSplineDlgAddBackTool* newTool=new CSplineDlgAddBackTool(m_pDialog,m_pCurve);
		m_pDialog->SetState(newTool);
	}
}

CSplineDlgAbstractTool::ToolKind CSplineDlgRemoveTool::GetKind()
{
	return kRemove;
}

CString CSplineDlgRemoveTool::getToolComment()
{
	CString strComment;
	strComment.LoadString(IDS_SPLINE_TOOL_REMOVE);
	return strComment;

}
