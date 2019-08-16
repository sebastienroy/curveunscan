// ContinuousResults.cpp: implementation of the CContinuousResults class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "CurveUnscan.h"
#include "ContinuousResults.h"
#include "CoordSyst.h"
#include "Curve.h"
#include "ContinuousCurve.h"
#include "Limit.h"
#include <Math.h>
#include <afxtempl.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CContinuousResults,CObject,1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CContinuousResults::CContinuousResults()
	:CResults()
	{
	m_DefinedPeriod=FALSE;
	m_Period=0;
	m_FirstValue=0;
	}

CContinuousResults::CContinuousResults(CCurve *pCurve)
	:CResults(pCurve)	
	{
	m_DefinedPeriod=FALSE;
	CCoordSyst* pCoord=pCurve->GetCoordSyst();

	double leftLimit=(((CContinuousCurve*)m_pCurve)->GetLeftLimit())->GetValue();
	m_FirstValue=leftLimit;

	double rightLimit=(((CContinuousCurve*)m_pCurve)->GetRightLimit())->GetValue();
	if(rightLimit<m_FirstValue) m_FirstValue=rightLimit;

	ComputeLastValue();

/*	POSITION headPos=m_pCurve->GetHeadPointPosition();
	if(NULL!=headPos)
		{
		CPoint firstPoint=m_pCurve->GetNextPoint(headPos);
		CLogicPoint firstLPoint=pCoord->ToLogic(firstPoint);
		double leftValue=firstLPoint.x;
		if(leftValue<m_FirstValue) m_FirstValue=leftValue;
		}

	POSITION tailPos=m_pCurve->GetTailPointPosition();
	if(NULL!=tailPos)
		{
		CPoint lastPoint=m_pCurve->GetPrevPoint(tailPos);
		CLogicPoint lastLPoint=pCoord->ToLogic(lastPoint);
		double rightValue=lastLPoint.x;
		if(rightValue<m_FirstValue) m_FirstValue=rightValue;
		}
*/

	}

CContinuousResults::~CContinuousResults()
	{

	}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


BOOL CContinuousResults::PeriodIsDefined() const
	{
	return m_DefinedPeriod;
	}

void CContinuousResults::SetPeriod(double value)
	{
#ifdef _DEBUG
	if(value<=0)
		{
		AfxMessageBox("Erreur dans CContinuousResults :\n Periode<=0");
		return;
		}
#endif // _DEBUG
	m_Period=value;
	m_DefinedPeriod=TRUE;
	}	

double CContinuousResults::GetPeriod() const
	{
	return m_Period;
	}

void CContinuousResults::Construct()
	{
	m_ResultArray.RemoveAll();
	double xValue=m_FirstValue;
	CLogicPoint ptA;
	CLogicPoint ptB;
	ResetBipoint();
	BOOL endOfCurve=!GetNextBipoint(ptA,ptB);

	while(!endOfCurve)	// process each abscissa
		{
		// get the bipoint
		bool bipointFound=FALSE;
		while( (!endOfCurve)&&(!bipointFound) )
			{
			if(ptB.x>=xValue)
				{
				bipointFound=true;
				}
			else
				{
				endOfCurve=!GetNextBipoint(ptA,ptB);
				}
			}
		if(endOfCurve)
			{
			continue;
			}
		
		//--- Record the pt
		CLogicPoint resultPoint;	
		resultPoint.x=xValue;
		if(ptA.x<=xValue)			// the curve is continuous
			{
			resultPoint.y=LinearInterpolation(xValue,ptA,ptB);
			}
		else						// the curve is not continuous
			{
			resultPoint.y=0.0;
			resultPoint.SetDefined(FALSE);
			}
		m_ResultArray.Add(resultPoint);

		// compute next abscissa
		GetNextAbscissa(xValue);
		}
/*
	m_ResultArray.RemoveAll();
	CCoordSyst* pCoord=m_pCurve->GetCoordSyst();
	BOOL reverse=pCoord->XAxeIsReverse();
	BOOL logX=(pCoord->GetXAxe())->GetLogarithmic();
	double highLimit=m_LastValue;
	double xValue=m_FirstValue;
	int contig=(reverse)?-1:+1;
	POSITION pos=(reverse)?(m_pCurve->GetTailPointPosition()):(m_pCurve->GetHeadPointPosition());
	CPoint actPoint=(reverse)?m_pCurve->GetPrevPoint(pos):m_pCurve->GetNextPoint(pos);
	CPoint prevPoint=actPoint;
	prevPoint.x-=contig;
	CLogicPoint actLogic=pCoord->ToLogic(actPoint);
	CLogicPoint prevLogic=pCoord->ToLogic(prevPoint);
	CLogicPoint newLPoint;
	while(xValue<=highLimit)
		{
		actLogic=pCoord->ToLogic(actPoint);
		while( (actLogic.x<xValue)&&(pos!=NULL) )// chopper le point correspondant
			{
			prevPoint=actPoint;
			prevLogic=actLogic;
			actPoint=(reverse)?m_pCurve->GetPrevPoint(pos):m_pCurve->GetNextPoint(pos);
			actLogic=pCoord->ToLogic(actPoint);
			}
		newLPoint.x=xValue;
		if( ((actPoint.x-prevPoint.x)==contig)&&(prevLogic.x<=xValue) )// si les points sont contigüs
			{
			newLPoint.y=actLogic.y;
			newLPoint.SetDefined(TRUE);
			}
		else								// si pas de courbe à cet endroit
			{
			newLPoint.y=0.0;
			newLPoint.SetDefined(FALSE);
			}
		m_ResultArray.Add(newLPoint);		// rajouter à la liste
		if(logX)							// incrémenter x
			{
			xValue=xValue*pow(10.0,m_Period);
			}
		else
			{
			xValue+=m_Period;
			}
		if(pos==NULL)						// attention si fin des points
			{
			contig=0;
			}
		}
		*/
	}

