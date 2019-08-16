// DensityResultsProcessor.h: interface for the CDensityResultsProcessor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DENSITYRESULTSPROCESSOR_H__3DD239D4_1A5B_4E8B_AD81_1689A978AB84__INCLUDED_)
#define AFX_DENSITYRESULTSPROCESSOR_H__3DD239D4_1A5B_4E8B_AD81_1689A978AB84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LogicPoint.h"

#include <vector>
using namespace std;

class CDensityResults;
class CDensityCurve;
class CCoordSyst;

class CDensityResultsProcessor  
{
	// constructor / desstructor
public:
	CDensityResultsProcessor(CDensityResults *pResults);
	virtual ~CDensityResultsProcessor();

	// methods
public:
	void Build();

protected:
	double GetLinearInterpolation(CPoint pt1, CPoint pt2, double val1, double val2, CLogicPoint lPoint) const;
	CLogicPoint GetFirstLogicPoint();
	bool IsPointBefore(const CPoint &segmentPoint, const CLogicPoint &expectedPhysPoint) const;
	CLogicPoint IterateLogicPoint(const CLogicPoint &pt, int nStep) const;
	double IterateLogicY(double dFirst,int nStep) const;
	double IterateLogicX(double dFirst,int nStep) const;

	// attributes
protected:
	CDensityResults *m_pResults;
	mutable CDensityCurve *m_pCurve;
	mutable CCoordSyst *m_pCoord;
	bool m_bUseX;
	bool m_bIterOnX;
	int m_nXDirection;
	int m_nYDirection;
	int m_nPhysXDirection;
	int m_nPhysYDirection;
	double m_dPeriodX;
	double m_dPeriodY;
	bool m_bXIsLog;
	bool m_bYIsLog;
	const vector<CPoint> &m_CurvePtVect;
	const vector<double> &m_CurveValVect;
	vector<CLogicPoint> &m_ResPtVect;
	vector<double> &m_ResValVect;

};

#endif // !defined(AFX_DENSITYRESULTSPROCESSOR_H__3DD239D4_1A5B_4E8B_AD81_1689A978AB84__INCLUDED_)
