// PenModificationTool.cpp: implementation of the CPenModificationTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "PenModificationTool.h"
#include <Dm/ContinuousCurve.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPenModificationTool::CPenModificationTool(CContinuousCurve* pCurve)
:CAbstractModificationTool(pCurve)
{

}

CPenModificationTool::~CPenModificationTool()
{

}

CRect CPenModificationTool::Apply(const CPoint &ptA, const CPoint &ptB) const
{
	CRect rect;
	if(ptA.x==ptB.x)
		{
		rect=m_pCurve->SetPoint(ptB);
		}
	else
		{
		rect=m_pCurve->SetLine(ptA,ptB);
		}
	return rect;
}
