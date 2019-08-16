// HandModificationDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CurveUnscan.h"
#include "HandModificationDialog.h"
#include "UnscanView.h"
#include "PenModificationTool.h"
#include "RubberModificationTool.h"

#include <Dm/ContinuousCurve.h>
#include <Dm/Limit.h>
#include <Dm/BmpManager.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHandModificationDialog dialog


CHandModificationDialog::CHandModificationDialog(UINT ID, CUnscanView *pView, CSequence *pSequence, CContinuousCurve *pCurve)
	:CConstructionDialog(ID,pView,pSequence)
	{
	m_pCurve=pCurve;
	m_pDoc=pView->GetDocument();
	m_DelayTimer=0;
	m_pRedrawRect=NULL;
	m_pModificationTool=new CPenModificationTool(m_pCurve);
	m_CursorShape=kManualDrawCursor;

	// Memento Initialisation
	m_nMementoIndex=0;
	list<CPoint>* initialList=new list<CPoint>;
	m_pCurve->GetPointList(initialList);
	m_MementoVector.push_back(initialList);
	m_ChosenTool=0;
	}

void CHandModificationDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHandModificationDialog)
	DDX_Radio(pDX, IDC_RADIO_TOOL_PEN, m_ChosenTool);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHandModificationDialog, CDialog)
	//{{AFX_MSG_MAP(CHandModificationDialog)
	ON_BN_CLICKED(IDC_PREVIOUS, OnPrevious)
	ON_MESSAGE(WM_END_PICK,OnEndPick)
	ON_MESSAGE(WM_MOVE_PICK,OnMovePick)
	ON_MESSAGE(WM_START_PICK,OnStartPick)
	ON_WM_HELPINFO()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_REDO, OnRedo)
	ON_BN_CLICKED(IDC_UNDO, OnUndo)
	ON_BN_CLICKED(IDC_RESET_MODIFICATION, OnResetModification)
	ON_BN_CLICKED(IDC_RADIO_TOOL_PEN, OnToolChange)
	ON_BN_CLICKED(IDC_RADIO_TOOL_RUBBER, OnToolChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHandModificationDialog message handlers

// Prévient que si retour en arrière, les modifications sont perdues.
void CHandModificationDialog::OnPrevious()
	{
	// TODO: Add your control notification handler code here

	CConstructionDialog::OnPrevious();
	}

// Aucune donnée à valider. retourne toujours TRUE.
BOOL CHandModificationDialog::DataValidation()
	{
	return TRUE;
	}

// Aucune donnée obligatoire, le bouton OK est toujours actif.
BOOL CHandModificationDialog::OKState()
	{
	int size=(m_MementoVector[m_nMementoIndex])->size();
	BOOL state=TRUE;
	if(0==size)
		{
		state=FALSE;
		}
		
	return state;
	}

// Aucune info non "temps réel".
void CHandModificationDialog::UpdateObjects()
	{
	
	}

// Commence la modification, initialise m_PrevPoint
LONG CHandModificationDialog::OnStartPick(UINT wParam, LONG lParam)
	{
	CPoint* point=(CPoint*)lParam;
	m_PrevPoint=*point;
//	CRect refreshRect=m_pCurve->SetPoint(m_PrevPoint);
	CRect refreshRect=m_pModificationTool->Apply(m_PrevPoint,m_PrevPoint);

//	refreshRect=ModifyPoint(m_PrevPoint);
	m_pCurve->SetHandModification(TRUE);

//	CUnscanView* pView=static_cast<CUnscanView*>(GetParent());
//	pView->RedrawWindow(refreshRect);

//	UpdateRedraw(refreshRect);
	m_pDoc->Draw(&refreshRect);

	return 0;
	}

// Modifie l'ensemble des points compris entre le point recu et m_PrevPoint
LONG CHandModificationDialog::OnMovePick(UINT wParam, LONG lParam)
	{
	CPoint* point=(CPoint*)lParam;
	CPoint lastPoint=*point;

	if(lastPoint==m_PrevPoint)	// can be == in the case of great zoom factors
		{
		return 0;
		}

	CBmpManager* pManager=m_pDoc->GetBmpManager();
	lastPoint=pManager->IntoBitmap(lastPoint);

	CRect refreshRect=m_pModificationTool->Apply(m_PrevPoint,lastPoint);


	m_PrevPoint=lastPoint;

	m_pDoc->Draw(&refreshRect);

	
	return 0;
	}

// update memento
LONG CHandModificationDialog::OnEndPick(UINT wParam, LONG lParam)
{
	// Redraw
/*	if(0==m_DelayTimer)
		{
			m_DelayTimer=SetTimer(ID_MODIFICATION_DELAY_TIMER,50,NULL);
		}*/

	// Update memento
	while(m_MementoVector.size()>(m_nMementoIndex+1))
		{
		delete m_MementoVector[m_MementoVector.size()-1];
		m_MementoVector.pop_back();
		}
	m_nMementoIndex++;
	list<CPoint>* newList=new list<CPoint>;
	m_pCurve->GetPointList(newList);
	m_MementoVector.push_back(newList);
	UpdateUndoRedoButtons();

	// Redraw
	m_pDoc->UpdateAllViews(NULL);
	UpdateOKButton();

	return 0;
}

BOOL CHandModificationDialog::OnInitDialog() 
	{
	CConstructionDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	CButton* undoButton=static_cast<CButton*>(GetDlgItem(IDC_UNDO));
	HICON undoIcon=AfxGetApp()->LoadIcon(IDI_UNDOICON);
	undoButton->SetIcon(undoIcon);
	CButton* redoButton=static_cast<CButton*>(GetDlgItem(IDC_REDO));
	HICON redoIcon=AfxGetApp()->LoadIcon(IDI_REDOICON);
	redoButton->SetIcon(redoIcon);
	UpdateUndoRedoButtons();

	CButton* penButton=static_cast<CButton*>(GetDlgItem(IDC_RADIO_TOOL_PEN));
	m_pBmpPen=new CBitmap;
	m_pBmpPen->LoadBitmap(IDB_BITMAP_PEN);
	penButton->SetBitmap(HBITMAP(*m_pBmpPen));

	CButton* rubberButton=static_cast<CButton*>(GetDlgItem(IDC_RADIO_TOOL_RUBBER));
	m_pBmpRubber=new CBitmap;
	m_pBmpRubber->LoadBitmap(IDB_BITMAP_RUBBER);
	rubberButton->SetBitmap(HBITMAP(*m_pBmpRubber));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
	}

BOOL CHandModificationDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CConstructionDialog::OnHelpInfo(pHelpInfo);
}

