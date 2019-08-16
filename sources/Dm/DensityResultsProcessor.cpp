// DensityResultsProcessor.cpp: implementation of the CDensityResultsProcessor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DensityResultsProcessor.h"

#include "DensityResults.h"
#include "DensityCurve.h"
#include "CoordSyst.h"
#include "LogicPoint.h"
#include "Utilities/Tools.h"

#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDensityResultsProcessor::CDensityResultsProcessor(CDensityResults *pResults)
:	m_pResults(pResults),
	m_pCurve(static_cast<CDensityCurve*>(pResults->GetCurve())),
	m_pCoord(pResults->GetCurve()->GetCoordSyst()),
	m_CurvePtVect(static_cast<CDensityCurve*>(pResults->GetCurve())->GetPointArray()),
	m_CurveValVect(static_cast<CDensityCurve*>(pResults->GetCurve())->GetValueArray()),
	m_ResPtVect(pResults->m_PointsArray),
	m_ResValVect(pResults->m_DensityValuesArray)
{
	// use x or y?
	m_bUseX=(kYdisplay!=m_pResults->m_DisplayKind)&&(m_pResults->m_bXPeriodIsUsed);
	
	// linearity
	m_bXIsLog=m_pCoord->GetXAxe()->GetLogarithmic();
	m_bYIsLog=m_pCoord->GetYAxe()->GetLogarithmic();

	// what is the iteration direction?
	CPoint ptFrom=m_pCurve->GetFromPoint();
	CPoint ptTo=m_pCurve->GetToPoint();
	int nDeltaX=abs(ptFrom.x-ptTo.x);
	int nDeltaY=abs(ptFrom.y-ptTo.y);
	m_bIterOnX=(nDeltaX>=nDeltaY);

	CLogicPoint ptLogicFrom=m_pCoord->ToLogic(ptFrom);
	CLogicPoint ptLogicTo=m_pCoord->ToLogic(ptTo);

	double dDeltaX=ptLogicTo.x-ptLogicFrom.x;
	double dDeltaY=ptLogicTo.y-ptLogicFrom.y;
	// x
	m_dPeriodX=m_pResults->GetXPeriod();
	m_nXDirection=((dDeltaX*m_dPeriodX)>0)?+1:-1;
	// y
	m_dPeriodY=m_pResults->GetYPeriod();
	m_nYDirection=((dDeltaY*m_dPeriodY)>0)?+1:-1;

	int nIterDirection=(m_bUseX)?m_nXDirection:m_nYDirection;
	
//	m_nPhysXDirection=( (1==nIterDirection)&&(ptTo.x>ptFrom.x) )?1:-1;
//	m_nPhysYDirection=( (1==nIterDirection)&&(ptTo.y>ptFrom.y) )?1:-1;	
	m_nPhysXDirection=(ptTo.x>ptFrom.x)?1:-1;
	m_nPhysXDirection*=nIterDirection;
	m_nPhysYDirection=(ptTo.y>ptFrom.y)?1:-1;
	m_nPhysYDirection*=nIterDirection;

}

CDensityResultsProcessor::~CDensityResultsProcessor()
{

}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

