////////////////////////////////////////////////////////////
// Profile.h

#if !defined(_PROFILE_H_)
#define _PROFILE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


size_t GetProfileString(const char *sectionName,
							   const char *entryName,
							   const char *defaultValue,
							   char *returnedString,
							   size_t capacity,
							   const char * fileName);

size_t GetProfileInt (const char *sectionName,
			    const char *entryName,
			    int defaultValue,
			    const char * fileName);

bool WriteProfileString(const char *sectionName,
			       const char *entryName,
			       const char *value,
			       const char * fileName);

void removeTrailingBlanks(CString &strLine,
						  const CString& strBlanks=CString(" \t"));




#endif // !defined(_PROFILE_H_)