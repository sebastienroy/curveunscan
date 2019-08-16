// Limit.cpp: implementation of the CLimit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "CurveUnscan.h"
#include "Limit.h"
#include "ContinuousCurve.h"
#include "LogicPoint.h"
#include "CoordSyst.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CLimit,CObject,1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLimit::CLimit()
	:CCurveElement()
	{
	m_Defined=FALSE;
//	m_pCoordSyst=NULL;
	}

CLimit::CLimit(CContinuousCurve *pCurve,BOOL left)
	:CCurveElement(pCurve)
	{
//	m_pCoordSyst=pCurve->GetCoordSyst();
	m_Defined=FALSE;
	m_Left=left;
	}

CLimit::CLimit(CLimit *otherLimit)
	{
//	CCurveElement::operator=(*otherLimit);
	*this=*otherLimit;
	}

CLimit::~CLimit()
	{
//	AfxMessageBox("~CLimit()");

	}

void CLimit::SetValue(double value)
	{
	m_Value=value;
	m_Defined=TRUE;
	m_pCurve->SetModifiedFlag(TRUE);
	}
	
double CLimit::GetValue()
	{
	if(m_Defined)
		{
		return m_Value;
		}
	else
		{
		return 0;
		}
	}

BOOL CLimit::IsDefined()
	{
	return m_Defined;
	}

BOOL CLimit::HaveIncluded(CPoint point)
// Retourne TRUE si le point spécifié est hors de la limite.
	{
	CCoordSyst *pCoordSyst=m_pCurve->GetCoordSyst();
	CLogicPoint lPoint=pCoordSyst->ToLogic(point);
	BOOL reverse=pCoordSyst->XAxeIsReverse();
	BOOL result=(lPoint.x<m_Value)?TRUE:FALSE;
	result=(m_Left)?result:!result;
	result=(reverse)?!result:result;
	return result;
	}

CLimit& CLimit::operator =(CLimit &otherLimit)
	{
	if(&otherLimit==this)
		{
		return *this;
		}
	m_Defined=otherLimit.m_Defined;
	m_Left=otherLimit.m_Left;
	m_Value=otherLimit.m_Value;
//	m_pCoordSyst=otherLimit.m_pCoordSyst;
	CCurveElement::operator=(otherLimit);

	return *this;
	}


BOOL CLimit::IsLimit()
	{
	return TRUE;
	}

BOOL CLimit::RemovePart(CPoint point, BOOL toLeft)
	{
// Sur les limites il n'y a rien à enlever
	return TRUE;
	}

BOOL CLimit::EraseValue()
	{
	BOOL old=m_Defined;
	m_Defined=FALSE;
	m_pCurve->SetModifiedFlag(TRUE);
	return old;
	}

RelativePosition CLimit::GetRelativePosition(const CPoint &point) const
{
	CCoordSyst *pCoordSyst=m_pCurve->GetCoordSyst();
	CLogicPoint lPoint=pCoordSyst->ToLogic(point);
	BOOL reverse=pCoordSyst->XAxeIsReverse();
	BOOL isOn=(lPoint.x<m_Value)?TRUE:FALSE;
	isOn=(m_Left)?isOn:!isOn;
	isOn=(reverse)?!isOn:isOn;
	RelativePosition relPos=(isOn)?kOn:kOutside;
	return relPos;
}

void CLimit::Serialize(CArchive &ar)
{
	CCurveElement::Serialize(ar);
	
	if( ar.IsStoring() )
	{
		ar << m_Left << m_Defined << m_Value;
	}
	else
	{
		ar >> m_Left >> m_Defined >> m_Value;
	}
}
