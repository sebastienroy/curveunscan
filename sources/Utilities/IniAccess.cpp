// IniAccess.cpp: implementation of the IniAccess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IniAccess.h"

#include "Tokenizer.h"

#include <strstream>
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IniAccess::IniAccess()
{

}

IniAccess::~IniAccess()
{

}

CString IniAccess::GetString(const char *strSection, const char *strEntry, const char *strDefault, const char *strFilename)
{
	char *buffer=NULL;
	int bufferSize=512;
	bool overflow=true;
	CString strResult;
	do
	{
		buffer=new char[bufferSize];
		int readSize=GetPrivateProfileString(strSection,strEntry,strDefault,buffer,bufferSize,strFilename);
		overflow=(readSize==(bufferSize-2));
		if(!overflow)
		{
			strResult=CString(buffer,readSize);
		}
		else
		{
			bufferSize*=2;
		}
		delete buffer;
		buffer=NULL;
	}
	while(overflow);

	return strResult;
}

int IniAccess::GetInt(const char *strSection, const char *strEntry, int nDefault, const char *strFilename)
{
	return GetPrivateProfileInt(strSection,strEntry,nDefault,strFilename);
}

void IniAccess::WriteString(const char *strSection, const char *strEntry, const char *strValue, const char *strFilename)
{
	WritePrivateProfileString(strSection,strEntry,strValue,strFilename);
}


void IniAccess::WriteInt(const char *strSection, const char *strEntry, int nValue, const char *strFilename)
{
	ostrstream buffer;
	buffer << nValue << ends;
	WritePrivateProfileString(strSection,strEntry,buffer.str(),strFilename);
}

void IniAccess::GetSections(list<CString> &outSectionList, const char *strFilename)
{
	outSectionList.clear();

	char *buffer=NULL;
	int bufferSize=512;	
	bool overflow=true;
	CString strResult;
	do
	{
		buffer=new char[bufferSize];
		int readSize=GetPrivateProfileSectionNames(buffer,bufferSize,strFilename);
		overflow=(readSize==(bufferSize-2));
		if(!overflow)
		{
			strResult=CString(buffer,readSize);
		}
		else
		{
			bufferSize*=2;
		}
		delete buffer;
		buffer=NULL;
	}
	while(overflow);

	// tokenize
	CTokenizer token(strResult);
	CString strSection;
	while(!(strSection=token(CString("\0",1))).IsEmpty())
	{
		outSectionList.push_back(strSection);
	}
}

void IniAccess::GetEntries(const char *strSection, list<CString> &outEntriesList, const char *strFilename)
{
	outEntriesList.clear();

	char *buffer=NULL;
	int bufferSize=512;	
	bool overflow=true;
	CString strResult;
	do
	{
		buffer=new char[bufferSize];
		int readSize=GetPrivateProfileString(strSection,NULL,"",buffer,bufferSize,strFilename);
		overflow=(readSize==(bufferSize-2));
		if(!overflow)
		{
			strResult=CString(buffer,readSize);
		}
		else
		{
			bufferSize*=2;
		}
		delete buffer;
		buffer=NULL;
	}
	while(overflow);

	// tokenize
	CTokenizer token(strResult);
	CString strEntry;
	while(!(strEntry=token(CString("\0",1))).IsEmpty())
	{
		outEntriesList.push_back(strEntry);
	}
}

