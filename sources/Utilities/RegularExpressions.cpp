//////////////////////////////////////////////////////////
// RegularExpressions.cpp

#include "stdafx.h"

#include "RegularExpressions.h"
#include "RegExp.h"

int RegSearchReplace( CString& string, LPCTSTR sSearchExp, 
					 LPCTSTR sReplaceExp )
{
	int nPos = 0;
	int nReplaced = 0;
	CRegExp r;
	LPTSTR str = (LPTSTR)(LPCTSTR)string;

	try
	{
		r.RegComp( sSearchExp );
		while( (nPos = r.RegFind((LPTSTR)str)) != -1 )
		{
			nReplaced++;
			TCHAR *pReplaceStr = r.GetReplaceString( sReplaceExp );

			int offset = str-(LPCTSTR)string+nPos;
	//		string.Replace( offset, r.GetFindLen(), 
	//				pReplaceStr );
			StringReplace(string,offset,r.GetFindLen(),sReplaceExp);

			// Replace might have caused a reallocation
			str = (LPTSTR)(LPCTSTR)string + offset + _tcslen(pReplaceStr);
			delete pReplaceStr;
		}
	}
	catch(...)
	{
	}
	return nReplaced;
}

bool RegSearchReplaceOnce( CString& string, LPCTSTR sSearchExp, 
					 LPCTSTR sReplaceExp )
	{
	bool bReplaced=false;
	int nPos=0;
	CRegExp r;
	r.RegComp(sSearchExp);
	if ( (nPos = r.RegFind((LPCTSTR)string)) != -1 )
		{
		StringReplace(string,nPos,r.GetFindLen(),sReplaceExp);
		bReplaced=true;
		}
	return bReplaced;
	}

bool RegIsMatching(LPCTSTR string, LPCTSTR sSearchExp)
	{
	CRegExp r;
	r.RegComp(sSearchExp);
	return (r.RegFind((LPTSTR)string) != -1);
	}

CString RegMatch(LPCTSTR string, LPCTSTR sSearchExp)
	{
	CString strResult;
	int nPos;
	CRegExp r;
	r.RegComp(sSearchExp);
	if ( (nPos=r.RegFind((LPTSTR)string)) !=-1 )
		{
		strResult=CString(string).Mid(nPos,r.GetFindLen());
		}
	return strResult;
	}

bool StringReplace(CString& string, int nOffset, int nLength, LPCSTR pReplaceStr)
	{
	// Check validity
	if ( (nOffset<0)
		|| (nLength<0)
		|| (nOffset>string.GetLength())
		|| ((nOffset+nLength)>string.GetLength()) )
		{
		return false;
		}
	
	CString strTemp=string;
	string=strTemp.Left(nOffset);
	string+=pReplaceStr;
	string+=strTemp.Right(strTemp.GetLength()-(nOffset+nLength));
	return true;
	}

