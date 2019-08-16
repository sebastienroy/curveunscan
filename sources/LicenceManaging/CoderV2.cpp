// CoderV2.cpp: implementation of the CCoderV2 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "licencemanaging.h"
#include "CoderV2.h"

#include <Utilities/Unif.h>

#include <md5/md5checksum.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCoderV2::CCoderV2()
:	CCoder()
{

}

CCoderV2::CCoderV2(CString strCodeKey)
:	CCoder(strCodeKey)
{
}

CCoderV2::~CCoderV2()
{

}

CString CCoderV2::GetMd5CodedRegistrationNumber()
{
	// concatenate strings, add something between them to avoid equivalences
	CString strConcat=m_strCurrentSerial+CString("CONCAT")+m_strCurrentName+CString("CONCAT")+m_strCurrentCompany;

	//then, clean the string
	int nIndex;
	CString strSum;
	strConcat.MakeUpper();
	for(nIndex=0;nIndex<strConcat.GetLength();nIndex++)
	{
		char cCurrent=strConcat.GetAt(nIndex);
		bool isNumber=((cCurrent>='0')&&(cCurrent<='9'));
		bool isLetter=((cCurrent>='A')&&(cCurrent<='Z'));
		if(isNumber||isLetter)
		{
			strSum+=cCurrent;
		}
	}
	
	// code it, so it will be easy to change the coding
	strSum=getCodedString(strSum,m_strCodeKey);

	// Get a number depending on it
	CUnif unif;
	int sum=0;

	for(nIndex=0;nIndex<strSum.GetLength();nIndex++)
	{
		for(int counter=0;counter<(int)strSum[nIndex];counter++)
		{
			unif.GetInt();
		}
		sum+=unif.GetInt();
		sum%=CUnif::GetMaxInt();
	}
	while(sum<(CUnif::GetMaxInt()/10))
	{
		sum+=unif.GetInt();
		sum%=CUnif::GetMaxInt();
	}

	CString result;
	result.Format("%d",sum);
	CString strMd5codedResult=CMD5Checksum::GetMD5((BYTE*)(LPCSTR)result,result.GetLength());

	return strMd5codedResult;		
}

CString CCoderV2::getRegistrationNumber(CString strSerial, CString strName, CString strCompany)
{
	// concatenate strings, add something between them to avoid equivalences
	CString strConcat=strSerial+CString("CONCAT")+strName+CString("CONCAT")+strCompany;

	//then, clean the string
	int nIndex;
	CString strSum;
	strConcat.MakeUpper();
	for(nIndex=0;nIndex<strConcat.GetLength();nIndex++)
	{
		char cCurrent=strConcat.GetAt(nIndex);
		bool isNumber=((cCurrent>='0')&&(cCurrent<='9'));
		bool isLetter=((cCurrent>='A')&&(cCurrent<='Z'));
		if(isNumber||isLetter)
		{
			strSum+=cCurrent;
		}
	}
	
	// code it, so it will be easy to change the coding
	strSum=getCodedString(strSum,m_strCodeKey);

	// Get a number depending on it
	CUnif unif;
	int sum=0;

	for(nIndex=0;nIndex<strSum.GetLength();nIndex++)
	{
		for(int counter=0;counter<(int)strSum[nIndex];counter++)
		{
			unif.GetInt();
		}
		sum+=unif.GetInt();
		sum%=CUnif::GetMaxInt();
	}
	while(sum<(CUnif::GetMaxInt()/10))
	{
		sum+=unif.GetInt();
		sum%=CUnif::GetMaxInt();
	}

	CString result;
	result.Format("%d",sum);

	return result;
}
