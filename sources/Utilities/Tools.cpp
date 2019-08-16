// Tools.cpp: implementation of the CTools class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurveUnscan.h"
#include "Tools.h"
//#include "LogicPoint.h"
#include "Utilities\RegularExpressions.h"
#include "stdlib.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTools::CTools()
{

}

CTools::~CTools()
{

}

// renvoie la projection de O sur la droite (AB)
CPoint CTools::GetProjection(CPoint A, CPoint B, CPoint O)
{
//	CLogicPoint AB;
//	CLogicPoint lP;

	double ABx,ABy;
	double lPx,lPy;

	CPoint result;
	ABx=((double)B.x)-((double)A.x);
	ABy=((double)B.y)-((double)A.y);
	double k=GetNormalizedScalar(A,B,O);
	lPx=k*ABx;
	lPy=k*ABy;
	result.x=Round(lPx);
	result.y=Round(lPy);
	result.x+=A.x;
	result.y+=A.y;
	return result;

}

// Renvoie (vect(AB).vect(AO))/(|AB|.|AO|)
double CTools::GetNormalizedScalar(CPoint A, CPoint B, CPoint O)
{
	CPoint AB;
	CPoint AO;
	double scalABAO;
	double normeAB;
	double k;

	AB.x=B.x-A.x;	
	AB.y=B.y-A.y;
	AO.x=O.x-A.x;
	AO.y=O.y-A.y;
	scalABAO=((double)AB.x)*((double)AO.x)+((double)AB.y)*((double)AO.y);
	normeAB=((double)AB.x)*((double)AB.x);
	normeAB+=((double)AB.y)*((double)AB.y);
	k=scalABAO/normeAB;
	return k;

}

CPoint CTools::RotatedPoint(const CPoint &point, double alpha)
{
	double cosin=cos(alpha);
	double sinus=sin(alpha);

	double a=(double)point.x;
	double b=(double)point.y;

	double resX=a*cosin-b*sinus;
	double resY=a*sinus+b*cosin;

	return CPoint(Round(resX),Round(resY));
}

int CTools::Round(double value)
{
	value+=(value>0)?0.5:-0.5;
	return (int)value;
}

CString CTools::GetExtension(const CString &strFilename)
{
	return RegMatch(strFilename,"\\.[^.\\\\]+$");
}

CString CTools::GetNameFromPath(const CString &strPath)
{
	char strName[256];

	_splitpath(strPath,NULL,NULL,strName,NULL);
	return strName;
}

CString CTools::GetFullDirFromPath(const char *strPath)
{
	char strDrive[256];
	char strDir[256];
	_splitpath(strPath,strDrive,strDir,NULL,NULL);

	CString strResult=strDrive;
	strResult+=CString(strDir);
	return strResult;
}

CString CTools::GetFileFiltersFromExtension(const CString &strExtension)
{
	CString strFilter;

	CString strExcelFilter;
	strExcelFilter.LoadString(IDS_EXCEL_FILTER);
	CString strTextFilter;
	strTextFilter.LoadString(IDS_TEXT_FILTER);
	CString strAllFileFilter;
	strAllFileFilter.LoadString(IDS_OUTPUTFILTERNAME);

	CString strExt=strExtension;
	strExt.MakeLower();
	if( (strExt!="xls")&&(strExt!="txt") )	// add filter
	{
		CString strGenericFilter;
		strGenericFilter.LoadString(IDS_GENERIC_FILTER);
		CString strNewFilter;
		strNewFilter.Format(strGenericFilter,(LPCSTR)strExtension,(LPCSTR)strExtension,(LPCSTR)strExtension);

		strFilter=strNewFilter+strExcelFilter+strTextFilter+strAllFileFilter;
	}
	else if(strExt=="xls")	// Excel extension
	{
		strFilter=strExcelFilter+strTextFilter+strAllFileFilter;
	}
	else		// It is Text extension
	{
		strFilter=strTextFilter+strExcelFilter+strAllFileFilter;
	}

	return strFilter;
}

double CTools::GetVectorialProduct(CPoint v1, CPoint v2)
{
	return (v1.x*v2.y)-(v1.y*v2.x);
}

double CTools::GetVectorialProduct(CPoint v1From, CPoint v1To, CPoint v2From, CPoint v2To)
{
	return GetVectorialProduct(v1To-v1From,v2To-v2From);
}

bool CTools::GetAllSubdirectories(const char *strPath, list<CString> &pathList)
{
	HANDLE hSearch;
	WIN32_FIND_DATA searchResult;

	// verify and construct search string
	CString strSearch(strPath);
	if(strSearch.IsEmpty())
	{
		return false;
	}
	char cLastChar=strSearch[strSearch.GetLength()-1];
	if(('\\'!=cLastChar)&&('/'!=cLastChar))
	{
		strSearch+='\\';
	}
	
	//begin search
	CString strSearchString=strSearch+CString("*");
	hSearch=FindFirstFile(strSearchString,&searchResult);
	if(INVALID_HANDLE_VALUE==hSearch)
	{
		return false;
	}

	// add current dir
	pathList.push_back(CString(strPath));

	// look for subfolders
	do
	{
		CString strFilename=searchResult.cFileName;
		DWORD isSubdir=FILE_ATTRIBUTE_DIRECTORY & searchResult.dwFileAttributes;
		if((CString(".")!=strFilename)
			&& (CString("..")!=strFilename)
			&& isSubdir )
		{
			CString strSubdir=strSearch+strFilename;
			GetAllSubdirectories(strSubdir,pathList);
		}
	}
	while(FindNextFile(hSearch,&searchResult));

	FindClose(hSearch);
	return true;
}

// returns the first file in the directory srDir which match the expression strFilename
bool CTools::SearchFile(const char *strDir, const char *strFilename, CString &outPathName)
{
	bool found=false;
	HANDLE hSearch;
	WIN32_FIND_DATA searchResult;

	// verify and construct search string
	CString strSearch(strDir);
	if(strSearch.IsEmpty())
	{
		return false;
	}
	char cLastChar=strSearch[strSearch.GetLength()-1];
	if(('\\'!=cLastChar)&&('/'!=cLastChar))
	{
		strSearch+='\\';
	}

	//begin search
	CString strSearchString=strSearch+CString(strFilename);
	hSearch=FindFirstFile(strSearchString,&searchResult);
	if(INVALID_HANDLE_VALUE==hSearch)	// not found ?	
	{
		// look in subfolders
		CString strSearchString=strSearch+CString("*");
		hSearch=FindFirstFile(strSearchString,&searchResult);
		if(INVALID_HANDLE_VALUE!=hSearch)
		{
			do
			{
				CString strSubdirname=searchResult.cFileName;
				DWORD isSubdir=FILE_ATTRIBUTE_DIRECTORY & searchResult.dwFileAttributes;
				if((CString(".")!=strSubdirname)
					&& (CString("..")!=strSubdirname)
					&& isSubdir )
				{
					CString strSubdir=strSearch+strSubdirname;
					found=SearchFile(strSubdir,strFilename,outPathName);
				}
			}
			while( (FindNextFile(hSearch,&searchResult)) && (!found));	
			
			FindClose(hSearch);
		}
	}
	else	// found in current folder
	{
		found=true;
		outPathName=strSearch+CString(searchResult.cFileName);
	}
	return found;
}

double CTools::Distance(const CPoint &ptA, const CPoint &ptB)
{
	int dx=ptA.x-ptB.x;
	int dy=ptA.y-ptB.y;
	return sqrt(dx*dx+dy*dy);
}
