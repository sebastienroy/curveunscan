// IntSettingValue.cpp: implementation of the CIntSettingValue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IntSettingValue.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIntSettingValue::CIntSettingValue(	const char *strSection,
									const char *strEntry,
									int nDefaultValue,
									int nMin,
									int nMax)
:	CAbstractSettingValue(strSection,strEntry),
	m_nDefaultValue(nDefaultValue),
	m_nMinValue(nMin),
	m_nMaxValue(nMax)
{
	ASSERT( IsValuePermitted(m_nDefaultValue) );
	ReadValue();
}

CIntSettingValue::~CIntSettingValue()
{
	WriteValue();
}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////


bool CIntSettingValue::IsValuePermitted(int nValue) const
{
	return ( (nValue>=m_nMinValue)&&(nValue<=m_nMaxValue) );
}

void CIntSettingValue::WriteValue() const
{
	CWinApp *pApp=AfxGetApp();
	pApp->WriteProfileInt(m_strSection,m_strEntry,m_nCurrentValue);
}

void CIntSettingValue::ReadValue()
{
	CWinApp *pApp=AfxGetApp();
	m_nCurrentValue=pApp->GetProfileInt(m_strSection,m_strEntry,m_nDefaultValue);
	if(!IsValuePermitted(m_nCurrentValue))
	{
		m_nCurrentValue=m_nDefaultValue;
	}
}

int CIntSettingValue::GetValue() const
{
	return m_nCurrentValue;
}

bool CIntSettingValue::SetValue(int nValue)
{
	bool bIsOk=IsValuePermitted(nValue);
	if(bIsOk)
	{
		m_nCurrentValue=nValue;
	}
	return bIsOk;
}

void CIntSettingValue::SetToDefault()
{
	m_nCurrentValue=m_nDefaultValue;
}

int CIntSettingValue::GetDefaultValue() const
{
	return m_nDefaultValue;
}
