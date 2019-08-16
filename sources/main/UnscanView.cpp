// UnscanView.cpp : implementation of the CUnscanView class
//

#include "stdafx.h"
#include "CurveUnscan.h"

#include "ZoomDialog.h"
#include "ConstructionDialog.h"
#include "UnscanDoc.h"
#include "UnscanView.h"
#include "Sequence.h"
#include "CompleteSequence.h"
#include "DiscreteSequence.h"
#include "DensitoSequence.h"
#include "SplineSequence.h"
#include "ContinuousSequence.h"
#include "CoordSequence.h"
#include "MainFrm.h"
#include "enums.h"

#include <Dm/CoordSyst.h>
#include <Dm/ContinuousCurve.h>
#include <Dm/DiscreteCurve.h>
#include <Dm/DensityCurve.h>
#include <Dm/SplineCurve.h>
#include <Dm/Curve.h>
#include <Dm/BmpManager.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUnscanView

IMPLEMENT_DYNCREATE(CUnscanView, CScrollView)

BEGIN_MESSAGE_MAP(CUnscanView, CScrollView)
	//{{AFX_MSG_MAP(CUnscanView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_GRAPH_NEWSYSTEM, OnGraphNewsystem)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_NEWSYSTEM, OnUpdateGraphNewsystem)
	ON_WM_TIMER()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_GRAPH_NEWDISCRETE, OnGraphNewdiscrete)
	ON_COMMAND(ID_GRAPH_NEWCONTINUOUS, OnGraphNewcontinuous)
	ON_COMMAND(ID_GRAPH_NEWDENSITOCURVE, OnGraphNewdensito)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_NEWCONTINUOUS, OnUpdateGraphNewcontinuous)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_NEWDISCRETE, OnUpdateGraphNewdiscrete)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_NEWDENSITOCURVE, OnUpdateGraphNewdensito)
	ON_COMMAND(ID_GRAPH_MODIFY, OnGraphModify)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_MODIFY, OnUpdateGraphModify)
	ON_COMMAND(ID_GRAPH_DELETEOBJECT, OnGraphDeleteobject)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_DELETEOBJECT, OnUpdateGraphDeleteobject)
	ON_COMMAND(ID_GRAPH_NEW_COORDANDCURVE, OnGraphNewCoordandcurve)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_NEW_COORDANDCURVE, OnUpdateGraphNewCoordandcurve)
	ON_COMMAND(ID_VIEW_ZOOM, OnViewZoom)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM, OnUpdateViewZoom)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_HELP_FINDER, OnHelpFinder)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OPTIONS, OnUpdateViewOptions)
	ON_WM_SETCURSOR()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_GRAPH_NEWSPLINECURVE, OnGraphNewsplinecurve)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_NEWSPLINECURVE, OnUpdateGraphNewsplinecurve)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUnscanView construction/destruction

CUnscanView::CUnscanView()
{
	// TODO: add construction code here
	m_pActiveDialog=NULL;
	m_pZoomDialog=NULL;
	m_nZoom=100;
	m_CurrentState=WaitState;
	m_ScrollDirection=CPoint(0,0);
	m_FirstAppears=TRUE;
	m_pSequence=NULL;
}

CUnscanView::~CUnscanView()
{
	delete m_pZoomDialog;
	delete m_pSequence;
}

BOOL CUnscanView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	UINT style=cs.style;

	cs.style=style|CS_OWNDC;
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CUnscanView drawing

void CUnscanView::OnDraw(CDC* pDC)
{
	CUnscanDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	CRect rect;
	GetClientRect(&rect);
	pDC->DPtoLP(&rect);
	pDoc->Draw(pDC,&rect);

}

/////////////////////////////////////////////////////////////////////////////
// CUnscanView diagnostics

#ifdef _DEBUG
void CUnscanView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CUnscanView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CUnscanDoc* CUnscanView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUnscanDoc)));
	return (CUnscanDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUnscanView message handlers

void CUnscanView::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CSize size;
	CUnscanDoc* pDoc=(CUnscanDoc*)GetDocument();
	bool opened=(pDoc->GetBmpManager())->IsBmpOpened();
	if( (opened)&&(m_nZoom>0) )
		{
		CSize sizeBmp=(pDoc->GetBmpManager())->GetBmpSize();
		size.cx=(sizeBmp.cx*m_nZoom)/100;
		size.cy=(sizeBmp.cy*m_nZoom)/100;
		}
	else
		{
		size.cx = size.cy = 0;
		}

	SetScrollSizes(MM_TEXT, size);

}

