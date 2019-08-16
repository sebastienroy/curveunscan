// DensityCurve.h: interface for the CDensityCurve class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DENSITYCURVE_H__62FFEFDE_40D8_4203_B8F6_9FE4644C6FAD__INCLUDED_)
#define AFX_DENSITYCURVE_H__62FFEFDE_40D8_4203_B8F6_9FE4644C6FAD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Curve.h"

#include <vector>
using namespace std;

class CColorScale;
class CCoordSyst;

class CDensityCurve : public CCurve  
{
	// constructor / destructor
public:
	CDensityCurve(	CCoordSyst *pCoordSyst,
					CColorScale *pColorScale=NULL,
					CPoint* pPtFrom=NULL,
					CPoint *pPtTo=NULL);
	CDensityCurve();
	virtual ~CDensityCurve();

public:
	virtual CResults* GetResults();
	CPoint GetToPoint() const;
	CPoint GetFromPoint() const;
	const vector<CPoint>& GetPointArray() const;
	const vector<double>& GetValueArray() const;
	bool Compute();
	CColorScale* GetColorScale();
	virtual void Serialize(CArchive &ar);
	virtual BOOL Draw(CDC* pDC) const;
	virtual BOOL IsPresentOn(CPoint point) const;
	CDensityCurve& operator =(const CDensityCurve& other);
	virtual CCurve* Clone() const;
	void SetPosition(const CPoint& ptFrom, const CPoint& ptTo);
	bool IsPositionDefined() const;

protected:
	CColorScale* m_pColorScale;
	CPoint* m_pPtTo;
	CPoint* m_pPtFrom;
	vector<double> m_ValuesArray;
	vector<CPoint> m_PtArray;

protected:
	DECLARE_SERIAL(CDensityCurve)

};

#endif // !defined(AFX_DENSITYCURVE_H__62FFEFDE_40D8_4203_B8F6_9FE4644C6FAD__INCLUDED_)
