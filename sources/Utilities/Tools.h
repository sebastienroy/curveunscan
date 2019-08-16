// Tools.h: interface for the CTools class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOOLS_H__80C35B40_A545_11D4_935E_B6EF5A86B478__INCLUDED_)
#define AFX_TOOLS_H__80C35B40_A545_11D4_935E_B6EF5A86B478__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>
using namespace std;

class CTools  
{
public:
	static double Distance(const CPoint& ptA, const CPoint& ptB);
	static bool SearchFile(const char* strDir, const char* strFilename, CString &outPathName);
	static bool GetAllSubdirectories(const char *strPath, list<CString>& pathList);
	static double GetVectorialProduct(CPoint v1From,CPoint v1To,CPoint v2From, CPoint v2To);
	static double GetVectorialProduct(CPoint v1, CPoint v2);
	static CString GetFileFiltersFromExtension(const CString& strExtension);
	static CString GetFullDirFromPath(const char *strPath);
	static CString GetNameFromPath(const CString &strPath);
	static CString GetExtension(const CString &strFilename);
	static int Round(double value);
	static CPoint RotatedPoint(const CPoint& point,double alpha);
	static double GetNormalizedScalar(CPoint A, CPoint B, CPoint O);
	static CPoint GetProjection(CPoint A, CPoint B, CPoint O);
	CTools();
	virtual ~CTools();

};

#endif // !defined(AFX_TOOLS_H__80C35B40_A545_11D4_935E_B6EF5A86B478__INCLUDED_)
