// ContinuousCurve.cpp: implementation of the CContinuousCurve class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "ContinuousCurve.h"
#include "CurveElement.h"
#include "PartialCurve.h"
#include "Limit.h"
#include "LogicPoint.h"
#include "CoordSyst.h"
#include "plpixel32.h"
#include "FlatThicknessCorrector.h"
#include "SmartThicknessCorrector.h"
#include "ContinuousResults.h"
#include "SimpleSnail.h"
#include "DashedSnail.h"
#include <list>
using namespace std;
#include "SettingsManagement/ContinuousCurveDefaultValues.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CContinuousCurve,CObject,1)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CContinuousCurve::CContinuousCurve()
	:CCurve()
	{
	Initialize();
	}

CContinuousCurve::CContinuousCurve(CCoordSyst *pCoord, const SContinuousCurveDefaultValues &defaultValues)
	:CCurve(pCoord)
	{
	Initialize(defaultValues);
	}

CContinuousCurve::CContinuousCurve(CContinuousCurve &otherCurve)
	:CCurve(otherCurve),m_pThicknessCorrector(NULL)
	{
	*this=otherCurve;
	}

CContinuousCurve::~CContinuousCurve()
	{
	RemoveAllElements();
	}

// Trace une courbe continue. Interrompt le trait si les points ne sont pas contigus.
BOOL CContinuousCurve::Draw(CDC *pDC) const
	{
	if(m_PointList.IsEmpty())
		{
		return FALSE;
		}
	CPen pen(PS_SOLID,(m_Selected)?2:1,m_Color);
	CPen* oldPen=pDC->SelectObject(&pen);
	POSITION pointPos=m_PointList.GetHeadPosition();
	CPoint point=m_PointList.GetNext(pointPos);
	pDC->MoveTo(point);
	CPoint prevPoint=point;
	while(pointPos!=NULL)
		{
		point=m_PointList.GetNext(pointPos);
		if((point.x-prevPoint.x)!=1)
			{
			pDC->MoveTo(point);
			}
		else
			{
			pDC->LineTo(point);
			}
		prevPoint=point;
		}
	POSITION elementPos=m_pElementList.GetHeadPosition();
	CCurveElement* pElement;
	CPoint genesisPoint;
	CPoint from;
	CPoint to;
	while(elementPos!=NULL)
		{
		pElement=m_pElementList.GetNext(elementPos);
		if(pElement->IsPartialCurve())
			{
			genesisPoint=((CPartialCurve*)pElement)->GetPosition();
			from=to=genesisPoint;
			from.y+=2;
			to.y-=3;
			pDC->MoveTo(from);
			pDC->LineTo(to);
			from=to=genesisPoint;
			from.x+=2;
			to.x-=3;
			pDC->MoveTo(from);
			pDC->LineTo(to);
			}
		}
	pDC->SelectObject(oldPen);
	return TRUE;
	}

CContinuousCurve& CContinuousCurve::operator =(const CContinuousCurve &otherCurve)
	{
	if(&otherCurve==this)
		{
		return *this;
		}
	CCurve::operator =(otherCurve);
	m_BlackLevel=otherCurve.m_BlackLevel;
	CAbstractThicknessCorrector* aCorrector=otherCurve.GetThicknessCorrector();
	delete m_pThicknessCorrector;
	m_pThicknessCorrector=aCorrector->Clone(this);
	m_TopFollow=otherCurve.m_TopFollow;
	m_HandModification=otherCurve.m_HandModification;
	m_bDashed=otherCurve.m_bDashed;
	m_nDashMaxDist=otherCurve.m_nDashMaxDist;
	m_pSnail=NULL;

	//--- curve elements
	POSITION pos;
	if(!m_pElementList.IsEmpty())
		{
		pos=m_pElementList.GetHeadPosition();
		while(pos!=NULL)
			{
			delete m_pElementList.GetNext(pos);
			}
		m_pElementList.RemoveAll();
		}
	CCurveElement* prevElement;
	CCurveElement* currentElement;
	CCurveElement* pElement;
	pos=otherCurve.m_pElementList.GetHeadPosition();
	currentElement=otherCurve.m_pElementList.GetNext(pos);
	pElement=new CLimit((CLimit*)currentElement);
	pElement->SetCurve(this);
	m_pElementList.AddTail(pElement);
	while(pos!=NULL)	// pas beau le code! il aurait fallu faire un clone() !
		{
		prevElement=pElement;
		currentElement=otherCurve.m_pElementList.GetNext(pos);
		if(currentElement->IsLimit())
			{	
			pElement=(CCurveElement*)new CLimit((CLimit*)currentElement);
			}
		else
			{
			pElement=(CCurveElement*)new CPartialCurve((CPartialCurve*)currentElement);
			}
		pElement->SetCurve(this);
		m_pElementList.AddTail(pElement);
		prevElement->SetRightElement(pElement);
		pElement->SetLeftElement(prevElement);
		}

	//--- results (Performed by the base class)
/*	m_pResults=NULL;
	CResults* pResults=otherCurve.m_pResults;
	if(NULL!=pResults)
		{
		m_pResults=pResults->Clone(this);
		}
*/
	return *this;
	}

