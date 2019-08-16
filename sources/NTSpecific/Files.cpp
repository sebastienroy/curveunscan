// Files.cpp
//

#include "stdafx.h"
#include "Files.h"

bool CreateWritableFile(const char *filename)
{
	// declare and initialize a security attributes structure
	SECURITY_ATTRIBUTES fileAttributes;
	ZeroMemory( &fileAttributes, sizeof(fileAttributes) );
	fileAttributes.nLength = sizeof( fileAttributes );
	fileAttributes.bInheritHandle = FALSE; // object uninheritable

	HANDLE hFile=NULL;
	bool created=false;

	// declare and initialize a security descriptor
	SECURITY_DESCRIPTOR SD;
	BOOL bInitOk = InitializeSecurityDescriptor( &SD,
						 SECURITY_DESCRIPTOR_REVISION );
	if ( bInitOk )
	{
		// give the security descriptor a Null Dacl
		// done using the  "TRUE, (PACL)NULL" here
		BOOL bSetOk = SetSecurityDescriptorDacl( &SD,
												TRUE,
												(PACL)NULL,
												FALSE );
		if ( bSetOk )
		{
			// Make the security attributes point 
			// to the security descriptor
			fileAttributes.lpSecurityDescriptor = &SD;

			// use the attributes with the Null Dacl to
			// create the mutex
			hFile = ::CreateFile( filename,
								GENERIC_READ|GENERIC_WRITE,
								0,
								&fileAttributes,
								OPEN_ALWAYS,
								FILE_ATTRIBUTE_NORMAL,
								NULL);
			//    dwMutexErr = GetLastError();
			if(INVALID_HANDLE_VALUE!=hFile)
			{
				created=true;
				::CloseHandle(hFile);
				return true;
			}
			else
			{
				return false;
			}
 
			//   ... same logic as before
		}
		else
		{
			return false;
		}

	}
	else
	{
		return false;
	}
}
