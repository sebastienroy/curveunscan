// Sequence.cpp: implementation of the CSequence class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "Sequence.h"
#include "UnscanView.h"
#include "UnscanDoc.h"
#include "ConstructionDialog.h"
#include "AxeDialog.h"
#include "CurveKindDialog.h"
#include "DiscreteDialog.h"
#include "LimitDialog.h"
#include "GenesisDialog.h"
#include "HandModificationDialog.h"
#include "DensitometryDialog.h"
#include "SplineDialog.h"

#include <Dm/CoordSyst.h>
#include <Dm/Curve.h>
#include <Dm/ContinuousCurve.h>
#include <Dm/BezierCurve.h>
#include <Dm/DiscreteCurve.h>
#include <Dm/DensityCurve.h>
#include <Dm/Colorscale.h>
#include <Dm/BmpManager.h>

#include <SettingsManagement/SettingsManager.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSequence::CSequence()
	{
	m_CurrentStep=0;
	m_pActiveDialog=NULL;
	m_pCurve=NULL;
	m_bIsCurveCreation=false;
	}

CSequence::CSequence(CUnscanView *pView, CUnscanDoc *pDoc, CCoordSyst *pCoord,CCurve* pCurve)
	{
	m_StepArray.SetSize(64);
	m_pView=pView;
	m_pDoc=pDoc;
	m_pCoordSyst=pCoord;
	m_bIsCurveCreation=false;
	m_pBackCoordSyst=NULL;
	m_pCurve=pCurve;
	m_pBackCurve=NULL;
	m_CurrentStep=0;
	m_pActiveDialog=NULL;
	CRect rect;
	CPoint point;
	pView->GetWindowRect(&rect);
	point=rect.TopLeft();
	point.x+=10;
	point.y+=10;
	m_WindowPosition=point;
	pDoc->UnselectAll();
	pView->InvalidateRgn(NULL);
	pView->PostMessage(WM_PAINT);
	}

CSequence::~CSequence()
	{
	m_pView->EndSequence();
	}

void CSequence::NextStep(int next)
	{
	if(m_pActiveDialog!=NULL)
		{
		m_pView->CancelActiveDialog(m_pActiveDialog);
		}
	m_CurrentStep+=next;
	STEP actualStep=m_StepArray[m_CurrentStep];
	switch (actualStep)
		{
		case openbitmap:
			OpenBitmapStep();
			break;
		case xaxe:
			XAxisStep();
			break;
		case yaxe:
			YAxisStep();
			break;
		case curvekind:
			CurveKindStep();
			break;
		case discrete:
			DiscreteStep();
			break;
		case limits:
			LimitsStep();
			break;
		case genesis:
			GenesisStep();
			break;
		case handmodif:
			HandModificationStep();
			break;
		case densitometry:
			DensitometryStep();
			break;
		case spline:
			SplineStep();
			break;
		case end:
			EndStep();
			break;
		default:;
#ifdef _DEBUG
			CString str;
			str.Format("%d",actualStep);
			str=CString("Erreur : Séquence : case default appelé\n step No ")+str;
			AfxMessageBox(str);
#endif //_DEBUG
		}
	}

void CSequence::CancelSequence(CDialog* pDialogue)
	{

	}


BOOL CSequence::Begin()
	{	
#ifdef _DEBUG
	AfxMessageBox("Erreur : appel de la fc Begin de base");
#endif //_DEBUG
	return FALSE;
	}

void CSequence::OpenBitmapStep()
{
	m_pDoc->InitialOpenBitmap();
	if((m_pDoc->GetBmpManager())->IsBmpOpened())
		{
		NextStep(+1);
		}
	else
		{
		CancelSequence(NULL);
		}
}


void CSequence::XAxisStep()
	{
	m_pActiveDialog=new CAxeDialog(IDD_AXE_X,m_pView,this,
		m_pCoordSyst->GetXAxe(),m_pCoordSyst->GetYAxe());
	m_pActiveDialog->Create(IDD_AXE_X,m_pView);
	UpdateOKPrevious(m_pActiveDialog);
	}


