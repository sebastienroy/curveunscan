// AbstractSettingValue.h: interface for the CAbstractSettingValue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABSTRACTSETTINGVALUE_H__2CC61FF9_1B0D_49E9_8D9F_428B8A538E4C__INCLUDED_)
#define AFX_ABSTRACTSETTINGVALUE_H__2CC61FF9_1B0D_49E9_8D9F_428B8A538E4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAbstractSettingValue  
{
public:
	CAbstractSettingValue(const char *strSection, const char *strEntry);
	virtual ~CAbstractSettingValue();

public:
	virtual void SetToDefault()=0;

protected:
	virtual void ReadValue()=0;
	virtual void WriteValue() const =0;
	CString m_strEntry;
	CString m_strSection;
};

#endif // !defined(AFX_ABSTRACTSETTINGVALUE_H__2CC61FF9_1B0D_49E9_8D9F_428B8A538E4C__INCLUDED_)
