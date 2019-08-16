// BezierCurve.h: interface for the CBezierCurve class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BEZIERCURVE_H__43E31B9A_F4CD_4DEF_B9F9_473BE9D10496__INCLUDED_)
#define AFX_BEZIERCURVE_H__43E31B9A_F4CD_4DEF_B9F9_473BE9D10496__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SplineCurve.h"

class CCoordSyst;
class CBezierQuickDraw;

class CBezierCurve : public CSplineCurve  
{
DECLARE_SERIAL(CBezierCurve)

public:
	CBezierCurve();
	CBezierCurve(CCoordSyst *pCoord);
	virtual ~CBezierCurve();

protected:
	CBezierCurve(const CBezierCurve& other);

public:
	// drawing optimization
	virtual void EndQuickDraw(CDC* pDC, const CPoint& pt);
	virtual void MoveQuickDraw(CDC* pDC, const CPoint& pt);
	virtual void BeginQuickDraw(CDC* pDC, const CPoint& pt);
	// tools
	virtual bool SetNodeModification(const CPoint &pt);
	virtual bool EndModification();
	virtual bool AddNodeFront(const CPoint& pt);
	virtual bool AddNodeBack(const CPoint& pt);
	// general
	virtual CCurve* Clone() const;

protected:
	virtual CSplineNode* InsertNode(CSplineSegment* pSegment, double t);
	virtual CSplineSegment* CreateSegment(int nPoints, 
											CSplineCurve* pCurve, 
											CSplineNode* pFrontNode, 
											CSplineNode* pBackNode,
											bool bMutable=false);
	virtual CSplineNode* CreateNode(CPoint pt);

protected:
	mutable CBezierQuickDraw* m_pQuickDraw;
};

#endif // !defined(AFX_BEZIERCURVE_H__43E31B9A_F4CD_4DEF_B9F9_473BE9D10496__INCLUDED_)
