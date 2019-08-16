// SplineDlgAddFrontTool.h: interface for the CSplineDlgAddFrontTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLINEDLGADDFRONTTOOL_H__8D055109_1CF0_430A_A798_B83BEF1BF113__INCLUDED_)
#define AFX_SPLINEDLGADDFRONTTOOL_H__8D055109_1CF0_430A_A798_B83BEF1BF113__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SplineDlgAbstractTool.h"

class CSplineDlgAddFrontTool : public CSplineDlgAbstractTool  
{
public:
	CSplineDlgAddFrontTool(CSplineDialog* pDialog, CSplineCurve* pCurve);
	virtual ~CSplineDlgAddFrontTool();

public:
	virtual CString getToolComment();
	virtual ToolKind GetKind();
	virtual void StartPick(const CPoint &pt, bool bModif1, bool bModif2);

};

#endif // !defined(AFX_SPLINEDLGADDFRONTTOOL_H__8D055109_1CF0_430A_A798_B83BEF1BF113__INCLUDED_)
