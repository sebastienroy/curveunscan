// DiscreteResults.cpp: implementation of the CDiscreteResults class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "DiscreteResults.h"
#include "LogicPoint.h"
#include "CoordSyst.h"
#include "Curve.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CDiscreteResults,CObject,1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDiscreteResults::CDiscreteResults()
	:CResults()
	{

	}

CDiscreteResults::CDiscreteResults(CCurve *pCurve)
	:CResults(pCurve)
	{

	}

CDiscreteResults::~CDiscreteResults()
	{

	}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

void CDiscreteResults::Construct()
	{
	CPoint point;
	CLogicPoint lPoint;
	int nIndex=0;
	CCoordSyst* pCoord=m_pCurve->GetCoordSyst();
	m_ResultArray.SetSize(m_pCurve->GetPointCount());
	POSITION pos=m_pCurve->GetHeadPointPosition();
	while(pos!=NULL)
		{
		point=m_pCurve->GetNextPoint(pos);
		lPoint=pCoord->ToLogic(point);
		m_ResultArray[nIndex++]=lPoint;
		}
	}

BOOL CDiscreteResults::IsDiscreteResults() const
	{
	return TRUE;
	}

CResults* CDiscreteResults::Clone(CCurve *pCurve/*=NULL*/) const
{
	CDiscreteResults* newResults=new CDiscreteResults(pCurve);

	//--- CResults base class attributes
	(newResults->m_ResultArray).Copy(m_ResultArray);

	return newResults;
}

void CDiscreteResults::Serialize(CArchive &ar)
{
	CResults::Serialize(ar);
	// That's all folks!
}
