// DensityResults.cpp: implementation of the CDensityResults class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DensityResults.h"
#include "DensityCurve.h"
#include "CoordSyst.h"
#include "Axe.h"
#include "DensityResultsProcessor.h"
#include "enums.h"

#include <math.h>


IMPLEMENT_SERIAL(CDensityResults,CObject,1)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDensityResults::CDensityResults()
:	CResults(),
	m_DisplayKind(kBothDisplay),
	m_bPeriodIsDefined(false)
{

}

CDensityResults::CDensityResults(CCurve *pCurve)
:	CResults(pCurve),
	m_bPeriodIsDefined(false)
{
	CDensityCurve *pDensityCurve=static_cast<CDensityCurve*>(pCurve);

	if(pDensityCurve->IsPositionDefined())
	{
		double minX, maxX;
		GetXRange(minX,maxX);

		double minY, maxY;
		GetYRange(minY, maxY);

		if(!IsXValid())
		{
			m_DisplayKind=kYdisplay;
			m_dFirstX=minX;
			m_dFirstY=minY;
		}
		else if(!IsYValid())
		{
			m_DisplayKind=kXdisplay;
			m_dFirstX=minX;
			m_dFirstY=minY;
		}
		else
		{
			m_DisplayKind=kBothDisplay;
			m_dFirstX=minX;
			m_dFirstY=GetYfromX(minX);
		}	
	}
	else // curve not already defined (during curve clonage)
	{
		m_bPeriodIsDefined=false;
		m_dFirstX=m_dFirstY=0;
	}

}

CDensityResults::~CDensityResults()
{

}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

void CDensityResults::Serialize(CArchive &ar)
{
	CResults::Serialize(ar);

	if(ar.IsStoring())
	{
		ar << (int)m_DisplayKind
			<< (BOOL)m_bPeriodIsDefined
			<< (BOOL)m_bXPeriodIsUsed
			<< m_dXPeriod
			<< m_dYPeriod
			<< m_dFirstX
			<< m_dFirstY;


/*		ar << m_DensityValuesArray.size();
		for(int nCounter=0;nCounter<m_DensityValuesArray.size();nCounter++)
		{
			ar << m_DensityValuesArray[nCounter];
		}*/
	}
	else
	{
		m_DensityValuesArray.clear();
		int nDisplayKind;
		BOOL BperiodIsDefined;
		BOOL BxPeriodIsUsed;

		ar >> nDisplayKind
			>> BperiodIsDefined
			>> BxPeriodIsUsed
			>> m_dXPeriod
			>> m_dYPeriod
			>> m_dFirstX
			>> m_dFirstY;

		m_DisplayKind=(DensitoDisplayKind)nDisplayKind;
		m_bPeriodIsDefined=(bool)BperiodIsDefined;
		m_bXPeriodIsUsed=(bool)BxPeriodIsUsed;

/*		int nSize;
		ar >> nSize;
		for(int nCounter=0;nCounter<nSize;nCounter++)
		{
			double dValue;
			ar >> dValue;
			m_DensityValuesArray.push_back(dValue);
		}*/
	}
}

CResults* CDensityResults::Clone(CCurve *pCurve/*=NULL*/) const
{
	if(NULL==pCurve)
	{
		pCurve=m_pCurve;
	}
	CDensityResults *pClone=new CDensityResults(pCurve);

	pClone->operator =(*this);
	if(NULL!=pCurve)
	{
		pClone->m_pCurve=pCurve;
	}
	else
	{
		pClone->m_pCurve=m_pCurve;
	}

	return pClone;
}

CDensityResults& CDensityResults::operator =(const CDensityResults &other)
{
	if(&other==this)
	{
		return *this;
	}

	CResults::operator =(other);

	m_bPeriodIsDefined=other.m_bPeriodIsDefined;
	m_dFirstX=other.m_dFirstX;
	m_dFirstY=other.m_dFirstY;
	m_dXPeriod=other.m_dXPeriod;
	m_dYPeriod=other.m_dYPeriod;
	m_bXPeriodIsUsed=other.m_bXPeriodIsUsed;
	m_DisplayKind=other.m_DisplayKind;

	// TODO : arrays copy?

	return *this;
}

