// CompleteSequence.cpp: implementation of the CCompleteSequence class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "CompleteSequence.h"
#include "UnscanDoc.h"
#include "UnscanView.h"
#include "ConstructionDialog.h"

#include <SettingsManagement/SettingsManager.h>

#include <Dm/CoordSyst.h>
#include <Dm/Curve.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCompleteSequence::CCompleteSequence()
	{

	}

CCompleteSequence::CCompleteSequence(CUnscanView *pView, CUnscanDoc *pDoc)
	:CSequence(pView,pDoc)
	{
	m_pCoordSyst=new CCoordSyst(pDoc);
	if(m_pCoordSyst!=NULL)
		{
		pDoc->AddCoordSyst(m_pCoordSyst);
		}
	}

CCompleteSequence::~CCompleteSequence()
	{

	}

BOOL CCompleteSequence::Begin()
	{
	if(m_pCoordSyst!=NULL)
		{
		m_StepArray[0]=begin;
		m_StepArray[1]=xaxe;
		m_StepArray[2]=yaxe;
		m_StepArray[3]=curvekind;
		m_StepArray[4]=end;
	
		m_CurrentStep=0;
		NextStep(1);
		return TRUE;
		}
	else
		{
		delete this;
		return FALSE;
		}
	}


void CCompleteSequence::CancelSequence(CDialog *pDialogue)
	{
	if(m_pCurve!=NULL)
		{
		m_pCoordSyst->RemoveCurve(m_pCurve);
		}
	if(m_pCoordSyst!=NULL)
		{
		m_pDoc->DeleteCoordSyst(m_pCoordSyst);
		}
	if(m_pActiveDialog!=NULL)
		{
		m_pView->CancelActiveDialog(m_pActiveDialog);
		}
	m_pView->InvalidateRgn(NULL);
	m_pView->PostMessage(WM_PAINT);

	delete this;
	}

void CCompleteSequence::EndStep()
	{
	m_pCoordSyst->SetSelected();
	m_pView->InvalidateRgn(NULL);
	m_pView->PostMessage(WM_PAINT);
	if(m_pCurve!=NULL)
		{

		m_pCurve->IncrementIDNumber();
//		m_pCurve->SetModifiedFlag(TRUE);
		bool bShouldSave=true;
		CSettingsManager *settings=CSettingsManager::GetInstance();
		if(NULL!=settings)
		{
			bShouldSave=settings->MustPromptForExport();
		}

		if( (m_pCurve->GetModifiedFlag())&&(bShouldSave) )
			{
			CDialog dlg(IDD_ASKTOSAVE_DIALOG);
			if(m_pCurve->GetModifiedFlag())
				{
				if(IDOK==dlg.DoModal())
					{
					m_pDoc->SaveCurves();
					}
				}
			}
		}
	if(m_pCoordSyst!=NULL)
		{
		m_pCoordSyst->IncrementIDNumber();
		}
	delete this;
	}
