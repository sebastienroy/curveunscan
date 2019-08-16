// SnailAlgorithm.cpp: implementation of the CSnailAlgorithm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "CurveUnscan.h"
#include "BmpManager.h"
#include "SnailAlgorithm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSnailAlgorithm::CSnailAlgorithm(CBmpManager* pBmpManager,
								const PLPixel32& blackLevel,
								bool bTopFollow)
:	m_pBmpManager(pBmpManager),
	m_BlackLevel(blackLevel),
	m_bTopFollow(bTopFollow),
	m_bToLeft(true),
	m_bIsInitialized(false)	// members that will be initialized by Initialize() method
{

}

CSnailAlgorithm::~CSnailAlgorithm()
{

}

//////////////////////////////////////////////////////////////////////
// Public Methods
//////////////////////////////////////////////////////////////////////

bool CSnailAlgorithm::Initialize(CPoint &ptInitial, bool bToLeft)
{
	ASSERT(FALSE);	// the inherited methods must be called, not the base one
	return false;
}



