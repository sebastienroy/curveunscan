// AbstractModificationTool.cpp: implementation of the CAbstractModificationTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "AbstractModificationTool.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAbstractModificationTool::CAbstractModificationTool(CContinuousCurve* pCurve)
:m_pCurve(pCurve)
{

}

CAbstractModificationTool::~CAbstractModificationTool()
{

}
