// SmartThicknessCorrector.h: interface for the CSmartThicknessCorrector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SMARTTHICKNESSCORRECTOR_H__568B11A4_3C81_11D5_935E_BA3BA588DF78__INCLUDED_)
#define AFX_SMARTTHICKNESSCORRECTOR_H__568B11A4_3C81_11D5_935E_BA3BA588DF78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AbstractThicknessCorrector.h"
#include <vector>
using namespace std;

class CSmartThicknessCorrector : public CAbstractThicknessCorrector  
{

public:
	CSmartThicknessCorrector(CContinuousCurve* pCurve);
	CSmartThicknessCorrector(CContinuousCurve* pCurve, int nWidth);
	virtual ~CSmartThicknessCorrector();

public:
	virtual void Serialize(CArchive &ar);
	void SetWidth(int nWidth);
	int GetWidth() const;
	virtual void CompensateThickness(CList<CPoint,CPoint>& pointList, bool bTopFollow);
	virtual CAbstractThicknessCorrector* Clone(CContinuousCurve* pCurve);

protected:
	CSmartThicknessCorrector();
	bool GetInitialPointFromX(CPoint& ptValue, int nX) const;
	bool IsUnder(const CPoint& ptA, const CPoint& ptB, bool bTopFollow);
	CPoint GetLowerPoint(const CPoint& ptCorrected, const CPoint& ptCurve, int nMinDist, bool bTopFollow) const;
	void CorrectTranslation(const vector<CPoint>& initialPoints,const CPoint& initialOffset, int index, CPoint& newPoint);
	void AddPoint(CPoint point,vector<CPoint>& vectPoints, bool continuous, bool bTopFollow);
	bool IsCurveContinuous(int index, vector<CPoint>& vectPoints);
	double GetAngle(int index,vector<CPoint>& vectPoints);
	int m_nWidth;
	mutable vector<CPoint> m_initialPoints;
	mutable int m_nCurrentIndex;

protected:
	DECLARE_SERIAL(CSmartThicknessCorrector)
};


inline int CSmartThicknessCorrector::GetWidth() const { return m_nWidth; }


#endif // !defined(AFX_SMARTTHICKNESSCORRECTOR_H__568B11A4_3C81_11D5_935E_BA3BA588DF78__INCLUDED_)
