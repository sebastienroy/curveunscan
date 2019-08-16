// BezierCurve.cpp: implementation of the CBezierCurve class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BezierCurve.h"

#include "CoordSyst.h"
#include "BezierNode.h"
#include "BezierSegment.h"
#include "BezierQuickDraw.h"

#include <assert.h>

#include <algorithm>
using namespace std;

IMPLEMENT_SERIAL(CBezierCurve,CObject,1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBezierCurve::CBezierCurve()
:	CSplineCurve(),
	m_pQuickDraw(NULL)
{
	
}

CBezierCurve::CBezierCurve(const CBezierCurve &other)
:	m_pQuickDraw(NULL)
{

}

CBezierCurve::CBezierCurve(CCoordSyst *pCoord)
:	CSplineCurve(pCoord),
	m_pQuickDraw(NULL)
{

}

CBezierCurve::~CBezierCurve()
{
	delete m_pQuickDraw;
}

//////////////////////////////////////////////////////////////////////
// Interfaces, pure virtual functions
//////////////////////////////////////////////////////////////////////


CCurve* CBezierCurve::Clone() const
{
	CBezierCurve* pNewCurve=new CBezierCurve(m_pCoordSyst);
	pNewCurve->operator =(*this);
	return pNewCurve;
}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

CSplineNode* CBezierCurve::CreateNode(CPoint pt)
{
	return new CBezierNode(this, pt);

}

CSplineSegment* CBezierCurve::CreateSegment(int nPoints, 
											CSplineCurve *pCurve, 
											CSplineNode *pFrontNode, 
											CSplineNode *pBackNode,
											bool bMutable/*=false*/)
{
	return new CBezierSegment(nPoints,pCurve,pFrontNode,pBackNode,bMutable);
}

bool CBezierCurve::AddNodeBack(const CPoint& pt)
{
	CSplineCurve::AddNodeBack(pt);

	assert(NULL!=m_pActiveNode);
	CBezierNode* pNode=static_cast<CBezierNode*>(m_pActiveNode);
	pNode->SetSelection(CBezierNode::kBackPointSelected);
	pNode->SetState(CBezierNode::kCreationState);

	return true;
}

bool CBezierCurve::AddNodeFront(const CPoint& pt)
{
	CSplineCurve::AddNodeFront(pt);

	assert(NULL!=m_pActiveNode);
	CBezierNode* pNode=static_cast<CBezierNode*>(m_pActiveNode);
	pNode->SetSelection(CBezierNode::kFrontPointSelected);
	pNode->SetState(CBezierNode::kCreationState);

	return true;

}

bool CBezierCurve::EndModification()
{
	if(NULL!=m_pActiveNode)
	{
		CBezierNode* pNode=static_cast<CBezierNode*>(m_pActiveNode);
		pNode->SetSelection(CBezierNode::kNothingSelected);
		pNode->SetState(CBezierNode::kNormalState);
		m_pActiveNode=NULL;
	}
	return true;

}

bool CBezierCurve::SetNodeModification(const CPoint &pt)
{
	if(m_NodeList.empty())
	{
		return false;
	}

	m_pActiveNode=NULL;
	CBezierNode* pNode=NULL;

	// try to select influence point
	list<CSplineNode*>::const_iterator iterPoint=m_NodeList.begin();
	while( (NULL==m_pActiveNode)&&(iterPoint!=m_NodeList.end()) )
	{
		pNode=static_cast<CBezierNode*>(*iterPoint);
		if(pNode->SelectPointAt(pt))
		{
			m_pActiveNode=pNode;
		}
		iterPoint++;
	}

	// try to select position
	if(NULL==m_pActiveNode)
	{
		list<CSplineNode*>::const_iterator iterPosition=m_NodeList.begin();
		while( (NULL==m_pActiveNode)&&(iterPosition!=m_NodeList.end()) )
		{
			pNode=static_cast<CBezierNode*>(*iterPosition);
			if(pNode->SelectPositionAt(pt))
			{
				m_pActiveNode=pNode;
			}
			iterPosition++;
		}

	}

	if(NULL!=m_pActiveNode)
	{
		pNode=static_cast<CBezierNode*>(m_pActiveNode);	// enfoncer le clou
		pNode->SetState(CBezierNode::kModificationState);
	}

	return (NULL!=m_pActiveNode);
}

// Note that pSegment will be deleted
CSplineNode* CBezierCurve::InsertNode(CSplineSegment *pSegment, double t)
{
	CBezierSegment* pBSegment=static_cast<CBezierSegment*>(pSegment);
	
	//--- create node modify neighbours
	CBezierNode* pNewNode=pBSegment->CreateIndermediateNode(t);
	if(NULL==pNewNode)
	{
		return NULL;
	}
	pNewNode->SetSelection(CBezierNode::kPositionSelected);
	//--- modify neighbours
	pBSegment->ReshapeInfluencePoints(t);
	//--- create new segments
	CSplineNode* pFrontNode=pSegment->GetFrontNode();
	CSplineNode* pBackNode=pSegment->GetBackNode();
	CBezierSegment* pNewFrontSegment=new CBezierSegment(m_nPointsPerSegment,this,pFrontNode,pNewNode);
	pNewFrontSegment->Compute();
	CBezierSegment* pNewBackSegment=new CBezierSegment(m_nPointsPerSegment,this,pNewNode,pBackNode);
	pNewBackSegment->Compute();


	//--- reorganize the lists
	// get location
	list<CSplineNode*>::iterator backNodePos=find(m_NodeList.begin(),m_NodeList.end(),pBackNode);
	assert(m_NodeList.end()!=backNodePos);
	list<CSplineSegment*>::iterator segmentPos=find(m_SegmentList.begin(),m_SegmentList.end(),pSegment);
	assert(m_SegmentList.end()!=segmentPos);
	// insert new node
	m_NodeList.insert(backNodePos,pNewNode);
	// insert new segment
	m_SegmentList.insert(segmentPos,pNewFrontSegment);
	m_SegmentList.insert(segmentPos,pNewBackSegment);
	// remove old segment
	m_SegmentList.erase(segmentPos);
	// delete it now
	delete pSegment;

	return pNewNode;
	
}

void CBezierCurve::BeginQuickDraw(CDC *pDC, const CPoint &pt)
{
	if(NULL!=m_pActiveNode)
	{
		delete m_pQuickDraw;
		m_pQuickDraw=new CBezierQuickDraw(static_cast<CBezierNode*>(m_pActiveNode));
	}
}

void CBezierCurve::MoveQuickDraw(CDC *pDC, const CPoint &pt)
{
	if(NULL==m_pQuickDraw)
	{
		BeginQuickDraw(pDC,pt);
	}
	if(NULL!=m_pActiveNode)
	{
		m_pQuickDraw->Draw(pDC);
	}
}

void CBezierCurve::EndQuickDraw(CDC *pDC, const CPoint &pt)
{
	delete m_pQuickDraw;
	m_pQuickDraw=NULL;
}
