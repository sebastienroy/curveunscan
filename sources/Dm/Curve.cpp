// Curve.cpp: implementation of the CCurve class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Curve.h"
#include "CoordSyst.h"
#include "UnscanDoc.h"
#include "CurveUnscan.h"
#include "Results.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//IMPLEMENT_SERIAL(CCurve,CObject,1)

long CCurve::m_NextIdentifierNumber=1;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCurve::CCurve()
	{
	m_pCoordSyst=NULL;
	Initialize();
	}

CCurve::CCurve(CCoordSyst *pCoord)
	{
	m_pCoordSyst=pCoord;
	Initialize();
	}

CCurve::CCurve(CCurve &otherCurve)
	{
	m_pResults=NULL;
	*this=otherCurve;
	}

void CCurve::Initialize()
// Initialisation de la courbe
// fonction appelée par le constructeur
	{
	m_IdentifierNumber=m_NextIdentifierNumber;
	CUnscanDoc* pDoc=(m_pCoordSyst==NULL)?NULL:m_pCoordSyst->GetDocument();
	m_Color=(pDoc==NULL)?RGB(255,0,0):pDoc->GetColor(m_IdentifierNumber);
	CString strNumber;
	strNumber.Format("%d",m_IdentifierNumber);
	m_CurveName.LoadString(IDS_CURVE);
	m_CurveName+=CString(" ")+strNumber;
	m_Selected=FALSE;
	m_ModifiedFlag=FALSE;
	m_pResults=NULL;
	}

CCurve::~CCurve()
	{
	m_PointList.RemoveAll();
	delete m_pResults;
	}

// dessine la jolie courbe
/*BOOL CCurve::Draw(CDC *pDC)
	{
#ifdef _DEBUG
	AfxMessageBox("Erreur : appel de la fonction\n Draw de la classe CCurve de base");
#endif //_DEBUG
	return FALSE;
	// si cette fonction est appelée c'est que les classes
	// derivees n'ont rien foutu
	}*/

CCurve& CCurve::operator =(const CCurve &otherCurve)
	{
	m_CurveName=otherCurve.m_CurveName;
	m_IdentifierNumber=otherCurve.m_IdentifierNumber;
	m_pCoordSyst=otherCurve.m_pCoordSyst;
	m_Selected=otherCurve.m_Selected;
	m_Color=otherCurve.m_Color;
	m_ModifiedFlag=otherCurve.m_ModifiedFlag;
	if(m_PointList.GetCount()>0)
		{
		m_PointList.RemoveAll();
		}
	POSITION pos=otherCurve.m_PointList.GetHeadPosition();
	while(pos!=NULL)
		{
		m_PointList.AddTail(otherCurve.m_PointList.GetNext(pos));
		}

	// Results
	delete m_pResults;
	m_pResults=NULL;
	if(NULL!=otherCurve.m_pResults)
		{
		// clone using the first curve for construction
		// the current object may be not valid
		m_pResults=otherCurve.m_pResults->Clone(const_cast<CCurve*>(&otherCurve));	
		m_pResults->SetOwner(this);								
		}
	return *this;
	}

CString CCurve::GetName()
	{
	return m_CurveName;
	}

void CCurve::SetName(CString name)
	{
	m_CurveName=name;
	SetModifiedFlag(TRUE);
	}

long CCurve::GetIdentifierNumber()
	{
	return m_IdentifierNumber;
	}


BOOL CCurve::IsDiscreteCurve() const
	{
	return FALSE;
	}

BOOL CCurve::IsContinuousCurve() const
	{
	return FALSE;
	}

void CCurve::SetCoordSyst(CCoordSyst *pCoord)
	{
	m_pCoordSyst=pCoord;
	}

CCoordSyst* CCurve::GetCoordSyst()
	{
	return m_pCoordSyst;
	}

POSITION CCurve::GetHeadPointPosition()
	{
	return m_PointList.GetHeadPosition();
	}

CPoint CCurve::GetNextPoint(POSITION &rPos)
	{
	return m_PointList.GetNext(rPos);
	}

POSITION CCurve::GetTailPointPosition()
	{
	return m_PointList.GetTailPosition();
	}

CPoint CCurve::GetPrevPoint(POSITION &rPos)
	{
	return m_PointList.GetPrev(rPos);
	}

