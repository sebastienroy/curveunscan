// FlatThicknessCorrector.cpp: implementation of the CFlatThicknessCorrector class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "CurveUnscan.h"
#include "FlatThicknessCorrector.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


IMPLEMENT_SERIAL(CFlatThicknessCorrector,CObject,1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFlatThicknessCorrector::CFlatThicknessCorrector(CContinuousCurve* pCurve)
:CAbstractThicknessCorrector(pCurve)
{

}

// protected constructor used by the serialization
CFlatThicknessCorrector::CFlatThicknessCorrector()
:	CAbstractThicknessCorrector(NULL)
{

}

CFlatThicknessCorrector::~CFlatThicknessCorrector()
{

}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

void CFlatThicknessCorrector::CompensateThickness(CList<CPoint,CPoint> &pointList, bool bTopFollow)
{
	int offset=m_nThickness/2;
	if(0==offset)
		{
		return;
		}
	if(!bTopFollow)
		{
		offset*=-1;
		}
	POSITION pos=pointList.GetHeadPosition();
	while(NULL!=pos)
		{
		POSITION previousPos=pos;
		CPoint currentPoint=pointList.GetNext(pos);
		CPoint newPoint=currentPoint;
		newPoint.y=newPoint.y+offset;
		pointList.SetAt(previousPos,newPoint);
		}
}

CAbstractThicknessCorrector* CFlatThicknessCorrector::Clone(CContinuousCurve* pCurve)
{
	CFlatThicknessCorrector* aClone=new CFlatThicknessCorrector(pCurve);
	aClone->m_nThickness=m_nThickness;
	return aClone;
}

void CFlatThicknessCorrector::Serialize(CArchive &ar)
{
	CAbstractThicknessCorrector::Serialize(ar);

	// that's all folks!
}
