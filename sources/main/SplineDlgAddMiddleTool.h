// SplineDlgAddMiddleTool.h: interface for the CSplineDlgAddMiddleTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLINEDLGADDMIDDLETOOL_H__777DE1ED_8081_4A49_B8C7_A5A717E6EE91__INCLUDED_)
#define AFX_SPLINEDLGADDMIDDLETOOL_H__777DE1ED_8081_4A49_B8C7_A5A717E6EE91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SplineDlgAbstractTool.h"

class CSplineDlgAddMiddleTool : public CSplineDlgAbstractTool  
{
public:
	CSplineDlgAddMiddleTool(CSplineDialog* pDialog, CSplineCurve* pCurve);
	virtual ~CSplineDlgAddMiddleTool();

public:
	virtual CString getToolComment();
	virtual ToolKind GetKind();
	virtual void StartPick(const CPoint& pt, bool bModif1, bool bModif2);

};

#endif // !defined(AFX_SPLINEDLGADDMIDDLETOOL_H__777DE1ED_8081_4A49_B8C7_A5A717E6EE91__INCLUDED_)
