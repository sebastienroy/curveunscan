// PartialCurve.cpp: implementation of the CPartialCurve class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "CurveUnscan.h"
#include "PartialCurve.h"
#include "ContinuousCurve.h"
#include "CoordSyst.h"
#include "BmpManager.h"
#include "SnailAlgorithm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CPartialCurve,CObject,1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPartialCurve::CPartialCurve()
	{

	}

CPartialCurve::CPartialCurve(CContinuousCurve *pCurve)
	:CCurveElement(pCurve)
	{
	m_pBmpManager=((pCurve->GetCoordSyst())->GetDocument())->GetBmpManager();
	}

CPartialCurve::CPartialCurve(CPartialCurve *pOther)
	{
	*this=*pOther;
	}

CPartialCurve::~CPartialCurve()
	{
	m_PointArray.RemoveAll();
	}

CPartialCurve& CPartialCurve::operator=(const CPartialCurve &other)
	{
	if(this==&other)
		{
		return *this;
		}
	CCurveElement::operator=(other);
	m_pBmpManager=other.m_pBmpManager;
	m_Position=other.m_Position;
	int size=other.m_PointArray.GetSize();
	m_PointArray.RemoveAll();
	m_PointArray.SetSize(size);
	for(int i=0;i<size;i++)
		{
		m_PointArray[i]=other.m_PointArray[i];
		}
	return *this;
	}

BOOL CPartialCurve::IsPartialCurve()
	{
	return TRUE;
	}

void CPartialCurve::SetPosition(CPoint point)
	{
	m_pCurve->SetModifiedFlag(TRUE);
	m_Position=point;
	}

CPoint CPartialCurve::GetPosition()
	{
	return m_Position;
	}


BOOL CPartialCurve::HaveIncluded(CPoint point)
	{
	if(point.x==m_Position.x)
		{
		return TRUE;
		}
	int size=m_PointArray.GetSize();
	if(size==0)
		{
		return FALSE;
		}
	int index=point.x-(m_PointArray[0]).x;
	if( (index<0)||(index>=size) )
		{
		return FALSE;
		}
	if( (m_PointArray[index]).y==point.y)
		{
		return TRUE;
		}
	else
		{
		return FALSE;
		}

	}

// Construit la courbe à partir du point initial et en fonction des autres Elements
BOOL CPartialCurve::Construct()
{
	m_PointArray.RemoveAll();
	CList<CPoint,CPoint> PointList;
	CPoint point=m_Position;
	CPoint prevPoint;	// used to tell to the left element where to remove its points

	CSnailAlgorithm* snail=m_pCurve->GetSnail();

	///////////////////// Chopper les points à gauche ////
	BOOL found=snail->Initialize(point,true/*to left*/);
	if( (found)&&(kOn==m_pLeftElement->GetRelativePosition(point)) ) // si le premier point est inclus
	{				// dans l'élément de gauche, renvoyer FALSE
		return FALSE;	// -> destruction de l'élément
	}

	RelativePosition previousRelPos=kUndefined;
	RelativePosition currentRelPos=m_pLeftElement->GetRelativePosition(point);
	while( (found)
			&&(currentRelPos!=kOn)
			&& !( (kUp==currentRelPos)&&(kDown==previousRelPos) )
			&& !( (kDown==currentRelPos)&&(kUp==previousRelPos) ) )
	{
		PointList.AddHead(point);
		prevPoint=point;
		found=snail->FindNext(point);
		previousRelPos=currentRelPos;
		currentRelPos=m_pLeftElement->GetRelativePosition(point);
	}
	// if the neighbour element is a limit, add the last point
	if( (found)&&(m_pLeftElement->IsLimit()) )
	{
		PointList.AddHead(point);
		prevPoint=point;
	}

	m_pLeftElement->RemovePart(prevPoint,FALSE);
	point=(PointList.IsEmpty())?m_Position:PointList.GetTail();
	snail->Initialize(point,false/*to right*/);
	found=snail->FindNext(point);	// do no take the first point twice
	previousRelPos=kUndefined;
	currentRelPos=m_pRightElement->GetRelativePosition(point);

	while( (found)
			&&(currentRelPos!=kOn)
			&& !( (kUp==currentRelPos)&&(kDown==previousRelPos) )
			&& !( (kDown==currentRelPos)&&(kUp==previousRelPos) ) )
	{
		PointList.AddTail(point);
		found=snail->FindNext(point);
		previousRelPos=currentRelPos;
		currentRelPos=m_pRightElement->GetRelativePosition(point);
	}
	// add the next to detect the intial point redondance
	if(found)
	{
		PointList.AddTail(point);
	}

	// copy the list into an array
	int size=PointList.GetCount();
	m_PointArray.SetSize(size);
	POSITION pos=PointList.GetHeadPosition();
	int index=0;
	while(pos!=NULL)
	{
		m_PointArray[index++]=PointList.GetNext(pos);
	}
	PointList.RemoveAll();
	return TRUE;
}

// Vire la partie à partir du point inclus et dans la direction spécifiés
BOOL CPartialCurve::RemovePart(CPoint point, BOOL toLeft)
	{
	int size=m_PointArray.GetSize();
	if(size==0)
		{
		return FALSE;
		}
	int index=point.x-(m_PointArray[0]).x;
	if( (index<0)||(index>=size) )
		{
		return FALSE;
		}
	if(toLeft)
		{
		m_PointArray.RemoveAt(0,index+1);
		m_PointArray.FreeExtra();
		}
	else
		{
		m_PointArray.RemoveAt(index,size-index);
		m_PointArray.FreeExtra();
		}
	return TRUE;
	}

// Renvoie le nb de point que contient la courbe partielle.
int CPartialCurve::GetPointsNumber()
	{
	return m_PointArray.GetSize();
	}

// Renvoie le point d'indice précisé en paramètre
CPoint CPartialCurve::GetPoint(int index)
	{
	if( (index>=0)&&(index<m_PointArray.GetSize()) )
		{
		return m_PointArray[index];
		}
	else
		{
		return CPoint(0,0);
		}
	}

void CPartialCurve::DeleteContent()
	{
	m_PointArray.RemoveAll();
	m_PointArray.FreeExtra();
	}

RelativePosition CPartialCurve::GetRelativePosition(const CPoint &point) const
{
	if(point.x==m_Position.x)
	{
		return kOn;
	}
	int size=m_PointArray.GetSize();
	if(size==0)
	{
		return kOutside;
	}
	int index=point.x-(m_PointArray[0]).x;
	if( (index<0)||(index>=size) )
	{
		return kOutside;
	}
	if( (m_PointArray[index]).y==point.y)
	{
		return kOn;
	}
	else if(point.y>(m_PointArray[index]).y)
	{
		return kUp;
	}
	else
	{
		return kDown;
	}
}

void CPartialCurve::Serialize(CArchive &ar)
{
	CCurveElement::Serialize(ar);

	if (ar.IsStoring() )
	{
		ar << m_Position;
	}
	else
	{
		ar >> m_Position;
	}
}
