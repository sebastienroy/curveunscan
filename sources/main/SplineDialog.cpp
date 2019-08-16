// SplineDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CurveUnscan.h"
#include "SplineDialog.h"
#include "SplineDlgAddFrontTool.h"
#include "SplineDlgAddBackTool.h"
#include "SplineDlgAddMiddleTool.h"
#include "SplineDlgRemoveTool.h"
#include "SplineDlgModifyTool.h"

#include "Sequence.h"
#include "UnscanDoc.h"

#include <Dm/SplineCurve.h>

#include <assert.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplineDialog dialog


CSplineDialog::CSplineDialog(UINT ID, CUnscanView *pView, 
							 CSequence *pSequence, 
							 CSplineCurve *pCurve)
:	CConstructionDialog(ID,pView,pSequence),
	m_pCurve(pCurve),
	m_pState(NULL)
{
	//{{AFX_DATA_INIT(CSplineDialog)
	m_nTool = 0;
	m_strCurveName = _T(pCurve->GetName());
	//}}AFX_DATA_INIT

}


void CSplineDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSplineDialog)
	DDX_Radio(pDX, IDC_RADIO_SPLINE_ADDBACK, m_nTool);
	DDX_Text(pDX, IDC_EDIT_CURVENAME, m_strCurveName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSplineDialog, CDialog)
	//{{AFX_MSG_MAP(CSplineDialog)
	ON_BN_CLICKED(IDC_PREVIOUS, OnPrevious)
	ON_MESSAGE(WM_END_PICK,OnEndPick)
	ON_MESSAGE(WM_MOVE_PICK,OnMovePick)
	ON_MESSAGE(WM_START_PICK,OnStartPick)
	ON_BN_CLICKED(IDC_MINIMIZE_BUTTON, OnMinimizeButton)
	ON_EN_CHANGE(IDC_EDIT_CURVENAME, OnChangeEditCurvename)
	ON_BN_CLICKED(IDC_RADIO_SPLINE_ADDBACK, OnRadioSplineAddback)
	ON_BN_CLICKED(IDC_RADIO_SPLINE_ADDFRONT, OnRadioSplineAddfront)
	ON_BN_CLICKED(IDC_RADIO_SPLINE_ADDMIDDLE, OnRadioSplineAddmiddle)
	ON_BN_CLICKED(IDC_RADIO_SPLINE_MODIFY, OnRadioSplineModify)
	ON_BN_CLICKED(IDC_RADIO_SPLINE_REMOVE, OnRadioSplineRemove)
	ON_BN_CLICKED(IDC_UNDO_SPLINE_BUTTON, OnUndoSplineButton)
	ON_BN_CLICKED(IDC_REDO_SPLINE_BUTTON, OnRedoSplineButton)
	ON_BN_CLICKED(IDC_SPLINE_CLEAN_ALL, OnSplineCleanAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplineDialog message handlers

BOOL CSplineDialog::OnInitDialog() 
{
	CConstructionDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	// Set icons on  buttons
	CButton* addBackButton=static_cast<CButton*>(GetDlgItem(IDC_RADIO_SPLINE_ADDBACK));
	HICON addBackIcon=AfxGetApp()->LoadIcon(IDI_SPLINE_ADD_BACK);
	addBackButton->SetIcon(addBackIcon);

	CButton* addFrontButton=static_cast<CButton*>(GetDlgItem(IDC_RADIO_SPLINE_ADDFRONT));
	HICON addFrontIcon=AfxGetApp()->LoadIcon(IDI_SPLINE_ADD_FRONT);
	addFrontButton->SetIcon(addFrontIcon);

	CButton* addMiddleButton=static_cast<CButton*>(GetDlgItem(IDC_RADIO_SPLINE_ADDMIDDLE));
	HICON addMiddleIcon=AfxGetApp()->LoadIcon(IDI_SPLINE_ADD_MIDDLE);
	addMiddleButton->SetIcon(addMiddleIcon);
	
	CButton* removeButton=static_cast<CButton*>(GetDlgItem(IDC_RADIO_SPLINE_REMOVE));
	HICON removeIcon=AfxGetApp()->LoadIcon(IDI_SPLINE_REMOVE);
	removeButton->SetIcon(removeIcon);

	CButton* modifyButton=static_cast<CButton*>(GetDlgItem(IDC_RADIO_SPLINE_MODIFY));
	HICON modifyIcon=AfxGetApp()->LoadIcon(IDI_SPLINE_MODIFY);
	modifyButton->SetIcon(modifyIcon);

//	CSplineDlgAddBackTool* pTool=new CSplineDlgAddBackTool(this,m_pCurve);
//	SetState(pTool);

	if(0==m_pCurve->GetNodeCount())	// spline creation
	{
		m_nTool=(int)CSplineDlgAbstractTool::kAddBack;
	}
	else	// spline modification
	{
		m_nTool=(int)CSplineDlgAbstractTool::kModify;
	}
	UpdateToolState();
	SetToolComment(m_pState->getToolComment());

	// undo - redo buttons
	CButton* undoButton=static_cast<CButton*>(GetDlgItem(IDC_UNDO_SPLINE_BUTTON));
	HICON undoIcon=AfxGetApp()->LoadIcon(IDI_UNDOICON);
	undoButton->SetIcon(undoIcon);

	CButton* redoButton=static_cast<CButton*>(GetDlgItem(IDC_REDO_SPLINE_BUTTON));
	HICON redoIcon=AfxGetApp()->LoadIcon(IDI_REDOICON);
	redoButton->SetIcon(redoIcon);

	RefreshToolButton();


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSplineDialog::DataValidation()
{
	UpdateData(TRUE);

	return CheckCurveNameUnicity(m_pCurve,m_strCurveName);

}

BOOL CSplineDialog::OKState()
{
	UpdateData(TRUE);

	bool flag=( (m_strCurveName.GetLength()!=0)
				&& (m_pCurve->GetNodeCount()>=2) );

	return flag;
}

void CSplineDialog::OnPrevious() 
{
	// TODO: Add your control notification handler code here
	CConstructionDialog::OnPrevious();	
}

void CSplineDialog::OnMinimizeButton() 
{
	// TODO: Add your control notification handler code here
	MessageBox("Not implemented yet");
}

void CSplineDialog::UpdateObjects()
{
	UpdateData(TRUE);
	m_pCurve->SetName(m_strCurveName);
}

void CSplineDialog::OnChangeEditCurvename() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateOKButton();

}

void CSplineDialog::SetState(CSplineDlgAbstractTool *pDlgState)
{
	delete m_pState;
	m_pState=pDlgState;

	RefreshToolButton();
	SetToolComment(m_pState->getToolComment());
}

void CSplineDialog::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete m_pState;
	
	CConstructionDialog::PostNcDestroy();
}

