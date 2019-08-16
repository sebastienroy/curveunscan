// StringResultDumper.cpp: implementation of the CStringResultDumper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "StringResultDumper.h"

#include <Dm/Results.h>

#include <list>
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStringResultDumper::CStringResultDumper(list<CResults*>* pResultList,CString& outString,int maxLines, int columnWidth)
	:	CAbstractResultDumper(pResultList),
		m_OutString(outString),
		m_nMaxLines(maxLines),
		m_nColumnWidth(columnWidth)
{

}

CStringResultDumper::~CStringResultDumper()
{

}

void CStringResultDumper::DumpLine(CString strLine)
{
	strLine+="\r\n";		// Carriage return in the case of an Edit control
	m_OutString+=strLine;
}

void CStringResultDumper::ConstructLine(list<CString> &inStrList, CString &outString)
{
	CString strField;
	int fieldLength;
	list<CString>::iterator iter;
	for(iter=inStrList.begin();iter!=inStrList.end();iter++)
		{
		strField=*iter;
		fieldLength=strField.GetLength();
		if(fieldLength>m_nColumnWidth)
			{
			strField=strField.Left(m_nColumnWidth);
			}
		else if(fieldLength<m_nColumnWidth)
			{
			while(strField.GetLength()<m_nColumnWidth)
				{
				strField+=' ';
				}
			}
		outString+=strField;
		}
}

void CStringResultDumper::DumpResults()
{
	bool trunked=false;

	//--- Get the max result line lines
	int maxLines=0;
	list<CResults*>::iterator iter;
	for(iter=m_ResultsList.begin();iter!=m_ResultsList.end();iter++)
		{
		CResults* aResult=*iter;
		int aMax=aResult->GetResultCount();
		if(aMax>maxLines)
			{
			maxLines=aMax;
			}
		}

	//--- limits the size
	if(maxLines>m_nMaxLines)
		{
		maxLines=m_nMaxLines;
		trunked=true;
		}

	//--- Construct each line
	for(int counter=0;counter<maxLines;counter++)
		{
		list<CString> strLineList;
		CString strLine;
		for(iter=m_ResultsList.begin();iter!=m_ResultsList.end();iter++)
			{
			CResults* aResult=*iter;
			aResult->GetResultLine(counter,strLineList);
			}
		ConstructLine(strLineList,strLine);
		DumpLine(strLine);
		}

	if(trunked)
		{
		CString strMessage;
		strMessage.LoadString(IDS_PREVIEWLIMIT);
		CString msg;
		msg.Format(strMessage,m_nMaxLines);
		DumpLine("");
		DumpLine(msg);
		}

}
