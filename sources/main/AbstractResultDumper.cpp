// AbstractResultDumper.cpp: implementation of the CAbstractResultDumper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "AbstractResultDumper.h"
#include <list>
using namespace std;
#include <Dm/Results.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAbstractResultDumper::CAbstractResultDumper(list<CResults*>* pResultList)
	: m_ResultsList(*pResultList)
{
	
}

CAbstractResultDumper::~CAbstractResultDumper()
{

}

void CAbstractResultDumper::DumpLine(CString strLine)
{

}

void CAbstractResultDumper::ConstructLine(list<CString> &inStrList, CString &outString)
{

}

void CAbstractResultDumper::DumpResults()
{
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

}

void CAbstractResultDumper::DumpTitles()
{
	//--- Get the max header lines
	int maxLines=0;
	list<CResults*>::iterator iter;
	for(iter=m_ResultsList.begin();iter!=m_ResultsList.end();iter++)
		{
		CResults* aResult=*iter;
		int aMax=aResult->GetLegendCount();
		if(aMax>maxLines)
			{
			maxLines=aMax;
			}
		}
	//--- Construct each line
	for(int counter=0;counter<maxLines;counter++)
		{
		list<CString> strLineList;
		CString strLine;
		for(iter=m_ResultsList.begin();iter!=m_ResultsList.end();iter++)
			{
			CResults* aResult=*iter;
			int currentLineCount=aResult->GetLegendCount();
			int nLine=currentLineCount-maxLines+counter;
			aResult->GetLegendLine(nLine,strLineList);
			}
		ConstructLine(strLineList,strLine);
		DumpLine(strLine);
		}
}

void CAbstractResultDumper::DumpHeader()
{
	CString strHeaderLine;
	strHeaderLine.LoadString(IDS_RESULTHEADER1);
	DumpLine(strHeaderLine);
	strHeaderLine.LoadString(IDS_RESULTHEADER2);
	DumpLine(strHeaderLine);
	strHeaderLine.LoadString(IDS_RESULTHEADER3);
	DumpLine(strHeaderLine);
	DumpLine(GetBitmapName());
	DumpLine("");
}

void CAbstractResultDumper::Dump()
{
	DumpHeader();
	DumpTitles();
	DumpResults();
}

CString CAbstractResultDumper::GetBitmapName()
{
	if(m_ResultsList.size()>0)
		{
		CResults* pResult=m_ResultsList.front();
		return pResult->GetBitmapName();
		}
	else
		{
		return CString("");
		}
}
