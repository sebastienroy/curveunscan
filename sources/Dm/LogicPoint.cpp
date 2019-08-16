// LogicPoint.cpp: implementation of the CLogicPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "CurveUnscan.h"
#include "LogicPoint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogicPoint::CLogicPoint()
	{
	x=y=0;
	m_Defined=TRUE;
	}

CLogicPoint::CLogicPoint(double a, double b)
	{
	x=a;
	y=b;
	m_Defined=TRUE;
	}

CLogicPoint::~CLogicPoint()
	{

	}

CLogicPoint::CLogicPoint(const CLogicPoint &otherPoint)
	{
	*this=otherPoint;
	}

CLogicPoint& CLogicPoint::operator =(const CLogicPoint &otherPoint)
	{
	if(&otherPoint==this)
		{
		return *this;
		}
	x=otherPoint.x;
	y=otherPoint.y;
	m_Defined=otherPoint.m_Defined;
	return *this;	
	}

BOOL CLogicPoint::IsDefined()
	{
	return m_Defined;
	}

BOOL CLogicPoint::SetDefined(BOOL value)
	{
	BOOL oldValue=m_Defined;
	m_Defined=value;
	return oldValue;
	}
