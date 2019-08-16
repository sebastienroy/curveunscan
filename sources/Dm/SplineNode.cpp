// SplineNode.cpp: implementation of the CSplineNode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SplineNode.h"
#include "SplineCurve.h"

#include <Utilities/Tools.h>

#include <assert.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSplineNode::CSplineNode(CSplineCurve* pCurve, CPoint pt)
:	m_Position(pt),
	m_bSelected(false),
	m_pBackSegment(NULL),
	m_pFrontSegment(NULL),
	m_pCurve(pCurve)
{

}

CSplineNode::CSplineNode()
:	m_Position(0,0),
	m_bSelected(false),
	m_pBackSegment(NULL),
	m_pFrontSegment(NULL),
	m_pCurve(NULL)
{

}

CSplineNode::~CSplineNode()
{
	assert( (NULL==m_pBackSegment)&&(NULL==m_pFrontSegment) );
}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

const CPoint& CSplineNode::GetPosition() const
{
	return m_Position;
}

CSplineNode& CSplineNode::operator =(const CSplineNode &other)
{
	m_Position=other.m_Position;
	m_pCurve=other.m_pCurve;
	return *this;
}

void CSplineNode::SetFrontSegment(CSplineSegment *pSegment)
{
	m_pFrontSegment=pSegment;
}

void CSplineNode::SetBackSegment(CSplineSegment *pSegment)
{
	m_pBackSegment=pSegment;
}

void CSplineNode::BackSegmentRemoved(CSplineSegment* pSegment)
{
	if(m_pBackSegment==pSegment)
	{
		m_pBackSegment=NULL;
	}
}

void CSplineNode::FrontSegmentRemoved(CSplineSegment* pSegment)
{
	if(m_pFrontSegment==pSegment)
	{
		m_pFrontSegment=NULL;
	}
}

bool CSplineNode::MoveSelection(const CPoint &pt, bool bModif1, bool bModif2)
{
	assert(false);	// pure virtual method.
	return false;
}

CSplineSegment* CSplineNode::GetFrontSegment()
{
	return m_pFrontSegment;
}

CSplineSegment* CSplineNode::GetBackSegment()
{
	return m_pBackSegment;
}

// returns true if the position has changed
bool CSplineNode::MovePosition(const CPoint &pt)
{
	if(pt!=m_Position)
	{
		m_Position=pt;
		return true;
	}
	else
	{
		return false;
	}
}

void CSplineNode::SetCurve(CSplineCurve *pCurve)
{
	m_pCurve=pCurve;
}

BOOL CSplineNode::Draw(CDC *pDC) const
{
	int size=m_pCurve->GetHitTolerance();
	CRect rect(m_Position.x-size,m_Position.y-size,m_Position.x+size+1,m_Position.y+size+1);
	pDC->Rectangle(&rect);

	return TRUE;
}

void CSplineNode::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	if(ar.IsStoring())
	{
		ar << m_Position;
	}
	else
	{
		ar >> m_Position;
	}
}

bool CSplineNode::IsPresentOn(CPoint &point) const
{
	return (CTools::Distance(m_Position,point)<=m_pCurve->GetHitTolerance());
}
