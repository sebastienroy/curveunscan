// SnailAlgorithm.h: interface for the CSnailAlgorithm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNAILALGORITHM_H__4739C103_A6D3_4822_8BD2_4B5D9738866D__INCLUDED_)
#define AFX_SNAILALGORITHM_H__4739C103_A6D3_4822_8BD2_4B5D9738866D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <plpixel32.h>

class CBmpManager;
class CContinuousCurve;

class CSnailAlgorithm  
{
	// Constructors / destructors
protected:
	friend class CContinuousCurve;
	CSnailAlgorithm(CBmpManager* pBmpManager,
					const PLPixel32& blackLevel,
					bool bTopFollow);
public:
	virtual ~CSnailAlgorithm();

	// Public methods
	virtual bool FindNext(CPoint& point) =0;
	virtual bool Initialize(CPoint& ptInitial, bool bToLeft);

protected:

	// current following job members
	bool m_bToLeft;
	bool m_bIsInitialized;

	// constant members
	const bool m_bTopFollow;
	const PLPixel32 m_BlackLevel;
	const CBmpManager* m_pBmpManager;
};

#endif // !defined(AFX_SNAILALGORITHM_H__4739C103_A6D3_4822_8BD2_4B5D9738866D__INCLUDED_)