void CSequence::YAxisStep()
{
	m_pActiveDialog=new CAxeDialog(IDD_AXE_Y,m_pView,this,
		m_pCoordSyst->GetYAxe(),m_pCoordSyst->GetXAxe());
	m_pActiveDialog->Create(IDD_AXE_Y,m_pView);
	UpdateOKPrevious(m_pActiveDialog);

}

void CSequence::CurveKindStep()
{
	m_pActiveDialog=NULL;
	CCurveKindDialog kindDialog(this);
	if(m_StepArray[4]==discrete)
	{
		kindDialog.m_Kind=1;
	}
	if(kindDialog.DoModal()==IDOK)
	{
		if(kindDialog.m_Next==+1)	// "Next"
		{
			if(kindDialog.m_Kind==0)	// Continuous curve
			{
				CSettingsManager *pSettings=CSettingsManager::GetInstance();
				if(m_pCurve==NULL)
				{
					m_pCurve=new CContinuousCurve(m_pCoordSyst,pSettings->GetContinuousCurveDefaultValues());
					m_pCoordSyst->AddCurve(m_pCurve);
				}
				if(!m_pCurve->IsContinuousCurve())
				{
					m_pCoordSyst->RemoveCurve(m_pCurve);
					m_pCurve=new CContinuousCurve(m_pCoordSyst,pSettings->GetContinuousCurveDefaultValues());
					m_pCoordSyst->AddCurve(m_pCurve);
					m_pView->InvalidateRgn(NULL);
					m_pView->PostMessage(WM_PAINT);
				}
				m_StepArray[4]=limits;
				m_StepArray[5]=genesis;
				m_StepArray[6]=handmodif;
				m_StepArray[7]=end;
			}
			else if(1==kindDialog.m_Kind)	// spline curve
			{
				if((NULL!=m_pCurve)&&(NULL==dynamic_cast<CSplineCurve*>(m_pCurve)))
				{
					m_pCoordSyst->RemoveCurve(m_pCurve);
					m_pCurve=NULL;
				}
				if(m_pCurve==NULL)
				{
					m_pCurve=new CBezierCurve(m_pCoordSyst);
					m_pCoordSyst->AddCurve(m_pCurve);
				}
				m_StepArray[4]=spline;
				m_StepArray[5]=end;
			}
			else if(2==kindDialog.m_Kind)					// Discrete curve
			{
				if(m_pCurve==NULL)
				{
					m_pCurve=new CDiscreteCurve(m_pCoordSyst);
					m_pCoordSyst->AddCurve(m_pCurve);
				}
				if(!m_pCurve->IsDiscreteCurve())
				{
					m_pCoordSyst->RemoveCurve(m_pCurve);
					m_pCurve=new CDiscreteCurve(m_pCoordSyst);
					m_pCoordSyst->AddCurve(m_pCurve);
					m_pView->InvalidateRgn(NULL);
					m_pView->PostMessage(WM_PAINT);
				}
				m_StepArray[4]=discrete;
				m_StepArray[5]=end;
			}
			else if(3==kindDialog.m_Kind)	// densitometry
			{
				if((NULL!=m_pCurve)&&(NULL==dynamic_cast<CDensityCurve*>(m_pCurve)))
				{
					m_pCoordSyst->RemoveCurve(m_pCurve);
					m_pCurve=NULL;
				}
				if(NULL==m_pCurve)
				{
					CSettingsManager *pSettings=CSettingsManager::GetInstance();
					CColorScale* pColorScale=new CColorScale(pSettings->GetColorScale());
					m_pCurve=new CDensityCurve(m_pCoordSyst,pColorScale);
					m_pCoordSyst->AddCurve(m_pCurve);
				}
				m_StepArray[4]=densitometry;
				m_StepArray[5]=end;				
			}

			NextStep(+1);
		}
		else						// "Previous"
		{
			NextStep(-1);
		}
	}
	else							// "Cancel"
	{
		CancelSequence(NULL);
	}
}

void CSequence::DiscreteStep()
{
	m_pActiveDialog=new CDiscreteDialog(IDD_DISCRETE_DIALOG,m_pView,this,
		(CDiscreteCurve*)m_pCurve);
	m_pActiveDialog->Create(IDD_DISCRETE_DIALOG,m_pView);
	UpdateOKPrevious(m_pActiveDialog);
}

