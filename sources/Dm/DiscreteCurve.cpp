// DiscreteCurve.cpp: implementation of the CDiscreteCurve class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "CurveUnscan.h"
#include "DiscreteCurve.h"
#include "DiscreteResults.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


IMPLEMENT_SERIAL(CDiscreteCurve,CObject,1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDiscreteCurve::CDiscreteCurve()
	:CCurve()
	{

	}

CDiscreteCurve::CDiscreteCurve(CCoordSyst *pCoord)
	:CCurve(pCoord)
	{

	}

CDiscreteCurve::CDiscreteCurve(CDiscreteCurve &otherCurve)
	{
	*this=otherCurve;
	}

CDiscreteCurve::~CDiscreteCurve()
	{

	}

CDiscreteCurve& CDiscreteCurve::operator =(const CDiscreteCurve &otherCurve)
	{
	CCurve::operator =(otherCurve);

	//--- results (performed by the base class
/*	delete m_pResults;
	m_pResults=NULL;
	CResults* pResults=otherCurve.m_pResults;
	if(NULL!=pResults)
		{
		m_pResults=pResults->Clone(this);
		}
*/
	return *this;
	}


BOOL CDiscreteCurve::IsDiscreteCurve() const
	{
	return TRUE;
	}

BOOL CDiscreteCurve::Draw(CDC *pDC) const
// trace des croix sur les points
	{
	if(m_PointList.IsEmpty())
		{
		return FALSE;
		}
	CPen pen(PS_SOLID,(m_Selected)?2:1,m_Color);
	CPen* oldPen=pDC->SelectObject(&pen);
	POSITION pos=m_PointList.GetHeadPosition();
	int x;
	int y;
	while(pos!=NULL)
		{
		CPoint point=m_PointList.GetNext(pos);
		x=point.x;
		y=(point.y)-5;
		pDC->MoveTo(x,y);
		y+=10;
		pDC->LineTo(x,y);
		x-=5;
		y-=5;
		pDC->MoveTo(x,y);
		x+=10;
		pDC->LineTo(x,y);
		}
	pDC->SelectObject(oldPen);
	return TRUE;
	}

void CDiscreteCurve::RemovePoint(POSITION pos)
	{
	m_PointList.RemoveAt(pos);
	SetModifiedFlag(TRUE);
	}

POSITION CDiscreteCurve::AddPoint(CPoint point)
	{
	POSITION pos=m_PointList.AddTail(point);
	SetModifiedFlag(TRUE);
	return pos;
	}

BOOL CDiscreteCurve::IsPresentOn(CPoint point) const
	{
	BOOL flag=FALSE;
	POSITION pos=m_PointList.GetHeadPosition();
	CPoint tryPoint;
	while( (pos!=NULL)&&(flag==FALSE) )
		{
		tryPoint=m_PointList.GetNext(pos);
		if( (abs(point.x-tryPoint.x)<=1)&&(abs(point.y-tryPoint.y)<=1) )
			{
			flag=TRUE;
			}
		}
	return flag;	
	}

void CDiscreteCurve::Serialize(CArchive &ar)
{
	CCurve::Serialize(ar);
	// That's all folks! (no attributes)
}

CCurve* CDiscreteCurve::Clone() const
{
	CDiscreteCurve *pClone=new CDiscreteCurve();
	
	*pClone=(*this);

	return pClone;
}

CResults * CDiscreteCurve::GetResults()
{
	if(NULL==m_pResults)
	{
		m_pResults=new CDiscreteResults(this);
	}
	return m_pResults;
}
