#if !defined(AFX_COLOREDBUTTON_H__568B11A6_3C81_11D5_935E_BA3BA588DF78__INCLUDED_)
#define AFX_COLOREDBUTTON_H__568B11A6_3C81_11D5_935E_BA3BA588DF78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColoredButton.h : header file
//

#include "plpixel32.h"


/////////////////////////////////////////////////////////////////////////////
// CColoredButton window

class CColoredButton : public CButton
{
// Construction
public:
	CColoredButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColoredButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetColor(PLPixel32 color);
	PLPixel32 GetColor();
	virtual ~CColoredButton();

	// Generated message map functions
protected:
	PLPixel32 m_Color;
	//{{AFX_MSG(CColoredButton)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLOREDBUTTON_H__568B11A6_3C81_11D5_935E_BA3BA588DF78__INCLUDED_)