void CUnscanView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
	{
	// TODO: Add your specialized code here and/or call the base class
	
	CScrollView::OnPrepareDC(pDC, pInfo);

	pDC->SetMapMode(MM_ISOTROPIC);		// zoom
	pDC->SetWindowExt(100,100);
	int nZoom=(m_nZoom>0)?m_nZoom:GetFittedZoom();
	pDC->SetViewportExt(nZoom,nZoom);


}

void CUnscanView::OnLButtonDown(UINT nFlags, CPoint point) 
	{
	// TODO: Add your message handler code here and/or call default
	
	CScrollView::OnLButtonDown(nFlags, point);


	if( (m_pActiveDialog!=NULL)&&(m_CurrentState==WaitDialogState) )
		{
		SetCapture();
		m_CurrentState=PickingState;
		CClientDC dc(this);
		OnPrepareDC(&dc);
		dc.DPtoLP(&point);
		point=(GetDocument()->GetBmpManager())->IntoBitmap(point);
		m_pActiveDialog->SendMessage(WM_START_PICK,(WPARAM)nFlags,(LPARAM) &point);
		}
	}

void CUnscanView::OnMouseMove(UINT nFlags, CPoint point) 
	{
	// TODO: Add your message handler code here and/or call default
	
	CScrollView::OnMouseMove(nFlags, point);

	UpdateCoordStatus(point);

	if (GetCapture() != this)
		return; // If this window (view) didn't capture the mouse,
				// then the user isn't drawing in this window.
	CRect wndRect;
	GetClientRect(&wndRect);
	m_ScrollDirection=ScrollDirection(point);
	try
		{
		CClientDC dc(this);
		OnPrepareDC(&dc);
		dc.DPtoLP(&point);
		CUnscanDoc *pDoc=(CUnscanDoc*)GetDocument();
		point=(pDoc->GetBmpManager())->IntoBitmap(point);
		
		switch (m_CurrentState)
			{
			case PickingState:
				if(m_ScrollDirection!=CPoint(0,0))
					{
					m_TimerID=SetTimer(ID_SCROLL_TIMER,50,NULL);
					m_CurrentState=ScrollingState;
					if(m_pActiveDialog!=NULL)
						{
						m_pActiveDialog->SendMessage(WM_SCROLL_ON,(WPARAM)nFlags,(LPARAM) &point);
						}
					}
				else if(m_pActiveDialog!=NULL)
					{
					m_pActiveDialog->SendMessage(WM_MOVE_PICK,(WPARAM)nFlags,(LPARAM) &point);
					}
				break;
			case ScrollingState:
				if(m_ScrollDirection==CPoint(0,0))
					{
					KillTimer(m_TimerID);
					m_pActiveDialog->SendMessage(WM_SCROLL_OFF,(WPARAM)nFlags,(LPARAM) &point);
					m_CurrentState=PickingState;
					}
				break;
			default:;
			#ifdef _DEBUG
				MessageBox("Erreur : traitement par défaut dans OnMouseMove()");
			#endif //_DEBUG
			}
		}
	catch (CResourceException* e)
		{
		AfxMessageBox("Exception when trying to create ClientDC object");
		e->Delete();
		}
	catch (...)
		{
		AfxMessageBox("Unknown exception when trying to create ClientDC object");
		}

	}

void CUnscanView::OnLButtonUp(UINT nFlags, CPoint point) 
	{
	// TODO: Add your message handler code here and/or call default
	
	CScrollView::OnLButtonUp(nFlags, point);
	if (GetCapture() != this)
		return; // If this window (view) didn't capture the mouse,
				// then the user isn't drawing in this window.
	switch (m_CurrentState)
		{
		case ScrollingState:
			KillTimer(m_TimerID);
		case PickingState:
			m_CurrentState=WaitDialogState;
			break;
		default:;
#ifdef _DEBUG
			MessageBox("Erreur : traitement par défaut dans OnLButtonUp()");
#endif //_DEBUG
		}
	try
		{
		if(m_pActiveDialog!=NULL)
			{
			CClientDC dc(this);
			OnPrepareDC(&dc);
			dc.DPtoLP(&point);
			CUnscanDoc* pDoc=GetDocument();	
			point=(pDoc->GetBmpManager())->IntoBitmap(point);
			m_pActiveDialog->SendMessage(WM_END_PICK,nFlags,(LPARAM) &point);
			}
		}
	catch (CResourceException* e)
		{
//		AfxMessageBox("Exception when trying to create ClientDC object");
		e->Delete();
		}
	catch (...)
		{
//		AfxMessageBox("Unknown exception when trying to create ClientDC object");
		}
	
	ReleaseCapture();
	}

