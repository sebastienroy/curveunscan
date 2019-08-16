// ColorScaleButton.cpp : implementation file
//

#include "stdafx.h"
//#include "CurveUnscan.h"
#include "ColorScaleButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorScaleButton

CColorScaleButton::CColorScaleButton()
:	m_TopColor(0,0,0),
	m_BottomColor(255,255,255)
{
}

CColorScaleButton::~CColorScaleButton()
{
}

CColorScaleButton::CColorScaleButton(const PLPixel32 &topColor, const PLPixel32 &bottomColor)
:	m_TopColor(topColor),
	m_BottomColor(bottomColor)
{

}

BEGIN_MESSAGE_MAP(CColorScaleButton, CButton)
	//{{AFX_MSG_MAP(CColorScaleButton)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorScaleButton message handlers


void CColorScaleButton::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CButton::OnPaint() for painting messages

	CDC* pDC=GetWindowDC();

	int topRed=m_TopColor.GetR();
	int topGreen=m_TopColor.GetG();
	int topBlue=m_TopColor.GetB();
	
	int bottomRed=m_BottomColor.GetR();
	int bottomGreen=m_BottomColor.GetG();
	int bottomBlue=m_BottomColor.GetB();

	CRect wndRect;
	GetWindowRect(&wndRect);
	wndRect-=wndRect.TopLeft();	// the origin is now (0,0)
	int nWidth=wndRect.Width();
	int nHeight=wndRect.Height();

	for(int nLine=0;nLine<nHeight;nLine++)
	{
		// calculate the line to draw (a rectangle in fact)
		CRect rect(0,nLine,nWidth,nLine+1);

		// calculate the current color
		double dCoef=(double)nLine/(double)nHeight;
		int nRed=topRed+(int)(dCoef*(bottomRed-topRed));
		int nGreen=topGreen+(int)(dCoef*(bottomGreen-topGreen));
		int nBlue=topBlue+(int)(dCoef*(bottomBlue-topBlue));

		COLORREF crColor=nBlue;
		crColor<<=8;
		crColor+=nGreen;
		crColor<<=8;
		crColor+=nRed;

		// draw
		CBrush brush(crColor);
		pDC->FillRect(&rect,&brush);
	}

	ReleaseDC(pDC);
}
