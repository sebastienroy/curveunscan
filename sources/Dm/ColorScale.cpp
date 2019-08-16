// ColorScale.cpp: implementation of the CColorScale class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "CurveUnscan.h"
#include "ColorScale.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include <math.h>

IMPLEMENT_SERIAL(CColorScale,CObject,1)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CColorScale::CColorScale()
:	m_TopColor(0,0,0),
	m_BottomColor(255,255,255),
	m_dTopValue(100),
	m_dBottomValue(0),
	m_bUpToDate(false)
{

}

CColorScale::CColorScale(const PLPixel32 &topColor, const PLPixel32 &bottomColor, double dTopValue, double dBottomValue)
:	m_TopColor(topColor),
	m_BottomColor(bottomColor),
	m_dTopValue(dTopValue),
	m_dBottomValue(dBottomValue),
	m_bUpToDate(false)
{

}

CColorScale::CColorScale(const CColorScale& other)
:	m_TopColor(other.m_TopColor),
	m_BottomColor(other.m_BottomColor),
	m_dTopValue(other.m_dTopValue),
	m_dBottomValue(other.m_dBottomValue),
	m_bUpToDate(false)
{
}

CColorScale::~CColorScale()
{

}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

CColorScale* CColorScale::Clone() const
{
	return new CColorScale(m_TopColor,m_BottomColor,m_dTopValue,m_dBottomValue);
}


ScaleCoherence CColorScale::GetCoherence() const
{
	if((m_TopColor.GetR()==m_BottomColor.GetR())
		&&(m_TopColor.GetG()==m_BottomColor.GetG())
		&&(m_TopColor.GetB()==m_BottomColor.GetB()) )
	{
		return COLORS_IDENTICAL;
	}
	else if(m_dTopValue==m_dBottomValue)
	{
		return VALUES_IDENTICAL;
	}
	else
	{
		return SCALE_OK;
	}
}

void CColorScale::SetTopColor(const PLPixel32 &color)
{
	m_TopColor=color;
	m_bUpToDate=false;
}

void CColorScale::SetBottomColor(const PLPixel32 &color)
{
	m_BottomColor=color;
	m_bUpToDate=false;
}

void CColorScale::SetTopValue(double dValue)
{
	m_dTopValue=dValue;
	m_bUpToDate=false;
}

void CColorScale::SetBottomValue(double dValue)
{
	m_dBottomValue=dValue;
	m_bUpToDate=false;
}

PLPixel32 CColorScale::GetTopColor() const
{
	return m_TopColor;
}

PLPixel32 CColorScale::GetBottomColor() const
{
	return m_BottomColor;
}

double CColorScale::GetTopValue() const
{
	return m_dTopValue;
}

double CColorScale::GetBottomValue() const
{
	return m_dBottomValue;
}

double CColorScale::GetPixelValue(const PLPixel32 &color) const
{
	if(!m_bUpToDate)
	{
		ComputeMutableValues();
	}

	if(0==m_dColorNorm)
	{
		return 0;
	}

	int nRelRed=(int)color.GetR()-(int)m_BottomColor.GetR();
	int nRelGreen=(int)color.GetG()-(int)m_BottomColor.GetG();
	int nRelBlue=(int)color.GetB()-(int)m_BottomColor.GetB();

	double dScalar=(double)(nRelRed*m_nRedDist+nRelGreen*m_nGreenDist+nRelBlue*m_nBlueDist);

	double dRelDist=dScalar/m_dColorNorm;
	double result=m_dBottomValue+(m_dValueDifference*dRelDist);

	return result;
}



void CColorScale::ComputeMutableValues() const
{
	m_nRedDist=(int)m_TopColor.GetR()-(int)m_BottomColor.GetR();
	m_nGreenDist=(int)m_TopColor.GetG()-(int)m_BottomColor.GetG();
	m_nBlueDist=(int)m_TopColor.GetB()-(int)m_BottomColor.GetB();
	m_dColorNorm=m_nRedDist*m_nRedDist+m_nGreenDist*m_nGreenDist+m_nBlueDist*m_nBlueDist;
	m_dValueDifference=m_dTopValue-m_dBottomValue;
	m_bUpToDate=true;
}

void CColorScale::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);

	if(ar.IsStoring())
	{
		ar << m_dTopValue
			<< m_dBottomValue
			<< m_TopColor.GetR()
			<< m_TopColor.GetG()
			<< m_TopColor.GetB()
			<< m_BottomColor.GetR()
			<< m_BottomColor.GetG()
			<< m_BottomColor.GetB();
	}
	else
	{
		PLBYTE topR,topG,topB,bottomR,bottomG,bottomB;

		ar >> m_dTopValue
			>> m_dBottomValue
			>> topR
			>> topG
			>> topB
			>> bottomR
			>> bottomG
			>> bottomB;

		m_TopColor=PLPixel32(topR,topG,topB);
		m_BottomColor=PLPixel32(bottomR,bottomG,bottomB);
		m_bUpToDate=false;
	}
}

CColorScale& CColorScale::operator =(const CColorScale &other)
{
	if(&other==this)
	{
		return *this;
	}

	m_TopColor=other.m_TopColor;
	m_BottomColor=other.m_BottomColor;
	m_dTopValue=other.m_dTopValue;
	m_dBottomValue=other.m_dBottomValue;
	m_bUpToDate=false;
	
	return *this;
}

