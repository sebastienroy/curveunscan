// DensitoSequence.cpp: implementation of the CDensitoSequence class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "UnscanView.h"
#include "UnscanDoc.h"
#include "ConstructionDialog.h"
#include "DensitoSequence.h"
#include <SettingsManagement/SettingsManager.h>

#include <Dm/DensityCurve.h>
#include <Dm/ColorScale.h>
#include <Dm/CoordSyst.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDensitoSequence::CDensitoSequence()
{

}

CDensitoSequence::CDensitoSequence(CUnscanView *pView, CUnscanDoc *pDoc, CCoordSyst *pCoord, CDensityCurve *pCurve/*=NULL*/)
:	CSequence(pView,pDoc,pCoord,pCurve)
{
	if(pCurve==NULL)
	{
		CSettingsManager *pSettings=CSettingsManager::GetInstance();
		CColorScale* pColorScale=new CColorScale(pSettings->GetColorScale());
		m_pCurve=new CDensityCurve(m_pCoordSyst,pColorScale);
		m_pCoordSyst->AddCurve(m_pCurve);
		m_bIsCurveCreation=true;
	}
	else
	{
#ifdef _DEBUG
		if(NULL==dynamic_cast<CDensityCurve*>(m_pCurve))
		{
			AfxMessageBox("Chié! Séquence densito avec\ncourbe non densito!");
		}
#endif // _DEBUG
		m_pBackCurve=m_pCurve->Clone();
		m_bIsCurveCreation=false;
	}
}

CDensitoSequence::~CDensitoSequence()
{

}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

BOOL CDensitoSequence::Begin()
{
	if( (m_pCoordSyst!=NULL)&&(m_pCurve!=NULL) )
	{
		m_StepArray[0]=begin;
		m_StepArray[1]=densitometry;
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

void CDensitoSequence::CancelSequence(CDialog *pDialogue)
{
	CancelCurveSequence(pDialogue);
}

void CDensitoSequence::EndStep()
{
	EndStepCurve();
}
