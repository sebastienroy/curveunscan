// Tokenizer.h: interface for the CTokenizer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOKENIZER_H__B685AD90_DC23_4305_A009_10EEFB2F8DFC__INCLUDED_)
#define AFX_TOKENIZER_H__B685AD90_DC23_4305_A009_10EEFB2F8DFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTokenizer  
{
public:
	CTokenizer(const CString& string);
	CTokenizer(const char* string);
	virtual ~CTokenizer();

public:
	CString operator ()(const CString& strToken);

private:
	const char * m_buffer;
	int m_nCurrentPos;
	int m_nSize;
};

#endif // !defined(AFX_TOKENIZER_H__B685AD90_DC23_4305_A009_10EEFB2F8DFC__INCLUDED_)
