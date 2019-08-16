// SplineNode.h: interface for the CSplineNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLINENODE_H__39A0D092_3741_4B63_8149_8141120CEF1A__INCLUDED_)
#define AFX_SPLINENODE_H__39A0D092_3741_4B63_8149_8141120CEF1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSplineSegment;
class CSplineCurve;

class CSplineNode  : public CObject
{
public:
	CSplineNode();
	CSplineNode(CSplineCurve* pCurve, CPoint pt);
	virtual ~CSplineNode();

public:
	virtual bool IsPresentOn(CPoint &point) const;
	virtual void Serialize(CArchive& ar);
	virtual BOOL Draw(CDC *pDC) const;
	void SetCurve(CSplineCurve* pCurve);
	CSplineSegment* GetBackSegment();
	CSplineSegment* GetFrontSegment();
	virtual bool MoveSelection(const CPoint& pt, bool bModif1, bool bModif2) =0;
	void FrontSegmentRemoved(CSplineSegment* pSegment);
	void BackSegmentRemoved(CSplineSegment* pSegment);
	void SetBackSegment(CSplineSegment* pSegment);
	void SetFrontSegment(CSplineSegment* pSegment);
	CSplineNode& operator =(const CSplineNode &other);
	virtual CSplineNode* Clone() =0;
	const CPoint& GetPosition() const;

protected:
	bool MovePosition(const CPoint& pt);

protected:
	CPoint m_Position;
	bool m_bSelected;
	CSplineCurve* m_pCurve;

	mutable CSplineSegment* m_pBackSegment;
	mutable CSplineSegment* m_pFrontSegment;

};

#endif // !defined(AFX_SPLINENODE_H__39A0D092_3741_4B63_8149_8141120CEF1A__INCLUDED_)
