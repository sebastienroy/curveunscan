// BezierSegment.h: interface for the CBezierSegment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BEZIERSEGMENT_H__97479893_B8F6_4B95_8595_6108517FBC74__INCLUDED_)
#define AFX_BEZIERSEGMENT_H__97479893_B8F6_4B95_8595_6108517FBC74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SplineSegment.h"

class CBezierNode;

class CBezierSegment : public CSplineSegment  
{
public:
	CBezierSegment(int nPoints,
				   CSplineCurve* pCurve, 
				   CSplineNode* pFrontNode,
				   CSplineNode* pBackNode, 
				   bool bMutable=false);
	virtual ~CBezierSegment();

public:
	void ReshapeInfluencePoints(double t);
	CBezierNode* CreateIndermediateNode(double t);
	virtual void Compute();

protected:
	void ComputeCoefs();
	mutable double m_Ax,m_Bx,m_Cx,m_Dx;
	mutable double m_Ay,m_By,m_Cy,m_Dy;
};

#endif // !defined(AFX_BEZIERSEGMENT_H__97479893_B8F6_4B95_8595_6108517FBC74__INCLUDED_)