void CUnscanView::OnLButtonDblClk(UINT nFlags, CPoint point) 
// Gestion du double-click :
// Sélection des objets se trouvant à l'endroit double-clické
// si un dialogue est actif, il ne se passe rien.
	{
	// TODO: Add your message handler code here and/or call default
	
	CScrollView::OnLButtonDblClk(nFlags, point);
	if(m_pActiveDialog!=NULL)
		{
		return;
		}
	try
		{
		CClientDC dc(this);
		OnPrepareDC(&dc);
		CUnscanDoc* pDoc=GetDocument();	
		dc.DPtoLP(&point);
		pDoc->SelectOn(point);
		InvalidateRgn(NULL);
		PostMessage(WM_PAINT);
		}
	catch (CResourceException* e)
		{
		AfxMessageBox("Exception when trying to create ClientDC object");
		e->Delete();
		}
	catch (...)
		{
		AfxMessageBox("Unknown exception when trying to create ClientDC object");
		}
	}

BOOL CUnscanView::SetActiveDialog(CDialog *dialogue)
// enregistre le message de présence du dialogue et permet le suivi des 
// évènements souris : tracé des axes, choix des points....
	{

#ifdef _DEBUG
	if(m_pActiveDialog!=NULL)
		{
		AfxMessageBox("Achtung! Deux dialogues se chevauchent!");
		return FALSE;
		}
#endif _DEBUG
	m_pActiveDialog=dialogue;
	m_CurrentState=WaitDialogState;
	return TRUE;
	}

BOOL CUnscanView::CancelActiveDialog(CDialog *pDialogue)
	{

#ifdef _DEBUG
	if(m_pActiveDialog==NULL)
		{
		AfxMessageBox("Bordel! Il n'y a pas de dialogue a virer dans la vue");
		return FALSE;
		}
	if(m_pActiveDialog!=pDialogue)
		{
		AfxMessageBox("Shit! Un dialogue veut en virer un autre dans la vue!");
		return FALSE;
		}
#endif //_DEBUG
	m_pActiveDialog=NULL;
	m_CurrentState=WaitState;
	return TRUE;
	}

CPoint CUnscanView::ScrollDirection(CPoint point)
// Renvoie un Cpoint qui donne le sens du scroll en fonction du point 
//  donné en parametre et de la taille de la fenêtre.
	{
	CPoint direction(0,0);
	CRect winRect;
	GetClientRect(&winRect);
	CSize totalSize=GetTotalSize();
	static int step=25;
	if( (point.x>winRect.Width())&&((GetScrollPos(SB_HORZ)+winRect.Width())<totalSize.cx) )
		{
		direction.x=step;
		}
	if( (point.x<0)&&(GetScrollPos(SB_HORZ)>0) )
		{
		direction.x=-1*step;
		}
	if( (point.y>winRect.Height())&&((GetScrollPos(SB_VERT)+winRect.Height())<totalSize.cy) )
		{
		direction.y=step;
		}
	if( (point.y<0)&&(GetScrollPos(SB_VERT)>0) )
		{
		direction.y=-1*step;
		}
	return direction;
	}

void CUnscanView::OnTimer(UINT nIDEvent) 
	{
	// TODO: Add your message handler code here and/or call default
	
	CScrollView::OnTimer(nIDEvent);

	if(nIDEvent!=m_TimerID)
		{
		return;
		}

	if(m_CurrentState==ScrollingState)
		{
		int posx=GetScrollPos(SB_HORZ);
		int posy=GetScrollPos(SB_VERT);
		posx+=m_ScrollDirection.x;
		posy+=m_ScrollDirection.y;
		SetScrollPos(SB_HORZ,posx);
		SetScrollPos(SB_VERT,posy);
		}
//	InvalidateRgn(NULL);
//	PostMessage(WM_PAINT);
	GetDocument()->UpdateAllViews(NULL);
	MSG msg;
	while(::PeekMessage(&msg, m_hWnd, WM_TIMER, WM_TIMER, PM_REMOVE));
	}