void CSplineDialog::OnRadioSplineAddback() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	UpdateToolState();
	
}

void CSplineDialog::OnRadioSplineAddfront() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	UpdateToolState();
	
}

void CSplineDialog::OnRadioSplineAddmiddle() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	UpdateToolState();
	
}

void CSplineDialog::OnRadioSplineModify() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	UpdateToolState();
	
}

void CSplineDialog::OnRadioSplineRemove() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	UpdateToolState();
}

void CSplineDialog::UpdateToolState()
{
	CSplineDlgAbstractTool* pTool=NULL;
	switch(m_nTool)
	{
	case 0:
		pTool=new CSplineDlgAddBackTool(this,m_pCurve);
		break;
	case 1:
		pTool=new CSplineDlgAddFrontTool(this,m_pCurve);
		break;
	case 2:
		pTool=new CSplineDlgAddMiddleTool(this,m_pCurve);
		break;
	case 3:
		pTool=new CSplineDlgRemoveTool(this,m_pCurve);
		break;
	case 4:
		pTool=new CSplineDlgModifyTool(this,m_pCurve);
		break;
	default:
		assert(false);

	}
	SetState(pTool);
	SetToolComment(m_pState->getToolComment());
}

LONG CSplineDialog::OnStartPick(UINT wParam, LONG lParam)
{
	CPoint* point=(CPoint*)lParam;
	bool bShiftPressed=MK_SHIFT&wParam;
	bool bCtrlPressed=MK_CONTROL&wParam;
	m_pState->StartPick(*point,bShiftPressed,bCtrlPressed);

	return 0;
}

LONG CSplineDialog::OnMovePick(UINT wParam, LONG lParam)
{
	CPoint* point=(CPoint*)lParam;
	bool bShiftPressed=MK_SHIFT&wParam;
	bool bCtrlPressed=MK_CONTROL&wParam;
	m_pState->MovePick(*point,bShiftPressed,bCtrlPressed);

	return 0;
}

LONG CSplineDialog::OnEndPick(UINT wParam, LONG lParam)
{
	CPoint* point=(CPoint*)lParam;
	bool bShiftPressed=MK_SHIFT&wParam;
	bool bCtrlPressed=MK_CONTROL&wParam;
	m_pState->EndPick(*point,bShiftPressed,bCtrlPressed);

	m_pSequence->GetDocument()->UpdateAllViews(NULL);
	UpdateOKButton();
	RefreshToolButton();

	return 0;
}


void CSplineDialog::OnUndoSplineButton() 
{
	// TODO: Add your control notification handler code here
	MessageBox("Not implemented yet");
}

void CSplineDialog::OnRedoSplineButton() 
{
	// TODO: Add your control notification handler code here
	MessageBox("Not implemented yet");	
}

void CSplineDialog::RefreshToolButton()
{
	UpdateData(TRUE);
	m_nTool=(int)m_pState->GetKind();
	UpdateData(FALSE);
	
	bool atLeastOne=m_pCurve->GetNodeCount()>=1;
	bool atLeastTwo=m_pCurve->GetNodeCount()>=2;

	GetDlgItem(IDC_RADIO_SPLINE_ADDFRONT)->EnableWindow(atLeastOne);
	GetDlgItem(IDC_RADIO_SPLINE_ADDMIDDLE)->EnableWindow(atLeastTwo);
	GetDlgItem(IDC_RADIO_SPLINE_REMOVE)->EnableWindow(atLeastOne);
	GetDlgItem(IDC_RADIO_SPLINE_MODIFY)->EnableWindow(atLeastOne);

	GetDlgItem(IDC_SPLINE_CLEAN_ALL)->EnableWindow(atLeastOne);
}

void CSplineDialog::OnSplineCleanAll() 
{
	// TODO: Add your control notification handler code here
	if(IDYES==AfxMessageBox(IDS_SPLINE_CLEANALL_CONFIRM,MB_ICONQUESTION|MB_YESNO))
	{
		m_pCurve->Clear();
		m_pSequence->GetDocument()->UpdateAllViews(NULL);

		CSplineDlgAbstractTool* pTool=new CSplineDlgAddBackTool(this,m_pCurve);
		SetState(pTool);

		
		UpdateOKButton();
		RefreshToolButton();
	}
	
}

void CSplineDialog::SetToolComment(CString strComment)
{
	CWnd* pStatic=GetDlgItem(IDC_STATIC_SPLINE_TOOL_COMMENT);
	pStatic->SetWindowText(strComment);
	pStatic->RedrawWindow();
}
