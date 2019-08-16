// SplineDlgModifyTool.cpp: implementation of the CSplineDlgModifyTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "UnscanView.h"
#include "SplineDlgModifyTool.h"
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

CSplineDlgModifyTool::CSplineDlgModifyTool(CSplineDialog* pDialog, CSplineCurve* pCurve)
:	CSplineDlgAbstractTool(pDialog,pCurve)
{
}

CSplineDlgModifyTool::~CSplineDlgModifyTool()
{

}

void CSplineDlgModifyTool::StartPick(const CPoint &pt, bool bModif1, bool bModif2)
{
	if(!m_pCurve->SetNodeModification(pt))
	{	
		// should not go here...
		CString msg;
		msg.LoadString(IDS_SPLINE_CANNOT_MODIFY_POINT);
		m_pDialog->MessageBox(msg,NULL,MB_ICONINFORMATION|MB_OK);
		m_pDialog->GetView()->PickingStopped();
	}
}

CSplineDlgAbstractTool::ToolKind CSplineDlgModifyTool::GetKind()
{
	return kModify;
}

CString CSplineDlgModifyTool::getToolComment()
{
	CString strComment;
	strComment.LoadString(IDS_SPLINE_TOOL_MODIFY);
	return strComment;

}
