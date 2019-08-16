// SplineCurve.cpp: implementation of the CSplineCurve class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SplineCurve.h"
#include "SplineSegment.h"
#include "CoordSyst.h"
#include "SplineResults.h"

#include <Utilities/Tools.h>

#include <assert.h>

#include <algorithm>
using namespace std;

//////////////////////////////////////////////////////////////////////
// Static members
//////////////////////////////////////////////////////////////////////

int CSplineCurve::m_nHitTolerance=2;
int CSplineCurve::m_nPointsPerSegment=30;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSplineCurve::CSplineCurve()
:	CCurve(),
	m_bSegmentsConstructed(false),
	m_pActiveNode(NULL)
{

}

CSplineCurve::CSplineCurve(CCoordSyst *pCoord)
:	CCurve(pCoord),
	m_bSegmentsConstructed(false),
	m_pActiveNode(NULL)
{

}

CSplineCurve::CSplineCurve(const CSplineCurve &other)
:	m_bSegmentsConstructed(false),
	m_pActiveNode(NULL)
{
	// this constructor should not be used
	assert(false);
}

CSplineCurve::~CSplineCurve()
{
	ClearSegments();
	ClearNodes();
}


//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

void CSplineCurve::Serialize(CArchive &ar)
{
	CCurve::Serialize(ar);

	if(ar.IsStoring())
	{
		ar << m_NodeList.size();
		list<CSplineNode*>::const_iterator iter;
		for(iter=m_NodeList.begin();iter!=m_NodeList.end();iter++)
		{
			ar << *iter;
		}
	}
	else
	{
		int nNodeNb=0;
		ar >> nNodeNb;
		for(int counter=0;counter<nNodeNb;counter++)
		{
			CObject *pObj=NULL;
			ar >> pObj;
			CSplineNode* pNode=dynamic_cast<CSplineNode*>(pObj);
			assert(NULL!=pNode);
			m_NodeList.push_back(pNode);
		}
		Compute();
	}

}

// Method call by the document to select some curve...
BOOL CSplineCurve::IsPresentOn(CPoint point) const
{
	bool isPresent=false;
	list<CSplineNode*>::const_iterator iterNode;
	for(iterNode=m_NodeList.begin();(iterNode!=m_NodeList.end())&&(!isPresent);iterNode++)
	{
		isPresent=(*iterNode)->IsPresentOn(point);
	}

	if(!isPresent)
	{
		list<CSplineSegment*>::const_iterator iterSegment;
		for(iterSegment=m_SegmentList.begin();(iterSegment!=m_SegmentList.end())&&(!isPresent);iterSegment++)
		{
			isPresent=(*iterSegment)->IsPresentOn(point);
		}
	}
	return isPresent;
}

int CSplineCurve::GetNodeCount()
{
	return m_NodeList.size();
}

int CSplineCurve::GetHitTolerance()
{
	return m_nHitTolerance;
}

CSplineNode* CSplineCurve::CreateNode(CPoint pt)
{
	assert(false);
	return NULL;

}

bool CSplineCurve::AddNodeBack(const CPoint& pt)
{
	CSplineNode* pPreviousNode=NULL;
	if(!m_NodeList.empty())
	{
		pPreviousNode=m_NodeList.back();
	}

	CSplineNode* pNode=CreateNode(pt);
	m_NodeList.push_back(pNode);

	if(NULL!=pPreviousNode)
	{
		CSplineSegment* pSegment=CreateSegment(m_nPointsPerSegment,this,pPreviousNode,pNode);
		pSegment->Compute();
		m_SegmentList.push_back(pSegment);
	}

	m_pActiveNode=pNode;

	return true;
}

CSplineSegment* CSplineCurve::CreateSegment(int nPoints, 
											CSplineCurve *pCurve, 
											CSplineNode *pFrontNode, 
											CSplineNode *pBackNode,
											bool bMutable/*=false*/)
{
	assert(false);
	return NULL;
}

bool CSplineCurve::AddNodeFront(const CPoint& pt)
{
	CSplineNode* pPreviousNode=NULL;
	if(!m_NodeList.empty())
	{
		pPreviousNode=m_NodeList.front();
	}

	CSplineNode* pNode=CreateNode(pt);
	m_NodeList.push_front(pNode);

	if(NULL!=pPreviousNode)
	{
		CSplineSegment* pSegment=CreateSegment(m_nPointsPerSegment,this,pNode,pPreviousNode);
		pSegment->Compute();
		m_SegmentList.push_front(pSegment);
	}

	m_pActiveNode=pNode;

	return true;
}