void CContinuousCurve::Initialize()
	{
	m_TopFollow=TRUE;
	m_HandModification=FALSE;
	m_bDashed=false;
	m_nDashMaxDist=20;
	m_pSnail=NULL;
	m_BlackLevel=PLPixel32(70,70,70,0);
	m_pThicknessCorrector=new CSmartThicknessCorrector(this);

	CLimit* pLLimit=new CLimit(this,TRUE);
	CLimit* pRLimit=new CLimit(this,FALSE);

	m_pElementList.AddHead(pLLimit);
	m_pElementList.AddTail(pRLimit);
	pLLimit->SetRightElement(pRLimit);
	pRLimit->SetLeftElement(pLLimit);

	}

void CContinuousCurve::Initialize(const SContinuousCurveDefaultValues &defaultValues)
{
	m_TopFollow=(kTopFollow==defaultValues.m_nFollow)?TRUE:FALSE;
	m_bDashed=defaultValues.m_bDashed;
	m_nDashMaxDist=defaultValues.m_nDashMaxDist;
	m_BlackLevel=defaultValues.m_BlackColor;
	if(kSmartAlgo==defaultValues.m_nThicknessAlgo)
	{
		m_pThicknessCorrector=new CSmartThicknessCorrector(this,defaultValues.m_nSmartAlgoRange);
	}
	else
	{
		m_pThicknessCorrector=new CFlatThicknessCorrector(this);
	}

	CLimit* pLLimit=new CLimit(this,TRUE);
	CLimit* pRLimit=new CLimit(this,FALSE);

	m_pElementList.AddHead(pLLimit);
	m_pElementList.AddTail(pRLimit);
	pLLimit->SetRightElement(pRLimit);
	pRLimit->SetLeftElement(pLLimit);
	

	m_pSnail=NULL;
	m_HandModification=FALSE;
}

//Remplit la liste de points de la courbe à partir des différents éléments de courbe.
//Renvoie FALSE s'il n'existe que les limites.
BOOL CContinuousCurve::FillFromElements()
	{
	m_PointList.RemoveAll();
	if(m_pElementList.GetCount()<=2)
		{
		return FALSE;
		}
	POSITION pos=m_pElementList.GetHeadPosition();
	POSITION pointPos;
	CCurveElement* pElement;
	BOOL error=FALSE;
	while( (pos!=NULL)&&(!error) )
		{
		pElement=m_pElementList.GetNext(pos);
		if(pElement->IsPartialCurve())
			{
			CPartialCurve* pPartial=(CPartialCurve*)pElement;
			int nbPoints=pPartial->GetPointsNumber();
			CPoint point;
			for(int i=0;(i<nbPoints)&&(!error);i++)
				{
				point=pPartial->GetPoint(i);
//				(point.y)+=(m_TopFollow)?m_LineThickness/2:(m_LineThickness*(-1)/2);
				pointPos=m_PointList.AddTail(point);
				if(pointPos==NULL)
					{
					error=TRUE;
					}
				}
			}
		}
	// now compensate with the thickness
	m_pThicknessCorrector->CompensateThickness(m_PointList,(bool)m_TopFollow);
	m_HandModification=FALSE;
	SetModifiedFlag(TRUE);
	return !error;
	}

