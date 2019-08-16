// Sequence.h: interface for the CSequence class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEQUENCE_H__C1CFB5E1_4620_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_SEQUENCE_H__C1CFB5E1_4620_11D4_935E_0080C7A4F675__INCLUDED_

#include <afxtempl.h>
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef enum STEP
	{
	begin,
	openbitmap,
	xaxe,
	yaxe,
	xdraw,
	xscale,
	ydraw,
	yscale,
	curvekind,
	limits,
	genesis,
	handmodif,
	discrete,
	densitometry,
	spline,
	end
	}step;

class CUnscanView;
class CUnscanDoc;
class CCurve;
class CCoordSyst;
class CConstructionDialog;

class CSequence  
{
public:
	CCoordSyst* GetCoordSyst();
	CUnscanDoc* GetDocument();
	CUnscanView* GetView();
	void SetActWndPosition(CPoint point);
	CPoint GetPrevWndPosition();
	virtual BOOL Begin();
	CSequence(CUnscanView* pView,CUnscanDoc* pDoc,CCoordSyst* pCoord=NULL,CCurve* pCurve=NULL);
	virtual void CancelSequence(CDialog* pDialogue);
	void NextStep(int next);
	CSequence();
	virtual ~CSequence();

protected:
	void CancelCurveSequence(CDialog *pDialogue);
	void YAxisStep();
	void XAxisStep();
	bool m_bIsCurveCreation;
	void OpenBitmapStep();
	void CurveKindStep();
	void HandModificationStep();
	void GenesisStep();
	void LimitsStep();
	void DiscreteStep();
	void SetPosition();
	void UpdateOKPrevious(CConstructionDialog* pDialog);
	void DensitometryStep();
	void SplineStep();
	virtual void EndStep();

protected:
	virtual void EndStepCurve();
	CPoint m_WindowPosition;
	CCoordSyst* m_pBackCoordSyst;
	CCurve* m_pBackCurve;
	CCurve* m_pCurve;
	CCoordSyst* m_pCoordSyst;
	int m_CurrentStep;
	CArray<STEP,STEP> m_StepArray;
	CUnscanView* m_pView;
	CUnscanDoc* m_pDoc;
	CConstructionDialog* m_pActiveDialog;
};

#endif // !defined(AFX_SEQUENCE_H__C1CFB5E1_4620_11D4_935E_0080C7A4F675__INCLUDED_)