CSplineCurve& CSplineCurve::operator =(const CSplineCurve &otherCurve)
{
	// Generic Curve attributes
	m_CurveName=otherCurve.m_CurveName;
	m_IdentifierNumber=otherCurve.m_IdentifierNumber;
	m_pCoordSyst=otherCurve.m_pCoordSyst;
	m_Selected=otherCurve.m_Selected;
	m_Color=otherCurve.m_Color;
	m_ModifiedFlag=otherCurve.m_ModifiedFlag;
	if(m_PointList.GetCount()>0)
		{
		m_PointList.RemoveAll();
		}
	POSITION pos=otherCurve.m_PointList.GetHeadPosition();
	while(pos!=NULL)
		{
		m_PointList.AddTail(otherCurve.m_PointList.GetNext(pos));
		}

	// Results
	delete m_pResults;
	m_pResults=NULL;
	if(NULL!=otherCurve.m_pResults)
		{
		// clone using the first curve for construction
		// the current object may be not valid
		m_pResults=otherCurve.m_pResults->Clone(const_cast<CSplineCurve*>(&otherCurve));	
		m_pResults->SetOwner(this);								
		}

	// Spline specific
	ClearNodes();
	list<CSplineNode*>::const_iterator iter;
	for(iter=otherCurve.m_NodeList.begin();iter!=otherCurve.m_NodeList.end();iter++)
	{
		CSplineNode* pNode=(*iter)->Clone();
		m_NodeList.push_back(pNode);
	}

	ClearSegments();
	m_bSegmentsConstructed=false;

	return *this;
}

void CSplineCurve::ConstructSegments()
{
	if(m_NodeList.size()<2)
	{
		return;
	}

	list<CSplineNode*>::const_iterator iter=m_NodeList.begin();
	CSplineNode* pNodeBack=*iter;
	CSplineNode* pNodeFront=NULL;
	iter++;
	while(iter!=m_NodeList.end())
	{
		pNodeFront=pNodeBack;
		pNodeBack=*iter;
		CSplineSegment* pSegment=CreateSegment(m_nPointsPerSegment,this,pNodeFront,pNodeBack);
		m_SegmentList.push_back(pSegment);

		iter++;
	}
	m_bSegmentsConstructed=true;
}

void CSplineCurve::ClearSegments()
{
	if(!m_SegmentList.empty())
	{
		list<CSplineSegment*>::const_iterator iter;
		for(iter=m_SegmentList.begin();iter!=m_SegmentList.end();iter++)
		{
			delete (*iter);
		}
	}
	m_SegmentList.clear();
}

void CSplineCurve::ClearNodes()
{
	if(!m_NodeList.empty())
	{
		list<CSplineNode*>::const_iterator iter;
		for(iter=m_NodeList.begin();iter!=m_NodeList.end();iter++)
		{
			delete (*iter);
		}
	}
	m_NodeList.clear();

}

void CSplineCurve::Compute()
{
	if(m_NodeList.size()<2)
	{
		return;
	}

	if(!m_bSegmentsConstructed)
	{
		ConstructSegments();
	}
	list<CSplineSegment*>::const_iterator iter;
	for(iter=m_SegmentList.begin();iter!=m_SegmentList.end();iter++)
	{
		(*iter)->Compute();
	}
}

bool CSplineCurve::MoveSelection(const CPoint &pt, bool bModif1, bool bModif2)
{
	if(NULL==m_pActiveNode)
	{
		return false;
	}

	bool bSomethingModified=m_pActiveNode->MoveSelection(pt,bModif1,bModif2);
	if(bSomethingModified)
	{
		CSplineSegment* pFrontSegment=m_pActiveNode->GetFrontSegment();
		CSplineSegment* pBackSegment=m_pActiveNode->GetBackSegment();

		if(NULL!=pFrontSegment)
		{
			pFrontSegment->Compute();
		}
		if(NULL!=pBackSegment)
		{
			pBackSegment->Compute();
		}

	}
	return bSomethingModified;
}

bool CSplineCurve::EndModification()
{
	assert(false);
	return true;
}

