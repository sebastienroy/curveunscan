// CurveElement.cpp: implementation of the CCurveElement class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "CurveUnscan.h"
#include "CurveElement.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCurveElement::CCurveElement()
	{
	m_pCurve=NULL;
	Initialize();
	}

CCurveElement::CCurveElement(CContinuousCurve *pCurve)
	{
	Initialize();
	m_pCurve=pCurve;
	}

// Initialisation de l'élément
// fonction appelée par le constructeur
void CCurveElement::Initialize()
	{
	m_pLeftElement=m_pRightElement=NULL;
	}

CCurveElement::~CCurveElement()
	{
//	AfxMessageBox("~CCurveElement()");
	}


CContinuousCurve* CCurveElement::GetCurve()
	{
	return m_pCurve;
	}

BOOL CCurveElement::HaveIncluded(CPoint point)
	{
	return FALSE;
	}

CCurveElement* CCurveElement::GetRightElement()
	{
	return m_pRightElement;
	}

CCurveElement* CCurveElement::GetLeftElement()
	{
	return m_pLeftElement;
	}

void CCurveElement::SetLeftElement(CCurveElement *pElement)
	{
	m_pLeftElement=pElement;
	}

void CCurveElement::SetRightElement(CCurveElement *pElement)
	{
	m_pRightElement=pElement;
	}

void CCurveElement::SetCurve(CContinuousCurve *pCurve)
	{
	m_pCurve=pCurve;
	}

BOOL CCurveElement::IsLimit()
	{
	return FALSE;
	}

BOOL CCurveElement::IsPartialCurve()
	{
	return FALSE;
	}


// Elève une partie de l'élément
// Fonction virtuelle
BOOL CCurveElement::RemovePart(CPoint point, BOOL toLeft)
	{
#ifdef _DEBUG
	AfxMessageBox("Appel de RemovePart(...) de la classe de base");
#endif // _DEBUG
	return FALSE;
	}


CCurveElement& CCurveElement::operator =(const CCurveElement &otherElement)
{
	if(this==&otherElement)
		{
		return *this;
		}
	m_pCurve=otherElement.m_pCurve;
	m_pLeftElement=otherElement.m_pLeftElement;
	m_pRightElement=otherElement.m_pRightElement;
	return *this;
}


void CCurveElement::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	// That's all folks!
}
