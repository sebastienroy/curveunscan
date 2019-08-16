#if !defined(AFX_CONTINUOUSADVOPTDLG_H__568B11A5_3C81_11D5_935E_BA3BA588DF78__INCLUDED_)
#define AFX_CONTINUOUSADVOPTDLG_H__568B11A5_3C81_11D5_935E_BA3BA588DF78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ContinuousAdvOptDlg.h : header file
//

#include "Utilities/ColoredButton.h"

class CContinuousCurve;
class CGenesisDialog;

/////////////////////////////////////////////////////////////////////////////
// CContinuousAdvOptDlg dialog

class CContinuousAdvOptDlg : public CDialog
{
// Construction
public:
	CContinuousAdvOptDlg(CContinuousCurve* pCurve,CGenesisDialog* pGenesisDlg,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CContinuousAdvOptDlg)
	enum { IDD = IDD_CONTINUOUSOPTION_DIALOG };
	CSliderCtrl	m_GreenSlider;
	CSliderCtrl	m_RedSlider;
	CSliderCtrl	m_BlueSlider;
	CColoredButton	m_ColoredButton;
	BOOL	m_bPickColor;
	int		m_nBlue;
	int		m_nGreen;
	int		m_nRed;
	int		m_nThickWidth;
	int		m_ThickKindRadio;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContinuousAdvOptDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool ActionConfirmed();
	CGenesisDialog* m_pParent;
	bool DataValidation();
	bool m_bModified;
	void UpdateColorButton();
	CContinuousCurve* m_pCurve;

	// Generated message map functions
	//{{AFX_MSG(CContinuousAdvOptDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnReleasedcaptureSliderRed(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderGreen(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderBlue(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndPick(UINT wParam, LONG lParam);
	afx_msg void OnChangeEditRed();
	afx_msg void OnChangeEditGreen();
	afx_msg void OnChangeEditBlue();
	afx_msg void OnRadioFlatThickness();
	afx_msg void OnRadioSmartThickness();
	virtual void OnOK();
	afx_msg void OnChangeEditThickRange();
	virtual void OnCancel();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnCheckPickcolor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTINUOUSADVOPTDLG_H__568B11A5_3C81_11D5_935E_BA3BA588DF78__INCLUDED_)
