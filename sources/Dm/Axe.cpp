// Axe.cpp: implementation of the CAxe class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "CurveUnscan.h"
#include "CoordSyst.h"
#include "Axe.h"
#include <Utilities/Tools.h>
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CAxe,CObject,1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAxe::CAxe()
	{
	m_From=m_To=CPoint(0,0);
	m_Logarithmic=FALSE;
	m_Angle=0;
	m_Defined=FALSE;
	m_ScalePoint1.SetAxe(this);
	m_ScalePoint2.SetAxe(this);
	}

CAxe::CAxe(CAxe &other)
	{
	*this=other;
	}

CAxe::~CAxe()
	{

	}

BOOL CAxe::Draw(CDC *pDC) const
// Dessine les axes (choisis par l'utilisateur
// Si l'origine du système de coordonnées est définie et qu'elle 
//  n'est pas située entre les deux points de définition de l'axe, 
//  le tracé s'effectue à partir de l'origine.
	{
	if(!m_Defined)
		{
		return FALSE;
		}
	CPoint A=m_From;
	CPoint B=m_To;
	if(m_pCoordSyst->OriginIsDefined())
		{
		CPoint O=m_pCoordSyst->GetOrigin();
		double k=CTools::GetNormalizedScalar(A,B,O);
		if(k<0)
			{
			A=O;
			}
		else if(k>1.0)
			{
			B=O;
			}
		}
	pDC->MoveTo(A);
	pDC->LineTo(B);
	m_ScalePoint1.Draw(pDC);
	m_ScalePoint2.Draw(pDC);
	return TRUE;
	}

double CAxe::Actualize()
// calcule l'angle de l'axe et met a jour la variable "m_Defined"
// Appelée après modification des points de l'axe.(SetPositions)
	{
	if ((m_From==CPoint(0,0))||(m_To==CPoint(0,0)) )
		{
		m_Angle=0;
		}
	else
		{
		double numerateur;
		double denominateur;
		numerateur=(double)(m_To.y-m_From.y);
		denominateur=(double)(m_To.x-m_From.x);
		if((fabs(denominateur))<=1.0e-5)
			{
			double pi=acos(-1.0);
			m_Angle=pi/2.0;
			}
		else
			{
			m_Angle=atan(numerateur/denominateur);
			}
		m_ScalePoint1.Actualize();
		m_ScalePoint2.Actualize();
		}
	m_Defined=((m_From==CPoint(0,0))&&(m_To==CPoint(0,0)))?FALSE:TRUE;
	return m_Angle;
	}


CAxe& CAxe::operator =(const CAxe &other)
	{
	if(&other==this)
		{
		return *this;
		}
	m_Angle=other.m_Angle;
	m_AxeName=other.m_AxeName;
	m_Defined=other.m_Defined;
	m_From=other.m_From;
	m_To=other.m_To;
	m_Logarithmic=other.m_Logarithmic;
	m_ScalePoint1=other.m_ScalePoint1;
	m_ScalePoint1.SetAxe(this);
	m_ScalePoint2=other.m_ScalePoint2;
	m_ScalePoint2.SetAxe(this);
	return *this;
	}


BOOL CAxe::SetLogarithmic(BOOL toto)
	{
	m_Logarithmic=toto;
	m_pCoordSyst->SetModified();
	return toto;
	}	

void CAxe::SetPosition(CPoint from, CPoint to)
	{
	m_From=from;
	m_To=to;
	m_Defined=TRUE;
	m_pCoordSyst->SetModified();
	Actualize();
	}


void CAxe::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);

	if( ar.IsStoring() )
	{
		ar	<< m_From << m_To << m_Logarithmic << m_AxeName;			
		m_ScalePoint1.Serialize(ar);
		m_ScalePoint2.Serialize(ar);
	}
	else
	{
		ar	>> m_From >> m_To >> m_Logarithmic >> m_AxeName;
		m_ScalePoint1.Serialize(ar);
		m_ScalePoint2.Serialize(ar);

		m_ScalePoint1.SetOwner(this);
		m_ScalePoint2.SetOwner(this);
		Actualize();
	}

}

bool CAxe::IsSegmentParallal(CPoint pt1, CPoint pt2) const
{
	if(!m_Defined)
	{
		return true;
	}
	double vectProduct=CTools::GetVectorialProduct(pt1,pt2,m_From,m_To);
	return (0==vectProduct);
}