// Enlève un élément de la liste et rétablit les liens entre les éléments restants.
// La destruction des éléments concernés est à charge de la fonction appelante.
// Renvoie FALSE si l'élément n'a pas été trouvé.
BOOL CContinuousCurve::RemoveElement(CCurveElement *pElement)
	{
	POSITION pos=m_pElementList.Find(pElement);
	if(pos==NULL)
		{
#ifdef _DEBUG
		AfxMessageBox("RemoveElement(...) : courbe partielle non trouvée.");
#endif // _DEBUG
		return FALSE;
		}
	CCurveElement* prevElement=pElement->GetLeftElement();
	CCurveElement* nextElement=pElement->GetRightElement();
	if(prevElement!=NULL)
		{
		prevElement->SetRightElement(nextElement);
		}
	if(nextElement!=NULL)
		{
		nextElement->SetLeftElement(prevElement);
		}
#ifdef _DEBUG
	if( (prevElement==NULL)||(nextElement==NULL) )
		{
		AfxMessageBox("RemoveElement(...) : Element voisin NULL.");
		}
#endif // _DEBUG
	m_pElementList.RemoveAt(pos);

	return TRUE;
	}

// Construit l'ensemble des courbes partielles et remplit la liste de points
// à partir de celles-ci.
void CContinuousCurve::Construct()
	{
	POSITION pos;
	BOOL isNotRedundant;
	BOOL tryAgain=TRUE;
	while(tryAgain)		// tant qu'il y a des éléments redondants de détectés
		{
		pos=m_pElementList.GetHeadPosition();
		CCurveElement* pElement;
		while(pos!=NULL)	// Tout d'abord, virer les points existants
			{
			pElement=m_pElementList.GetNext(pos);
			if(pElement->IsPartialCurve())
				{
				((CPartialCurve*)pElement)->DeleteContent();
				}
			}
		tryAgain=FALSE;
		pos=m_pElementList.GetHeadPosition();
		while(pos!=NULL)	
			{
			pElement=m_pElementList.GetNext(pos);	// construire les différents éléments
			if(pElement->IsPartialCurve())
				{
				isNotRedundant=((CPartialCurve*)pElement)->Construct();
				if(!isNotRedundant)			// et virer ceux qui sont redondants
					{	
					CPoint redundant=((CPartialCurve*)pElement)->GetPosition();
					CLogicPoint lRedundant=m_pCoordSyst->ToLogic(redundant);
					CString msgFormat;
					msgFormat.LoadString(IDS_GENESIS_POINT_REDUNDANT);
					CString str;
					str.Format(msgFormat,lRedundant.x,lRedundant.y);
					AfxMessageBox(str,MB_OK|MB_ICONINFORMATION);
					RemoveElement(pElement);
					delete pElement;
					tryAgain=TRUE;
					break;
					}
				}
			}
		}
	FillFromElements();
	m_HandModification=FALSE;
	}

// Ajoute une courbe partielle à la liste.
// La place dans l'ordre des x croissants.
POSITION CContinuousCurve::AddElement(CPartialCurve *pPartial)
	{
	CPoint newPoint=pPartial->GetPosition();
	CPoint elementPoint;
	POSITION pos=m_pElementList.GetHeadPosition();
	POSITION prevPos;
	POSITION newPos=NULL;
	CCurveElement* pElement=m_pElementList.GetNext(pos);
	CCurveElement* prevElement;
	if(pElement->HaveIncluded(newPoint))
		{
#ifdef _DEBUG
		AfxMessageBox("Element inclus dans la limite gauche");
#endif // _DEBUG
		return NULL;
		}
	while(pos!=NULL)
		{
		prevElement=pElement;
		prevPos=pos;
		pElement=m_pElementList.GetNext(pos);
		if(pElement->IsPartialCurve())
			{
			elementPoint=((CPartialCurve*)pElement)->GetPosition();
			if( (newPoint.x)<(elementPoint.x) )
				{
				pElement->SetLeftElement(pPartial);
				prevElement->SetRightElement(pPartial);
				newPos=m_pElementList.InsertBefore(prevPos,pPartial);
				pPartial->SetLeftElement(prevElement);
				pPartial->SetRightElement(pElement);
				SetModifiedFlag(TRUE);
				return newPos;
				}
			}
		else
			{

			if(pElement->HaveIncluded(newPoint))
				{
#ifdef _DEBUG
		AfxMessageBox("Element inclus dans la limite droite");
#endif // _DEBUG
				return NULL;
				}
			else
				{
				pElement->SetLeftElement(pPartial);
				prevElement->SetRightElement(pPartial);
				newPos=m_pElementList.InsertBefore(prevPos,pPartial);
				pPartial->SetLeftElement(prevElement);
				pPartial->SetRightElement(pElement);
				SetModifiedFlag(TRUE);
				return newPos;
				}
			}
		}
	return NULL;
	}