BOOL CUnscanView::IsDialogOn()
// Renvoie TRUE si un dialogue est actif
	{
	BOOL result=FALSE;
	if (m_pActiveDialog!=NULL)
		{
		result=TRUE;
		}
	return result;
	}

void CUnscanView::OnGraphNewsystem() 
	{
	// TODO: Add your command handler code here
	CUnscanDoc* pDoc=GetDocument();
	m_pSequence=new CCoordSequence(this,pDoc);
	CString msg;
	msg.LoadString(IDS_OUT_OF_MEMORY);
	if(m_pSequence==NULL)
		{
		MessageBox(msg);
		}
	else if( (m_pSequence->Begin())==FALSE ) 
		{
		MessageBox(msg);
		delete m_pSequence;
		}
	}

void CUnscanView::OnUpdateGraphNewsystem(CCmdUI* pCmdUI) 
	{
	// TODO: Add your command update UI handler code here
	bool opened=GetDocument()->GetBmpManager()->IsBmpOpened();
	if( (!opened)||(m_pActiveDialog!=NULL) )
		{
		pCmdUI->Enable(FALSE);
		}
	}

void CUnscanView::OnGraphNewdensito() 
{
	// TODO: Add your command handler code here
	CUnscanDoc *pDoc=GetDocument();
	CCoordSyst *pCoord=pDoc->GetSelectedCoordSyst();
	if(pCoord==NULL)
	{
		CString msg;
		msg.LoadString(IDS_SELECT_COORD_SYST);
		MessageBox(msg,"CurveUnscan",MB_OK|MB_ICONINFORMATION);
		return;
	}
	m_pSequence=new CDensitoSequence(this,pDoc,pCoord);
	if(m_pSequence==NULL)
	{
		CString msg;
		msg.LoadString(IDS_OUT_OF_MEMORY);
		MessageBox(msg);
	}
	else if( (m_pSequence->Begin())==FALSE ) 
	{
		CString msg;
		msg.LoadString(IDS_OUT_OF_MEMORY);
		MessageBox(msg);
		delete m_pSequence;
		m_pSequence=NULL;
	}

}

void CUnscanView::OnGraphNewdiscrete() 
	{
	// TODO: Add your command handler code here
	CUnscanDoc *pDoc=GetDocument();
	CCoordSyst *pCoord=pDoc->GetSelectedCoordSyst();
	if(pCoord==NULL)
		{
		CString msg;
		msg.LoadString(IDS_SELECT_COORD_SYST);
		MessageBox(msg,"CurveUnscan",MB_OK|MB_ICONINFORMATION);
		return;
		}
	m_pSequence=new CDiscreteSequence(this,pDoc,pCoord);
	if(m_pSequence==NULL)
		{
		CString msg;
		msg.LoadString(IDS_OUT_OF_MEMORY);
		MessageBox(msg);
		}
	else if( (m_pSequence->Begin())==FALSE ) 
		{
		CString msg;
		msg.LoadString(IDS_OUT_OF_MEMORY);
		MessageBox(msg);
		delete m_pSequence;
		m_pSequence=NULL;
		}
	}

void CUnscanView::OnGraphNewcontinuous() 
	{
	// TODO: Add your command handler code here
	CUnscanDoc *pDoc=GetDocument();
	CCoordSyst *pCoord=pDoc->GetSelectedCoordSyst();
	if(pCoord==NULL)
		{
		CString msg;
		msg.LoadString(IDS_SELECT_COORD_SYST);
		MessageBox(msg,"CurveUnscan",MB_OK|MB_ICONINFORMATION);
		return;
		}
	m_pSequence=new CContinuousSequence(this,pDoc,pCoord);
	if(m_pSequence==NULL)
		{
		CString msg;
		msg.LoadString(IDS_OUT_OF_MEMORY);
		MessageBox(msg);
		}
	else if( (m_pSequence->Begin())==FALSE ) 
		{
		CString msg;
		msg.LoadString(IDS_OUT_OF_MEMORY);
		MessageBox(msg);
		delete m_pSequence;
		m_pSequence=NULL;
		}
	}

