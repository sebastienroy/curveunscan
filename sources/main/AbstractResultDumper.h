// AbstractResultDumper.h: interface for the CAbstractResultDumper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABSTRACTRESULTDUMPER_H__227A8121_3E2A_11D5_935E_8850D1C1C678__INCLUDED_)
#define AFX_ABSTRACTRESULTDUMPER_H__227A8121_3E2A_11D5_935E_8850D1C1C678__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>
using namespace std;

class CResults;

class CAbstractResultDumper  
{
public:
	CAbstractResultDumper(list<CResults*>* pResultList);
	virtual ~CAbstractResultDumper();

public:
	void Dump();

protected:
	CString GetBitmapName();
	void DumpHeader();
	void DumpTitles();
	virtual void DumpResults();
	virtual void ConstructLine(list<CString>& inStrList, CString& outString)=0;
	virtual void DumpLine(CString strLine)=0;
	list<CResults*> m_ResultsList;

};

#endif // !defined(AFX_ABSTRACTRESULTDUMPER_H__227A8121_3E2A_11D5_935E_8850D1C1C678__INCLUDED_)
