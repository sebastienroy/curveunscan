// SplineResults.h: interface for the CSplineResults class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLINERESULTS_H__2CD22F13_A798_4BFC_99EE_6EBF8350A0EA__INCLUDED_)
#define AFX_SPLINERESULTS_H__2CD22F13_A798_4BFC_99EE_6EBF8350A0EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Results.h"


class CSplineResults : public CResults  
{
public:
	CSplineResults();
	CSplineResults(CCurve *pCurve);
	virtual ~CSplineResults();

public:
	void SetPointsPerSegmentNb(int nb);
	int GetPointsPerSegmentNb();
	virtual void Serialize(CArchive &ar);
	virtual void Construct();
	virtual CResults* Clone(CCurve* pCurve=NULL) const;

protected:
	int m_nPointsPerSegment;
	static int m_nDefaultPointsPerSegment;


DECLARE_SERIAL(CSplineResults)

};

#endif // !defined(AFX_SPLINERESULTS_H__2CD22F13_A798_4BFC_99EE_6EBF8350A0EA__INCLUDED_)
