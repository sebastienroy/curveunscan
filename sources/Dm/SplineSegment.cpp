// SplineSegment.cpp: implementation of the CSplineSegment class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <Dm/SplineSegment.h>
#include <Dm/SplineCurve.h>

#include <Utilities/Tools.h>

#include <assert.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSplineSegment::CSplineSegment(int nPoints,
							   CSplineCurve* pCurve, 
							   CSplineNode* pFrontNode,
							   CSplineNode* pBackNode, 
							   bool bMutable/*=false*/)
:	m_nPoints(nPoints),
	m_pCurve(pCurve),
	m_pFrontNode(pFrontNode),
	m_pBackNode(pBackNode),
	m_bMutable(bMutable),
	m_bSelected(false),
	m_bComputed(false)
{
	if(!m_bMutable)
	{
		m_pBackNode->SetFrontSegment(this);
		m_pFrontNode->SetBackSegment(this);
	}
}

CSplineSegment::~CSplineSegment()
{
	if( (NULL==m_pBackNode)||(NULL==m_pFrontNode) )
	{
		assert(false);
	}
	m_pBackNode->FrontSegmentRemoved(this);
	m_pFrontNode->BackSegmentRemoved(this);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


void CSplineSegment::Compute()
{
	// virtual method
}

bool CSplineSegment::HitTest(const CPoint &pt)
{
	double t;
	return HitTest(pt,t);
}

// pt is the point where to search for the segment 
// return true if present on that point
// return false if it is the beginning or the ending point
// if true, outT is set to the relative position from the beginning of the segment
bool CSplineSegment::HitTest(const CPoint &pt, double& outT)
{
	if(!m_bComputed)
	{
		Compute();
	}
	assert(m_PointList.size()>1);

	// check from beginning and ending point
	CPoint ptBegin=m_PointList.front();
	if(CTools::Distance(ptBegin,pt)<=GetHitTolerance())
	{
		return false;
	}
	CPoint ptEnd=m_PointList.back();
	if(CTools::Distance(ptEnd,pt)<=GetHitTolerance())
	{
		return false;
	}

	double t=0;
	double h=1.0/(double)m_nPoints;
	int nStep=0;

	list<CPoint>::const_iterator iter=m_PointList.begin();
	CPoint pt1=*iter;
	CPoint pt2;
	iter++;
	bool itsEnd=(iter==m_PointList.end());
	bool found=false;
	while( !found && !itsEnd)
	{
		pt2=pt1;
		pt1=*iter;
		// compute
		int minx=__min(pt1.x,pt2.x)-GetHitTolerance();
		int maxx=__max(pt1.x,pt2.x)+GetHitTolerance();
		if( (pt.x>=minx)&&(pt.x<=maxx) )
		{
			int miny=__min(pt1.y,pt2.y)-GetHitTolerance();
			int maxy=__max(pt1.y,pt2.y)+GetHitTolerance();
			if( (pt.y>=miny)&&(pt.y<=maxy) )
			{
				// compute distance from the point to its projection 
				//   on the current segment
				CPoint ptProj=CTools::GetProjection(pt1,pt2,pt);
				double dist=CTools::Distance(ptProj,pt);

				if(dist<=GetHitTolerance())
				{
					found=true;
					double dRelPos=CTools::GetNormalizedScalar(pt2,pt1,pt);
					t=h*((double)nStep+dRelPos);
				}
			}
		}

		iter++;
		nStep++;
		itsEnd=(iter==m_PointList.end());
	}

	double reallyFound=false;
	if( (found)&&(t>0)&&(t<1) )
	{
		outT=t;
		reallyFound=true;
	}

	return reallyFound;
}

int CSplineSegment::GetHitTolerance()
{
	return CSplineCurve::GetHitTolerance();
}

void CSplineSegment::SetNotComputed()
{
	m_bComputed=false;
}

CSplineNode* CSplineSegment::GetBackNode()
{
	return m_pBackNode;
}

CSplineNode* CSplineSegment::GetFrontNode()
{
	return m_pFrontNode;
}

BOOL CSplineSegment::Draw(CDC *pDC) const
{
	if(m_PointList.size()<2)
	{
		return TRUE;
	}

	list<CPoint>::const_iterator iter=m_PointList.begin();
	CPoint pt=*iter;
	pDC->MoveTo(pt);
	iter++;
	while(iter!=m_PointList.end())
	{
		pt=*iter;
		pDC->LineTo(pt);
		iter++;
	}

	return TRUE;
}

bool CSplineSegment::IsPresentOn(CPoint &point) const
{
	return const_cast<CSplineSegment*>(this)->HitTest(point);
}

void CSplineSegment::GetPoints(vector<CPoint> &outPoints)
{
	list<CPoint>::const_iterator iter;
	for(iter=m_PointList.begin();iter!=m_PointList.end();iter++)
	{
		outPoints.push_back(*iter);
	}
}
