// StringSettingValue.cpp: implementation of the CStringSettingValue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StringSettingValue.h"
#include "../Utilities/RegularExpressions.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStringSettingValue::CStringSettingValue(const char *strSection,
										 const char *strEntry,
										 const char *strDefaultValue,
										 const char *strPermittedValues)
:	CAbstractSettingValue(strSection,strEntry),
	m_strDefaultValue(strDefaultValue),
	m_strPermittedValues(strPermittedValues)	
{
	ASSERT(IsValuePermitted(m_strDefaultValue));
	ReadValue();
}

CStringSettingValue::~CStringSettingValue()
{
	WriteValue();
}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////


bool CStringSettingValue::IsValuePermitted(const CString &strValue) const
{
	try
	{
		return ( ( EmptyRegExp ==m_strPermittedValues)
				|| (RegIsMatching(strValue,m_strPermittedValues)) );
	}
	catch(...)
	{
		return false;
	}
}

void CStringSettingValue::ReadValue()
{
	CWinApp *pApp=AfxGetApp();
	m_strCurrentValue=pApp->GetProfileString(m_strSection,m_strEntry,m_strDefaultValue);
	if(!IsValuePermitted(m_strCurrentValue))
	{
		m_strCurrentValue=m_strDefaultValue;
	}
}

void CStringSettingValue::WriteValue() const
{
	CWinApp *pApp=AfxGetApp();
	pApp->WriteProfileString(m_strSection,m_strEntry,m_strCurrentValue);
}

CString CStringSettingValue::GetValue() const
{
	return m_strCurrentValue;
}

bool CStringSettingValue::SetValue(CString strValue)
{
	bool bValueOk=IsValuePermitted(strValue);
	if(bValueOk)
	{
		m_strCurrentValue=strValue;
	}
	return bValueOk;
}

void CStringSettingValue::SetToDefault()
{
	m_strCurrentValue=m_strDefaultValue;
}

CString CStringSettingValue::GetDefaultValue() const
{
	return m_strDefaultValue;
}
