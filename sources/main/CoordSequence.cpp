// CoordSequence.cpp: implementation of the CCoordSequence class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CoordSequence.h"
#include "CurveUnscan.h"
#include "UnscanDoc.h"
#include "UnscanView.h"
#include "ConstructionDialog.h"

#include <Dm/CoordSyst.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCoordSequence::CCoordSequence()
	{

	}

CCoordSequence::~CCoordSequence()
{

}

CCoordSequence::CCoordSequence(CUnscanView *pView, CUnscanDoc *pDoc, CCoordSyst *pCoord)
	:CSequence(pView,pDoc,pCoord)
	{
	if(pCoord==NULL)
		{
		m_pCoordSyst=new CCoordSyst(pDoc);
		pDoc->AddCoordSyst(m_pCoordSyst);
		}
	else
		{
		m_pBackCoordSyst=new CCoordSyst(*pCoord);
		if(m_pBackCoordSyst==NULL)
			{
			m_pCoordSyst=NULL;
			}
		}

	}

BOOL CCoordSequence::Begin()
	{
	if(m_pCoordSyst!=NULL)
		{
		m_StepArray[0]=begin;
		m_StepArray[1]=xaxe;
		m_StepArray[2]=yaxe;
		m_StepArray[3]=end;
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

void CCoordSequence::EndStep()
	{
	if(m_pBackCoordSyst!=NULL)
		{
		delete m_pBackCoordSyst;
		}
	if(m_pCoordSyst!=NULL)
		{
		m_pCoordSyst->IncrementIDNumber();
		}
	m_pDoc->UnselectAll();
	m_pCoordSyst->SetSelected();
	m_pView->InvalidateRgn(NULL);
	m_pView->PostMessage(WM_PAINT);
	delete this;
	}

void CCoordSequence::CancelSequence(CDialog *pDialogue)
	{
#ifdef _DEBUG
	if((m_pActiveDialog==NULL)||(m_pActiveDialog!=pDialogue))
		{
		AfxMessageBox("Putain! Un dialogue veut en virer un\nautre dans la sequence");
		}
#endif //_DEBUG
	if(m_pCoordSyst!=NULL)
		{
		m_pDoc->DeleteCoordSyst(m_pCoordSyst);
		}
	if(m_pBackCoordSyst!=NULL)
		{
		m_pDoc->AddCoordSyst(m_pBackCoordSyst);
		m_pBackCoordSyst=NULL;
		}
	if(m_pActiveDialog!=NULL)
		{
		m_pView->CancelActiveDialog(m_pActiveDialog);
		}
	m_pView->InvalidateRgn(NULL);
	m_pView->PostMessage(WM_PAINT);
	delete this;

	}
