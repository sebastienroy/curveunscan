// SplineDlgAddBackTool.h: interface for the CSplineDlgAddBackTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLINEDLGADDBACKTOOL_H__C61E5DD0_B23A_4FF0_BFFE_295EF6E9DDB8__INCLUDED_)
#define AFX_SPLINEDLGADDBACKTOOL_H__C61E5DD0_B23A_4FF0_BFFE_295EF6E9DDB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SplineDlgAbstractTool.h"

class CSplineDlgAddBackTool : public CSplineDlgAbstractTool  
{
public:
	CSplineDlgAddBackTool(CSplineDialog* pDialog, CSplineCurve* pCurve);
	virtual ~CSplineDlgAddBackTool();

public:
	virtual CString getToolComment();
	virtual ToolKind GetKind();
	virtual void StartPick(const CPoint &pt, bool bModif1, bool bModif2);

};

#endif // !defined(AFX_SPLINEDLGADDBACKTOOL_H__C61E5DD0_B23A_4FF0_BFFE_295EF6E9DDB8__INCLUDED_)