void CUnscanView::OnGraphNewsplinecurve() 
{
	// TODO: Add your command handler code here
	CUnscanDoc *pDoc=GetDocument();
	CCoordSyst *pCoord=pDoc->GetSelectedCoordSyst();
	if(pCoord==NULL)
	{
		CString msg;
		msg.LoadString(IDS_SELECT_COORD_SYST);
		MessageBox(msg,"CurveUnscan",MB_OK|MB_ICONINFORMATION);
		return;
	}
	m_pSequence=new CSplineSequence(this,pDoc,pCoord);
	if(m_pSequence==NULL)
	{
		CString msg;
		msg.LoadString(IDS_OUT_OF_MEMORY);
		MessageBox(msg);
	}
	else if( (m_pSequence->Begin())==FALSE ) 
	{
		CString msg;
		msg.LoadString(IDS_OUT_OF_MEMORY);
		MessageBox(msg);
		delete m_pSequence;
		m_pSequence=NULL;
	}	
}

void CUnscanView::OnUpdateGraphNewsplinecurve(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CUnscanDoc* pDoc=(CUnscanDoc*)GetDocument();
	if( (pDoc->GetHeadCoordSystPosition()==NULL)||(m_pActiveDialog!=NULL) )
	{
		pCmdUI->Enable(FALSE);
	}	
	
}

void CUnscanView::OnUpdateGraphNewdensito(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CUnscanDoc* pDoc=(CUnscanDoc*)GetDocument();
	if( (pDoc->GetHeadCoordSystPosition()==NULL)||(m_pActiveDialog!=NULL) )
	{
		pCmdUI->Enable(FALSE);
	}	
	
}

void CUnscanView::OnUpdateGraphNewcontinuous(CCmdUI* pCmdUI) 
	{
	// TODO: Add your command update UI handler code here
	CUnscanDoc* pDoc=(CUnscanDoc*)GetDocument();
	if( (pDoc->GetHeadCoordSystPosition()==NULL)||(m_pActiveDialog!=NULL) )
		{
		pCmdUI->Enable(FALSE);
		}	
	}

void CUnscanView::OnUpdateGraphNewdiscrete(CCmdUI* pCmdUI) 
	{
	// TODO: Add your command update UI handler code here
	CUnscanDoc* pDoc=(CUnscanDoc*)GetDocument();
	if( (pDoc->GetHeadCoordSystPosition()==NULL)||(m_pActiveDialog!=NULL) )
		{
		pCmdUI->Enable(FALSE);
		}	
	}

void CUnscanView::OnGraphModify() 
{
	// TODO: Add your command handler code here
	CUnscanDoc* pDoc=(CUnscanDoc*)GetDocument();

	CCoordSyst* pCoord=pDoc->GetSelectedCoordSyst();	// is the selected object a CoordSyst?
	if(pCoord!=NULL)
	{
		m_pSequence=new CCoordSequence(this,pDoc,pCoord);
		if(m_pSequence==NULL)
		{
			CString msg;
			msg.LoadString(IDS_OUT_OF_MEMORY);
			MessageBox(msg);
		}
		else if( (m_pSequence->Begin())==FALSE ) 
		{
			CString msg;
			msg.LoadString(IDS_OUT_OF_MEMORY);
			MessageBox(msg);
			delete m_pSequence;
			m_pSequence=NULL;
		}
		return;
	}

	CCurve* pCurve=pDoc->GetSelectedCurve();	// is the selected object a curve?
	if(pCurve!=NULL)
	{
		pCoord=pCurve->GetCoordSyst();
		if(pCurve->IsContinuousCurve())
		{
			m_pSequence=new CContinuousSequence(this,pDoc,pCoord,(CContinuousCurve*)pCurve);
		}
		else if(NULL!=dynamic_cast<CDiscreteCurve*>(pCurve))
		{
			m_pSequence=new CDiscreteSequence(this,pDoc,pCoord,(CDiscreteCurve*)pCurve);
		}
		else if(NULL!=dynamic_cast<CDensityCurve*>(pCurve))
		{
			m_pSequence=new CDensitoSequence(this,pDoc,pCoord,static_cast<CDensityCurve*>(pCurve));
		}
		else if(NULL!=dynamic_cast<CSplineCurve*>(pCurve))
		{
			m_pSequence=new CSplineSequence(this,pDoc,pCoord,static_cast<CSplineCurve*>(pCurve));
		}
		else
		{
#if defined(_DEBUG)
			MessageBox("Unrecognized curve!!!");
			return;
#endif
		}

		if(m_pSequence==NULL)
		{
			CString msg;
			msg.LoadString(IDS_OUT_OF_MEMORY);
			MessageBox(msg);
		}
		else if( (m_pSequence->Begin())==FALSE ) 
		{
			CString msg;
			msg.LoadString(IDS_OUT_OF_MEMORY);
			MessageBox(msg);
			delete m_pSequence;
			m_pSequence=NULL;
		}
	}
}