// Remplace (ou insere) le point passé en paramètre dans la liste de points.
//  ( modification manuelle )
// Renvoie le rectangle de la région à raffraichir
CRect CContinuousCurve::SetPoint(CPoint point)
	{
	CPoint previousPoint;
	BOOL thereIsPrevious=FALSE;

	POSITION pos=m_PointList.GetHeadPosition();
	POSITION prevPos;
	POSITION newPos=NULL;
	CPoint targetPoint(0,0);
	while( (pos!=NULL)&&(newPos==NULL) )
		{
		prevPos=pos;
		targetPoint=m_PointList.GetNext(pos);
		if(point.x==targetPoint.x)// il existe un point de même x
			{
			//--- set the point
			newPos=prevPos;
			m_PointList.SetAt(prevPos,point);

			thereIsPrevious=TRUE;	// used for rectangle
			previousPoint=targetPoint;
			}
		if(targetPoint.x>point.x)// il n'existe pas de point de même x mais il
			{						// existe des points après
			newPos=m_PointList.InsertBefore(prevPos,point);
			}
		}
	if(newPos==NULL)	// il n'existe que des points avant ou pas de points
		{				// du tout
		newPos=m_PointList.AddTail(point);
		}

	//--- get the rectangle
	int minx;
	int maxx;
	int miny;
	int maxy;

	minx=maxx=point.x;
	miny=maxy=point.y;
//	SetMinMax(point.x,minx,maxx);
//	SetMinMax(point.y,miny,maxy);

	if(thereIsPrevious)					// get the replaced point
		{
		SetMinMax(previousPoint.y,miny,maxy);
		}
	pos=newPos;							// get the point after
	m_PointList.GetNext(pos);
	if(pos!=NULL)
		{
		targetPoint=m_PointList.GetNext(pos);
		SetMinMax(targetPoint.y,miny,maxy);

		}
	pos=newPos;							// get the point before
	m_PointList.GetPrev(pos);
	if(pos!=NULL)
		{
		targetPoint=m_PointList.GetPrev(pos);
		SetMinMax(targetPoint.y,miny,maxy);
		}

	SetModifiedFlag(TRUE);
	return CRect(minx-2,miny-1,maxx+2,maxy+1);
	}

