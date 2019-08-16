// DensitoPreviewWnd.cpp : implementation file
//

#include "stdafx.h"
#include "CurveUnscan.h"
#include "DensitoPreviewWnd.h"

#include <Dm/DensityCurve.h>
#include <Dm/ColorScale.h>
#include <Dm/CoordSyst.h>
#include <Dm/LogicPoint.h>

#include <vector>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CDensitoPreviewWnd

CDensitoPreviewWnd::CDensitoPreviewWnd(CWnd *pParent,CDensityCurve* pCurve)
:	m_pCurve(pCurve),
	m_pParent(pParent),
	m_bParentClosed(false)
{
	CBrush brush(0x00ffffff);
	CString strClassName=AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,0,(HBRUSH)brush);
	CString strWndName;
	strWndName.LoadString(IDS_DENSITO_PREVIEW_TITLE);

	/*
	CreateEx(0,
		strClassName,
		strWndName,
		WS_OVERLAPPED|WS_SYSMENU|WS_CAPTION|WS_BORDER,
		50,50,600,300,
		NULL,
		NULL);
*/


	CreateEx(WS_EX_CLIENTEDGE|WS_EX_DLGMODALFRAME|WS_EX_OVERLAPPEDWINDOW,
		strClassName,
		strWndName,
		WS_OVERLAPPEDWINDOW|WS_BORDER,
		50,50,600,300,
		NULL,
		NULL);
		
}

CDensitoPreviewWnd::~CDensitoPreviewWnd()
{
}


BEGIN_MESSAGE_MAP(CDensitoPreviewWnd, CWnd)
	//{{AFX_MSG_MAP(CDensitoPreviewWnd)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDensitoPreviewWnd message handlers

void CDensitoPreviewWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect clientRect;
	GetClientRect(&clientRect);

	static int leftMargin=80;
	static int bottomMargin=20;
	static int vertTickMargin=20;
	static int horzTickMargin=50;
	static int tickLength=4;

	int drawWidth=clientRect.Width()-(leftMargin+2*horzTickMargin);
	int drawHeight=clientRect.Height()-(bottomMargin+2*vertTickMargin);

	if( (drawWidth<30)
		||(drawHeight<30) )
	{
		return;
	}

	// legend text
	// x
	CPoint ptFrom=m_pCurve->GetFromPoint();
	CLogicPoint lFrom=m_pCurve->GetCoordSyst()->ToLogic(ptFrom);
	CString strFrom;
	strFrom.Format("x = %g ; y = %g",lFrom.x,lFrom.y);

	CPoint ptTo=m_pCurve->GetToPoint();
	CLogicPoint lTo=m_pCurve->GetCoordSyst()->ToLogic(ptTo);
	CString strTo;
	strTo.Format("x = %g ; y = %g",lTo.x,lTo.y);

	// y
	double minValue=m_pCurve->GetColorScale()->GetBottomValue();
	double maxValue=m_pCurve->GetColorScale()->GetTopValue();
	if(minValue>maxValue)
	{
		double temp=minValue;
		minValue=maxValue;
		maxValue=temp;
	}
	CString strMinValue;
	strMinValue.Format("%g",minValue);
	CString strMaxValue;
	strMaxValue.Format("%g",maxValue);


	CFont font;
	font.CreateFont(13,		// height
					0,		// width 
					0,		// escapement
					0,		// orientation
					FW_LIGHT,	// weight
					0,		// italic
					0,		// underlined
					0,		// strike out
					ANSI_CHARSET,	// char set
					OUT_DEFAULT_PRECIS,		// draw precision
					CLIP_DEFAULT_PRECIS,	// clipping precision
					DEFAULT_QUALITY,		// quality
					FF_SWISS,		// ??
					"Arial");

	CFont *pOldFont=dc.SelectObject(&font);


	// draw axes
	CPoint origin(clientRect.left+leftMargin,clientRect.bottom-bottomMargin);
	dc.MoveTo(origin);
	dc.LineTo(origin.x,clientRect.top+2);
	dc.MoveTo(origin);
	dc.LineTo(clientRect.right-2,origin.y);

	// draw ticks
	CPoint tickOrigin;

	// first point
	dc.SetTextAlign(TA_CENTER|TA_TOP);
	tickOrigin.x=origin.x+horzTickMargin;
	tickOrigin.y=origin.y;
	dc.MoveTo(tickOrigin);
	dc.LineTo(tickOrigin.x,tickOrigin.y+tickLength);
	dc.TextOut(tickOrigin.x,tickOrigin.y+tickLength,strFrom);
	// last point
	tickOrigin.x=clientRect.right-horzTickMargin;
	dc.MoveTo(tickOrigin);
	dc.LineTo(tickOrigin.x,tickOrigin.y+tickLength);
	dc.SetTextAlign(TA_RIGHT|TA_TOP);
	dc.TextOut(clientRect.right-2,tickOrigin.y+tickLength,strTo);

	// top value
	dc.SetTextAlign(TA_RIGHT|TA_BASELINE);
	tickOrigin.x=origin.x;
	tickOrigin.y=clientRect.top+vertTickMargin;
	dc.MoveTo(tickOrigin);
	dc.LineTo(tickOrigin.x-tickLength,tickOrigin.y);
	dc.TextOut(tickOrigin.x-tickLength,tickOrigin.y,strMaxValue);
	// bottom value
	tickOrigin.y=clientRect.bottom-bottomMargin-vertTickMargin;
	dc.MoveTo(tickOrigin);
	dc.LineTo(tickOrigin.x-tickLength,tickOrigin.y);
	dc.TextOut(tickOrigin.x-tickLength,tickOrigin.y,strMinValue);

	CPoint drawOrigin;
	drawOrigin.x=clientRect.left+leftMargin+horzTickMargin;
	drawOrigin.y=clientRect.bottom-bottomMargin-vertTickMargin;

	CSize drawSize;
	drawSize.cx=drawWidth;
	drawSize.cy=drawHeight;

	// draw graphic

	const vector<double> &valueVect=m_pCurve->GetValueArray();

	int nx=drawOrigin.x;
	int ny=drawOrigin.y-GetPixelOffset(valueVect[0],minValue,maxValue,drawSize.cy);
	dc.MoveTo(drawOrigin.x,ny);

	for(int nCounter=1;nCounter<drawSize.cx;nCounter++)
	{
		// get index
		double relCounter=(double)nCounter/(double)drawSize.cx;
		int valueIndex=(double)(valueVect.size()-1)*relCounter;
		nx=nCounter+drawOrigin.x;
		ny=drawOrigin.y-GetPixelOffset(valueVect[valueIndex],minValue,maxValue,drawSize.cy);
		dc.LineTo(nx,ny);
	}

	

	dc.SelectObject(pOldFont);
	// Do not call CWnd::OnPaint() for painting messages
}

void CDensitoPreviewWnd::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
//	m_pParent->SendMessage(WM_PREVIEWCLOSED);
	
	CWnd::OnClose();
}

void CDensitoPreviewWnd::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	if(!m_bParentClosed)
	{
		m_pParent->SendMessage(WM_PREVIEWCLOSED);
	}

	delete this;
	
//	CWnd::PostNcDestroy();
}

int CDensitoPreviewWnd::GetPixelOffset(double value, double min, double max, int size) const
{
	double diff=max-min;
	double delta=value-min;
	double relOffset=delta/diff;
	return (int)((double)size*relOffset);
}

void CDensitoPreviewWnd::ParentClosed()
{
	m_bParentClosed=true;
}
