// SmartThicknessCorrector.cpp: implementation of the CSmartThicknessCorrector class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "CurveUnscan.h"
#include "SmartThicknessCorrector.h"
#include <Utilities/Tools.h>
#include "ContinuousCurve.h"
#include <math.h>

#include <vector>
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CSmartThicknessCorrector,CObject,1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Used for serialization only
CSmartThicknessCorrector::CSmartThicknessCorrector()
:	CAbstractThicknessCorrector(NULL),
	 m_nWidth(2)
{

}


CSmartThicknessCorrector::CSmartThicknessCorrector(CContinuousCurve* pCurve)
:CAbstractThicknessCorrector(pCurve), m_nWidth(2)
{

}


CSmartThicknessCorrector::CSmartThicknessCorrector(CContinuousCurve *pCurve, int nWidth)
:	CAbstractThicknessCorrector(pCurve), 
	m_nWidth(nWidth)
{

}

CSmartThicknessCorrector::~CSmartThicknessCorrector()
{

}

CAbstractThicknessCorrector* CSmartThicknessCorrector::Clone(CContinuousCurve *pCurve)
{
	CAbstractThicknessCorrector* aClone=new CSmartThicknessCorrector(pCurve);
	((CSmartThicknessCorrector*)aClone)->m_nThickness=m_nThickness;
	((CSmartThicknessCorrector*)aClone)->m_nWidth=m_nWidth;
	return aClone;
}

void CSmartThicknessCorrector::CompensateThickness(CList<CPoint,CPoint> &pointList, bool bTopFollow)
{

	//--- Calculate the initial translation vector
	int offset=m_nThickness/2;
	if(0==offset)
		{
		return;
		}
	if(!bTopFollow)
		{
		offset*=-1;
		}
	CPoint offsetVect(0,offset);

	//--- first, copy the list in a vector to make easier the calculous
	m_initialPoints.clear();
	POSITION pos=pointList.GetHeadPosition();
	while(NULL!=pos)
		{
		m_initialPoints.push_back(pointList.GetNext(pos));
		}

#if defined(_DEBUG)	// check no duplicated points with the same x
	CPoint previousPoint=m_initialPoints[0];
	CPoint currentPoint;
	for(int debugCounter=1;debugCounter<m_initialPoints.size();debugCounter++)
		{
		currentPoint=m_initialPoints[debugCounter];
		ASSERT(currentPoint.x!=previousPoint.x);
		previousPoint=currentPoint;
		}
	
#endif	// defined(_DEBUG)

	//--- construct the new list
	vector<CPoint> finalPoints;
	for(int index=0;index<m_initialPoints.size();index++)
		{

#if defined(_DEBUG)	// a special point in the oxycarbure.gif graphic
		CPoint ptDebug=m_initialPoints[index];
		if(ptDebug.x==851)
		{
			int toto=0;
		}
#endif
		// calculate the angle
		double alpha=GetAngle(index,m_initialPoints);
		// calculate the translated point
		CPoint ptOffset=CTools::RotatedPoint(offsetVect,alpha);
		CPoint newPoint=m_initialPoints[index];
		newPoint.x+=ptOffset.x;
		newPoint.y+=ptOffset.y;
		// the new point must be translated at least by a value of thickness/2
		CorrectTranslation(m_initialPoints,offsetVect,index,newPoint);
		// is the curve continuous at this point?
		bool continuous=IsCurveContinuous(index,m_initialPoints);
		// add the new point
		m_nCurrentIndex=index;	// used to speed up the algorithm
		AddPoint(newPoint, finalPoints, continuous, bTopFollow);		
		}

	//--- replace the original list
	pointList.RemoveAll();
	for(int counter=0;counter<finalPoints.size();counter++)
		{
		pointList.AddTail(finalPoints[counter]);
		}

#if defined(_DEBUG)	// check no duplicated points with the same x
	previousPoint=finalPoints[0];
	currentPoint;
	for(debugCounter=1;debugCounter<finalPoints.size();debugCounter++)
		{
		currentPoint=finalPoints[debugCounter];
		ASSERT(currentPoint.x!=previousPoint.x);
		previousPoint=currentPoint;
		}
	
#endif	// defined(_DEBUG)
}

