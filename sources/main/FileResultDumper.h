// FileResultDumper.h: interface for the CFileResultDumper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILERESULTDUMPER_H__227A8122_3E2A_11D5_935E_8850D1C1C678__INCLUDED_)
#define AFX_FILERESULTDUMPER_H__227A8122_3E2A_11D5_935E_8850D1C1C678__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AbstractResultDumper.h"
#include <list>
using namespace std;

class CResults;

class CFileResultDumper : public CAbstractResultDumper  
{
public:
	CFileResultDumper(list<CResults*>* pResultList,CString filename,char separator);
	virtual ~CFileResultDumper();

public:

protected:
	CStdioFile m_OutFile;
	virtual void ConstructLine(list<CString> &inStrList, CString &outString);
	virtual void DumpLine(CString strLine);
	char m_cSeparator;

};

#endif // !defined(AFX_FILERESULTDUMPER_H__227A8122_3E2A_11D5_935E_8850D1C1C678__INCLUDED_)
