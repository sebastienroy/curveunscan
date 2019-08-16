// Results.h: interface for the CResults class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESULTS_H__9726C6E3_692E_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_RESULTS_H__9726C6E3_692E_11D4_935E_0080C7A4F675__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include <list>
using namespace std;
#include "LogicPoint.h"

class CCurve;
class CUnscanDoc;

class CResults : public CObject  
{
	// constructors / destructors
public:
	CResults(CCurve* pCurve);
	CResults();
	virtual ~CResults();

public:
	CResults& operator =(const CResults &other);
	virtual void Serialize(CArchive &ar);
	virtual CResults* Clone(CCurve* pCurve=NULL) const =0;
	void SetOwner(CCurve* pCurve);
	virtual void Construct();
	CCurve* GetCurve();

	// dumper interface
	CString GetBitmapName() const;
	virtual int GetLegendCount();
	virtual int GetResultCount();
	virtual void GetLegendLine(int index,list<CString>& outList);
	virtual void GetResultLine(int index,list<CString>& outList);

	// obsolescence (ya le dynamic_cast)
	virtual BOOL IsDiscreteResults() const;
	virtual BOOL IsContinuousResults() const;

protected:
	// not very smart. Should be implement deeper in the hierarchy or be more generic
	mutable CArray<CLogicPoint,CLogicPoint> m_ResultArray;
	CCurve* m_pCurve;
};

#endif // !defined(AFX_RESULTS_H__9726C6E3_692E_11D4_935E_0080C7A4F675__INCLUDED_)
