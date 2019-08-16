// Axe.h: interface for the CAxe class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AXE_H__AB02B000_454F_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_AXE_H__AB02B000_454F_11D4_935E_0080C7A4F675__INCLUDED_

#include "ScalePoint.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCoordSyst;

class CAxe : public CObject  
{
DECLARE_SERIAL(CAxe)

friend class CCoordSyst;
public:
	bool IsSegmentParallal(CPoint pt1,CPoint pt2) const;
	virtual void Serialize(CArchive &ar);
	CAxe();
	CAxe(CAxe& other);
	CAxe& operator =(const CAxe &other);
	BOOL Draw(CDC* pDC) const;
	virtual ~CAxe();
	inline void SetCoordSyst(CCoordSyst* pCoord);
	inline BOOL ScaleDefined();
	void SetPosition(CPoint from,CPoint to);
	inline CCoordSyst* GetCoordSyst() const;
	inline BOOL GetLogarithmic() const;
	BOOL SetLogarithmic(BOOL toto);
	inline BOOL IsDefined() const;
	inline CScalePoint* GetScalePoint(int n);
	inline CPoint GetTo() const;
	inline CPoint GetFrom() const;
	inline CString GetName() const;
	inline void SetName(CString &name);
	inline double GetAngle() const;

protected: 
	double Actualize();

protected:
	// link
	CCoordSyst* m_pCoordSyst;
	// attributes
	CScalePoint m_ScalePoint2;
	CScalePoint m_ScalePoint1;
	BOOL m_Logarithmic;
	CString m_AxeName;
	CPoint m_To;
	CPoint m_From;
	// derivated attributes (computed into Actualize() method)
	mutable BOOL m_Defined;
	mutable double m_Angle;
};

// renvoie l'angle de l'axe p/r a l'horizontale en gradians
double CAxe::GetAngle() const
	{
	return m_Angle;
	}

void CAxe::SetName(CString &name)
	{
	m_AxeName=name;
	}

CString CAxe::GetName() const
	{
	return m_AxeName;
	}

CPoint CAxe::GetFrom() const
	{
	return m_From;
	}

CPoint CAxe::GetTo() const
	{
	return m_To;
	}

BOOL CAxe::IsDefined() const
	{
	return m_Defined;
	}

BOOL CAxe::GetLogarithmic() const
	{
	return m_Logarithmic;
	}

void CAxe::SetCoordSyst(CCoordSyst *pCoord)
	{
	m_pCoordSyst=pCoord;
	}

CCoordSyst* CAxe::GetCoordSyst() const
	{
	return m_pCoordSyst;
	}

CScalePoint* CAxe::GetScalePoint(int n)
	{
	if(n==1)
		{
		return &m_ScalePoint1;
		}
	else
		{
		return &m_ScalePoint2;
		}
	}

BOOL CAxe::ScaleDefined()
	{
	return ( (m_ScalePoint1.IsDefined())&&(m_ScalePoint2.IsDefined()) );
	}



#endif // !defined(AFX_AXE_H__AB02B000_454F_11D4_935E_0080C7A4F675__INCLUDED_)