bool CDensityResults::IsXValid() const
{
	CDensityCurve *pCurve=static_cast<CDensityCurve*>(m_pCurve);
	CAxe *pAxe=m_pCurve->GetCoordSyst()->GetYAxe();
	bool bParallel=pAxe->IsSegmentParallal(pCurve->GetFromPoint(),pCurve->GetToPoint());
	return !bParallel;
}

bool CDensityResults::IsYValid() const 
{
	CDensityCurve *pCurve=static_cast<CDensityCurve*>(m_pCurve);
	CAxe *pAxe=m_pCurve->GetCoordSyst()->GetXAxe();
	bool bParallel=pAxe->IsSegmentParallal(pCurve->GetFromPoint(),pCurve->GetToPoint());
	return !bParallel;
}

double CDensityResults::GetXToYPeriodFactor() const
{
	if( (!IsXValid()) || (!IsYValid()) )
	{
		return 0;
	}
	double x1,x2,y1,y2;

	CDensityCurve *pCurve=static_cast<CDensityCurve*>(m_pCurve);
	CCoordSyst *pCoord=m_pCurve->GetCoordSyst();

	CPoint pt1=pCurve->GetFromPoint();
	CPoint pt2=pCurve->GetToPoint();

	CLogicPoint lPt1=pCoord->ToLogic(pt1);
	CLogicPoint lPt2=pCoord->ToLogic(pt2);

	x1=lPt1.x;
	x2=lPt2.x;
	if(pCoord->GetXAxe()->GetLogarithmic())
	{
		x1=log10(x1);
		x2=log10(x2);
	}

	y1=lPt1.y;
	y2=lPt2.y;
	if(pCoord->GetYAxe()->GetLogarithmic())
	{
		y1=log10(y1);
		y2=log10(y2);
	}

	double result=(y2-y1)/(x2-x1);
	return result;
}


double CDensityResults::GetYfromX(double x) const
{
	double a,b;
	if(!GetAxPlusBValues(a,b))	// segment is || to Y
	{
		CDensityCurve *pCurve=static_cast<CDensityCurve*>(m_pCurve);
		CPoint physPoint=pCurve->GetFromPoint();
		CLogicPoint logPoint=m_pCurve->GetCoordSyst()->ToLogic(physPoint);
		return logPoint.y;
	}
	if(m_pCurve->GetCoordSyst()->GetXAxe()->GetLogarithmic())
	{
		x=log10(x);
	}
	double y=a*x+b;
	if(m_pCurve->GetCoordSyst()->GetYAxe()->GetLogarithmic())
	{
		y=pow(y,10);
	}
	return y;
}

double CDensityResults::GetXfromY(double y) const
{
	double a,b;
	if(!GetAxPlusBValues(a,b))	// segment is || to Y
	{
		CDensityCurve *pCurve=static_cast<CDensityCurve*>(m_pCurve);
		CPoint physPoint=pCurve->GetFromPoint();
		CLogicPoint logPoint=m_pCurve->GetCoordSyst()->ToLogic(physPoint);
		return logPoint.x;
	}
	double x=(y-b)/a;
	return x;
}

// calculates the factor a and b from the segment equation y=a*x+b
bool CDensityResults::GetAxPlusBValues(double &a, double &b) const
{
	if( (!IsXValid()) || (!IsYValid()) )
	{
		return false;
	}
	a=GetXToYPeriodFactor();

	CDensityCurve *pCurve=static_cast<CDensityCurve*>(m_pCurve);
	CCoordSyst *pCoord=m_pCurve->GetCoordSyst();

	CPoint pt=pCurve->GetFromPoint();
	CLogicPoint lPt=pCoord->ToLogic(pt);

	double x=lPt.x;
	double y=lPt.y;
	if(pCoord->GetXAxe()->GetLogarithmic())
	{
		x=log10(x);
	}
	if(pCoord->GetYAxe()->GetLogarithmic())
	{
		y=log10(y);
	}

	b=y-(a*x);
	return true;
}