BOOL CContinuousCurve::IsPresentOn(CPoint point) const
	{
/*	BOOL flag=FALSE;	// il est douteux ce code...
	BOOL first=TRUE;
	POSITION pos=m_PointList.GetHeadPosition();
	CPoint tryPoint(0,0);
	CPoint nextPoint;
	CPoint prevPoint;
	while( (pos!=NULL)&&(flag==FALSE) )
		{
		prevPoint=tryPoint;
		tryPoint=m_PointList.GetNext(pos);
		if(point.x==tryPoint.x)
			{
			if(first)
				{
				prevPoint=tryPoint;
				}
			nextPoint=(pos!=NULL)?m_PointList.GetAt(pos):tryPoint;
			int min=(prevPoint.y<tryPoint.y)?prevPoint.y:tryPoint.y;
			min=(min<nextPoint.y)?min:nextPoint.y;
			int max=(prevPoint.y>tryPoint.y)?prevPoint.y:tryPoint.y;
			max=(max>nextPoint.y)?max:nextPoint.y;
			if( (point.y>=min-2)&&(point.y<=max+2) )
				{
				flag=TRUE;
				}
			}
		first=FALSE;
		}
	return flag;*/

	// First, find the point which have the same x
	bool found=false;
	POSITION pos;
	POSITION previousPos;
	POSITION middlePos;
	CPoint currentPoint;
	pos=m_PointList.GetHeadPosition();
	while( (NULL!=pos)&&(!found) )
		{
		previousPos=pos;
		currentPoint=m_PointList.GetNext(pos);
		if(currentPoint.x==point.x)
			{
			found=true;
			middlePos=previousPos;
			}
		}
	
	if(!found)	// no point with the same x
		{
		return false;
		}

	// a point have been found
	int ymin=currentPoint.y;
	int ymax=currentPoint.y;
	CPoint leftPoint;

	// Get the point immediately to the right
	if(NULL!=pos)	// pos is now set to the n+1 element
		{
		CPoint rightPoint;
		rightPoint=m_PointList.GetAt(pos);
		if(rightPoint.x-1==point.x)	// if curve continuous
			{
			if(rightPoint.y>ymax)	ymax=rightPoint.y;
			if(rightPoint.y<ymin)	ymin=rightPoint.y;
			}
		}

	// Get the point immediately to the left
	pos=middlePos;
	m_PointList.GetPrev(pos);
	if(NULL!=pos)	// pos is now set to the n-1 element
		{
		CPoint leftPoint;
		leftPoint=m_PointList.GetAt(pos);
		if(leftPoint.x+1==point.x)	// if curve continuous
			{
			if(leftPoint.y>ymax)	ymax=leftPoint.y;
			if(leftPoint.y<ymin)	ymin=leftPoint.y;
			}
		}

	// Set a little range arround the min and the max
	ymax+=2;
	ymin-=2;

	// is the user point inside this interval?
	bool result=( (point.y>=ymin)&&(point.y<=ymax) );
	return result;	
	}


// ATTENTION VERIFIER LE SENS DANS LEQUEL LES POINTS SONT ENREGISTRES
// gauche : Head ; droite : tail
CRect CContinuousCurve::SetLine(CPoint ptA, CPoint ptB)
	{
	CRect refreshRect;

	if(ptA.x==ptB.x) // cas où les deux points sont verticaux
		{
		refreshRect=SetPoint(ptB);
		}
	else	// Points non verticaux->plusieurs points à traiter
		{
		int minx=ptA.x;	// refresh rectangle
		int maxx=ptA.x;
		int miny=ptA.y;
		int maxy=ptA.y;
		SetMinMax(ptB.x,minx,maxx);
		SetMinMax(ptB.y,miny,maxy);
		POSITION posA;
		POSITION posB;

		if(ptA.x>ptB.x)	// on choisit d'aller de la gauche à la droite
			{
			CPoint ptTemp(ptA);
			ptA=ptB;
			ptB=ptTemp;
			}
		// tout d'abord virer les eventuels points existants
		POSITION pos=m_PointList.GetHeadPosition();
		POSITION previousPos;
		CPoint currentPoint;
		while(pos!=NULL)
			{
			previousPos=pos;
			currentPoint=m_PointList.GetNext(pos);
			if( (currentPoint.x>=ptA.x)&&(currentPoint.x<=ptB.x) )
				{
				SetMinMax(currentPoint.y,miny,maxy);
				m_PointList.RemoveAt(previousPos);
				}
			}
		// Trouver l'endroit ou on va insérer la ligne
		pos=m_PointList.GetHeadPosition();
		bool found=false;
		while( (pos!=NULL)&&(!found) )
			{
			previousPos=pos;
			currentPoint=m_PointList.GetNext(pos);
			if(currentPoint.x>ptA.x)
				{
				found=true;
				}
			}
		// Insertion of the first point
		POSITION currentPos;
		if(found) // there is points after the line
			{
			currentPos=m_PointList.InsertBefore(previousPos,ptA);
			}
		else	// the list is empty or no points after the line
			{
			currentPos=m_PointList.AddTail(ptA);
			}
		posA=currentPos;
		// Insertion of the other points
		int num=ptB.y-ptA.y;
		int den=ptB.x-ptA.x;
		double coef=(double)num/(double)den;
		int abscisse;
		int ordonnee;
		for(int i=1;i<=(ptB.x-ptA.x);i++)
			{
			abscisse=i+ptA.x;
			ordonnee=ptA.y+(int)(coef*(double)i);
			currentPos=m_PointList.InsertAfter(currentPos,CPoint(abscisse,ordonnee));
			}
		posB=currentPos;

		// include y of first left and first right points in the refresh rectangle
		currentPos=posA;	// left
		m_PointList.GetPrev(currentPos);
		if(NULL!=currentPos)
			{
			currentPoint=m_PointList.GetPrev(currentPos);
			SetMinMax(currentPoint.y,miny,maxy);
			}

		currentPos=posB;	// right
		m_PointList.GetNext(currentPos);
		if(NULL!=currentPos)
			{
			currentPoint=m_PointList.GetNext(currentPos);
			SetMinMax(currentPoint.y,miny,maxy);
			}

		refreshRect=CRect(minx-1,miny-1,maxx+1,maxy+1);
		}

#if defined(_DEBUG)	// check no duplicated x
	POSITION debugPos;
	CPoint debugCurrentPt;
	CPoint debugPreviousPt;
	debugPos=m_PointList.GetHeadPosition();
	if(NULL!=debugPos)
		{
		debugPreviousPt=m_PointList.GetNext(debugPos);
		}
	while(NULL!=debugPos)
		{
		debugCurrentPt=m_PointList.GetNext(debugPos);
		ASSERT(debugPreviousPt.x!=debugCurrentPt.x);
		debugPreviousPt=debugCurrentPt;
		}
#endif	// defined(_DEBUG)

	SetModifiedFlag(TRUE);
	return refreshRect;
	}

