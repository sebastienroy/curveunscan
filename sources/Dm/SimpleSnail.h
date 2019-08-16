// SimpleSnail.h: interface for the CSimpleSnail class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPLESNAIL_H__6B2AC4B5_CD8F_4917_AD62_2CABA7824DF5__INCLUDED_)
#define AFX_SIMPLESNAIL_H__6B2AC4B5_CD8F_4917_AD62_2CABA7824DF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SnailAlgorithm.h"

class CSimpleSnail : public CSnailAlgorithm  
{

protected:
	friend class CContinuousCurve;
	CSimpleSnail(CBmpManager* pBmpManager,
					const PLPixel32& blackLevel,
					bool bTopFollow);
public:
	virtual bool Initialize(CPoint& ptInitial, bool bToLeft);
	virtual bool FindNext(CPoint& point);
	virtual ~CSimpleSnail();

protected:
	CPoint m_ptCurrent;


};

#endif // !defined(AFX_SIMPLESNAIL_H__6B2AC4B5_CD8F_4917_AD62_2CABA7824DF5__INCLUDED_)
