#if !defined(AFX_DENSITOPROPAGE_H__D6676D3D_88CB_4735_8D56_6E70AA704CA4__INCLUDED_)
#define AFX_DENSITOPROPAGE_H__D6676D3D_88CB_4735_8D56_6E70AA704CA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DensitoProPage.h : header file
//

#include "Utilities/ColoredButton.h"
#include "Utilities/ColorScaleButton.h"
#include "ValueEdit.h"

#include "Dm/ColorScale.h"

/////////////////////////////////////////////////////////////////////////////
// CDensitoProPage dialog

class CDensitoProPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CDensitoProPage)

// Construction
public:
	const CColorScale& GetColorScale() const;
	void SetColorScale(const CColorScale &colorScale);
	CDensitoProPage();
	~CDensitoProPage();

// Dialog Data
	//{{AFX_DATA(CDensitoProPage)
	enum { IDD = IDD_PROPPAGE_DENSITO };
	CValueEdit	m_TopValueEdit;
	CValueEdit	m_BottomValueEdit;
	CColoredButton	m_TopColorButton;
	CColorScaleButton	m_ColorScaleCtrl;
	CColoredButton	m_BottomColorButton;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDensitoProPage)
	public:
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool CheckScaleValidity();
	CColorScale m_ColorScale;
	// Generated message map functions
	//{{AFX_MSG(CDensitoProPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnTopcolorButton();
	afx_msg void OnBottomcolorButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DENSITOPROPAGE_H__D6676D3D_88CB_4735_8D56_6E70AA704CA4__INCLUDED_)
