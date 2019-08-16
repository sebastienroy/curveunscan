// ContinuousSequence.cpp: implementation of the CContinuousSequence class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UnscanView.h"
#include "ContinuousSequence.h"
#include "CurveUnscan.h"
#include "ConstructionDialog.h"
#include "UnscanDoc.h"

#include <SettingsManagement/SettingsManager.h>
#include <Dm/ContinuousCurve.h>
#include <Dm/CoordSyst.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CContinuousSequence::CContinuousSequence()
{

}

CContinuousSequence::~CContinuousSequence()
{

}

CContinuousSequence::CContinuousSequence(CUnscanView *pView, CUnscanDoc *pDoc, CCoordSyst *pCoord, CContinuousCurve *pCurve)
	:CSequence(pView,pDoc,pCoord,pCurve)
	{
	if(pCurve==NULL)
		{
		CSettingsManager *pSettings=CSettingsManager::GetInstance();
		m_pCurve=(CContinuousCurve*)new CContinuousCurve(pCoord,pSettings->GetContinuousCurveDefaultValues());
		if(m_pCurve!=NULL)
			{
			pCoord->AddCurve(m_pCurve);
			}
		m_bIsCurveCreation=true;
		}
	else
		{
#ifdef _DEBUG
		if(!pCurve->IsContinuousCurve())
			{
			AfxMessageBox("Chié! Séquence continue avec\ncourbe non continue!");
			}
#endif // _DEBUG
		m_pBackCurve=new CContinuousCurve(*pCurve);
		if(m_pBackCurve==NULL)
			{
			m_pCurve=NULL;
			}
		m_bIsCurveCreation=false;
		}

	}

BOOL CContinuousSequence::Begin()
	{
	if( (m_pCurve!=NULL)&&(m_pCoordSyst!=NULL) )
		{
		m_StepArray[0]=begin;
		m_StepArray[1]=limits;
		m_StepArray[2]=genesis;
		m_StepArray[3]=handmodif;
		m_StepArray[4]=end;
	
		m_CurrentStep=0;
		NextStep(1);
		return TRUE;
		}
	else
		{
		return FALSE;
		}
	}

void CContinuousSequence::CancelSequence(CDialog *pDialogue)
{
	CancelCurveSequence(pDialogue);
}

void CContinuousSequence::EndStep()
{
	EndStepCurve();
}
