// FirstUseInfo.cpp: implementation of the CFirstUseInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "licencemanaging.h"
#include "FirstUseInfo.h"

#include "Licencemanagingresources.h"
#include "Coder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFirstUseInfo::CFirstUseInfo()
:	m_strSection(CCoder::GetInstance()->EncodeString(CONFIRM_SECTION)),
	m_strInstallEntry(CCoder::GetInstance()->EncodeString(INSTALL_ENTRY)),
	m_strFirstUseEntry(CCoder::GetInstance()->EncodeString(FIRSTUSE_ENTRY)),
	m_strLastUseEntry(CCoder::GetInstance()->EncodeString(LASTUSE_ENTRY))
{
	m_strFilename=CONFIRM_FILENAME;
	m_strFilePath=GetSystemDirectory();
	m_strRegistryPath=CONFIRM_REGPATH;
	m_strRegistryEntryName=CONFIRM_REGKEYNAME;

	if(IsRegKeyExists())
	{
		m_bUsefile=false;
	}
}

CFirstUseInfo::~CFirstUseInfo()
{

}

bool CFirstUseInfo::ConfirmDate(const char *strDate)
{
	try
	{
		// first check : the current date must not be less than the given date
		CTime installTime=CCoder::GetInstance()->GetDecodedTime(strDate);
		CTime currentTime=CTime::GetCurrentTime();
		if(TimeIsGreater(installTime,currentTime))
		{
			return false;
		}

		// check file existence
		if(!IsInitialized())
		{

			if(EnoughTimeIsElapsed(installTime,currentTime))
			{
//				bool success=CreateConfirmFile(filename,strDate);
				bool success=InitializeSupport();
				if(!success)
				{
					return true;	// no check if the file is not created
				}
				SetValue(m_strSection,m_strInstallEntry,strDate);
				CString currentDate=CCoder::GetInstance()->GetEncodedTimeStamp();
				SetValue(m_strSection,m_strFirstUseEntry,currentDate);
				SetValue(m_strSection,m_strLastUseEntry,currentDate);
			}
			return true; // 
		}

		// Get file values
		CString strFileDate=GetValue(m_strSection,m_strInstallEntry);
		
		CString strFirstUse=GetValue(m_strSection,m_strFirstUseEntry);
		
		CString strLastUse=GetValue(m_strSection,m_strLastUseEntry);
		
		// Perform checks
		if(strFileDate!=strDate)
		{
			return false;
		}

		CTime firstTime=CCoder::GetInstance()->GetDecodedTime(strFirstUse);
		CTime lastTime=CCoder::GetInstance()->GetDecodedTime(strLastUse);
#if defined(_DEBUG)
		int nYear=lastTime.GetYear();
		int nMonth=lastTime.GetMonth();
		int nDay=lastTime.GetDay();
		int nHour=lastTime.GetHour();
		int nMinute=lastTime.GetMinute();
		int nSecond=lastTime.GetSecond();
#endif

		// coherence test. Should not happen
		if( (firstTime<installTime)
			||(lastTime<firstTime) )	
		{
			return false;
		}

		// tests with current date
//		if(lastTime>currentTime)
		if(TimeIsGreater(lastTime,currentTime))
		{
			return false;
		}

		// Everything is Ok, so write the current date as the last use
		CString strCurrentDate=CCoder::GetInstance()->GetEncodedTimeStamp();
		SetValue(m_strSection,m_strLastUseEntry,strCurrentDate);

	}
	catch(...)
	{
		return false;
	}

	return true;
}

bool CFirstUseInfo::TimeIsGreater(const CTime &time1, const CTime &time2)
{
	int nYear1=time1.GetYear();
	int nMonth1=time1.GetMonth();
	int nDay1=time1.GetDay();

	int nYear2=time2.GetYear();
	int nMonth2=time2.GetMonth();
	int nDay2=time2.GetDay();

	if(nYear1>nYear2)
	{
		return true;
	}
	else if(nYear1<nYear2)
	{
		return false;
	}
	else	// same year
	{
		if(nMonth1>nMonth2)
		{
			return true;
		}
		else if(nMonth1<nMonth2)
		{
			return false;
		}
		else	// same month
		{
			if(nDay1>nDay2)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}

bool CFirstUseInfo::EnoughTimeIsElapsed(const CTime &time1, const CTime &time2)
{
	CTimeSpan elapsed=time2-time1;
	bool isElapsed=(elapsed.GetDays()>=NBOFDAYSBEFOREWRITINGCONFIRMFILE);
	return isElapsed;
	
}

void CFirstUseInfo::WriteFileSkeleton(ofstream &file)
{
	file<<"["<<LPCTSTR(m_strSection)<<"]"<<endl;
	file<<LPCTSTR(m_strInstallEntry)<<"="<<endl;
	file<<LPCTSTR(m_strFirstUseEntry)<<"="<<endl;
	file<<LPCTSTR(m_strLastUseEntry)<<"="<<endl;

}
