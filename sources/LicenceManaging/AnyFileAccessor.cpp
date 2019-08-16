// AnyFileAccessor.cpp: implementation of the CAnyFileAccessor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "licencemanaging.h"
#include "AnyFileAccessor.h"

#include "Utilities/Tools.h"

#include <iostream>
#include <fstream>
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAnyFileAccessor* CAnyFileAccessor::m_pInstance=NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAnyFileAccessor::CAnyFileAccessor(const char *rootDir)
:	m_strRootdir(rootDir)
{
	CTools::GetAllSubdirectories(m_strRootdir,m_SubDirList);

}

CAnyFileAccessor::~CAnyFileAccessor()
{

}

CAnyFileAccessor* CAnyFileAccessor::GetInstance()
{
	if(NULL==m_pInstance)
	{
		char buffer[256];
		GetWindowsDirectory(buffer,256);
		m_pInstance=new CAnyFileAccessor(buffer);
	}
	return m_pInstance;
}

void CAnyFileAccessor::AccessToSomeFiles()
{
	
	// choose some paths
	srand( (unsigned)time( NULL ) );
	list<int> indexList;
	for(int nCounter=0;nCounter<20;nCounter++)
	{
		int nChosenIndex=rand();
		nChosenIndex%=m_SubDirList.size();
		indexList.push_back(nChosenIndex);
	}
	indexList.sort();

	list<int>::iterator indexIter=indexList.begin();
	list<CString>::iterator pathIter=m_SubDirList.begin();
	list<CString> chosenPathList;
	int pathIndex=0;

	for(;indexIter!=indexList.end();indexIter++)
	{
		int currentIndex=*indexIter;
		while(pathIndex<currentIndex)
		{
			pathIter++;
			pathIndex++;
		}
		chosenPathList.push_back(*pathIter);
	}

	// now, in each path, open a file and read it a little
	pathIter=chosenPathList.begin();
	for(;pathIter!=chosenPathList.end();pathIter++)
	{
		CString strPathName;
		CString strPath=*pathIter;
		strPath+="\\*";
		HANDLE hSearch;
		WIN32_FIND_DATA searchResult;
		hSearch=FindFirstFile(strPath,&searchResult);
		if(INVALID_HANDLE_VALUE!=hSearch)
		{
			bool found=false;
			while(!found && FindNextFile(hSearch,&searchResult));
			{
				found=!(FILE_ATTRIBUTE_DIRECTORY & searchResult.dwFileAttributes);
			}

			if(found)
			{
				strPathName=*pathIter+CString("\\")+CString(searchResult.cFileName);
				ReadFile(strPathName);
			}
			FindClose(hSearch);


		}
	}	
}

void CAnyFileAccessor::ReadFile(const char *filename)
{
	try
	{
		ifstream file;
		file.open(filename);
		char buffer[1024];

		file.read(buffer,1024);
		file.close();
	}
	catch(...)
	{
	}
}

void CAnyFileAccessor::Clear()
{
	delete m_pInstance;
	m_pInstance=NULL;
}
