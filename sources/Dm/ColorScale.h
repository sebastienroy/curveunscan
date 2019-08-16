// ColorScale.h: interface for the CColorScale class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLORSCALE_H__4C3C0266_039D_4879_9AC7_2D9DDF191992__INCLUDED_)
#define AFX_COLORSCALE_H__4C3C0266_039D_4879_9AC7_2D9DDF191992__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "plpixel32.h"

	typedef enum SCALECOHERENCE
	{
		SCALE_OK=0,
		COLORS_IDENTICAL=1,
		VALUES_IDENTICAL=2
	} ScaleCoherence;

class CColorScale : public CObject
{
public:

	// construction / destruction
public:
	CColorScale(const PLPixel32 &TopColor, const PLPixel32 &bottomColor, double dTopValue, double sBottomValue);
	CColorScale(const CColorScale& other);
	CColorScale();
	virtual ~CColorScale();

	// Methods
public:
	CColorScale& operator =(const CColorScale &other);
	virtual void Serialize(CArchive &ar);
	double GetPixelValue(const PLPixel32 &color) const;
	ScaleCoherence GetCoherence() const;
	virtual CColorScale* Clone() const;

	// Accessors / mutators
public:
	double GetBottomValue() const;
	double GetTopValue() const;
	PLPixel32 GetBottomColor() const;
	PLPixel32 GetTopColor() const;
	void SetBottomValue(double dValue);
	void SetTopValue(double dValue);
	void SetBottomColor(const PLPixel32 &color);
	void SetTopColor(const PLPixel32 &color);

	// Internal methods
protected:
	void ComputeMutableValues() const;

	// Attributes
protected:
	PLPixel32 m_TopColor;
	PLPixel32 m_BottomColor;
	double m_dTopValue;
	double m_dBottomValue;
	
	// mutable values
	mutable bool m_bUpToDate;
	mutable double m_dColorNorm;
	mutable int m_nRedDist;
	mutable int m_nGreenDist;
	mutable int m_nBlueDist;
	mutable double m_dValueDifference;

protected:
DECLARE_SERIAL(CColorScale)

};

#endif // !defined(AFX_COLORSCALE_H__4C3C0266_039D_4879_9AC7_2D9DDF191992__INCLUDED_)
