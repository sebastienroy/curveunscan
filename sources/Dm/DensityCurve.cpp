// DensityCurve.cpp: implementation of the CDensityCurve class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "CurveUnscan.h"
#include "DensityCurve.h"
#include "ColorScale.h"
#include "CoordSyst.h"
#include "UnscanDoc.h"
#include "BmpManager.h"
#include "DensityResults.h"
#include <Utilities/Tools.h>
#include <algorithm>
#include <vector>
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CDensityCurve,CObject,1)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDensityCurve::CDensityCurve()
:	CCurve(),
	m_pPtFrom(NULL),
	m_pPtTo(NULL),
	m_pColorScale(new CColorScale)
{

}

CDensityCurve::CDensityCurve(CCoordSyst *pCoordSyst,
							 CColorScale *pColorScale/*=NULL*/,
							 CPoint *pPtFrom/*=NULL*/,
							 CPoint *pPtTo/*=NULL*/)
:	CCurve(pCoordSyst),
	m_pColorScale(pColorScale),
	m_pPtFrom(pPtFrom),
	m_pPtTo(pPtTo)
{
	if(NULL==pColorScale)
	{
		pColorScale=new CColorScale;
	}
}

CDensityCurve::~CDensityCurve()
{
	delete m_pColorScale;
	delete m_pPtFrom;
	delete m_pPtTo;
}


bool CDensityCurve::IsPositionDefined() const
{
	return ( (NULL!=m_pPtFrom)
			|| (NULL!=m_pPtTo) );
}

void CDensityCurve::SetPosition(const CPoint &ptFrom, const CPoint &ptTo)
{
	delete m_pPtFrom;
	delete m_pPtTo;
	m_pPtFrom=new CPoint(ptFrom);
	m_pPtTo=new CPoint(ptTo);

	SetModifiedFlag(TRUE);
}

CCurve* CDensityCurve::Clone() const
{
	CDensityCurve *pClone=new CDensityCurve();
	*pClone=*this;

	return pClone;
}

CDensityCurve& CDensityCurve::operator =(const CDensityCurve& other)
{
	if(&other==this)
	{
		return *this;
	}

	CCurve::operator =(other);

	delete m_pPtFrom;
	m_pPtFrom=NULL;
	if(NULL!=other.m_pPtFrom)
	{
		m_pPtFrom=new CPoint(*(other.m_pPtFrom));
	}

	delete m_pPtTo;
	m_pPtTo=NULL;
	if(NULL!=other.m_pPtTo)
	{
		m_pPtTo=new CPoint(*(other.m_pPtTo));
	}

	delete m_pColorScale;
	m_pColorScale=NULL;
	if(NULL!=other.m_pColorScale)
	{
		m_pColorScale=other.m_pColorScale->Clone();
	}

	return *this;

}

BOOL CDensityCurve::IsPresentOn(CPoint point) const
{
	if( (NULL==m_pPtFrom)
		||(NULL==m_pPtTo) )
	{
		return FALSE;
	}

	// Check bounds
	int nMinX=min(m_pPtFrom->x,m_pPtTo->x);
	int nMaxX=max(m_pPtFrom->x,m_pPtTo->x);
	int nMinY=min(m_pPtFrom->y,m_pPtTo->y);
	int nMaxY=max(m_pPtFrom->y,m_pPtTo->y);
	if( (point.x>nMaxX)
		|| (point.x<nMinX)
		|| (point.y>nMaxY)
		|| (point.y<nMinY) )
	{
		return FALSE;
	}

	// Compare the difference between the point and its projection on the segment

	CPoint ptProjection=CTools::GetProjection(*m_pPtFrom,*m_pPtTo,point);
	int nDeltaX=abs(ptProjection.x-point.x);
	int nDeltaY=abs(ptProjection.y-point.y);

	if( (nDeltaX>3)||(nDeltaY>3) )
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}	
}