BOOL CContinuousCurve::IsContinuousCurve() const
	{
	return TRUE;
	}

// Raffraichit un min et un max par rapport à une valeur
// laisse une marge de 1 pixel, ne peut être < 0
// Utilisé par SetPoint et par SetLine
void CContinuousCurve::SetMinMax(int nValue, int &nMin, int &nMax) const
{
	if(nMin>nValue) nMin=nValue;
	if(nMax<nValue) nMax=nValue;
	if(nMin<0)
		{
		nMin=0;
		}
	if(nMax<0)
		{
		nMax=0;
		}
}

// Method used to the undo/redo feature of manual modification
void CContinuousCurve::GetPointList(list<CPoint>* pointList) const
{
	POSITION pos=m_PointList.GetHeadPosition();
	CPoint aPoint;
	while(NULL!=pos)
		{
		aPoint=m_PointList.GetNext(pos);
		pointList->push_back(aPoint);
		}
}

// Method used to the undo/redo feature of manual modification
void CContinuousCurve::SetPointList(const list<CPoint>* pointList)
{
	m_PointList.RemoveAll();
	list<CPoint>::const_iterator iter;
	for(iter=pointList->begin();iter!=pointList->end();iter++)
		{
		m_PointList.AddTail(*iter);
		}
	SetModifiedFlag(TRUE);
}

PLPixel32 CContinuousCurve::GetBlackLevel()
{
	return m_BlackLevel;
}

void CContinuousCurve::SetThicknessCorrector(CAbstractThicknessCorrector *theCorrector)
{
	delete m_pThicknessCorrector;
	m_pThicknessCorrector=theCorrector;
	SetModifiedFlag(TRUE);
}

CAbstractThicknessCorrector* CContinuousCurve::GetThicknessCorrector() const
{
	return m_pThicknessCorrector;
}

void CContinuousCurve::SetBlackLevel(PLPixel32 pixel)
{
	m_BlackLevel=pixel;
	SetModifiedFlag(TRUE);
}

