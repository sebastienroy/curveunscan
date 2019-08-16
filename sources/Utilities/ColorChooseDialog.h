#if !defined(AFX_COLORCHOOSEDIALOG_H__C442D0BC_D40E_409E_8593_F277E7278E15__INCLUDED_)
#define AFX_COLORCHOOSEDIALOG_H__C442D0BC_D40E_409E_8593_F277E7278E15__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorChooseDialog.h : header file
//

#include "../Utilities/ColoredButton.h"
#include "../Utilities/Resource.h"
#include "PLPixel32.h"

/////////////////////////////////////////////////////////////////////////////
// CColorChooseDialog dialog

class CColorChooseDialog : public CDialog
{
// Construction
public:
	PLPixel32 GetColor() const;
	void SetColor(const PLPixel32 &color);
	PLPixel32 m_Color;
	CColorChooseDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CColorChooseDialog)
	enum { IDD = IDD_DIALOG_COLORCHOOSE };
	CColoredButton	m_ButtonColor;
	int		m_nBlue;
	int		m_nGreen;
	int		m_nRed;
	int		m_nBlueSlider;
	int		m_nGreenSlider;
	int		m_nRedSlider;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorChooseDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int IntoRange(int nValue) const;

	// Generated message map functions
	//{{AFX_MSG(CColorChooseDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditBlue();
	afx_msg void OnChangeEditGreen();
	afx_msg void OnChangeEditRed();
	afx_msg void OnReleasedcaptureSliderBlue(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderGreen(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderRed(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORCHOOSEDIALOG_H__C442D0BC_D40E_409E_8593_F277E7278E15__INCLUDED_)
