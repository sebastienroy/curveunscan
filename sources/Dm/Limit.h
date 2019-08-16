// Limit.h: interface for the CLimit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIMIT_H__7AAEEBE1_6240_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_LIMIT_H__7AAEEBE1_6240_11D4_935E_0080C7A4F675__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CurveElement.h"

class CLimit : public CCurveElement  
{
DECLARE_SERIAL(CLimit)

public:
	virtual void Serialize(CArchive &ar);
	virtual RelativePosition GetRelativePosition(const CPoint &point) const;
	BOOL EraseValue();
	BOOL RemovePart(CPoint point, BOOL toLeft=TRUE);
	BOOL IsLimit();
	CLimit(CLimit* otherLimit);
	CLimit& operator =(CLimit &otherLimit);
	virtual BOOL HaveIncluded(CPoint point);
	BOOL IsDefined();
	double GetValue();
	void SetValue(double value);
	CLimit(CContinuousCurve* pCurve,BOOL left);
	CLimit();
	virtual ~CLimit();

protected:
	//CCoordSyst* m_pCoordSyst;
	BOOL m_Left;
	BOOL m_Defined;
	double m_Value;
};

#endif // !defined(AFX_LIMIT_H__7AAEEBE1_6240_11D4_935E_0080C7A4F675__INCLUDED_)
