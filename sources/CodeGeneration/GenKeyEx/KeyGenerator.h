// KeyGenerator.h
//

#if !defined(_KEYGENERATOR_H_)
#define _KEYGENERATOR_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CArgsParser;

typedef int UserLanguage ;

class CKeyGenerator
{
public:
	CKeyGenerator(CArgsParser* parser, char* result1, char* result2);
	virtual ~CKeyGenerator();

public:
	int generate();

protected:
	CArgsParser *m_pParser;
	char *m_pResult1;
	char *m_pResult2;
	UserLanguage m_Language;
};


#endif // defined(_KEYGENERATOR_H_)