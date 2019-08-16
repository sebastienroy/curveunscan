// SplineSequence.h: interface for the CSplineSequence class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLINESEQUENCE_H__D0AD77FA_C3BE_44BF_912B_08636AD72654__INCLUDED_)
#define AFX_SPLINESEQUENCE_H__D0AD77FA_C3BE_44BF_912B_08636AD72654__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Sequence.h"

class CUnscanView;
class CUnscanDoc;
class CCoordSyst;
class CSplineCurve;

class CSplineSequence : public CSequence  
{
public:
	virtual void EndStep();
	virtual void CancelSequence(CDialog *pDialogue);
	virtual BOOL Begin();
	CSplineSequence(CUnscanView *pView, CUnscanDoc *pDoc, CCoordSyst *pCoord, CSplineCurve *pCurve=NULL);
	CSplineSequence();
	virtual ~CSplineSequence();

protected:
//	CSplineCurve *m_pCurve;

};

#endif // !defined(AFX_SPLINESEQUENCE_H__D0AD77FA_C3BE_44BF_912B_08636AD72654__INCLUDED_)
