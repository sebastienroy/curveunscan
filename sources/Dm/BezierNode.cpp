// BezierNode.cpp: implementation of the CBezierNode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <Dm/BezierNode.h>
#include <Dm/SplineCurve.h>

#include <Utilities/Tools.h>

#include <math.h>
#include <assert.h>

IMPLEMENT_SERIAL(CBezierNode,CObject,1)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CBezierNode::CBezierNode()
:	CSplineNode(),
	m_State(kNormalState),
	m_Selection(kNothingSelected)
{

}

CBezierNode::CBezierNode(CSplineCurve* pCurve, const CPoint& pt)
:	CSplineNode(pCurve, pt),
	m_FrontPoint(0,0),
	m_BackPoint(0,0),
	m_bPointsLinked(true),
	m_State(kNormalState),
	m_Selection(kNothingSelected)
{

}

CBezierNode::CBezierNode(CSplineCurve* pCurve, const CPoint& pt, const CPoint& ptFront, const CPoint& ptBack)
:	CSplineNode(pCurve, pt),
	m_FrontPoint(ptFront),
	m_BackPoint(ptBack),
	m_bPointsLinked(true),
	m_State(kNormalState),
	m_Selection(kNothingSelected)
{

}

CBezierNode::CBezierNode(const CBezierNode &other)
:	CSplineNode(other.m_pCurve, other.m_Position)
{
	assert(false);
	CopyMembers(other);
}


CBezierNode::~CBezierNode()
{

}

const CPoint& CBezierNode::GetBackPoint() const
{
	return m_BackPoint;
}

const CPoint& CBezierNode::GetFrontPoint() const
{
	return m_FrontPoint;
}

bool CBezierNode::LinkPoints(bool value)
{
	bool bOldValue=m_bPointsLinked;
	m_bPointsLinked=value;
	return bOldValue;
}

bool CBezierNode::ArePointsLinked() const
{
	return m_bPointsLinked;
}

// ptB is set colinear to ptA in relation to the (0,0) point
void CBezierNode::SetPointsColinear(const CPoint &ptA, CPoint &ptB)
{
	static const CPoint nullPoint(0,0);

	if(nullPoint==ptA)
	{
		return;
	}

	double dA=sqrt(ptA.x*ptA.x+ptA.y*ptA.y);
	double dB=sqrt(ptB.x*ptB.x+ptB.y*ptB.y);
	double k=dB/dA;

	ptB.x=(-1)*CTools::Round(k*(double)(ptA.x));
	ptB.y=(-1)*CTools::Round(k*(double)(ptA.y));
}

CSplineNode* CBezierNode::Clone()
{
	CBezierNode* pNewNode=new CBezierNode();
	pNewNode->operator =(*this);
	return pNewNode;
}

CBezierNode& CBezierNode::operator =(const CBezierNode &other)
{
	CSplineNode::operator=(other);
	CopyMembers(other);
	return *this;
}

void CBezierNode::CopyMembers(const CBezierNode &other)
{
	m_BackPoint=other.m_BackPoint;
	m_FrontPoint=other.m_FrontPoint;
	m_bPointsLinked=other.m_bPointsLinked;
}

// called by Bezier curve
void CBezierNode::SetSelection(selection sel)
{
	m_Selection=sel;
}

void CBezierNode::SetState(state newState)
{
	m_State=newState;
}

bool CBezierNode::MoveSelection(const CPoint &pt, bool bModif1, bool bModif2)
{
	switch(m_Selection)
	{
	case kNothingSelected:
		return false;
		break;
	case kPositionSelected:
		return MovePosition(pt);
		break;
	case kFrontPointSelected:
		SetLinkState(bModif1,bModif2);
		return MovePoints(m_FrontPoint,m_BackPoint, pt, bModif1, bModif2);
		break;
	case kBackPointSelected:
		SetLinkState(bModif1,bModif2);
		return MovePoints(m_BackPoint,m_FrontPoint, pt, bModif1, bModif2);
		break;
	default:
		assert(false);
		return false;
	}
}

void CBezierNode::SetLinkState(bool &bModif1, bool &bModif2)
{
	if(bModif1&&bModif2)
	{
		// change nothing
		bModif1=bModif2=false;
	}
	else if(bModif1)
	{
		m_bPointsLinked=true;
	}
	else if(bModif2)
	{
		m_bPointsLinked=false;
	}

}

