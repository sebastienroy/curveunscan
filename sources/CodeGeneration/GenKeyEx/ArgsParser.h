
//	ArgsParser.h
//

#if !defined(_ARGSPARSER_H_)
#define _ARGSPARSER_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <map>
using namespace std;

class CArgsParser
{
public:
	CArgsParser(char * args[]);
	virtual ~CArgsParser();

public:
	CString getValue(const char* strVarName);
	int getSize();

protected:
	map<CString, CString > m_ValueMap;
};

#endif // defined _ARGSPARSER_H_