BOOL CContinuousResults::IsContinuousResults() const
	{
	return TRUE;
	}

double CContinuousResults::SetFirstValue(double value)
	{
	double oldValue;
	oldValue=m_FirstValue;
	m_FirstValue=value;
	return oldValue;
	}

double CContinuousResults::GetFirstValue() const
	{
	return m_FirstValue;
	}

double CContinuousResults::GetLastValue() const
{
	ComputeLastValue();
	return m_LastValue;
}

CResults* CContinuousResults::Clone(CCurve *pCurve/*=NULL*/) const
{
	CContinuousResults* newResults=new CContinuousResults(pCurve);

	//--- CResults base class attributes
	(newResults->m_ResultArray).Copy(m_ResultArray);

	//--- CContinuousResults class attributes
	newResults->m_DefinedPeriod=m_DefinedPeriod;
	newResults->m_FirstValue=m_FirstValue;
	newResults->m_Period=m_Period;
	newResults->m_LastValue=m_LastValue;

	return newResults;
}

void CContinuousResults::ComputeLastValue() const
{
	CCoordSyst* pCoord=m_pCurve->GetCoordSyst();

	double rightLimit=(((CContinuousCurve*)m_pCurve)->GetRightLimit())->GetValue();
	m_LastValue=rightLimit;

	double leftLimit=(((CContinuousCurve*)m_pCurve)->GetLeftLimit())->GetValue();
	if(leftLimit>m_LastValue) m_LastValue=leftLimit;

	POSITION headPos=m_pCurve->GetHeadPointPosition();
	if(NULL!=headPos)
		{
		CPoint firstPoint=m_pCurve->GetNextPoint(headPos);
		CLogicPoint firstLPoint=pCoord->ToLogic(firstPoint);
		double leftValue=firstLPoint.x;
		if(leftValue>m_LastValue) m_LastValue=leftValue;
		}

	POSITION tailPos=m_pCurve->GetTailPointPosition();
	if(NULL!=tailPos)
		{
		CPoint lastPoint=m_pCurve->GetPrevPoint(tailPos);
		CLogicPoint lastLPoint=pCoord->ToLogic(lastPoint);
		double rightValue=lastLPoint.x;
		if(rightValue>m_LastValue) m_LastValue=rightValue;
		}
}


void CContinuousResults::ResetBipoint() const
	{
	CCoordSyst* pCoord=m_pCurve->GetCoordSyst();

	m_bReverse=pCoord->XAxeIsReverse();
	m_Contig=(m_bReverse)?-1:+1;
	m_bXIsLog=pCoord->GetXAxe()->GetLogarithmic();
	m_bYIsLog=pCoord->GetYAxe()->GetLogarithmic();

	m_ActPos=(m_bReverse)?(m_pCurve->GetTailPointPosition()):(m_pCurve->GetHeadPointPosition());
	if(NULL!=m_ActPos)
		{
		m_ActPoint=(m_bReverse)?m_pCurve->GetPrevPoint(m_ActPos):m_pCurve->GetNextPoint(m_ActPos);
		}
	}

BOOL CContinuousResults::GetNextBipoint(CLogicPoint& ptA,CLogicPoint& ptB) const
	{
	if(NULL==m_ActPos)
		{
		return FALSE;
		}

	bool found=false;
	CPoint physicalPtA;
	CPoint physicalPtB;
	while( (NULL!=m_ActPos)&&(!found) )
		{
		physicalPtA=m_ActPoint;
		physicalPtB=(m_bReverse)?m_pCurve->GetPrevPoint(m_ActPos):m_pCurve->GetNextPoint(m_ActPos);
		m_ActPoint=physicalPtB;
		if( (physicalPtB.x-physicalPtA.x)==m_Contig)
			{
			found=true;
			}
		}

	if(!found)
		{
		return FALSE;
		}

	CCoordSyst* pCoord=m_pCurve->GetCoordSyst();
	ptA=pCoord->ToLogic(physicalPtA);
	ptB=pCoord->ToLogic(physicalPtB);
	return TRUE;
	}

double CContinuousResults::LinearInterpolation(double x, const CLogicPoint &ptA, const CLogicPoint &ptB) const
{
	if(ptA.x==ptB.x)
		{
		return ptB.y;
		}

	double Ax=ptA.x;
	double Bx=ptB.x;
	if(m_bXIsLog)
		{
		Ax=log(Ax);
		Bx=log(Bx);
		x=log(x);
		}
	double Ay=ptA.y;
	double By=ptB.y;
	if(m_bYIsLog)
		{
		Ay=log(Ay);
		By=log(By);
		}

	double rapport=(x-Ax)/(Bx-Ax);
	double result=Ay+rapport*(By-Ay);

	if(m_bYIsLog)
		{
		result=exp(result);
		}

	return result;
}


void CContinuousResults::GetNextAbscissa(double &x) const
{
	if(m_bXIsLog)							// incrémenter x
		{
		x=x*pow(10.0,m_Period);
		}
	else
		{
		x+=m_Period;
		}
}

void CContinuousResults::Serialize(CArchive &ar)
{
	CResults::Serialize(ar);

	if( ar.IsStoring() )
	{
		ar << m_FirstValue << m_DefinedPeriod << m_Period;
	}
	else
	{
		ar >> m_FirstValue >> m_DefinedPeriod >> m_Period;
	}
}
