// DiscreteSequence.cpp: implementation of the CDiscreteSequence class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "UnscanView.h"
#include "DiscreteSequence.h"
#include "ConstructionDialog.h"
#include "UnscanDoc.h"

#include <SettingsManagement/SettingsManager.h>
#include <Dm/DiscreteCurve.h>
#include <Dm/CoordSyst.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDiscreteSequence::CDiscreteSequence(CUnscanView *pView, CUnscanDoc *pDoc, CCoordSyst *pCoord, CDiscreteCurve *pCurve)
	:CSequence(pView,pDoc,pCoord,pCurve)
	{
	if(pCurve==NULL)
		{
		m_pCurve=new CDiscreteCurve(pCoord);
		if(m_pCurve!=NULL)
			{
			pCoord->AddCurve(m_pCurve);
			}
		m_bIsCurveCreation=true;
		}
	else
		{
#ifdef _DEBUG
		if(!pCurve->IsDiscreteCurve())
			{
			AfxMessageBox("Chié! Séquence discrète avec\ncourbe non discrete!");
			}
#endif // _DEBUG
		m_pBackCurve=new CDiscreteCurve(*pCurve);
		if(m_pBackCurve==NULL)
			{
			m_pCurve=NULL;
			}
		m_bIsCurveCreation=false;
		}
	}

CDiscreteSequence::CDiscreteSequence()
{

}

CDiscreteSequence::~CDiscreteSequence()
{

}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BOOL CDiscreteSequence::Begin()
	{
	if( (m_pCoordSyst!=NULL)&&(m_pCurve!=NULL) )
		{
		m_StepArray[0]=begin;
		m_StepArray[1]=discrete;
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

void CDiscreteSequence::EndStep()
{
	EndStepCurve();
}


void CDiscreteSequence::CancelSequence(CDialog *pDialogue)
{
	CancelCurveSequence(pDialogue);
}
