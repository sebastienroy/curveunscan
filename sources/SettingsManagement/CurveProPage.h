#if !defined(AFX_CURVEPROPAGE_H__87DCAC57_1AC4_4A46_9378_55DA27CDC34E__INCLUDED_)
#define AFX_CURVEPROPAGE_H__87DCAC57_1AC4_4A46_9378_55DA27CDC34E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CurveProPage.h : header file
//

#include "../Utilities/ColoredButton.h"
#include "PLPixel32.h"

/////////////////////////////////////////////////////////////////////////////
// CCurveProPage dialog

class CCurveProPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CCurveProPage)

// Construction
public:
	PLPixel32 m_BlackColor;
	PLPixel32 m_DefaultBlackColor;
	int		m_nDefaultThicknessAlgo;
	int		m_nDefaultSmartAlgoRange;
	int		m_nDefaultFollow;
	int		m_nDefaultDashMaxDist;
	int		m_nDefaultDashed;

	CCurveProPage();
	~CCurveProPage();

// Dialog Data
	//{{AFX_DATA(CCurveProPage)
	enum { IDD = IDD_PROPPAGE_CURVE };
	CSpinButtonCtrl	m_SpinThickRange;
	CSpinButtonCtrl	m_SpinDashMax;
	CColoredButton	m_BlackLevelButton;
	int		m_nThicknessAlgo;
	int		m_nSmartAlgoRange;
	int		m_nFollow;
	int		m_nDashMaxDist;
	int		m_nDashed;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCurveProPage)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCurveProPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonBlackcolor();
	afx_msg void OnButtonCurveDefaults();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURVEPROPAGE_H__87DCAC57_1AC4_4A46_9378_55DA27CDC34E__INCLUDED_)