DensitoDisplayKind CDensityResults::GetDisplayKind() const
{
	DensitoDisplayKind result=m_DisplayKind;
	if(!IsXValid())
	{
		result=kYdisplay;
	}
	else if(!IsYValid())
	{
		result=kXdisplay;
	}
	return result;
}

void CDensityResults::SetDisplayKind(DensitoDisplayKind value)
{
	if(!IsXValid())
	{
		value=kYdisplay;
	}
	else if(!IsYValid())
	{
		value=kXdisplay;
	}
	m_DisplayKind=value;
}

void CDensityResults::GetXRange(double &dMin, double &dMax) const
{
	CDensityCurve *pCurve=static_cast<CDensityCurve*>(m_pCurve);
	CCoordSyst *pCoord=pCurve->GetCoordSyst();
	CLogicPoint lPt1=pCoord->ToLogic(pCurve->GetFromPoint());
	CLogicPoint lPt2=pCoord->ToLogic(pCurve->GetToPoint());

	dMin=(lPt1.x>lPt2.x)?lPt2.x:lPt1.x;
	dMax=(lPt1.x>lPt2.x)?lPt1.x:lPt2.x;
}

void CDensityResults::GetYRange(double &dMin, double &dMax) const
{
	CDensityCurve *pCurve=static_cast<CDensityCurve*>(m_pCurve);
	CCoordSyst *pCoord=pCurve->GetCoordSyst();
	CLogicPoint lPt1=pCoord->ToLogic(pCurve->GetFromPoint());
	CLogicPoint lPt2=pCoord->ToLogic(pCurve->GetToPoint());

	dMin=(lPt1.y>lPt2.y)?lPt2.y:lPt1.y;
	dMax=(lPt1.y>lPt2.y)?lPt1.y:lPt2.y;

}

bool CDensityResults::IsPeriodDefined() const
{
	return m_bPeriodIsDefined;
}

double CDensityResults::GetFirstX() const
{
	return m_dFirstX;
}

double CDensityResults::GetFirstY() const
{
	return m_dFirstY;
}

void CDensityResults::SetFirstX(double value)
{
	if(!IsXValid())
	{
		return;
	}
	m_dFirstX=value;
	if(IsYValid())
	{
		m_dFirstY=GetYfromX(value);
	}
}

void CDensityResults::SetFirstY(double value)
{
	if(!IsYValid())
	{
		return;
	}
	m_dFirstY=value;
	if(IsXValid())
	{
		m_dFirstX=GetXfromY(value);
	}

}

double CDensityResults::GetXPeriod() const
{
	if(IsPeriodDefined())
	{
		return m_dXPeriod;
	}
	else
	{
		return 0;
	}
}

double CDensityResults::GetYPeriod() const
{
	if(IsPeriodDefined())
	{
		return m_dYPeriod;
	}
	else
	{
		return 0;
	}

}

void CDensityResults::UndefPeriod()
{
	m_bPeriodIsDefined=false;
}

void CDensityResults::SetXPeriod(double value)
{
	if( !IsXValid() || (0==value) )
	{
		return;
	}
	m_dXPeriod=value;
	m_bPeriodIsDefined=true;
	m_bXPeriodIsUsed=true;
	if(IsYValid())
	{
		double factor=GetXToYPeriodFactor();
		m_dYPeriod=m_dXPeriod*factor;
	}
}

void CDensityResults::SetYPeriod(double value)
{
	if( !IsYValid() || (0==value) )
	{
		return;
	}
	m_dYPeriod=value;
	m_bPeriodIsDefined=true;
	m_bXPeriodIsUsed=false;
	if(IsXValid())
	{
		double factor=GetXToYPeriodFactor();
		m_dXPeriod=m_dXPeriod/factor;
	}
}

int CDensityResults::GetNbOfSavedPoints() const
{
	if(!m_bPeriodIsDefined)
	{
		return 0;
	}
	if( (kYdisplay!=m_DisplayKind)&&(m_bXPeriodIsUsed) )
	{
		return GetNbOfSavedPointsFromX();
	}
	else	
	{
		return GetNbOfSavedPointsFromY();
	}
}