bool CSplineCurve::RemoveNodeAt(const CPoint &pt)
{
	CSplineNode* pNode=GetNodeAtPosition(pt);
	if(NULL==pNode)
	{
		return false;
	}

	CSplineNode* pBackNode=NULL;
	CSplineNode* pFrontNode=NULL;

	CSplineSegment* pFrontSegment=pNode->GetFrontSegment();
	CSplineSegment* pBackSegment=pNode->GetBackSegment();

	if(NULL!=pBackSegment)
	{
		pBackNode=pBackSegment->GetBackNode();
		m_SegmentList.remove(pBackSegment);
	}
	if(NULL!=pFrontSegment)
	{
		pFrontNode=pFrontSegment->GetFrontNode();
		m_SegmentList.remove(pFrontSegment);
	}

	delete pBackSegment;
	pBackSegment=NULL;

	delete pFrontSegment;
	pFrontSegment=NULL;

	m_NodeList.remove(pNode);
	delete pNode;
	pNode=NULL;

	// create new segment if necessary
	if( (NULL!=pBackNode)&&(NULL!=pFrontNode) )
	{
		CSplineSegment* pNewSegment=CreateSegment(m_nPointsPerSegment,this,pFrontNode,pBackNode);
		pNewSegment->Compute();
		// insert it in the list
		CSplineSegment* pNextSegment=pBackNode->GetBackSegment();
		if(NULL==pNextSegment)
		{
			m_SegmentList.push_back(pNewSegment);
		}
		else
		{
			list<CSplineSegment*>::iterator nextPos=find(m_SegmentList.begin(),m_SegmentList.end(),pNextSegment);
			m_SegmentList.insert(nextPos,pNewSegment);
		}
	}


	return true;
}

CSplineNode* CSplineCurve::GetNodeAtPosition(const CPoint &pt)
{
	if(m_NodeList.empty())
	{
		return NULL;
	}

	CSplineNode* pNode=NULL;
	list<CSplineNode*>::const_iterator iter(m_NodeList.begin());
	while( (NULL==pNode)&&(iter!=m_NodeList.end()) )
	{
		CPoint currentPt=(*iter)->GetPosition();
		if(CTools::Distance(pt,currentPt)<=m_nHitTolerance)
		{
			pNode=*iter;
		}
		iter++;
	}

	return pNode;
}

bool CSplineCurve::SetNodeModification(const CPoint &pt)
{
	assert(false);	// abstract method
	return true;
}

bool CSplineCurve::AddNodeMiddle(const CPoint &pt)
{
	if(m_SegmentList.empty())
	{
		return false;
	}

	CSplineNode* pAddedNode=NULL;

	list<CSplineSegment*>::const_iterator iterSegment(m_SegmentList.begin());
	bool found=false;
	CSplineSegment* pSegment=NULL;
	double t;
	while( (!found)&&(iterSegment!=m_SegmentList.end()) )
	{
		found=(*iterSegment)->HitTest(pt,t);
		if(found)
		{
			pSegment=*iterSegment;
		}
		iterSegment++;
	}

	if(found)
	{
		pAddedNode=InsertNode(pSegment,t);
		m_pActiveNode=pAddedNode;
	}

	return (NULL!=pAddedNode);
}

BOOL CSplineCurve::Draw(CDC *pDC) const
{
	CPen pen(PS_SOLID,(m_Selected)?2:1,m_Color);
	CPen* oldPen=pDC->SelectObject(&pen);

	// draw segments
	list<CSplineSegment*>::const_iterator iterSegment;
	for(iterSegment=m_SegmentList.begin();iterSegment!=m_SegmentList.end();iterSegment++)
	{
		(*iterSegment)->Draw(pDC);
	}

	// draw nodes
	list<CSplineNode*>::const_iterator iterNode;
	for(iterNode=m_NodeList.begin();iterNode!=m_NodeList.end();iterNode++)
	{
		(*iterNode)->Draw(pDC);
	}

	pDC->SelectObject(oldPen);
	return TRUE;
}

void CSplineCurve::Clear()
{
	ClearSegments();
	ClearNodes();
	m_pActiveNode=NULL;
}

void CSplineCurve::GetSegmentPoints(int nPointsPerSegment, vector<CLogicPoint> &outPointVect)
{
	if(m_NodeList.size()<2)
	{
		return;
	}

	outPointVect.clear();
	list<CSplineNode*>::const_iterator iter=m_NodeList.begin();
	CSplineNode *pBackNode=*iter;
	CSplineNode *pFrontNode=NULL;

	iter++;
	while(iter!=m_NodeList.end())
	{
		pFrontNode=pBackNode;
		pBackNode=*iter;
		iter++;

		// get physical points
		CSplineSegment *pSegment=CreateSegment(nPointsPerSegment,this,pFrontNode,pBackNode,true/*mutable segment*/);
		pSegment->Compute();
		vector<CPoint> physicalPoints;
		pSegment->GetPoints(physicalPoints);
		delete pSegment;
		pSegment=NULL;

		// conversion to logical points
		bool isEnd=(iter==m_NodeList.end());
		int nTot=(isEnd)?nPointsPerSegment+1:nPointsPerSegment;
		for(int nCounter=0;nCounter<nTot;nCounter++)
		{
			CLogicPoint lPt=m_pCoordSyst->ToLogic(physicalPoints[nCounter]);
			outPointVect.push_back(lPt);
		}
	}
}

CResults* CSplineCurve::GetResults()
{
	if(NULL==m_pResults)
	{
		m_pResults=new CSplineResults(this);
	}
	return m_pResults;
}
