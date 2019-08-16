// LogicPoint.h: interface for the CLogicPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGICPOINT_H__1FB72A48_4607_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_LOGICPOINT_H__1FB72A48_4607_11D4_935E_0080C7A4F675__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLogicPoint  
{
public:
	BOOL SetDefined(BOOL value=TRUE);
	BOOL IsDefined();
	CLogicPoint(double a,double b);
	CLogicPoint(const CLogicPoint &otherPoint);
	CLogicPoint& operator =(const CLogicPoint &otherPoint);
	double y;
	double x;
	CLogicPoint();
	virtual ~CLogicPoint();

private:
	BOOL m_Defined;
};

#endif // !defined(AFX_LOGICPOINT_H__1FB72A48_4607_11D4_935E_0080C7A4F675__INCLUDED_)
