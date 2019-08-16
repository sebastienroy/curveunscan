// PreviewDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CurveUnscan.h"
#include "PreviewDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPreviewDialog dialog


CPreviewDialog::CPreviewDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPreviewDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPreviewDialog)
	m_PreviewString = _T("");
	//}}AFX_DATA_INIT
}


void CPreviewDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPreviewDialog)
	DDX_Text(pDX, IDC_PREVIEW_EDIT, m_PreviewString);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPreviewDialog, CDialog)
	//{{AFX_MSG_MAP(CPreviewDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPreviewDialog message handlers