void CUnscanView::OnUpdateGraphModify(CCmdUI* pCmdUI) 
	{
	// TODO: Add your command update UI handler code here
	CUnscanDoc* pDoc=(CUnscanDoc*)GetDocument();
	BOOL selected=FALSE;
	if(pDoc->GetSelectedCoordSyst()!=NULL)
		{
		selected=TRUE;
		}
	if(pDoc->GetSelectedCurve()!=NULL)
		{
		selected=TRUE;
		}
	if(m_pActiveDialog!=NULL)
		{
		selected=FALSE;
		}
	pCmdUI->Enable(selected);
	}

void CUnscanView::OnGraphDeleteobject() 
	{
	// TODO: Add your command handler code here
	CUnscanDoc* pDoc=(CUnscanDoc*)GetDocument();
	CCoordSyst* pCoord=pDoc->GetSelectedCoordSyst();
	if(pCoord!=NULL)
		{
		if(pCoord->GetCurveCount()>0)
			{
			CString strText;
			strText.LoadString(IDS_DELETE_COORD_SYST);
			CString strCaption="CurveUnscan";
			if(MessageBox(strText,strCaption,MB_YESNO|MB_ICONEXCLAMATION)!=IDYES)
				{
				return;
				}
			}
		pDoc->DeleteCoordSyst(pCoord);
		InvalidateRgn(NULL);
		PostMessage(WM_PAINT);
		return;
		}
	CCurve* pCurve=pDoc->GetSelectedCurve();
	if(pCurve!=NULL)
		{
		pCoord=pCurve->GetCoordSyst();
		pCoord->RemoveCurve(pCurve);
		InvalidateRgn(NULL);
		PostMessage(WM_PAINT);
		}
	}

void CUnscanView::OnUpdateGraphDeleteobject(CCmdUI* pCmdUI) 
	{
	// TODO: Add your command update UI handler code here
	CUnscanDoc* pDoc=(CUnscanDoc*)GetDocument();
	BOOL selected=FALSE;
	if(pDoc->GetSelectedCoordSyst()!=NULL)
		{
		selected=TRUE;
		}
	if(pDoc->GetSelectedCurve()!=NULL)
		{
		selected=TRUE;
		}
	if(m_pActiveDialog!=NULL)
		{
		selected=FALSE;
		}
	pCmdUI->Enable(selected);	
	}

void CUnscanView::OnGraphNewCoordandcurve() 
	{
	// TODO: Add your command handler code here
	CUnscanDoc* pDoc=GetDocument();
	m_pSequence=new CCompleteSequence(this,pDoc);
	if(m_pSequence==NULL)
		{
		CString msg;
		msg.LoadString(IDS_OUT_OF_MEMORY);
		MessageBox(msg);
		}
	else if( (m_pSequence->Begin())==FALSE ) 
		{
		CString msg;
		msg.LoadString(IDS_OUT_OF_MEMORY);
		MessageBox(msg);
		delete m_pSequence;
		m_pSequence=NULL;
		}	
	}

void CUnscanView::OnUpdateGraphNewCoordandcurve(CCmdUI* pCmdUI) 
	{
	// TODO: Add your command update UI handler code here
	bool opened=GetDocument()->GetBmpManager()->IsBmpOpened();
	if( (!opened)||(m_pActiveDialog!=NULL) )
		{
		pCmdUI->Enable(FALSE);
		}	
	}

void CUnscanView::OnViewZoom() 
	{
	// TODO: Add your command handler code here
	if(m_pZoomDialog==NULL)
		{
		m_pZoomDialog=new CZoomDialog(this);
		m_pZoomDialog->Create(IDD_ZOOM_DIALOG,this);
		}
	else
		{
		m_pZoomDialog->SetZoomValue(m_nZoom);
		m_pZoomDialog->ShowWindow(SW_SHOW);
		}
	}

