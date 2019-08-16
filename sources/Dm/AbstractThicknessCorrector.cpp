// AbstractThicknessCorrector.cpp: implementation of the CAbstractThicknessCorrector class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "CurveUnscan.h"
#include "AbstractThicknessCorrector.h"
#include "ContinuousCurve.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAbstractThicknessCorrector::CAbstractThicknessCorrector(CContinuousCurve* pCurve)
:m_pCurve(pCurve),m_nThickness(1)
{

}

CAbstractThicknessCorrector::~CAbstractThicknessCorrector()
{

}

void CAbstractThicknessCorrector::CompensateThickness(CList<CPoint,CPoint>& pointList, bool bTopFollow)
{

}

CAbstractThicknessCorrector* CAbstractThicknessCorrector::Clone(CContinuousCurve* pCurve)
{
	return NULL;
}

void CAbstractThicknessCorrector::SetThickness(int thickness) 
	{ 
	m_nThickness=thickness;
	m_pCurve->SetModifiedFlag(TRUE);
	}


void CAbstractThicknessCorrector::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);

	if( ar.IsStoring() )
	{
		ar << m_nThickness;
	}
	else
	{
		ar >> m_nThickness;
	}
}
