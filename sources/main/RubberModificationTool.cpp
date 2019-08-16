// RubberModificationTool.cpp: implementation of the CRubberModificationTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "RubberModificationTool.h"
#include <Dm/ContinuousCurve.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRubberModificationTool::CRubberModificationTool(CContinuousCurve* pCurve)
:CAbstractModificationTool(pCurve)
{

}

CRubberModificationTool::~CRubberModificationTool()
{

}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

CRect CRubberModificationTool::Apply(const CPoint &ptA, const CPoint &ptB) const
{
	CRect rect;
	if(ptA.x==ptB.x)
		{
		rect=m_pCurve->ErasePoint(ptB);
		}
	else
		{
		rect=m_pCurve->EraseLine(ptA,ptB);
		}
	return rect;
}
