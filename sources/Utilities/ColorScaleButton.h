#if !defined(AFX_COLORSCALEBUTTON_H__E9D622C5_1A57_47CB_BA88_4FEEFD1DB3B9__INCLUDED_)
#define AFX_COLORSCALEBUTTON_H__E9D622C5_1A57_47CB_BA88_4FEEFD1DB3B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorScaleButton.h : header file
//

#include "plpixel32.h"


/////////////////////////////////////////////////////////////////////////////
// CColorScaleButton window

class CColorScaleButton : public CButton
{
// Construction
public:
	CColorScaleButton();

// Attributes
public:

// Operations
public:
	const PLPixel32& getTopColor() const { return m_TopColor; }
	const PLPixel32& getBottomColor() const { return m_BottomColor; }

	void SetTopColor(const PLPixel32& color) {	m_TopColor=color; 
												RedrawWindow(); }
	void SetBottomColor(const PLPixel32& color) {	m_BottomColor=color; 
													RedrawWindow(); }
	void SetColors(const PLPixel32& topColor, const PLPixel32& bottomColor)
		{	
			m_TopColor=topColor;
			m_BottomColor=bottomColor;
			RedrawWindow();
		}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorScaleButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	CColorScaleButton(const PLPixel32& topColor, const PLPixel32& bottomColor);
	virtual ~CColorScaleButton();

	// Generated message map functions
protected:
	PLPixel32 m_BottomColor;
	PLPixel32 m_TopColor;
	//{{AFX_MSG(CColorScaleButton)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORSCALEBUTTON_H__E9D622C5_1A57_47CB_BA88_4FEEFD1DB3B9__INCLUDED_)
