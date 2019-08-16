// StringResultDumper.h: interface for the CStringResultDumper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGRESULTDUMPER_H__227A8124_3E2A_11D5_935E_8850D1C1C678__INCLUDED_)
#define AFX_STRINGRESULTDUMPER_H__227A8124_3E2A_11D5_935E_8850D1C1C678__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AbstractResultDumper.h"
#include <list>
using namespace std;

class CResults;

class CStringResultDumper : public CAbstractResultDumper  
{
public:
	CStringResultDumper(list<CResults*>* pResultList,CString& outString,int maxLines, int columnWidth);
	virtual ~CStringResultDumper();

public:
	virtual void DumpResults();

protected:
	virtual void ConstructLine(list<CString> &inStrList, CString &outString);
	virtual void DumpLine(CString strLine);

	// Attributes
protected:
	CString& m_OutString;
	int m_nMaxLines;
	int m_nColumnWidth;
};

#endif // !defined(AFX_STRINGRESULTDUMPER_H__227A8124_3E2A_11D5_935E_8850D1C1C678__INCLUDED_)
