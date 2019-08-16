// CompleteSequence.h: interface for the CCompleteSequence class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPLETESEQUENCE_H__29FADA63_6ACE_11D4_935E_0080C7A4F675__INCLUDED_)
#define AFX_COMPLETESEQUENCE_H__29FADA63_6ACE_11D4_935E_0080C7A4F675__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Sequence.h"

class CCompleteSequence : public CSequence  
{
public:
	CCompleteSequence(CUnscanView *pView, CUnscanDoc *pDoc);
	BOOL Begin();
	CCompleteSequence();
	virtual ~CCompleteSequence();

protected:
	void EndStep();
	void CancelSequence(CDialog *pDialogue);
};

#endif // !defined(AFX_COMPLETESEQUENCE_H__29FADA63_6ACE_11D4_935E_0080C7A4F675__INCLUDED_)