void CUnscanView::OnUpdateViewZoom(CCmdUI* pCmdUI) 
	{
	// TODO: Add your command update UI handler code here
	bool opened=GetDocument()->GetBmpManager()->IsBmpOpened();
	if(!opened)
		{
		pCmdUI->Enable(FALSE);
		}			
	}

int CUnscanView::GetZoom()
// Renvoie la valeur du zoom. Fonction utilisée par le dialogue du zoom.
	{
	return m_nZoom;
	}

int CUnscanView::GetFittedZoom()
// Calcule la valeur du zoom pour que le graphique s'insère dans la fenêtre
	{
	CUnscanDoc* pDoc=(CUnscanDoc*)GetDocument();
	CSize bmpSize=pDoc->GetBmpManager()->GetBmpSize();
	if(bmpSize==CSize(0,0))
		{
		return 100;
		}
	CRect rect;
	GetClientRect(&rect);
	double dblWndWidth=(double)(rect.Width());
	double dblBmpWidth=(double)(bmpSize.cx);
	double dblWndHeigth=(double)(rect.Height());
	double dblBmpHeigth=(double)(bmpSize.cy);
	int nZoom;
	try
		{
		double xFraction=dblWndWidth/dblBmpWidth;
		double yFraction=dblWndHeigth/dblBmpHeigth;
		double lowerFraction=(xFraction>yFraction)?yFraction:xFraction;
		nZoom=(int)(lowerFraction*100.0);
		if(nZoom<1) nZoom=1;
		}
	catch (...)
		{
		CString msg;
		msg.LoadString(IDS_DIVISION_BY_ZERO);
		AfxMessageBox(msg);
		nZoom=100;
		}
	return nZoom;
	}

void CUnscanView::RemoveZoomDialog()
	{
	delete m_pZoomDialog;
	m_pZoomDialog=NULL;
	}

// used by the zoom dialog to change the zoom factor
int CUnscanView::SetZoomValue(int value)
{
	int oldValue=m_nZoom;
	m_nZoom=value;
	if(oldValue!=m_nZoom)
		{
		OnInitialUpdate();
//		GetDocument()->UpdateAllViews(NULL);
		}
	return oldValue;
}

void CUnscanView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here

	// get the right popup menu
	int nMenuIndex=0;
	CUnscanDoc* pDoc=GetDocument();
	bool bmpOpened=pDoc->GetBmpManager()->IsBmpOpened();
	bool bCurveExists=pDoc->IsCurveBuilt();

	CCoordSyst* pSelectedCoordSyst=pDoc->GetSelectedCoordSyst();
	CCurve* pSelectedCurve=pDoc->GetSelectedCurve();
	if(!bmpOpened)
		{
		nMenuIndex=0;
		}
	else if(NULL!=m_pSequence)
		{
		nMenuIndex=1;
		}
	else if(NULL!=pSelectedCoordSyst)
		{
		if(!bCurveExists)
			{
			nMenuIndex=2;
			}
		else
			{
			nMenuIndex=3;
			}
		}
	else if(NULL!=pSelectedCurve)
		{
		nMenuIndex=4;
		}
	else		// nothing selected
		{
		if(!bCurveExists)
			{
			nMenuIndex=5;
			}
		else
			{
			nMenuIndex=6;
			}
		}

	CMenu menu;
	menu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu* pMenu=menu.GetSubMenu(nMenuIndex);
	pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,point.x,point.y,this);
}

void CUnscanView::OnHelpFinder() 
{
	// TODO: Add your command handler code here
	CView::OnHelpFinder();
}

