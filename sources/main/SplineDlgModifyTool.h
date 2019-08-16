// SplineDlgModifyTool.h: interface for the CSplineDlgModifyTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLINEDLGMODIFYTOOL_H__4EA00268_0115_4B01_9838_F12D15959325__INCLUDED_)
#define AFX_SPLINEDLGMODIFYTOOL_H__4EA00268_0115_4B01_9838_F12D15959325__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SplineDlgAbstractTool.h"

class CSplineDlgModifyTool : public CSplineDlgAbstractTool  
{
public:
	CSplineDlgModifyTool(CSplineDialog* pDialog, CSplineCurve* pCurve);
	virtual ~CSplineDlgModifyTool();

public:
	virtual CString getToolComment();
	virtual ToolKind GetKind();
	virtual void StartPick(const CPoint &pt, bool bModif1, bool bModif2);

};

#endif // !defined(AFX_SPLINEDLGMODIFYTOOL_H__4EA00268_0115_4B01_9838_F12D15959325__INCLUDED_)
