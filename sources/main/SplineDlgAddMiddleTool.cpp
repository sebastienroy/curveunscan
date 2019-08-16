// SplineDlgAddMiddleTool.cpp: implementation of the CSplineDlgAddMiddleTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "UnscanView.h"
#include "SplineDlgAddMiddleTool.h"
#include "SplinedlgModifyTool.h"
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

CSplineDlgAddMiddleTool::CSplineDlgAddMiddleTool(CSplineDialog* pDialog, CSplineCurve* pCurve)
:	CSplineDlgAbstractTool(pDialog,pCurve)
{
}

CSplineDlgAddMiddleTool::~CSplineDlgAddMiddleTool()
{

}

void CSplineDlgAddMiddleTool::StartPick(const CPoint &pt, bool bModif1, bool bModif2)
{
	if(!m_pCurve->AddNodeMiddle(pt))
	{
		CString msg;
		msg.LoadString(IDS_SPLINE_CANNOT_ADD_MIDDLEPOINT);
		m_pDialog->MessageBox(msg,NULL,MB_ICONINFORMATION|MB_OK);
		m_pDialog->GetView()->PickingStopped();
	}
	else // change mode to modification tool
	{
		CSplineDialog* pDialog=m_pDialog;
		CSplineDlgModifyTool* newTool=new CSplineDlgModifyTool(m_pDialog,m_pCurve);
		m_pDialog->SetState(newTool);		
	}
}

CSplineDlgAbstractTool::ToolKind CSplineDlgAddMiddleTool::GetKind()
{
	return kAddMiddle;
}

CString CSplineDlgAddMiddleTool::getToolComment()
{
	CString strComment;
	strComment.LoadString(IDS_SPLINE_TOOL_ADD_MIDDLE);
	return strComment;

}
