// ScalePoint.cpp: implementation of the CScalePoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "CurveUnscan.h"
#include "ScalePoint.h"
#include "Axe.h"
#include "CoordSyst.h"
#include "RedrawPart.h"
#include <Utilities/Tools.h>
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CScalePoint,CObject,1)

//////////////////////////////////////////////////////////////////////
// Statiic members
//////////////////////////////////////////////////////////////////////

const double CScalePoint::m_piSur2=acos(0);
const double CScalePoint::m_tickLength=5.0;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CScalePoint::CScalePoint()
	{
	m_AxePosition=m_Position=CPoint(0,0);
	m_Value=0;
	m_DefinedValue=FALSE;
	m_DefinedPosition=FALSE;
	m_pAxe=NULL;
	}

CScalePoint::CScalePoint(CScalePoint &other)
	{
	*this=other;
	}

CScalePoint::~CScalePoint()
	{

	}

BOOL CScalePoint::Draw(CDC *pDC) const
	{
	if(m_DefinedPosition)
		{
		DrawThick(pDC);
		if(m_DefinedValue)
			{
			DrawLegend(pDC);
			}
		return TRUE;
		}
	else
		{
		return FALSE;
		}
	}

BOOL CScalePoint::DrawThick(CDC *pDC) const
	{
	CPoint pt1;
	CPoint pt2;
	if(GetTickLine(pt1,pt2))
	{
		pDC->MoveTo(pt1);
		pDC->LineTo(pt2);
	}

	return TRUE;
	}

BOOL CScalePoint::DrawLegend(CDC *pDC) const
	{
	static const double piSur4=acos(0.707);
	static const int offset=10;
	double angle=m_pAxe->GetAngle();
	int x;
	int y;
	CString legende;
	legende.Format("%g",m_Value);
	if((fabs(angle))<piSur4)
		{
		x=m_AxePosition.x;
		y=m_AxePosition.y+offset;
		pDC->SetTextAlign(TA_TOP|TA_CENTER);
		}
	else
		{
		x=m_AxePosition.x-offset;
		y=m_AxePosition.y;
		pDC->SetTextAlign(TA_BOTTOM|TA_RIGHT);
		}
	pDC->TextOut(x,y,legende);
	return TRUE;
	}

BOOL CScalePoint::SetPosition(CPoint point,list<CRedrawPart>* redrawList/*=null*/)
	{
#ifdef _DEBUG
	if( (point.x<0)||(point.y<0) )
		{
		AfxMessageBox("Scale point : position<0");
		m_Position=CPoint(0,0);
		m_DefinedPosition=FALSE;
		return FALSE;
		}
#endif _DEBUG

	// calculate impacted drawing area
	CPoint pt1;
	CPoint pt2;
	if( (NULL!=redrawList) && (GetTickLine(pt1,pt2)) )
	{
		redrawList->push_back(CRedrawPart(pt1,pt2,true));
		// TO DO:
		// get legend Rect
	}

	m_Position=point;

	// Get new point Rgn
	if(NULL!=redrawList)
	{
		GetTickLine(pt1,pt2);
		redrawList->push_back(CRedrawPart(pt1,pt2,false));
		// TO DO:
		// get legend Rgn
	}

	// recalculate
	m_DefinedPosition=TRUE;
	m_pAxe->GetCoordSyst()->SetModified(TRUE);
	Actualize();
	m_pAxe->GetCoordSyst()->CalculateConversionFactors();
	return TRUE;
	}

BOOL CScalePoint::ValueIsDefined()
	{
	return m_DefinedValue;
	}

CScalePoint::SetValue(double valeur)
	{
	m_Value=valeur;
	m_DefinedValue=TRUE;
	m_pAxe->GetCoordSyst()->SetModified(TRUE);
	m_pAxe->GetCoordSyst()->CalculateConversionFactors();
	}

BOOL CScalePoint::PositionIsDefined()
	{
	return m_DefinedPosition;
	}

void CScalePoint::SetAxe(CAxe *pAxe)
	{
	m_pAxe=pAxe;
	}

BOOL CScalePoint::IsDefined()
	{
	return ( (PositionIsDefined())&&(ValueIsDefined()) );
	}

double CScalePoint::GetValue()
	{
	if (m_DefinedValue)
		{
		return m_Value;
		}
	else
		{
		return 0;
		}
	}

CScalePoint& CScalePoint::operator =(const CScalePoint &other)
// Opérateur de recopie
	{
	if(&other==this)
		{
		return *this;
		}
	m_AxePosition=other.m_AxePosition;
	m_DefinedPosition=other.m_DefinedPosition;
	m_DefinedValue=other.m_DefinedValue;
	m_Position=other.m_Position;
	m_Value=other.m_Value;
	return *this;
	}


// Calcule la projection orthogonale de m_Position sur l'axe
void CScalePoint::Actualize()
	{
	if(!m_DefinedPosition)
		{
		return;
		}
	CPoint A=m_pAxe->GetFrom();
	CPoint B=m_pAxe->GetTo();
	m_AxePosition=CTools::GetProjection(A,B,m_Position);
	}

//	Met la variable m_DefinedValue à FALSE. Valeur de retour : état précédant.
//  Fonction appellée par la classe CScaleDialog lorsque le Contrôle CEdit
//    correspondant est effacé.
BOOL CScalePoint::EraseValue()
	{
	BOOL old=m_DefinedValue;
	m_DefinedValue=FALSE;
	m_pAxe->GetCoordSyst()->SetModified(TRUE);
	m_pAxe->GetCoordSyst()->CalculateConversionFactors();
	return old;
	}

CPoint CScalePoint::GetAxePosition()
	{
	if(m_DefinedPosition)
		{
		return m_AxePosition;
		}
	else
		{
		return CPoint(0,0);
		}
	}


void CScalePoint::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);

	if(ar.IsStoring())
	{
		ar	<< m_DefinedValue
			<< m_DefinedPosition
//			<< m_AxePosition
			<< m_Position
			<< m_Value;
	}
	else
	{
		ar	>> m_DefinedValue
			>> m_DefinedPosition
//			>> m_AxePosition
			>> m_Position
			>> m_Value;
	}
}

bool CScalePoint::GetTickLine(CPoint &pt1, CPoint &pt2) const
{
	if(!m_DefinedPosition)
	{
		return false;
	}

	double angle=m_pAxe->GetAngle();
	int offsetx=(int)(m_tickLength*cos(angle+m_piSur2));
	int offsety=(int)(m_tickLength*sin(angle+m_piSur2));

	pt1.x=m_AxePosition.x+offsetx;
	pt1.y=m_AxePosition.y+offsety;

	pt2.x=m_AxePosition.x-offsetx;
	pt2.y=m_AxePosition.y-offsety;

	return true;
}
