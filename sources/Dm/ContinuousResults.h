// ContinuousResults.h: interface for the CContinuousResults class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTINUOUSRESULTS_H__A801C2C4_6943_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_CONTINUOUSRESULTS_H__A801C2C4_6943_11D4_935E_0080C7A4F675__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Results.h"
#include <deque>
using namespace std;

class CContinuousResults : public CResults  
{
// constructor / destructor
public:
	CContinuousResults(CCurve *pCurve);
	CContinuousResults();
	virtual ~CContinuousResults();

public:
	virtual void Serialize(CArchive& ar);
	virtual CResults* Clone(CCurve* pCurve=NULL) const;
	double GetLastValue() const;
	double GetFirstValue() const;
	double SetFirstValue(double value);
	BOOL IsContinuousResults() const;
	void Construct();
	double GetPeriod() const;
	void SetPeriod(double value);
	BOOL PeriodIsDefined() const;

protected:
	void GetNextAbscissa(double& x) const;
	double LinearInterpolation(double x,const CLogicPoint& ptA,const CLogicPoint& ptB) const;
	void ResetBipoint() const;
	BOOL GetNextBipoint(CLogicPoint& ptA,CLogicPoint& ptB) const;
	void ComputeLastValue() const;

	//attributes
protected:
	double m_FirstValue;
	BOOL m_DefinedPeriod;
	double m_Period;

	// temporary data used to construct the results
	mutable double m_LastValue;
	mutable POSITION m_ActPos;
	mutable CPoint m_ActPoint;
	mutable BOOL m_bReverse;
	mutable BOOL m_bXIsLog;
	mutable BOOL m_bYIsLog;
	mutable int m_Contig;

protected:
DECLARE_SERIAL(CContinuousResults)

};

#endif // !defined(AFX_CONTINUOUSRESULTS_H__A801C2C4_6943_11D4_935E_0080C7A4F675__INCLUDED_)
