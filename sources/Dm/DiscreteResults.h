// DiscreteResults.h: interface for the CDiscreteResults class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISCRETERESULTS_H__A801C2C3_6943_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_DISCRETERESULTS_H__A801C2C3_6943_11D4_935E_0080C7A4F675__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Results.h"

class CDiscreteResults : public CResults  
{
public:
	CDiscreteResults(CCurve *pCurve);
	CDiscreteResults();
	virtual ~CDiscreteResults();

public:
	virtual void Serialize(CArchive &ar);
	virtual CResults* Clone(CCurve* pCurve=NULL) const;
	BOOL IsDiscreteResults() const;
	void Construct();

protected:
DECLARE_SERIAL(CDiscreteResults)

};

#endif // !defined(AFX_DISCRETERESULTS_H__A801C2C3_6943_11D4_935E_0080C7A4F675__INCLUDED_)
