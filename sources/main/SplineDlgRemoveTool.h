// SplineDlgRemoveTool.h: interface for the CSplineDlgRemoveTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLINEDLGREMOVETOOL_H__75482869_7527_47DC_BF52_B80DBFD4251D__INCLUDED_)
#define AFX_SPLINEDLGREMOVETOOL_H__75482869_7527_47DC_BF52_B80DBFD4251D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SplineDlgAbstractTool.h"

class CSplineDlgRemoveTool : public CSplineDlgAbstractTool  
{
public:
	virtual CString getToolComment();
	virtual ToolKind GetKind();
	virtual void StartPick(const CPoint &pt, bool bModif1, bool bModif2);
	CSplineDlgRemoveTool(CSplineDialog* pDialog, CSplineCurve* pCurve);
	virtual ~CSplineDlgRemoveTool();

};

#endif // !defined(AFX_SPLINEDLGREMOVETOOL_H__75482869_7527_47DC_BF52_B80DBFD4251D__INCLUDED_)
