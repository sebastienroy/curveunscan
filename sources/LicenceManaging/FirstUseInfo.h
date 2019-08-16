// FirstUseInfo.h: interface for the CFirstUseInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIRSTUSEINFO_H__03A82B6D_04AE_4C70_B7C3_13712F81AF1A__INCLUDED_)
#define AFX_FIRSTUSEINFO_H__03A82B6D_04AE_4C70_B7C3_13712F81AF1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SecuredInfo.h"

class CFirstUseInfo : public CSecuredInfo  
{
public:
	bool ConfirmDate(const char* strDate);
	CFirstUseInfo();
	virtual ~CFirstUseInfo();

protected:
	bool EnoughTimeIsElapsed(const CTime &time1, const CTime &time2);
	bool TimeIsGreater(const CTime &time1, const CTime &time2);

protected:
	virtual void WriteFileSkeleton(ofstream &stream);
	CString m_strSection;
	CString m_strInstallEntry;
	CString m_strFirstUseEntry;
	CString m_strLastUseEntry;
};

#endif // !defined(AFX_FIRSTUSEINFO_H__03A82B6D_04AE_4C70_B7C3_13712F81AF1A__INCLUDED_)
