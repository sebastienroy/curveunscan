// DensityResults.h: interface for the CDensityResults class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DENSITYRESULTS_H__ED05D4A1_429E_4B7D_A472_7A3D13FC9122__INCLUDED_)
#define AFX_DENSITYRESULTS_H__ED05D4A1_429E_4B7D_A472_7A3D13FC9122__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Results.h"

class CCurve;
class CDensityResultsProcessor;

#include <vector>
using namespace std;

typedef enum DENSITODISPLAYKIND
{
	kXdisplay=0,
	kYdisplay=1,
	kBothDisplay=2
}	DensitoDisplayKind;

class CDensityResults : public CResults  
{
friend class CDensityResultsProcessor;

	// constructor / denstructor
public:
	CDensityResults(CCurve *pCurve);
	CDensityResults();
	virtual ~CDensityResults();

	// CResults interface implementation
public:
	virtual void Construct();
	virtual CResults* Clone(CCurve *pCurve=NULL) const;
	virtual void Serialize(CArchive &ar);

	// specific interface
public:
	bool IsXPeriodUsed() const;
	int GetNbOfSavedPoints() const;
	void SetYPeriod(double value);
	void SetXPeriod(double value);
	void UndefPeriod();
	double GetYPeriod() const;
	double GetXPeriod() const;
	void SetFirstY(double value);
	void SetFirstX(double value);
	double GetFirstY() const;
	double GetFirstX() const;
	bool IsPeriodDefined() const;
	void GetYRange(double &dMin,double &dMax) const;
	void GetXRange(double &dMin, double &dMax) const;
	void SetDisplayKind(DensitoDisplayKind value);
	DensitoDisplayKind GetDisplayKind() const;
	double GetXfromY(double y) const;
	double GetYfromX(double x) const;
	CDensityResults& operator =(const CDensityResults &other);
	double GetXToYPeriodFactor() const;
	bool IsYValid() const;
	bool IsXValid() const;

	// dumper interface
public:
	virtual void GetResultLine(int nIndex,list<CString>& outList);
	virtual int GetResultCount();
	virtual void GetLegendLine(int index, list<CString> &outList);


	// implementation
protected:
	bool GetAxPlusBValues(double &a,double &b) const;
	int GetNbOfSavedPointsFromY() const;
	int GetNbOfSavedPointsFromX() const;

protected:
	DensitoDisplayKind m_DisplayKind;
	vector<double>	m_DensityValuesArray;
	vector<CLogicPoint> m_PointsArray;
	double m_dFirstY;
	double m_dFirstX;
	bool m_bPeriodIsDefined;
	bool m_bXPeriodIsUsed;
	double m_dYPeriod;
	double m_dXPeriod;

DECLARE_SERIAL(CDensityResults)

};

#endif // !defined(AFX_DENSITYRESULTS_H__ED05D4A1_429E_4B7D_A472_7A3D13FC9122__INCLUDED_)
