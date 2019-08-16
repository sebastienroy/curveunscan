// FileResultDumper.cpp: implementation of the CFileResultDumper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "FileResultDumper.h"
#include "Utilities/UnscanException.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileResultDumper::CFileResultDumper(list<CResults*>* pResultList,CString filename,char separator)
:CAbstractResultDumper(pResultList),m_cSeparator(separator)
{
	if(!m_OutFile.Open(filename,CFile::modeCreate|CFile::modeWrite|CFile::typeText))
		{
		CString msg;
		msg.LoadString(IDS_CANNOT_OPEN_TO_WRITE);
		throw CUnscanException(msg);
		}

}

CFileResultDumper::~CFileResultDumper()
{

}

void CFileResultDumper::DumpLine(CString strLine)
{
	try
		{
		strLine+="\n";
		m_OutFile.WriteString(strLine);
		}
	catch(...)
		{
		CString msg;
		msg.LoadString(IDS_CANNOT_WRITE_INTO_FILE);
		throw CUnscanException(msg);
		}
}

void CFileResultDumper::ConstructLine(list<CString> &inStrList, CString &outString)
{
	list<CString>::iterator iter;
	for(iter=inStrList.begin();iter!=inStrList.end();iter++)
		{
		outString+=*iter;
		outString+=m_cSeparator;
		}

}
