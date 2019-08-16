// ColoredButton.cpp : implementation file
//

#include "stdafx.h"
//#include "CurveUnscan.h"
#include "ColoredButton.h"
#include "plpixel32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColoredButton

CColoredButton::CColoredButton()
{
}

CColoredButton::~CColoredButton()
{
}


BEGIN_MESSAGE_MAP(CColoredButton, CButton)
	//{{AFX_MSG_MAP(CColoredButton)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColoredButton message handlers

PLPixel32 CColoredButton::GetColor()
{
	return m_Color;
}

void CColoredButton::SetColor(PLPixel32 color)
{
	m_Color=color;
	RedrawWindow();
}

void CColoredButton::OnPaint() 
{
	CButton::OnPaint();	// default draw

	CDC* pDC=GetWindowDC();
	
	COLORREF crColor=m_Color.GetB();
	crColor<<=8;
	crColor+=m_Color.GetG();
	crColor<<=8;
	crColor+=m_Color.GetR();

	CRect rect;
	GetWindowRect(&rect);
	rect-=rect.TopLeft();	// the origin is now (0,0)

	CRect rectCadre(2,2,2,2);	// recadrage pour avoir la bordure
	rect-=rectCadre;

	CBrush brush(crColor);
	pDC->FillRect(&rect,&brush);

	ReleaseDC(pDC);
}
