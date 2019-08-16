// AbstractSettingValue.cpp: implementation of the CAbstractSettingValue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AbstractSettingValue.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAbstractSettingValue::CAbstractSettingValue(const char *strSection, const char *strEntry)
:	m_strSection(strSection),
	m_strEntry(strEntry)
{

}

CAbstractSettingValue::~CAbstractSettingValue()
{

}