CRect CContinuousCurve::ErasePoint(const CPoint &point)
{
	int minx=0;
	int miny=0;
	int maxx=0;
	int maxy=0;

	POSITION pos=m_PointList.GetHeadPosition();
	POSITION prevPos;

	bool found=false;

	while((pos!=NULL)&&(!found))
		{
		prevPos=pos;
		CPoint currentPt=m_PointList.GetNext(pos);
		if(currentPt.x==point.x)	// a point have been found	
			{
			found=true;
			POSITION erasePos=prevPos;

			//--- compute the refresh rectangle
			minx=maxx=currentPt.x;
			miny=maxy=currentPt.y;

			// look to the left
			pos=erasePos;
			m_PointList.GetPrev(pos);
			if(NULL!=pos)
				{
				CPoint leftPoint=m_PointList.GetPrev(pos);
				if(leftPoint.x==(currentPt.x-1))	// the curve is continuous to the left
					{
					SetMinMax(leftPoint.x,minx,maxx);
					SetMinMax(leftPoint.y,miny,maxy);
					}
				}

			// look to the right
			pos=erasePos;
			m_PointList.GetNext(pos);
			if(NULL!=pos)
				{
				CPoint rightPoint=m_PointList.GetNext(pos);
				if(rightPoint.x==(currentPt.x+1))	// the curve is continuous to the right
					{
					SetMinMax(rightPoint.x,minx,maxx);
					SetMinMax(rightPoint.y,miny,maxy);
					}
				}

			//--- Erase the point
			m_PointList.RemoveAt(erasePos);
			}
		
		}
	SetModifiedFlag(TRUE);
	return CRect(minx,miny,maxx+1,maxy+1);
}

CRect CContinuousCurve::EraseLine(CPoint ptA,CPoint ptB)
{
	int minx=0;
	int miny=0;
	int maxx=0;
	int maxy=0;

	if(ptA.x>ptB.x)
		{
		CPoint temp=ptA;
		ptA=ptB;
		ptB=temp;
		}

	POSITION pos=m_PointList.GetHeadPosition();
	POSITION firstPos;
	CPoint currentPoint;
	bool found=false;

	// first, get the first element to remove
	while( (NULL!=pos)&&(!found) )
		{
		firstPos=pos;
		currentPoint=m_PointList.GetNext(pos);
		if(currentPoint.x>=ptA.x)
			{
			if(currentPoint.x<=ptB.x)
				{
				found=true;
				minx=maxx=currentPoint.x;
				miny=maxy=currentPoint.y;
				}
			else
				{
				pos=NULL;	// stops the process
				}
			}
		}
	
	if(found)	
		{
			// get the element to the left to compute the refresh rectangle
			pos=firstPos;
			m_PointList.GetPrev(pos);
			if(NULL!=pos)
				{
				CPoint leftPoint=m_PointList.GetPrev(pos);
				if(leftPoint.x==(ptA.x-1))	// the curve is continuous to the left
					{
					SetMinMax(leftPoint.x,minx,maxx);
					SetMinMax(leftPoint.y,miny,maxy);
					}
				}

			// erase points while computing refresh rectangle
			pos=firstPos;
			POSITION prevPos;
			while( (pos!=NULL)&&(currentPoint.x<=ptB.x) )
				{
				prevPos=pos;
				currentPoint=m_PointList.GetNext(pos);
				if(currentPoint.x<=ptB.x)
					{
					SetMinMax(currentPoint.x,minx,maxx);
					SetMinMax(currentPoint.y,miny,maxy);
					m_PointList.RemoveAt(prevPos);
					}
				}

			// get the element to the right to compute the refresh rectangle
			if(NULL!=pos)
				{
				if(currentPoint.x==(ptB.x+1))
					{
					SetMinMax(currentPoint.x,minx,maxx);
					SetMinMax(currentPoint.y,miny,maxy);
					}
				}
		}
	SetModifiedFlag(TRUE);
	return CRect(minx-1,miny-1,maxx+1,maxy+1);
}

bool CContinuousCurve::IsDashed() const
{
	return m_bDashed;
}

// Mutator to m_bDashed attribute. Returns the previous value
bool CContinuousCurve::SetDashed(bool bDashed)
{
	bool bPrevious=m_bDashed;
	m_bDashed=bDashed;
	return bPrevious;
}

// Accessor to m_nDashMaxDist attribute
int CContinuousCurve::GetDashMaxDist() const
{
	return m_nDashMaxDist;
}