bool CBezierNode::MovePoints(CPoint &mainPt, 
							 CPoint &otherPt, 
							 const CPoint& pt, 
							 bool bModif1, 
							 bool bModif2)
{
	CPoint rPt;
	//--- threashold distance
	if((CTools::Distance(pt,m_Position))<=m_pCurve->GetHitTolerance())
	{
		rPt=CPoint(0,0);
	}
	else
	{
		rPt=pt-m_Position;
	}

	bool bSomethingModified=false;

	//--- main point
	if(mainPt!=rPt)
	{
		bSomethingModified=true;
		mainPt=rPt;
	}

	//--- secondary point
	CPoint previousOtherPt=otherPt;
	bool bSetSymetric=(   ( (kCreationState==m_State)&&(m_bPointsLinked) )
						||( (kModificationState==m_State)&&(bModif1) )
						);
	bool bSetColinear=m_bPointsLinked;	

	if(bSetSymetric)
	{
		otherPt.x=(-1)*mainPt.x;
		otherPt.y=(-1)*mainPt.y;
	}
	else if(bSetColinear)
	{
		SetPointsColinear(mainPt,otherPt);
	}
	else
	{
		// do nothing
	}

	if(previousOtherPt!=otherPt)
	{
		bSomethingModified=true;
	}

	return bSomethingModified;
}

bool CBezierNode::SelectPositionAt(const CPoint &pt)
{
	static double distMax=(double)m_pCurve->GetHitTolerance();
	double dist=CTools::Distance(m_Position,pt);
	if(dist<=distMax)
	{
		m_Selection=kPositionSelected;
		return true;
	}
	else
	{
		return false;
	}
}

bool CBezierNode::SelectPointAt(const CPoint &pt)
{
	static double distMax=(double)m_pCurve->GetHitTolerance();

	CPoint rPt=pt-m_Position;

	double distFront=CTools::Distance(m_FrontPoint,rPt);
	if(distFront<=distMax)
	{
		m_Selection=kFrontPointSelected;
		return true;
	}
	
	double distBack=CTools::Distance(m_BackPoint,rPt);
	if(distBack<=distMax)
	{
		m_Selection=kBackPointSelected;
		return true;
	}

	return false;
}

void CBezierNode::ReshapeBackPoint(double coef)
{
	double x=coef*(double)m_BackPoint.x;
	double y=coef*(double)m_BackPoint.y;

	CPoint newPoint(CTools::Round(x),CTools::Round(y));
	double minDist=m_pCurve->GetHitTolerance();
	if(CTools::Distance(newPoint,CPoint(0,0))<=minDist)
	{
		newPoint=CPoint(0,0);
	}

	m_BackPoint=newPoint;
}

void CBezierNode::ReshapeFrontPoint(double coef)
{
	double x=coef*(double)m_FrontPoint.x;
	double y=coef*(double)m_FrontPoint.y;

	CPoint newPoint(CTools::Round(x),CTools::Round(y));
	double minDist=m_pCurve->GetHitTolerance();
	if(CTools::Distance(newPoint,CPoint(0,0))<=minDist)
	{
		newPoint=CPoint(0,0);
	}

	m_FrontPoint=newPoint;
}

BOOL CBezierNode::Draw(CDC *pDC) const
{
	CPoint ptFrom=m_Position+m_BackPoint;
	CPoint ptTo=m_Position+m_FrontPoint;

	pDC->MoveTo(ptFrom);
	pDC->LineTo(m_Position);
	pDC->LineTo(ptTo);

	CSplineNode::Draw(pDC);

	int size=m_pCurve->GetHitTolerance();
	CPoint pt=ptFrom;
	pDC->Ellipse(pt.x-size,pt.y-size,pt.x+size+1,pt.y+size+1);
	pt=ptTo;
	pDC->Ellipse(pt.x-size,pt.y-size,pt.x+size+1,pt.y+size+1);

	return TRUE;
}

void CBezierNode::GetData(Data &outData)
{
	outData.ptPosition=m_Position;
	outData.ptBack=m_BackPoint;
	outData.ptFront=m_FrontPoint;
	return;
}

void CBezierNode::Serialize(CArchive &ar)
{
	CSplineNode::Serialize(ar);
	if(ar.IsStoring())
	{
		ar << m_BackPoint;
		ar << m_FrontPoint;
		ar << (BOOL)m_bPointsLinked;
	}
	else
	{
		ar >> m_BackPoint;
		ar >> m_FrontPoint;
		BOOL bLinked;
		ar >> bLinked;
		m_bPointsLinked=(bool)bLinked;
	}
}

bool CBezierNode::IsPresentOn(CPoint &point) const
{
	bool isPresent=CSplineNode::IsPresentOn(point);	// center of the node

	if(!isPresent)
	{
		CPoint ptBack=m_Position+m_BackPoint;
		isPresent=(CTools::Distance(ptBack,point)<=m_pCurve->GetHitTolerance());
	}

	if(!isPresent)
	{
		CPoint ptFront=m_Position+m_FrontPoint;
		isPresent=(CTools::Distance(ptFront,point)<=m_pCurve->GetHitTolerance());
	}
	return isPresent;
}
