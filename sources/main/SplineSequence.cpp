// SplineSequence.cpp: implementation of the CSplineSequence class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "SplineSequence.h"
#include "UnscanDoc.h"
#include "UnscanView.h"
#include "ConstructionDialog.h"

#include <Dm/BezierCurve.h>
#include <Dm/CoordSyst.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSplineSequence::CSplineSequence()
{

}

CSplineSequence::~CSplineSequence()
{

}

CSplineSequence::CSplineSequence(CUnscanView *pView, CUnscanDoc *pDoc, CCoordSyst *pCoord, CSplineCurve *pCurve)
:	CSequence(pView,pDoc,pCoord,pCurve)
{
	if(pCurve==NULL)
	{
		m_pCurve=new CBezierCurve(m_pCoordSyst);
		m_pCoordSyst->AddCurve(m_pCurve);
		m_bIsCurveCreation=true;
	}
	else
	{
#ifdef _DEBUG
		if(NULL==dynamic_cast<CSplineCurve*>(m_pCurve))
		{
			AfxMessageBox("Chié! Séquence spline avec\ncourbe non spline!");
		}
#endif // _DEBUG
		CSplineCurve* pBackCurve=static_cast<CSplineCurve*>(m_pCurve->Clone());
		pBackCurve->Compute();
		m_pBackCurve=pBackCurve;
		m_bIsCurveCreation=false;
	}
}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////


BOOL CSplineSequence::Begin()
{
	if( (m_pCoordSyst!=NULL)&&(m_pCurve!=NULL) )
	{
		m_StepArray[0]=begin;
		m_StepArray[1]=spline;
		m_StepArray[2]=end;
	
		m_CurrentStep=0;
		NextStep(1);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CSplineSequence::CancelSequence(CDialog *pDialogue)
{
	CancelCurveSequence(pDialogue);
}

void CSplineSequence::EndStep()
{
	EndStepCurve();
}