double CSmartThicknessCorrector::GetAngle(int index, vector<CPoint>& vectPoints)
{
	// principe : si le point est situé à un sommet ou dans un creux, l'angle est nul
	// autrement, l'angle est calculé à partir de la pente des points autour
	// Le nombre de points pris en compte est m_nWidth de part et d'autre,
	//		sauf si on est en fin de courbe ou si la dérivé change de signe

	//--- First, get the points located at m_nWidth pixels to the right and to the left
	CPoint startingPoint=vectPoints[index];

	bool bLeftContinue=true;	// flag indique si on continue a regarder dans la direction
	bool bRightContinue=true;
	bool bContinue=bLeftContinue||bRightContinue;


	int nLeftRate=0;	// signe de la pente si left*right<0, dérivée change de signe
	int nRightRate=0;
	int nInitialRate=0;

	CPoint leftPoint=startingPoint;
	CPoint rightPoint=startingPoint;

	// look for the first points
	if(index>0)
	{
		nLeftRate=(vectPoints[index].y)-(vectPoints[index-1].y);
		leftPoint=vectPoints[index-1];
	}
	else
	{
		bLeftContinue=false;
	}

	if((index+1)<vectPoints.size())
	{
		nRightRate=(vectPoints[index+1].y)-(vectPoints[index].y);
		rightPoint=vectPoints[index+1];
	}
	else
	{
		bRightContinue=false;
	}

	bContinue=bLeftContinue||bRightContinue;

	if( ((nLeftRate*nRightRate)<0)
		|| (!bContinue) )
	{
		return 0;	// angle is null
	}

	nInitialRate=(nLeftRate!=0)?nLeftRate:nRightRate;

	for(int counter=2;(counter<=m_nWidth)&&(bContinue);counter++)
	{
		// check left
		if(bLeftContinue)
		{
			nLeftRate=(leftPoint.y)-(vectPoints[index-counter].y);
			if((nLeftRate*nInitialRate)<0)
			{
				bLeftContinue=false;
			}
			else
			{
				if(0==nInitialRate)	// eventually initialyze the initial rate
				{
					nInitialRate=nLeftRate;
				}

				leftPoint=vectPoints[index-counter];
				if(0==(index-counter))
				{
					bLeftContinue=false;
				}
			}
		}
		if(bRightContinue)
		{
			nRightRate=(vectPoints[index+counter].y)-(rightPoint.y);
			if((nRightRate*nInitialRate)<0)
			{
				bRightContinue=false;
			}
			else
			{
				if(0==nInitialRate)	// eventually initialyze the initial rate
				{
					nInitialRate=nRightRate;
				}

				rightPoint=vectPoints[index+counter];
				if((index+counter)>=(vectPoints.size()-1))
				{
					bRightContinue=false;
				}
			}
		}

		bContinue=(bLeftContinue||bRightContinue);
	}


	//--- calculate the angle
	double alpha;
	if(leftPoint==rightPoint)
		{
		alpha=0.0;
		}
	else if(leftPoint.x==rightPoint.x)	// should not exist
		{
		alpha=acos(0.0);	// pi/2
		if(leftPoint.y>rightPoint.y)	// negative derivative
			{
			alpha*=-1.0;
			}
		else if(leftPoint.y==rightPoint.y)
			{
			alpha=0;
			}
		
		}
	else
		{
		double dy=(double)(rightPoint.y-leftPoint.y);
		double dx=(double)(rightPoint.x-leftPoint.x);
		alpha=atan(dy/dx);
		}
	return alpha;
}

// return true if there is a point immediately to the left of the point given in index
bool CSmartThicknessCorrector::IsCurveContinuous(int index, vector<CPoint> &vectPoints)
{
	if(0==index)
		{
		return false;
		}
	int current=(vectPoints[index]).x;
	int previous=(vectPoints[index-1]).x;
	if((current-1)==previous)
		{
		return true;
		}
	else
		{
		return false;
		}
}

void CSmartThicknessCorrector::AddPoint(CPoint point, vector<CPoint> &vectPoints, bool continuous, bool bTopFollow)
{
	// first, remove all the last points of the vector which y are greater and to the right of the new one
	while( (0!=vectPoints.size())
			&& (point.x<=vectPoints.back().x)
			&& (IsUnder(point,vectPoints.back(),bTopFollow)) )
	{
		vectPoints.pop_back();
	}

	if( 0!=vectPoints.size())
	{
		CPoint ptLast=vectPoints.back();
		if (ptLast.x>=point.x)
		{
			return;
		}
	}

	if( 0==vectPoints.size())	// do no add intermediate points if the vector is empty
	{
		continuous=false;
	}

	//--- add intermediate points if needed
	if( (continuous)&&((vectPoints.back().x+1)<point.x) )
	{
		CPoint ptFirst=vectPoints.back();

		int diffx=point.x-ptFirst.x;
		int diffy=point.y-ptFirst.y;
		int firstx=ptFirst.x;
		int firsty=ptFirst.y;
		double rate=((double)diffy)/((double)diffx);
		int y=ptFirst.y;
		for(int counter=ptFirst.x+1;counter<point.x;counter++)
		{
			double dy=rate*((double)(counter-firstx));
			CPoint ptCurrent=CPoint(counter,firsty+(int)dy);
			CPoint ptInitial;
			if(GetInitialPointFromX(ptInitial,counter))
			{
				ptCurrent=GetLowerPoint(ptCurrent,ptInitial,m_nThickness/2,bTopFollow);
			}
			vectPoints.push_back(ptCurrent);
		}
	}
		
	vectPoints.push_back(point);	// the dist have been checked before

	
/*

////////////////////////////////////////////////
	CPoint lastPoint;
	if(!(0==vectPoints.size()))
		{
		lastPoint=vectPoints.back();
		if(lastPoint.x>=point.x)
			{
			return;
			}
		}
	else
		{
		continuous=false;	// do no add intermediate points if the vector is empty
		}

	//--- add intermediate points if needed
	if( (continuous)&&((lastPoint.x+1)<point.x) )
		{
		int diffx=point.x-lastPoint.x;
		int diffy=point.y-lastPoint.y;
		int firstx=lastPoint.x;
		int firsty=lastPoint.y;
		double rate=((double)diffy)/((double)diffx);
		int y=lastPoint.y;
		for(int counter=lastPoint.x+1;counter<point.x;counter++)
			{
			double dy=rate*((double)(counter-firstx));
			vectPoints.push_back(CPoint(counter,firsty+(int)dy));
			}
		}
	//--- add last point
	vectPoints.push_back(point);*/
}

