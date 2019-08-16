// DiscreteDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CurveUnscan.h"
#include "Sequence.h"
#include "UnscanDoc.h"
#include "DiscreteDialog.h"

#include <Dm/DiscreteCurve.h>
#include <Dm/LogicPoint.h>
#include <Dm/CoordSyst.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiscreteDialog dialog

CDiscreteDialog::CDiscreteDialog(UINT ID, CUnscanView *pParent, CSequence *pSequence, CDiscreteCurve *pCurve)
	: CConstructionDialog(ID,pParent,pSequence)
	{
	m_pCurve=pCurve;
	m_pCoordSyst=pCurve->GetCoordSyst();
	m_GraphName=pCurve->GetName();
	m_CursorShape=kDrawLineCursor;
	}

void CDiscreteDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDiscreteDialog)
	DDX_Control(pDX, IDC_LIST_POINTS, m_PointListBox);
	DDX_Text(pDX, IDC_EDIT_GRAPHNAME, m_GraphName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDiscreteDialog, CDialog)
	//{{AFX_MSG_MAP(CDiscreteDialog)
	ON_MESSAGE(WM_END_PICK,OnEndPick)
	ON_BN_CLICKED(IDC_SORT, OnSort)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_PREVIOUS, OnPrevious)
	ON_LBN_SELCHANGE(IDC_LIST_POINTS, OnSelchangeListPoints)
	ON_EN_CHANGE(IDC_EDIT_GRAPHNAME, OnChangeEditGraphname)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiscreteDialog message handlers


void CDiscreteDialog::AddPoint(CPoint point, POSITION curvePos)
// Ajoute dans la ListBox du dialogue le point de la courbe de position curvePos
// Etablit le lien entre la ListeBox et la courbe
	{
	CLogicPoint lpoint;
	lpoint=m_pCoordSyst->ToLogic(point);
	CString strX;
	CString strY;
	CString strLB;
	strX.Format("%g",lpoint.x);
	int length=strX.GetLength();
	while(length<14)
		{
		strX+=CString("  ");
		length++;
		}
	strY.Format("%g",lpoint.y);
	strLB=strX+strY;
	int index=m_PointListBox.AddString(strLB);

	POSITION* pPos=new POSITION;
	*pPos=curvePos;
	m_PointListBox.SetItemDataPtr(index,pPos);
	}

void CDiscreteDialog::OnDelete() 
// Le bouton "Delete" a été cliqué.
// Effacer les points sélectionnés de la ListBox
// avertir l'utilisateur si aucun élément n'est sélectionné
	{
	// TODO: Add your control notification handler code here
	LPINT buffer=new int[128];
	int last=m_PointListBox.GetSelItems(128,buffer);
	if(last==0)
		{
		CString msg;
		msg.LoadString(IDS_NO_POINT_SELECTED);
		MessageBox(msg,"CurveUnscan",MB_OK|MB_ICONINFORMATION);
		return;
		}
	POSITION* pPos;
	for(int counter=0;counter<last;counter++)
		{
		pPos=(POSITION*)m_PointListBox.GetItemDataPtr(buffer[counter]);
		m_pCurve->RemovePoint(*pPos);
		}
	DeleteListBox();
	FillListBox();
	UpdateDeleteButton();
	UpdateSortButton();
	UpdateOKButton();
	delete buffer;
	CWnd* pWnd=GetParent();
	pWnd->InvalidateRgn(NULL);
	pWnd->PostMessage(WM_PAINT);

	}

void CDiscreteDialog::OnSort() 
// Fait trier les point de la CCurve
//  efface et reremplit la Listbox
	{
	// TODO: Add your control notification handler code here
	m_pCurve->SortStraight();
	DeleteListBox();
	FillListBox();	
	}

void CDiscreteDialog::FillListBox()
// Remplit la ListBox à partir des points de la courbe.
	{
	POSITION pos=m_pCurve->GetHeadPointPosition();
	POSITION curvePos;
	CPoint point;
	while(pos!=NULL)
		{
		curvePos=pos;
		point=m_pCurve->GetNextPoint(pos);
		AddPoint(point,curvePos);
		}
	UpdateSortButton();
	}