int CDensityResults::GetNbOfSavedPointsFromX() const
{
	double minX,maxX;
	GetXRange(minX,maxX);
	double dFirstX=m_dFirstX;
	double dLast=(m_dXPeriod>0)?maxX:minX;
	if(m_pCurve->GetCoordSyst()->GetXAxe()->GetLogarithmic())
	{
		if(m_dFirstX<=0)
		{
			return -1;
		}
		minX=log10(minX);
		maxX=log10(maxX);
		dFirstX=log10(dFirstX);
		dLast=log10(dLast);
	}
	double dNb=abs((dFirstX-dLast)/m_dXPeriod);
	if(dNb>1000000)
	{
		return -1;
	}
	return (int)dNb+1;

}

int CDensityResults::GetNbOfSavedPointsFromY() const
{
	double minY,maxY;
	GetYRange(minY,maxY);
	double dFirstY=m_dFirstY;
	double dLast=(m_dYPeriod>0)?maxY:minY;
	if(m_pCurve->GetCoordSyst()->GetYAxe()->GetLogarithmic())
	{
		if(m_dFirstY<=0)
		{
			return -1;
		}
		minY=log10(minY);
		maxY=log10(maxY);
		dFirstY=log10(dFirstY);
		dLast=log10(dLast);
	}
	double dNb=abs((dFirstY-dLast)/m_dYPeriod);
	if(dNb>1000000)
	{
		return -1;
	}
	return (int)dNb+1;
}

bool CDensityResults::IsXPeriodUsed() const
{
	return m_bXPeriodIsUsed;
}

void CDensityResults::Construct()
{
	CDensityResultsProcessor processor(this);	// use delegation for this hard work
	processor.Build();
}


void CDensityResults::GetLegendLine(int index, list<CString> &outList)
{
	if(0==index)
	{
		outList.push_back(m_pCurve->GetName());
		outList.push_back(CString(""));
		if(kBothDisplay==m_DisplayKind)
		{
			outList.push_back(CString(""));
		}
	}
	else if(1==index)
	{
		if( (kXdisplay==m_DisplayKind)||(kBothDisplay==m_DisplayKind) )
		{
			CString strX=m_pCurve->GetCoordSyst()->GetXAxe()->GetName();
			outList.push_back(strX);
		}
		if( (kYdisplay==m_DisplayKind)||(kBothDisplay==m_DisplayKind) )
		{
			CString strY=m_pCurve->GetCoordSyst()->GetYAxe()->GetName();
			outList.push_back(strY);
		}
		// value TODO
		outList.push_back(CString(""));
	}
	else	// empty line
	{
		outList.push_back(CString(""));
		outList.push_back(CString(""));
		if(kBothDisplay==m_DisplayKind)
		{
			outList.push_back(CString(""));
		}
	}

}

int CDensityResults::GetResultCount()
{
	return m_PointsArray.size();
}

void CDensityResults::GetResultLine(int nIndex, list<CString> &outList)
{
	if( (nIndex<0)||(nIndex>=m_PointsArray.size()) )
	{
		outList.push_back(CString(""));
		outList.push_back(CString(""));
		if(kBothDisplay==m_DisplayKind)
		{
			outList.push_back(CString(""));
		}
		return;
	}

	// X
	if( (kXdisplay==m_DisplayKind)||(kBothDisplay==m_DisplayKind) )
	{
		CString strX;
		strX.Format("%g",m_PointsArray[nIndex].x);
		outList.push_back(strX);
	}
	// Y
	if( (kYdisplay==m_DisplayKind)||(kBothDisplay==m_DisplayKind) )
	{
		CString strY;
		strY.Format("%g",m_PointsArray[nIndex].y);
		outList.push_back(strY);
	}
	// value
	CString strValue;
	strValue.Format("%g",m_DensityValuesArray[nIndex]);
	outList.push_back(strValue);

}
