// VersionInfo.h
/////////////////////////////////////////////

#if !defined(_VERSIONINFO_H)
#define _VERSIONINFO_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct SVersionInfo
{
	SVersionInfo()
		:	m_nMajorVersion(1),
			m_nMinorVersion(2),
			m_strManufacturer("SquarePoint Software"),
			m_strAppName("CurveUnscan"),
			m_nLanguage(0)
	{
	}

	int m_nMajorVersion;
	int m_nMinorVersion;
	CString m_strManufacturer;
	CString m_strAppName;
	CString m_strInfo;
	int m_nLanguage;
};

#endif	// !defined(_VERSIONINFO_H)