void CDiscreteDialog::DeleteListBox()
// vire le contenu de la listbox sans toucher à la curve.
	{
	int nCount=m_PointListBox.GetCount();
	POSITION* pPos;
	for(int nIndex=0;nIndex<nCount;nIndex++)
		{
		pPos=(POSITION*)m_PointListBox.GetItemDataPtr(nIndex);
		if((int)pPos!=-1)
			{
			delete pPos;
			}
		}
	m_PointListBox.ResetContent();
	}

void CDiscreteDialog::UpdateObjects()
// Met à jour le nom de la courbe et détruit les objets temporaires
//   (pointeurs de POSITION)
	{
	DeleteListBox();
	UpdateData(TRUE);
	if(m_GraphName!=m_pCurve->GetName())
		{
		m_pCurve->SetName(m_GraphName);
		}
	}

void CDiscreteDialog::OnPrevious() 
	{
	// TODO: Add your control notification handler code here
	CConstructionDialog::OnPrevious();	
	}

BOOL CDiscreteDialog::OKState()
// Si la liste de points est non vide, ainsi que le nom du graphe, c'est OK
	{
	UpdateData(TRUE);
	BOOL flag=TRUE;
	if(m_PointListBox.GetCount()==0)
		{
		flag=FALSE;
		}
//	CEdit* pEdit=(CEdit*)GetDlgItem(IDC_EDIT_GRAPHNAME);
//	char *pBuffer=new char[10];
//	if(pEdit->GetLine(0,pBuffer,5)==0)
	if(m_GraphName.GetLength()==0)
		{
		flag=FALSE;
		}
	return flag;
	}

BOOL CDiscreteDialog::DataValidation()
// Il n'y a rien a valider, la fonction renvoie toujours TRUE
{
	UpdateData(TRUE);

	return CheckCurveNameUnicity(m_pCurve,m_GraphName);

}

BOOL CDiscreteDialog::UpdateDeleteButton()
// Si des éléments sont sélectionnés, activer le bouton "Delete"
// dans le cas inverse, le désactiver
// Renvoie TRUE s'il est activé.
	{
	CButton *pButton=(CButton*)GetDlgItem(IDC_DELETE);
	int count=m_PointListBox.GetSelCount();
	BOOL flag=(count>0)?TRUE:FALSE;
	pButton->EnableWindow(flag);
	return flag;
	}

BOOL CDiscreteDialog::UpdateSortButton()
// Active le bouton de tri si 2 ou plus éléments dans la liste.
	{
	CButton *pButton=(CButton*)GetDlgItem(IDC_SORT);
	int nb=m_PointListBox.GetCount();
	BOOL flag=(nb>=2)?TRUE:FALSE;
	pButton->EnableWindow(flag);
	return flag;
	}

void CDiscreteDialog::OnSelchangeListPoints() 
// La sélection de la ListBox a changé, updater le bouton Delete
	{
	// TODO: Add your control notification handler code here
	UpdateDeleteButton();
	}

void CDiscreteDialog::OnEndPick(UINT wParam, LONG lParam)
// Rajout d'un point dans la courbe et dans la Listbox
	{
	CPoint* pPoint=(CPoint*)lParam;
	POSITION pos=m_pCurve->AddPoint(*pPoint);
	AddPoint(*pPoint,pos);
	UpdateSortButton();
	UpdateOKButton();
	CUnscanDoc* pDoc=m_pSequence->GetDocument();
	pDoc->UpdateAllViews(NULL);
	}

void CDiscreteDialog::OnChangeEditGraphname() 
	{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateOKButton();
	}

BOOL CDiscreteDialog::OnInitDialog() 
	{
	CConstructionDialog::OnInitDialog();
	FillListBox();
	UpdateSortButton();
	UpdateDeleteButton();
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
	}
	

BOOL CDiscreteDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CConstructionDialog::OnHelpInfo(pHelpInfo);
}