void CSmartThicknessCorrector::CorrectTranslation(const vector<CPoint> &initialPoints,const CPoint& initialOffset, int index, CPoint &newPoint)
{
	CPoint ptInitial=initialPoints[index];
	int diffX=newPoint.x-ptInitial.x;
	int newIndex=index+diffX;
	if( (newIndex<0)||(newIndex>=initialPoints.size()) )	// check bounds
		{
		return;
		}
	CPoint verticalPoint=initialPoints[newIndex];
	if(verticalPoint.x!=newPoint.x)	// if the curve is not continuous, do nothing
		{
		return;
		}

	double offsetRequired=(double)(initialOffset.y);
	double offsetObtained=(double)(newPoint.y-verticalPoint.y);
	if((offsetObtained/offsetRequired)<1)
		{
		newPoint.y=verticalPoint.y+initialOffset.y;
		}
}

void CSmartThicknessCorrector::SetWidth(int nWidth) 
	{ 
	m_nWidth=nWidth;
	m_pCurve->SetModifiedFlag(TRUE); 
	}

CPoint CSmartThicknessCorrector::GetLowerPoint(const CPoint &ptCorrected, const CPoint &ptCurve, int nMinDist, bool bTopFollow) const
{
	CPoint ptResult=ptCorrected;
	int nDirection=(bTopFollow)?+1:-1;
	int nDist=(ptCorrected.y-ptCurve.y);
	if( (nDist*nDirection)<nMinDist )
	{
		ptResult.y=ptCurve.y+(nMinDist*nDirection);
	}
	return ptResult;
}

// return true if the ptA is under the  ptB
bool CSmartThicknessCorrector::IsUnder(const CPoint &ptA, const CPoint &ptB, bool bTopFollow)
{
	int nDirection=(bTopFollow)?+1:-1;
	return ( ((ptA.y-ptB.y)*nDirection)>0 );
}

bool CSmartThicknessCorrector::GetInitialPointFromX(CPoint &ptValue, int nX) const
{
	const CPoint& initialPoint=m_initialPoints[m_nCurrentIndex];
	if(initialPoint.x==nX)
	{
		ptValue=initialPoint;
		return true;
	}
	CPoint ptCurrent;
	bool found=false;
	bool passed=false;
	int nSize=m_initialPoints.size();
	if(nX>initialPoint.x)
	{
		int nIndex=m_nCurrentIndex+1;
		while( (nIndex<nSize) && (!found) && (!passed) )
		{
			ptCurrent=m_initialPoints[nIndex];
			if(ptCurrent.x==nX)
			{
				found=true;
			}
			else if(ptCurrent.x>nX)
			{
				passed=true;
			}
			nIndex++;
		}
	}
	else
	{
		int nIndex=m_nCurrentIndex-1;
		while( (nIndex>=0) && (!found) && (!passed) )
		{
			ptCurrent=m_initialPoints[nIndex];
			if(ptCurrent.x==nX)
			{
				found=true;
			}
			else if(ptCurrent.x<nX)
			{
				passed=true;
			}
			nIndex--;
		}
	}
	if(found)
	{
		ptValue=ptCurrent;
	}
	return found;
	
}

void CSmartThicknessCorrector::Serialize(CArchive &ar)
{
	CAbstractThicknessCorrector::Serialize(ar);

	if( ar.IsStoring() )
	{
		ar << m_nWidth;
	}
	else
	{
		ar >> m_nWidth;
	}
}
