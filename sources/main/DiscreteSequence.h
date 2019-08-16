// DiscreteSequence.h: interface for the CDiscreteSequence class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISCRETESEQUENCE_H__7CE411C0_5E16_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_DISCRETESEQUENCE_H__7CE411C0_5E16_11D4_935E_0080C7A4F675__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Sequence.h"
class CUnscanView;
class CUnscanDoc;
class CCoordSyst;
class CDiscreteCurve;

class CDiscreteSequence : public CSequence  
{
public:
	CDiscreteSequence();
	CDiscreteSequence(CUnscanView *pView,
						CUnscanDoc *pDoc,
						CCoordSyst *pCoord,
						CDiscreteCurve *pCurve=NULL);
	virtual ~CDiscreteSequence();

public:
	virtual BOOL Begin();
	virtual void CancelSequence(CDialog *pDialogue);

protected:
	virtual void EndStep();
};

#endif // !defined(AFX_DISCRETESEQUENCE_H__7CE411C0_5E16_11D4_935E_0080C7A4F675__INCLUDED_)
