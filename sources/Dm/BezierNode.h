// BezierNode.h: interface for the CBezierNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BEZIERNODE_H__50719D79_BE98_47C4_8D49_722BA6858924__INCLUDED_)
#define AFX_BEZIERNODE_H__50719D79_BE98_47C4_8D49_722BA6858924__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SplineNode.h"

class CSplineCurve;

class CBezierNode : public CSplineNode  
{
DECLARE_SERIAL(CBezierNode)

	//--- Public typedefs
public:
	typedef enum
	{
		kNormalState,
		kCreationState,
		kModificationState
	} state;

	typedef enum
	{
		kNothingSelected,
		kPositionSelected,
		kFrontPointSelected,
		kBackPointSelected
	} selection;

	struct Data
	{
		CPoint ptPosition;
		CPoint ptBack;
		CPoint ptFront;
	};

	//--- Construction / destruction
public:
	CBezierNode();
	CBezierNode(CSplineCurve* pCurve, const CPoint& pt);
	CBezierNode(CSplineCurve* pCurve, const CPoint& pt, const CPoint& ptFront, const CPoint& ptBack);
	virtual ~CBezierNode();

protected:
	CBezierNode(const CBezierNode& other);	// should not be used

	//--- Interface
public:
	virtual bool IsPresentOn(CPoint &point) const;
	virtual void Serialize(CArchive& ar);
	void GetData(Data& outData);
	virtual BOOL Draw(CDC *pDC) const;
	void ReshapeFrontPoint(double coef);
	void ReshapeBackPoint(double coef);
	bool SelectPointAt(const CPoint& pt);
	bool SelectPositionAt(const CPoint& pt);
	virtual bool MoveSelection(const CPoint& pt, bool bModif1, bool bModif2);
	void SetState(state newState);
	void SetSelection(selection sel);
	CSplineNode* Clone();
	bool ArePointsLinked() const;
	bool LinkPoints(bool value=true);
	const CPoint& GetFrontPoint() const;
	const CPoint& GetBackPoint() const;
	CBezierNode& operator =(const CBezierNode &other);

	//--- Internal methods
protected:
	bool MovePoints(CPoint& mainPt, CPoint& otherPt, const CPoint& pt, bool bModif1, bool bModif2);
	void SetLinkState(bool& bModif1, bool& bModif2);
	void CopyMembers(const CBezierNode& other);
	void SetPointsColinear(const CPoint& ptA, CPoint& ptB);

	//--- Attributes
protected:
	// NB : influence points are stored relatively to the position point
	CPoint m_FrontPoint;	
	CPoint m_BackPoint;
	bool m_bPointsLinked;

	state m_State;
	selection m_Selection;

};

#endif // !defined(AFX_BEZIERNODE_H__50719D79_BE98_47C4_8D49_722BA6858924__INCLUDED_)