void CHandModificationDialog::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);

	if(nIDEvent!=m_DelayTimer)
		{
		return;
		}

//	m_pDoc->Draw(m_pRedrawRect);

//	delete m_pRedrawRect;
//	m_pRedrawRect=NULL;
	KillTimer(nIDEvent);
	m_DelayTimer=0;

	if(NULL!=m_pRedrawRect)
		{
		CRect refreshRect(*m_pRedrawRect);
//		UpdateRedraw(refreshRect);
		m_pDoc->Draw(&refreshRect);
		}

}

void CHandModificationDialog::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class

	for(int index=0;index<m_MementoVector.size();index++)
		{
		delete m_MementoVector[index];
		}
	m_MementoVector.empty();

	delete m_pBmpPen;
	delete m_pBmpRubber;
	delete m_pModificationTool;
	
	CConstructionDialog::PostNcDestroy();
}

void CHandModificationDialog::UpdateUndoRedoButtons()
{
	CButton* undoButton=static_cast<CButton*>(GetDlgItem(IDC_UNDO));
	if(0==m_nMementoIndex)
		{
		undoButton->EnableWindow(FALSE);
		}
	else
		{
		undoButton->EnableWindow(TRUE);
		}
	undoButton->UpdateWindow();

	CButton* redoButton=static_cast<CButton*>(GetDlgItem(IDC_REDO));
	if(m_MementoVector.size()==m_nMementoIndex+1)
		{
		redoButton->EnableWindow(FALSE);
		}
	else
		{
		redoButton->EnableWindow(TRUE);
		}
	redoButton->UpdateWindow();
}

void CHandModificationDialog::OnRedo() 
{
	// TODO: Add your control notification handler code here
	if(m_MementoVector.size()==m_nMementoIndex+1)
		{
		return;
		}
	m_nMementoIndex++;
	m_pCurve->SetPointList(m_MementoVector[m_nMementoIndex]);
	m_pDoc->UpdateAllViews(NULL);
	UpdateUndoRedoButtons();
	UpdateOKButton();
	
}

void CHandModificationDialog::OnUndo() 
{
	// TODO: Add your control notification handler code here
	if(0==m_nMementoIndex)
		{
		return;
		}
	m_nMementoIndex--;
	m_pCurve->SetPointList(m_MementoVector[m_nMementoIndex]);
	if(0==m_nMementoIndex)
		{
		m_pCurve->SetHandModification(FALSE);
		}
	m_pDoc->UpdateAllViews(NULL);
	UpdateUndoRedoButtons();
	UpdateOKButton();
	
}

void CHandModificationDialog::OnResetModification() 
{
	//--- Rebuild
	m_pCurve->Construct();
	//--- Update memento
	OnEndPick(0,0);
	//--- Redraw
	m_pDoc->UpdateAllViews(NULL);
	UpdateUndoRedoButtons();
	UpdateOKButton();

}
/*
void CHandModificationDialog::UpdateRedraw(CRect &rect)
{
	if(NULL==m_pRedrawRect)
		{
		m_pRedrawRect=new CRect(rect);
		}
	else
		{
		if(m_pRedrawRect->bottom<rect.bottom) m_pRedrawRect->bottom=rect.bottom;
		if(m_pRedrawRect->top>rect.top) m_pRedrawRect->top=rect.top;
		if(m_pRedrawRect->right<rect.right) m_pRedrawRect->right=rect.right;
		if(m_pRedrawRect->left>rect.left) m_pRedrawRect->left=rect.left;
		}

	if(0==m_DelayTimer)
		{
		m_pDoc->Draw(m_pRedrawRect);
		delete m_pRedrawRect;
		m_pRedrawRect=NULL;

		m_DelayTimer=SetTimer(ID_MODIFICATION_DELAY_TIMER,100,NULL);
		}

}
*/
void CHandModificationDialog::OnToolChange() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	delete m_pModificationTool;
	if(0==m_ChosenTool)
		{
		m_pModificationTool=new CPenModificationTool(m_pCurve);
		m_CursorShape=kManualDrawCursor;
		}
	else
		{
		m_pModificationTool=new CRubberModificationTool(m_pCurve);
		m_CursorShape=kRubberCursor;
		}
	
}
