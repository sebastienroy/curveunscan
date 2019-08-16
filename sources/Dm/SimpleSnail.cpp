// SimpleSnail.cpp: implementation of the CSimpleSnail class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "CurveUnscan.h"
#include "SimpleSnail.h"
#include "BmpManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSimpleSnail::CSimpleSnail(CBmpManager* pBmpManager,
								const PLPixel32& blackLevel,
								bool bTopFollow)
:	CSnailAlgorithm(pBmpManager,blackLevel,bTopFollow)
{

}

CSimpleSnail::~CSimpleSnail()
{

}

//////////////////////////////////////////////////////////////////////
// Public methods
//////////////////////////////////////////////////////////////////////

bool CSimpleSnail::FindNext(CPoint &point)
{
	bool found=m_pBmpManager->FindNext(m_ptCurrent,m_BlackLevel,m_bToLeft,m_bTopFollow);
	if(found)
	{
		point=m_ptCurrent;
	}
	return found;
}

bool CSimpleSnail::Initialize(CPoint &ptInitial, bool bToLeft)
{
	m_bToLeft=bToLeft;

	m_ptCurrent=ptInitial;
	m_bIsInitialized=m_pBmpManager->FindCurve(m_ptCurrent,m_BlackLevel,m_bTopFollow);
	if(m_bIsInitialized)
	{
		ptInitial=m_ptCurrent;
	}
	return m_bIsInitialized;
}
