// SplineSegment.h: interface for the CSplineSegment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLINESEGMENT_H__9AABA921_5D46_49D2_9BE5_B1592F73FA30__INCLUDED_)
#define AFX_SPLINESEGMENT_H__9AABA921_5D46_49D2_9BE5_B1592F73FA30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>
#include <vector>
using namespace std;

class CSplineNode;
class CSplineCurve;

class CSplineSegment  
{
public:
	CSplineSegment(int nPoints,
					CSplineCurve* pCurve, 
					CSplineNode* pFrontNode,
					CSplineNode* pBackNode, 
					bool bMutable=false);
	virtual ~CSplineSegment();

public:
	virtual void GetPoints(vector<CPoint> &outPoints);
	virtual bool IsPresentOn(CPoint &point) const;
	virtual BOOL Draw(CDC *pDC) const;
	CSplineNode* GetFrontNode();
	CSplineNode* GetBackNode();
	void SetNotComputed();
	static int GetHitTolerance();
	bool HitTest(const CPoint& pt);
	bool HitTest(const CPoint& pt, double& outT);
	virtual void Compute()=0;

protected:
	int m_nPoints;
	list<CPoint> m_PointList;
	CSplineNode *m_pBackNode;
	CSplineNode *m_pFrontNode;
	CSplineCurve *m_pCurve;
	bool m_bSelected;
	bool m_bComputed;
	bool m_bMutable;	// if true, the segment do not declare itself to the nodes

};

#endif // !defined(AFX_SPLINESEGMENT_H__9AABA921_5D46_49D2_9BE5_B1592F73FA30__INCLUDED_)