// Tri des points dans l'ordre ascendant 
// par la méthode "Straight Insertion"
void CCurve::SortStraight()
	{
	int size=m_PointList.GetCount();
	if(size<=1)
		{
		return;
		}
	POSITION actPos;	// position du point traité
	POSITION nextPos=m_PointList.GetHeadPosition(); // position du suivant
	POSITION insPos;
	POSITION prevPos;
	m_PointList.GetNext(nextPos);	// Initialisation sur le 1er
	
	CPoint actPoint;	// point traité
	CLogicPoint actLPoint;
	CPoint tryPoint;
	CLogicPoint tryLPoint;

	while(nextPos!=NULL)
		{
		actPos=nextPos;
		actPoint=m_PointList.GetNext(nextPos);
		actLPoint=m_pCoordSyst->ToLogic(actPoint);
		insPos=m_PointList.GetHeadPosition();
		while( (insPos!=actPos)&&(insPos!=NULL) )
			{
			prevPos=insPos;
			tryPoint=m_PointList.GetNext(insPos);
			tryLPoint=m_pCoordSyst->ToLogic(tryPoint);
			if(tryLPoint.x>actLPoint.x)
				{
				m_PointList.InsertBefore(prevPos,actPoint);
				m_PointList.RemoveAt(actPos);
				break;
				}
			}
		}
	SetModifiedFlag(TRUE);

	}

// Renvoie TRUE si la courbe passe par le point donné en paramètre
BOOL CCurve::IsPresentOn(CPoint point) const
	{
	BOOL flag=FALSE;
	POSITION pos=m_PointList.GetHeadPosition();
	while( (pos!=NULL)&&(flag==FALSE) )
		{
		if(point==m_PointList.GetNext(pos))
			{
			flag=TRUE;
//			AfxMessageBox("Double click sur la courbe");
			}
		}
	return flag;
	}

BOOL CCurve::IsSelected()
	{
	return m_Selected;
	}

void CCurve::SetSelected(BOOL flag)
	{
	m_Selected=flag;
	}

long CCurve::ResetIdentifierNumber()
	{
	long val=m_NextIdentifierNumber;
	m_NextIdentifierNumber=1;
	return val;
	}

int CCurve::GetPointCount()
	{
	return m_PointList.GetCount();
	}


long CCurve::IncrementIDNumber()
	{
	m_NextIdentifierNumber++;
	return m_NextIdentifierNumber;
	}

BOOL CCurve::GetModifiedFlag()
	{
	return m_ModifiedFlag;
	}

BOOL CCurve::SetModifiedFlag(BOOL flag)
	{
	BOOL previous=m_ModifiedFlag;
	m_ModifiedFlag=flag;

	CUnscanDoc *pDoc=m_pCoordSyst->GetDocument();
	pDoc->UpdateModifiedState();

	return previous;
	}


POSITION CCurve::FindPoint(CPoint point)
	{
	POSITION pos=m_PointList.GetHeadPosition();
	POSITION prevPos;
	POSITION foundPos=NULL;
	CPoint tryPoint;
	while( (pos!=NULL)&&(foundPos==NULL) )
		{
		prevPos=pos;
		tryPoint=m_PointList.GetNext(pos);
		if(tryPoint==point)
			{
			foundPos=prevPos;
			}
		}
	return foundPos;
	}

void CCurve::SetResults(CResults *pResults)
{
	delete m_pResults;
	m_pResults=pResults;
	m_pResults->SetOwner(this);		// enfoncer le clou
}

CResults* CCurve::GetResults()
{
	return m_pResults;
}

void CCurve::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	if(ar.IsStoring())
	{
		ar << m_Color 
			<< m_CurveName 
			<< m_IdentifierNumber
			<< m_NextIdentifierNumber
			<< m_Selected;

		// points
		int nPointsNb=m_PointList.GetCount();
		ar << nPointsNb;
		POSITION pos=m_PointList.GetHeadPosition();
		while(NULL!=pos)
		{
			CPoint point=m_PointList.GetNext(pos);
			ar << point;
		}

		// results
		ar << m_pResults;

	}
	else
	{
		ar >> m_Color 
			>> m_CurveName 
			>> m_IdentifierNumber
			>> m_NextIdentifierNumber
			>> m_Selected;

		// points
		int nPointsNb;
		ar >> nPointsNb;
		for(int nCounter=0;nCounter<nPointsNb;nCounter++)
		{
			CPoint point;
			ar >>  point;
			m_PointList.AddTail(point);
		}

		CObject *pObjResults=NULL;
		ar >> pObjResults;
		CResults *pResults=dynamic_cast<CResults*>(pObjResults);
		if(NULL!=pResults)
		{
			m_pResults=pResults;
			m_pResults->SetOwner(this);
		}

	}
}