void CSequence::LimitsStep()
{
	m_pActiveDialog=new CLimitDialog(IDD_CURVELIMITS_DIALOG,m_pView,this,
		(CContinuousCurve*)m_pCurve);
	m_pActiveDialog->Create(IDD_CURVELIMITS_DIALOG,m_pView);
	UpdateOKPrevious(m_pActiveDialog);
}

void CSequence::GenesisStep()
{
	m_pActiveDialog=new CGenesisDialog(IDD_CONTINUOUS_DIALOG,m_pView,this,
		(CContinuousCurve*)m_pCurve);
	m_pActiveDialog->Create(IDD_CONTINUOUS_DIALOG,m_pView);
	UpdateOKPrevious(m_pActiveDialog);
}

void CSequence::HandModificationStep()
{
	m_pActiveDialog=new CHandModificationDialog(IDD_HAND_DIALOG,m_pView,this,
		(CContinuousCurve*)m_pCurve);
	m_pActiveDialog->Create(IDD_HAND_DIALOG,m_pView);
	UpdateOKPrevious(m_pActiveDialog);
}

void CSequence::DensitometryStep()
{
	CDensityCurve *pCurve=dynamic_cast<CDensityCurve*>(m_pCurve);
	m_pActiveDialog=new CDensitometryDialog(IDD_DENSITO_DIALOG,m_pView,this,pCurve);
	m_pActiveDialog->Create(IDD_DENSITO_DIALOG,m_pView);
	UpdateOKPrevious(m_pActiveDialog);
}

void CSequence::SplineStep()
{
	CSplineCurve *pCurve=dynamic_cast<CSplineCurve*>(m_pCurve);
	m_pActiveDialog=new CSplineDialog(IDD_SPLINE_DIALOG,m_pView,this,pCurve);
	m_pActiveDialog->Create(IDD_SPLINE_DIALOG,m_pView);
	UpdateOKPrevious(m_pActiveDialog);

}
void CSequence::EndStep()
// Redéfini dans les classes dérivées
{
#ifdef _DEBUG
	AfxMessageBox("Erreur! Appel de la fonction EndStep() de base.");
#endif // _DEBUG
}

void CSequence::UpdateOKPrevious(CConstructionDialog *pDialog)
{
	if(pDialog==NULL)
	{
		return;
	}
	if(m_StepArray[m_CurrentStep-1]==begin)
	{
		pDialog->NoPrevious();
	}
	if(m_StepArray[m_CurrentStep+1]==end)
	{
		pDialog->SetLastDialog();
	}
	pDialog->UpdateOKButton();
}

CPoint CSequence::GetPrevWndPosition()
{
	return m_WindowPosition;
}

void CSequence::SetActWndPosition(CPoint point)
{
	m_WindowPosition=point;
}

CUnscanView* CSequence::GetView()
{
	return m_pView;
}

CUnscanDoc* CSequence::GetDocument()
{
	return m_pDoc;
}


CCoordSyst* CSequence::GetCoordSyst()
{
	return m_pCoordSyst;
}

void CSequence::CancelCurveSequence(CDialog *pDialogue)
{
#ifdef _DEBUG
	if((m_pActiveDialog==NULL)||(m_pActiveDialog!=pDialogue))
	{
		AfxMessageBox("Putain! Un dialogue veut en virer un\nautre dans la sequence");
	}
#endif //_DEBUG
	if(m_pCurve!=NULL)
	{
		m_pCoordSyst->RemoveCurve(m_pCurve);
	}
	if(m_pBackCurve!=NULL)
	{
		m_pCoordSyst->AddCurve(m_pBackCurve);
		m_pBackCurve=NULL;
	}
	if(m_pActiveDialog!=NULL)
	{
		m_pView->CancelActiveDialog(m_pActiveDialog);
	}
	m_pDoc->UpdateAllViews(NULL);
	delete this;
}

void CSequence::EndStepCurve()
{
	if(m_pBackCurve!=NULL)
	{
		delete m_pBackCurve;
	}
	if(m_pCurve!=NULL)
	{
		if(m_bIsCurveCreation)
		{
			m_pCurve->IncrementIDNumber();
		}
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
	m_pCoordSyst->SetSelected();
	m_pView->InvalidateRgn(NULL);
	m_pView->PostMessage(WM_PAINT);
	delete this;	
}
