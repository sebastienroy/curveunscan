// Results.cpp: implementation of the CResults class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "CurveUnscan.h"
#include "UnscanDoc.h"
#include "Results.h"
#include "Curve.h"
#include "CoordSyst.h"
#include "LogicPoint.h"
#include <list>
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CResults::CResults()
	{
	m_pCurve=NULL;
	}

CResults::CResults(CCurve* pCurve)
	{
	m_pCurve=pCurve;
	}

CResults::~CResults()
	{

	}

// Renvoie le nombre de points de la liste
int CResults::GetResultCount()
	{
	return m_ResultArray.GetSize();
	}

void CResults::GetLegendLine(int index,list<CString>& outList)
	{
	if(0==index)
		{
		outList.push_back(m_pCurve->GetName());
		outList.push_back(CString(""));
		}
	else if(1==index)
		{
		CString strX=m_pCurve->GetCoordSyst()->GetXAxe()->GetName();
		outList.push_back(strX);
		CString strY=m_pCurve->GetCoordSyst()->GetYAxe()->GetName();
		outList.push_back(strY);
		}
	else
		{
		outList.push_back(CString(""));
		outList.push_back(CString(""));
		}

	}

// Renvoie les données correspondant à la ligne passée en paramètre.
void CResults::GetResultLine(int nIndex,list<CString>& outList)
	{
	int size=m_ResultArray.GetSize();
	if(nIndex<size)
		{
		CString strX;
		CString strY;
		strX.Format("%g",(m_ResultArray[nIndex]).x);
		if(m_ResultArray[nIndex].IsDefined())
			{
			strY.Format("%g",(m_ResultArray[nIndex]).y);
			}
		else
			{
			strY=CString("");
			}
		outList.push_back(strX);
		outList.push_back(strY);
		
		}
	else
		{
		outList.push_back(CString(""));
		outList.push_back(CString(""));
		}
	}

// Construction des résultats. Fonction virtuelle redéfinie dans les classes dérivées
void CResults::Construct()
	{
#ifdef _DEBUG
	AfxMessageBox("Erreur : appel de la fonction construct de base de CResults");
#endif // _DEBUG
	}

CCurve* CResults::GetCurve()
	{
	return m_pCurve;
	}

BOOL CResults::IsContinuousResults() const
	{
	return FALSE;
	}

BOOL CResults::IsDiscreteResults() const
	{
	return FALSE;
	}	

int CResults::GetLegendCount()
{
	return 2;
}

CString CResults::GetBitmapName() const
{
	CUnscanDoc* pDoc=m_pCurve->GetCoordSyst()->GetDocument();
	return pDoc->GetBitmapName();
}

void CResults::SetOwner(CCurve *pCurve)
{
	m_pCurve=pCurve;
//	m_pDoc=pCurve->GetCoordSyst()->GetDocument();
}

CResults* CResults::Clone(CCurve *pCurve/*=NULL*/) const
{
	return NULL;
}

void CResults::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	// that's all folks!
}

CResults& CResults::operator =(const CResults &other)
{
	if(&other==this)
	{
		return *this;
	}
	m_pCurve=other.m_pCurve;
	m_ResultArray.Copy(other.m_ResultArray);
	return *this;
}
