// DiscreteCurve.h: interface for the CDiscreteCurve class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISCRETECURVE_H__FA768672_0362_4640_9B35_0F25D6183539__INCLUDED_)
#define AFX_DISCRETECURVE_H__FA768672_0362_4640_9B35_0F25D6183539__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Curve.h"
class CCoordSyst;
class CDiscreteCurve;

class CDiscreteCurve : public CCurve  
{
DECLARE_SERIAL(CDiscreteCurve)

public:
	CDiscreteCurve(CDiscreteCurve& otherCurve);
	CDiscreteCurve();
	virtual ~CDiscreteCurve();

public:
	virtual CResults * GetResults();
	virtual CCurve* Clone() const;
	virtual void Serialize(CArchive &ar);
	virtual BOOL IsPresentOn(CPoint point) const;
	POSITION AddPoint(CPoint point);
	void RemovePoint(POSITION pos);
	CDiscreteCurve(CCoordSyst* pCoord);
	BOOL Draw(CDC* pDC) const;
	virtual BOOL IsDiscreteCurve() const;
	CDiscreteCurve& operator =(const CDiscreteCurve &otherCurve);

};

#endif // !defined(AFX_DISCRETECURVE_H__FA768672_0362_4640_9B35_0F25D6183539__INCLUDED_)
