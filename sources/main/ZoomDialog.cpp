// ZoomDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CurveUnscan.h"
#include "UnscanView.h"
#include "ZoomCombo.h"
#include "ZoomDialog.h"
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZoomDialog dialog


CZoomDialog::CZoomDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CZoomDialog::IDD, pParent),
		m_pView(static_cast<CUnscanView*>(pParent))
	{
	//{{AFX_DATA_INIT(CZoomDialog)
	//}}AFX_DATA_INIT*/
	}

void CZoomDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZoomDialog)
	DDX_Control(pDX, IDC_COMBO_ZOOM, m_ZoomCombo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZoomDialog, CDialog)
	//{{AFX_MSG_MAP(CZoomDialog)
	ON_CBN_EDITCHANGE(IDC_COMBO_ZOOM, OnEditchangeComboZoom)
	ON_CBN_SELCHANGE(IDC_COMBO_ZOOM, OnSelchangeComboZoom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZoomDialog message handlers

BOOL CZoomDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	int nZoom=m_pView->GetZoom();
	SetZoomValue(nZoom);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// called when the user changes manually the field
void CZoomDialog::OnEditchangeComboZoom() 
{
	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
	CString text;
	m_ZoomCombo.GetWindowText(text);
	char aChar;
	for(int counter=0;counter<text.GetLength();counter++)
		{
		aChar=text[counter];
		if( (aChar<'0')||(aChar>'9') )
			{
			text.Delete(counter);
			counter--;
			}
		}
	m_ZoomCombo.SetWindowText(text);
}

void CZoomDialog::OnSelchangeComboZoom() 
{
	if(GetFocus()!=&m_ZoomCombo)
		{
		return;
		}
	int nZoom;

	int itemIndex=m_ZoomCombo.GetCurSel();
	CString text;
	m_ZoomCombo.GetLBText(itemIndex,text);
	CString strFitted;
	strFitted.LoadString(IDS_ZOOMFIT);
	if(strFitted==text)
		{
		nZoom=-1;
		}
	else
		{
		nZoom=atoi(text);
		}
	m_pView->SetZoomValue(nZoom);
}

void CZoomDialog::SetZoomValue(int nZoom)
{
	CString strComboText;
	if(nZoom>0)
		{
		strComboText.Format("%d",nZoom);
		}
	else
		{
		strComboText.LoadString(IDS_ZOOMFIT);
		}
	int itemIndex=m_ZoomCombo.FindStringExact(-1,strComboText);
	m_ZoomCombo.SetCurSel(itemIndex);
}
