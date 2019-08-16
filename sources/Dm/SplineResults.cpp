// SplineResults.cpp: implementation of the CSplineResults class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SplineResults.h"
#include "SplineCurve.h"
#include "LogicPoint.h"

#include <vector>
using namespace std;

IMPLEMENT_SERIAL(CSplineResults,CObject,1)

int CSplineResults::m_nDefaultPointsPerSegment=50;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSplineResults::CSplineResults()
:	CResults(),
	m_nPointsPerSegment(m_nDefaultPointsPerSegment)
{

}

CSplineResults::CSplineResults(CCurve *pCurve)
:	CResults(pCurve),
	m_nPointsPerSegment(m_nDefaultPointsPerSegment)
{

}

CSplineResults::~CSplineResults()
{

}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////


CResults* CSplineResults::Clone(CCurve *pCurve) const
{
	if(NULL==pCurve)
	{
		pCurve=m_pCurve;
	}
	CSplineResults* pClone=new CSplineResults(pCurve);

	pClone->m_nPointsPerSegment=m_nPointsPerSegment;
	// that's all : the base class do no contain persistant data

	return pClone;
}

void CSplineResults::Construct()
{
	// construct a "modern" vector
	vector<CLogicPoint> pointsArray;
	CSplineCurve* pCurve=static_cast<CSplineCurve*>(m_pCurve);
	pCurve->GetSegmentPoints(m_nPointsPerSegment,pointsArray);

	// copy it in the old Array (to reuse the code of the parent class)
	vector<CLogicPoint>::const_iterator iter;
	for(iter=pointsArray.begin();iter!=pointsArray.end();iter++)
	{
		m_ResultArray.Add(*iter);
	}
}

void CSplineResults::Serialize(CArchive &ar)
{
	CResults::Serialize(ar);

	if(ar.IsStoring())
	{	
		ar << m_nPointsPerSegment;
	}
	else
	{
		ar >> m_nPointsPerSegment;
	}
}

int CSplineResults::GetPointsPerSegmentNb()
{
	return m_nPointsPerSegment;
}

void CSplineResults::SetPointsPerSegmentNb(int nb)
{
	m_nPointsPerSegment=nb;
}