void CUnscanView::UpdateCoordStatus(const CPoint &ptCursor) 
{
	CString strX;
	CString strY;

	CCoordSyst* pCoord=NULL;

	// Is there a selected CoordSyst?
	CUnscanDoc* pDoc=static_cast<CUnscanDoc*>(GetDocument());
	pCoord=pDoc->GetSelectedCoordSyst();
	if(NULL==pCoord)
	{
		CCurve* pCurve=pDoc->GetSelectedCurve();
		if(NULL!=pCurve)
		{
			pCoord=pCurve->GetCoordSyst();
		}
	}
	if( (NULL==pCoord)&&(NULL!=m_pSequence) )
	{
		pCoord=m_pSequence->GetCoordSyst();
		if(!pCoord->IsDefined())
		{
			pCoord=NULL;
		}
	}
	// calculate coordinates
	if(NULL!=pCoord)
	{
		CPoint point=ptCursor;
		CClientDC dc(this);
		OnPrepareDC(&dc);
		dc.DPtoLP(&point);
		CLogicPoint lPoint=pCoord->ToLogic(point);
		strX.Format("%g",lPoint.x);
		strY.Format("%g",lPoint.y);
	}

	CMainFrame* pMain=static_cast<CMainFrame*>(GetParent());
	pMain->UpdateCoordStatus(strX,strY);
}

void CUnscanView::EndSequence()
{
	m_pSequence=NULL;
}

void CUnscanView::StartInitialSequence()
{
	OnGraphNewCoordandcurve();
}

void CUnscanView::OnUpdateViewOptions(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(NULL!=m_pActiveDialog)
	{
		pCmdUI->Enable(FALSE);
	}
}

PLPixel32 CUnscanView::GetPixelColor(const CPoint &point) const
{

	CUnscanDoc *pDoc=static_cast<CUnscanDoc*>((const_cast<CUnscanView*>(this))->GetDocument());
	CBmpManager *pManager=pDoc->GetBmpManager();
	if(NULL==pManager)
	{
		return PLPixel32(255,255,255);
	}

	return pManager->GetPixelColor(point);
}


BOOL CUnscanView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	CConstructionDialog* pConstrDlg=NULL;

	if((HTCLIENT==nHitTest)
		&&(NULL!=m_pActiveDialog)
		&&(NULL!=(pConstrDlg=dynamic_cast<CConstructionDialog*>(m_pActiveDialog))) )
	{
		CursorShape cursorShape=pConstrDlg->GetCursorShape();
		HCURSOR hCursor;
		switch(cursorShape)
		{
		case kPickColorCursor:
			hCursor=AfxGetApp()->LoadCursor(IDC_PICK_COLOR_POINTER);
			break;
		case kDrawLineCursor:
			hCursor=AfxGetApp()->LoadStandardCursor(IDC_CROSS);
			break;
		case kRubberCursor:
			hCursor=AfxGetApp()->LoadCursor(IDC_RUBBER_CURSOR);
			break;
		case kManualDrawCursor:
			hCursor=AfxGetApp()->LoadCursor(IDC_MANUALDRAW_CURSOR);
			break;
		case kDefaultCursor:
		default:
			hCursor=AfxGetApp()->LoadStandardCursor(IDC_ARROW);
			break;
		}
		if(NULL!=hCursor)
		{
			::SetCursor(hCursor);
			return TRUE;
		}
	}

	
	return CScrollView::OnSetCursor(pWnd, nHitTest, message);
}


void CUnscanView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class

/*
// test
	CRect rect(100,100,200,200);
	CRgn rgnTest;
	rgnTest.CreateRectRgnIndirect(&rect);

	CRgn rgnTest2;
	rgnTest2.CreateRectRgnIndirect(CRect(300,300,400,400));
	rgnTest.CombineRgn(&rgnTest,&rgnTest2,RGN_OR);

	InvalidateRgn(&rgnTest);
	return;
*/

	CRect clientRect;
	GetClientRect(&clientRect);
	CRgn rgn;
	rgn.CreateRectRgnIndirect(clientRect);

	CRgn* pRgnParam=NULL;
	CRect* pRectParam=NULL;


	if( NULL!=(pRgnParam=dynamic_cast<CRgn*>(pHint)) )
	{
		rgn.CombineRgn(&rgn,pRgnParam,RGN_AND);
	}
	else if( NULL!=(pRectParam=dynamic_cast<CRect*>(pHint)) )
	{
		CRgn rgn2;
		rgn2.SetRectRgn(pRectParam);
		rgn.CombineRgn(&rgn,pRgnParam,RGN_AND);
	}

	InvalidateRgn(&rgn);
}

void CUnscanView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	// first simulate the left button is released (bug 003)
	if(GetCapture()==this)
	{
		OnLButtonUp(nFlags,point);
	}
	
	CScrollView::OnRButtonDown(nFlags, point);
}


void CUnscanView::PickingStopped()
{
	m_CurrentState=WaitDialogState;
}
