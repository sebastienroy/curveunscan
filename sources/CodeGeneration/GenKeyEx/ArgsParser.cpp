
#include "stdafx.h"

#include "ArgsParser.h"

#include <map>
using namespace std;

CArgsParser::CArgsParser(char * args[])
{
	if (NULL==args)
	{
		return;
	}

	  /* get input values from array */
	while (args)
	{

		// get next tag
		char* tag=*args++;
		if (!tag)
		{
			break;
		}
		CString strTag(tag);

		// get assigned value for tag 
		char* value=*args++;
		if (!value)
		{
			break; 
		}
		CString strValue (value);

		m_ValueMap[strTag]=strValue;
	}
}

CArgsParser::~CArgsParser()
{
}

CString CArgsParser::getValue(const char* strVarName)
{
	map<CString,CString>::iterator myIter=m_ValueMap.find(CString(strVarName));
	if(myIter!=m_ValueMap.end())
	{
		return (*myIter).second;
	}
	else
	{
		return CString("");
	}
}

int CArgsParser::getSize()
{
	return m_ValueMap.size();
}