void CDensityResultsProcessor::Build()
{
	m_pCurve->Compute();

	// initialize
	CLogicPoint firstLogicPoint=GetFirstLogicPoint();
	int nStep=0;
	m_ResPtVect.clear();
	m_ResValVect.clear();

	CLogicPoint expectedLogicPoint=firstLogicPoint;
	CLogicPoint expectedPhysPoint=m_pCoord->ToPhysicDouble(expectedLogicPoint);

	// array iteration;
	int nIterDirection=(m_bUseX)?m_nXDirection:m_nYDirection;
	int nArrayIndex=(nIterDirection>0)?0:m_CurvePtVect.size()-1;

	CPoint ptCurrent=m_CurvePtVect[nArrayIndex];
	CPoint ptPrevious=ptCurrent;

	double currentValue=m_CurveValVect[nArrayIndex];
	double previousValue=currentValue;
	bool isEnd=false;

	while( !isEnd )
	{
		while( (IsPointBefore(ptCurrent,expectedPhysPoint)) && (!isEnd) )			
		{

			nArrayIndex+=nIterDirection;
			if( (nArrayIndex<0) || (nArrayIndex>=m_CurvePtVect.size()) )
			{
				isEnd=true;
			}
			else
			{
				ptPrevious=ptCurrent;
				previousValue=currentValue;

				ptCurrent=m_CurvePtVect[nArrayIndex];
				currentValue=m_CurveValVect[nArrayIndex];
			}
			
		}

		if(!isEnd)	// the last expected point must not be added if the segment stops before
		{
			double dValue=GetLinearInterpolation(ptPrevious,
												ptCurrent,
												previousValue,
												currentValue,
												expectedPhysPoint);

			m_ResPtVect.push_back(expectedLogicPoint);
			m_ResValVect.push_back(dValue);
		}

		// iterate
		nStep++;
		expectedLogicPoint=IterateLogicPoint(firstLogicPoint,nStep);
		expectedPhysPoint=m_pCoord->ToPhysicDouble(expectedLogicPoint);
	}

}

//////////////////////////////////////////////////////////////////////
// Internal methods
//////////////////////////////////////////////////////////////////////


CLogicPoint CDensityResultsProcessor::IterateLogicPoint(const CLogicPoint &pt, int nStep) const
{
	double x;
	double y;
	if(m_bUseX)
	{
		x=IterateLogicX(pt.x,nStep);
		y=m_pResults->GetYfromX(x);
	}
	else
	{
		y=IterateLogicY(pt.y,nStep);
		x=m_pResults->GetXfromY(y);
	}

	return CLogicPoint(x,y);
}


double CDensityResultsProcessor::IterateLogicX(double dFirst,int nStep) const 
{

	double result;
	if(m_bXIsLog)
	{
		result=dFirst*pow(10.0,(nStep*m_dPeriodX));
	}
	else
	{
		result=dFirst+(nStep*m_dPeriodX);
	}
	return result;
}

double CDensityResultsProcessor::IterateLogicY(double dFirst, int nStep) const
{

	double result;
	if(m_bYIsLog)
	{
		result=dFirst*pow(10.0,(nStep*m_dPeriodY));
	}
	else
	{
		result=dFirst+(nStep*m_dPeriodY);
	}
	return result;
}

bool CDensityResultsProcessor::IsPointBefore(const CPoint &segmentPoint, const CLogicPoint &expectedPhysPoint) const
{
	bool result;
	if(m_bIterOnX)
	{
		double dSegmentLocation=segmentPoint.x;
		result=((dSegmentLocation-expectedPhysPoint.x)*m_nPhysXDirection)<0;
	}
	else
	{
		double dSegmentLocation=segmentPoint.y;
		result=((dSegmentLocation-expectedPhysPoint.y)*m_nPhysYDirection)<0;
	}
	return result;
}

CLogicPoint CDensityResultsProcessor::GetFirstLogicPoint()
{
	double x;
	double y;
	if(m_bUseX)
	{
		x=m_pResults->GetFirstX();
		y=m_pResults->GetYfromX(x);
	}
	else
	{
		y=m_pResults->GetFirstY();
		x=m_pResults->GetXfromY(y);
	}
	return CLogicPoint(x,y);
}




double CDensityResultsProcessor::GetLinearInterpolation(CPoint pt1, 
														CPoint pt2, 
														double val1, 
														double val2, 
														CLogicPoint lPoint) const
{

	double A1=(m_bIterOnX)?pt1.x:pt1.y;
	double A2=(m_bIterOnX)?pt2.x:pt2.y;
	double P=(m_bIterOnX)?lPoint.x:lPoint.y;

	double distA1=P-A1;
	double distA2=A2-P;
	double distTot=A2-A1;

	if(0==distTot)
	{
		return val2;
	}

	double result=(distA1*val2+distA2*val1)/(distTot);
	return result;

}


