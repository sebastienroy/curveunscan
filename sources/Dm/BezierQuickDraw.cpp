// BezierQuickDraw.cpp: implementation of the CBezierQuickDraw class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BezierQuickDraw.h"
#include "BezierNode.h"
#include "SplineSegment.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBezierQuickDraw::CBezierQuickDraw(CBezierNode* pNode)
:	m_pNode(pNode),
	m_bDrawBack(false),
	m_bDrawFront(false),
	m_bAlreadyDrawn(false),
	m_pDrawnNode(NULL),
	m_PtArray(new CPoint[7]),
	m_nPtArrayCount(1)
{
	//--- initialization

	// back node
	CSplineSegment* pBackSegment=pNode->GetBackSegment();
	if(NULL!=pBackSegment)
	{
		CBezierNode* pBackNode=static_cast<CBezierNode*>(pBackSegment->GetBackNode());
		if(NULL!=pBackNode)
		{
			m_bDrawBack=true;
			pBackNode->GetData(m_BackData);
			// awful style!
			m_PtArray[0]=m_BackData.ptPosition;
			m_PtArray[1]=CPoint(m_BackData.ptPosition+m_BackData.ptFront);
			m_nPtArrayCount+=3;
		}
	}
	// front node
	CSplineSegment* pFrontSegment=pNode->GetFrontSegment();
	if(NULL!=pFrontSegment)
	{
		CBezierNode* pFrontNode=static_cast<CBezierNode*>(pFrontSegment->GetFrontNode());
		if(NULL!=pFrontNode)
		{
			m_bDrawFront=true;
			pFrontNode->GetData(m_FrontData);
			int index=m_bDrawBack?6:3;
			m_PtArray[index]=m_FrontData.ptPosition;
			m_PtArray[index-1]=CPoint(m_FrontData.ptPosition+m_FrontData.ptBack);
			
			m_nPtArrayCount+=3;
		}
	}

	UpdateData();
}

CBezierQuickDraw::~CBezierQuickDraw()
{
	delete m_pDrawnNode;
	delete []m_PtArray;
}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

void CBezierQuickDraw::Draw(CDC *pDC)
{

	if(m_bAlreadyDrawn)
	{
		Redraw(pDC);
	}
	UpdateData();
	Redraw(pDC);
	m_bAlreadyDrawn=true;
}

void CBezierQuickDraw::Redraw(CDC *pDC)
{
	int nOldMode=pDC->SetROP2(R2_NOT);

	if(m_nPtArrayCount>1)
	{
		pDC->PolyBezier(m_PtArray,m_nPtArrayCount);
	}
	m_pDrawnNode->Draw(pDC);

	pDC->SetROP2(nOldMode);
	
}

void CBezierQuickDraw::UpdateData()
{
	delete m_pDrawnNode;
	m_pDrawnNode=static_cast<CBezierNode*>(m_pNode->Clone());
	m_pDrawnNode->GetData(m_CurrentData);
	int index=(m_bDrawBack)?3:0;
	if(m_bDrawBack)
	{
		m_PtArray[index-1]=CPoint(m_CurrentData.ptPosition+m_CurrentData.ptBack);
	}
	m_PtArray[index]=m_CurrentData.ptPosition;
	if(m_bDrawFront)
	{
		m_PtArray[index+1]=CPoint(m_CurrentData.ptPosition+m_CurrentData.ptFront);
	}
}
