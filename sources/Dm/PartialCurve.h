// PartialCurve.h: interface for the CPartialCurve class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARTIALCURVE_H__7AAEEBE2_6240_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_PARTIALCURVE_H__7AAEEBE2_6240_11D4_935E_0080C7A4F675__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CurveElement.h"

class CPartialCurve : public CCurveElement  
{
DECLARE_SERIAL(CPartialCurve)

public:
	virtual void Serialize(CArchive &ar);
	virtual RelativePosition GetRelativePosition(const CPoint &point) const;
	void DeleteContent();
	CPoint GetPoint(int index);
	int GetPointsNumber();
	BOOL RemovePart(CPoint point,BOOL toLeft=TRUE);
	BOOL Construct();
	BOOL HaveIncluded(CPoint point);
	CPartialCurve(CContinuousCurve* pCurve);
	CPoint GetPosition();
	void SetPosition(CPoint point);
	CPartialCurve& operator=(const CPartialCurve &other);
	BOOL IsPartialCurve();
	CPartialCurve(CPartialCurve* pOther);
	CPartialCurve();
	virtual ~CPartialCurve();

protected:
	mutable CArray<CPoint,CPoint> m_PointArray;
	mutable CBmpManager* m_pBmpManager;
	CPoint m_Position;
};

#endif // !defined(AFX_PARTIALCURVE_H__7AAEEBE2_6240_11D4_935E_0080C7A4F675__INCLUDED_)
