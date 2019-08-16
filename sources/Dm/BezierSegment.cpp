// BezierSegment.cpp: implementation of the CBezierSegment class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <Dm/BezierSegment.h>
#include <Dm/BezierNode.h>

#include <Utilities/Tools.h>

#include <assert.h>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBezierSegment::CBezierSegment(int nPoints,
							   CSplineCurve* pCurve, 
							   CSplineNode* pFrontNode,
							   CSplineNode* pBackNode, 
							   bool bMutable/*=false*/)
:	CSplineSegment(nPoints,pCurve,pFrontNode,pBackNode,bMutable)
{

}

CBezierSegment::~CBezierSegment()
{

}

void CBezierSegment::Compute()
{
	m_PointList.clear();

	ComputeCoefs();

	// compute points
	// curves are build from front (beginning) to back (end)
	double h=1/(double)m_nPoints;
	for(int counter=0;counter<=m_nPoints;counter++)
	{
		double t=h*(double)counter;
		double x=(((m_Ax*t)+m_Bx)*t+m_Cx)*t+m_Dx;
		double y=(((m_Ay*t)+m_By)*t+m_Cy)*t+m_Dy;
		m_PointList.push_back(CPoint(CTools::Round(x),CTools::Round(y)));
	}
}

void CBezierSegment::ComputeCoefs()
{
	assert( (m_pBackNode!=NULL) && (m_pFrontNode!=NULL) );	

	// create aliases 
	const CPoint& pt0=m_pFrontNode->GetPosition();
	const CPoint& pt3=m_pBackNode->GetPosition();
	const CPoint pt1=pt0+static_cast<CBezierNode*>(m_pFrontNode)->GetBackPoint();
	const CPoint pt2=pt3+static_cast<CBezierNode*>(m_pBackNode)->GetFrontPoint();

	// compute intermediate calculus values
	m_Ax=(double)(pt3.x-3*pt2.x+3*pt1.x-pt0.x);
	m_Bx=(double)(3*pt2.x-6*pt1.x+3*pt0.x);
	m_Cx=(double)(3*pt1.x-3*pt0.x);
	m_Dx=(double)pt0.x;

	m_Ay=(double)(pt3.y-3*pt2.y+3*pt1.y-pt0.y);
	m_By=(double)(3*pt2.y-6*pt1.y+3*pt0.y);
	m_Cy=(double)(3*pt1.y-3*pt0.y);
	m_Dy=(double)pt0.y;
}

CBezierNode* CBezierSegment::CreateIndermediateNode(double t)
{
	assert( (t>=0)&&(t<=1) );

	if(!m_bComputed)	
	{
		ComputeCoefs();	
	}

	// compute point position
	double x=(((m_Ax*t)+m_Bx)*t+m_Cx)*t+m_Dx;
	double y=(((m_Ay*t)+m_By)*t+m_Cy)*t+m_Dy;
	CPoint ptPosition(CTools::Round(x),CTools::Round(y));

	// compute slope
	double dx=(((3.0*m_Ax*t)+2.0*m_Bx)*t+m_Cx)/3.0;
	double dy=(((3.0*m_Ay*t)+2.0*m_By)*t+m_Cy)/3.0;

	// compute front point
	double dxFront=-1.0*t*dx;
	double dyFront=-1.0*t*dy;
	CPoint ptFront(CTools::Round(dxFront),CTools::Round(dyFront));
	if(CTools::Distance(ptFront,CPoint(0,0))<=GetHitTolerance())
	{
		ptFront=CPoint(0,0);
	}

	// compute back point
	double dxBack=(1.0-t)*dx;
	double dyBack=(1.0-t)*dy;
	CPoint ptBack(CTools::Round(dxBack),CTools::Round(dyBack));
	if(CTools::Distance(ptBack,CPoint(0,0))<=GetHitTolerance())
	{
		ptBack=CPoint(0,0);
	}

	// create node
	CBezierNode* pNewNode=new CBezierNode(m_pCurve,ptPosition,ptFront,ptBack);

	return pNewNode;
}

void CBezierSegment::ReshapeInfluencePoints(double t)
{
	assert( (t>0)&&(t<1.0) );
	assert( (m_pBackNode!=NULL) && (m_pFrontNode!=NULL) );	

	static_cast<CBezierNode*>(m_pFrontNode)->ReshapeBackPoint(t);
	static_cast<CBezierNode*>(m_pBackNode)->ReshapeFrontPoint(1.0-t);
}

