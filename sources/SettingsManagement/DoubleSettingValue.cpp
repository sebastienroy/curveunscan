// DoubleSettingValue.cpp: implementation of the CDoubleSettingValue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "settingsmanagement.h"
#include "DoubleSettingValue.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDoubleSettingValue::CDoubleSettingValue(const char *strSection,
										 const char *strEntry,
										 double dDefaultValue)
:	CAbstractSettingValue(strSection,strEntry),
	m_dDefaultValue(dDefaultValue)

{
	ReadValue();
}

CDoubleSettingValue::~CDoubleSettingValue()
{
	WriteValue();
}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////



void CDoubleSettingValue::ReadValue()
{
	CString strDefaultValue;
	strDefaultValue.Format("%lf",m_dDefaultValue);
	CWinApp *pApp=AfxGetApp();
	CString strValue=pApp->GetProfileString(m_strSection,m_strEntry,strDefaultValue);
	m_dCurrentValue=atof((LPCSTR)strValue);

}

void CDoubleSettingValue::WriteValue() const
{
	CString strValue;
	strValue.Format("%lf",m_dCurrentValue);
	CWinApp *pApp=AfxGetApp();
	pApp->WriteProfileString(m_strSection,m_strEntry,strValue);

}

void CDoubleSettingValue::SetToDefault()
{
	m_dCurrentValue=m_dDefaultValue;
}


double CDoubleSettingValue::SetValue(double value)
{
	double oldValue=m_dCurrentValue;
	m_dCurrentValue=value;

	return oldValue;
}

double CDoubleSettingValue::GetValue() const
{
	return m_dCurrentValue;
}
