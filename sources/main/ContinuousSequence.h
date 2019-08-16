// ContinuousSequence.h: interface for the CContinuousSequence class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTINUOUSSEQUENCE_H__EA02B160_6214_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_CONTINUOUSSEQUENCE_H__EA02B160_6214_11D4_935E_0080C7A4F675__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Sequence.h"
class CUnscanView;
class CUnscanDoc;
class CCoordSyst;
class CContinuousCurve;

class CContinuousSequence : public CSequence  
{
public:
	void CancelSequence(CDialog *pDialogue);
	BOOL Begin();
	CContinuousSequence(CUnscanView *pView, CUnscanDoc *pDoc, CCoordSyst *pCoord, CContinuousCurve *pCurve=NULL);
	CContinuousSequence();
	virtual ~CContinuousSequence();

protected:
	void EndStep();
};

#endif // !defined(AFX_CONTINUOUSSEQUENCE_H__EA02B160_6214_11D4_935E_0080C7A4F675__INCLUDED_)
