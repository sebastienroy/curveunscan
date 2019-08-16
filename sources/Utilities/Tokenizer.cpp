// Tokenizer.cpp: implementation of the CTokenizer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Tokenizer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTokenizer::CTokenizer(const char* string)
:	m_buffer(string),
	m_nCurrentPos(0)
{
	m_nSize=strlen(string);
}

CTokenizer::CTokenizer(const CString &string)
:	m_buffer(LPCTSTR(string)),
	m_nSize(string.GetLength()),
	m_nCurrentPos(0)
{

}

CTokenizer::~CTokenizer()
{

}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////


CString CTokenizer::operator ()(const CString &strTokens) 
{
	int nInitialPos=m_nCurrentPos;
	bool found=false;

	while( (m_nCurrentPos<m_nSize) && !found )
	{
		found=(-1!=strTokens.Find(m_buffer[m_nCurrentPos]));
		m_nCurrentPos++;
	}
	int length=m_nCurrentPos-nInitialPos;
	if(found)
	{
		length--;
	}
	return CString(m_buffer+nInitialPos,length);
}