// Mutator to m_nDashMaxDist. Returns the previous value
int CContinuousCurve::SetDashMaxDist(int nDist)
{
	int nPrevious=m_nDashMaxDist;
	m_nDashMaxDist=nDist;
	return nPrevious;
}

CSnailAlgorithm* CContinuousCurve::GetSnail()
{
	delete m_pSnail;	// the previous one could be not up-to-date
	CBmpManager* pBmpManag=m_pCoordSyst->GetDocument()->GetBmpManager();
	if(m_bDashed)
	{
		m_pSnail=new CDashedSnail(pBmpManag,m_BlackLevel,m_TopFollow,m_nDashMaxDist);
	}
	else
	{
		m_pSnail=new CSimpleSnail(pBmpManag,m_BlackLevel,m_TopFollow);
	}
	return m_pSnail;
}

void CContinuousCurve::Serialize(CArchive &ar)
{
	CCurve::Serialize(ar);
	if(ar.IsStoring())
	{
		ar << m_TopFollow
			<< m_HandModification
			<< (BOOL)m_bDashed
			<< m_nDashMaxDist;
		// black level
		ar << m_BlackLevel.GetR()
			<< m_BlackLevel.GetG()
			<< m_BlackLevel.GetB();
		// thickness corrector
		ar << m_pThicknessCorrector;
		// curve elements
		int nElementNb=m_pElementList.GetCount();
		ar << nElementNb;
		POSITION pos=m_pElementList.GetHeadPosition();
		while(NULL!=pos)
		{
			CCurveElement *pElement;
			pElement=m_pElementList.GetNext(pos);
			ar << pElement;
		}
	}
	else
	{
		// clear the elements before all
		RemoveAllElements();

		ar >> m_TopFollow
			>> m_HandModification;
		BOOL bDashed;	// theses fucking MFC don't handle bool
		ar	>> bDashed;
		m_bDashed=(bool)bDashed;
		ar	>> m_nDashMaxDist;
		// black level
		PLBYTE red;
		PLBYTE green;
		PLBYTE blue;
		ar >> red
			>> green
			>> blue;
		m_BlackLevel=PLPixel32(red,green,blue);
		//thickness corrector
		CObject *pThickOb=NULL;
		ar >> pThickOb;
		CAbstractThicknessCorrector *pCorrector=dynamic_cast<CAbstractThicknessCorrector*>(pThickOb);
		if(NULL!=pCorrector)
		{
			pCorrector->SetOwner(this);
			m_pThicknessCorrector=pCorrector;
		}
		// curve elements
		int nElementNb;
		ar >> nElementNb;
		CCurveElement *pLastElem=NULL;
		for(int nCounter=0;nCounter<nElementNb;nCounter++)
		{
			CObject *pElementObject=NULL;
			ar >> pElementObject;
			CCurveElement *pElement=dynamic_cast<CCurveElement*>(pElementObject);
			if(NULL!=pElement)
			{
				m_pElementList.AddTail(pElement);
				pElement->SetCurve(this);
				pElement->SetLeftElement(pLastElem);
				if(NULL!=pLastElem)
				{
					pLastElem->SetRightElement(pElement);
				}
				pLastElem=pElement;
			}
		}
	}
}

// called by the destructor and before the serialization (extracting)
void CContinuousCurve::RemoveAllElements()
{
	POSITION pos=m_pElementList.GetHeadPosition();
	CCurveElement* pElement;
	while(pos!=NULL)
		{
		pElement=m_pElementList.GetNext(pos);
		delete pElement;
		}
	m_pElementList.RemoveAll();
	delete m_pThicknessCorrector;
	m_pThicknessCorrector=NULL;
	delete m_pSnail;
	m_pSnail=NULL;
}

CCurve* CContinuousCurve::Clone() const
{
	CContinuousCurve *pClone=new CContinuousCurve();

	pClone->operator =(*this);

	return pClone;
}

CResults* CContinuousCurve::GetResults()
{
	if(NULL==m_pResults)
	{
		m_pResults=new CContinuousResults(this);
	}
	return m_pResults;
}
