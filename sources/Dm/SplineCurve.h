// SplineCurve.h: interface for the CSplineCurve class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLINECURVE_H__F5B1CC0E_1966_4370_A35A_15013A988019__INCLUDED_)
#define AFX_SPLINECURVE_H__F5B1CC0E_1966_4370_A35A_15013A988019__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Curve.h"
#include "SplineNode.h"
#include "SplineSegment.h"
#include "logicPoint.h"

#include <list>
#include <vector>
using namespace std;


// CSplineCurve : abstract class
class CSplineCurve : public CCurve  
{
	//---------- Interface -------------------------

	// construction / destruction
public:
	CSplineCurve();
	CSplineCurve(CCoordSyst* pCoord);
	virtual ~CSplineCurve();

	// restricted contructor
private:
	CSplineCurve(const CSplineCurve& other);

	// interface with mmi (construction dialog)
public:
	// tools
	virtual bool AddNodeFront(const CPoint& pt);
	virtual bool AddNodeBack(const CPoint& pt);
	virtual bool AddNodeMiddle(const CPoint& pt);
	virtual bool RemoveNodeAt(const CPoint& pt);
	virtual bool SetNodeModification(const CPoint& pt);
	// tools common
	virtual bool MoveSelection(const CPoint &pt, bool bModif1, bool bModif2);
	virtual bool EndModification();
	// drawing optimization
	virtual void EndQuickDraw(CDC* pDC, const CPoint& pt) =0;
	virtual void MoveQuickDraw(CDC* pDC, const CPoint& pt) =0;
	virtual void BeginQuickDraw(CDC* pDC, const CPoint& pt) =0;

	// interface with document and other stuffs
public:
	virtual CResults* GetResults();
	int GetNodeCount();
	virtual BOOL IsPresentOn(CPoint point) const;
	virtual void Serialize(CArchive& ar);
	CSplineCurve& operator =(const CSplineCurve &other);
	void Compute();

	// internal public methods (used by agregated objects)
public:
	virtual void GetSegmentPoints(int nPointsPerSegment,vector<CLogicPoint> &outPointVect);	// Results
	void Clear();
	virtual BOOL Draw(CDC* pDC) const;
	virtual CSplineNode* GetNodeAtPosition(const CPoint& pt);
	static int GetHitTolerance();

	//----------- Implementation ------------------
protected:
	void ClearNodes();
	void ClearSegments();
	void ConstructSegments();
	virtual CSplineNode* InsertNode(CSplineSegment* pSegment, double t) =0;
	virtual CSplineNode* CreateNode(CPoint pt)=0;
	virtual CSplineSegment* CreateSegment(int nPoints, 
										CSplineCurve* pCurve, 
										CSplineNode* pFrontNode, 
										CSplineNode* pBackNode,
										bool bMutable=false)=0;

	//------------ Attributes ---------------------
protected:
	list<CSplineNode*> m_NodeList;

	static int m_nHitTolerance;
	static int m_nPointsPerSegment;

	// The segments do not contain any specific information. But they allow to speed up 
	//  the drawing and other stufs by keeping in memory intermediate calculous results.
	//  They also contain some algorithms (path formula, adding intermediate point,...)
	mutable list<CSplineSegment*> m_SegmentList;
	mutable bool m_bSegmentsConstructed;

	// construction state attributes
	mutable CSplineNode* m_pActiveNode;
};	

#endif // !defined(AFX_SPLINECURVE_H__F5B1CC0E_1966_4370_A35A_15013A988019__INCLUDED_)