BOOL CDensityCurve::Draw(CDC* pDC) const
{
	if( (NULL==m_pPtFrom)
		|| (NULL==m_pPtTo) )
	{
		return FALSE;
	}

	CPen pen(PS_SOLID,(m_Selected)?2:1,m_Color);
	CPen* oldPen=pDC->SelectObject(&pen);

	pDC->MoveTo(*m_pPtFrom);
	pDC->LineTo(*m_pPtTo);

	pDC->SelectObject(oldPen);

	return TRUE;
}

void CDensityCurve::Serialize(CArchive &ar)
{
	CCurve::Serialize(ar);

	if(ar.IsStoring())
	{
		ASSERT( (NULL!=m_pPtFrom)&&(NULL!=m_pPtTo) );

		ar << *m_pPtFrom
			<< *m_pPtTo
			<< m_pColorScale;
	}
	else
	{
		delete m_pPtFrom;
		delete m_pPtTo;
		delete m_pColorScale;
		m_pColorScale=NULL;
		CPoint ptFrom;
		CPoint ptTo;

		ar >> ptFrom
			>> ptTo
			>> m_pColorScale;

		m_pPtFrom=new CPoint(ptFrom);
		m_pPtTo=new CPoint(ptTo);
	}
}


CColorScale* CDensityCurve::GetColorScale()
{
	return m_pColorScale;
}

bool CDensityCurve::Compute()
{
	if( (NULL==m_pPtTo)
		||(NULL==m_pPtFrom)
		||(SCALE_OK!=m_pColorScale->GetCoherence()) )
	{
		return false;
	}

	// TODO : processing
	m_ValuesArray.clear();
	m_PtArray.clear();

	CBmpManager *pBmpManager=m_pCoordSyst->GetDocument()->GetBmpManager();

	CPoint ptFrom=*m_pPtFrom;
	CPoint ptTo=*m_pPtTo;

	int nDeltaX=ptTo.x - ptFrom.x;
	int nDeltaY=ptTo.y - ptFrom.y;
	double rate;

	bool bFollowX=(abs(nDeltaX) > abs(nDeltaY));
	int nDirection;
	bool bContinue=true;

	CPoint currentPoint;


	if(bFollowX)
	{
		rate=(double)nDeltaY/(double)nDeltaX;
		nDirection=(nDeltaX>0)?+1:-1;

		for(int nCounter=ptFrom.x;bContinue;nCounter+=nDirection)
		{
			int nDist=nCounter-ptFrom.x;
			int ny=ptFrom.y+(int)(nDist*rate);
			currentPoint.x=nCounter;
			currentPoint.y=ny;
			PLPixel32 color=pBmpManager->GetPixelColor(currentPoint);
			double value=m_pColorScale->GetPixelValue(color);

			m_ValuesArray.push_back(value);
			m_PtArray.push_back(currentPoint);
			bContinue=(nCounter!=ptTo.x);
		}
	}
	else
	{
		rate=(double)nDeltaX/(double)nDeltaY;
		nDirection=(nDeltaY>0)?+1:-1;

		for(int nCounter=ptFrom.y;bContinue;nCounter+=nDirection)
		{
			int nDist=nCounter-ptFrom.y;
			int nx=ptFrom.x+(int)(nDist*rate);
			currentPoint.y=nCounter;
			currentPoint.x=nx;
			PLPixel32 color=pBmpManager->GetPixelColor(currentPoint);
			double value=m_pColorScale->GetPixelValue(color);

			m_ValuesArray.push_back(value);
			m_PtArray.push_back(currentPoint);
			bContinue=(nCounter!=ptTo.y);
		}
	}
	
	return true;
}



const vector<double>& CDensityCurve::GetValueArray() const
{
	return m_ValuesArray;
}

const vector<CPoint>& CDensityCurve::GetPointArray() const
{
	return m_PtArray;
}

CPoint CDensityCurve::GetFromPoint() const
{
	return *m_pPtFrom;
}

CPoint CDensityCurve::GetToPoint() const
{
	return *m_pPtTo;
}

CResults* CDensityCurve::GetResults()
{
	if(NULL==m_pResults)
	{
		m_pResults=new CDensityResults(this);
	}
	return m_pResults;
}
