#include "stdafx.h"
#include "Crc32Dynamic.h"
#include <fstream.h>

//***********************************************
CCrc32Dynamic::CCrc32Dynamic() : m_pdwCrc32Table(NULL)
{
	Init();
}

//***********************************************
CCrc32Dynamic::~CCrc32Dynamic()
{
	Free();
}

//***********************************************
void CCrc32Dynamic::Init(void)
{
	// This is the official polynomial used by CRC32 in PKZip.
	// Often times the polynomial shown reversed as 0x04C11DB7.
	DWORD dwPolynomial = 0xEDB88320;
	int i, j;

	Free();
	m_pdwCrc32Table = new DWORD[256];

	DWORD dwCrc;
	for(i = 0; i < 256; i++)
	{
		dwCrc = i;
		for(j = 8; j > 0; j--)
		{
			if(dwCrc & 1)
				dwCrc = (dwCrc >> 1) ^ dwPolynomial;
			else
				dwCrc >>= 1;
		}
		m_pdwCrc32Table[i] = dwCrc;
	}
}

//***********************************************
void CCrc32Dynamic::Free(void)
{
	delete m_pdwCrc32Table;
	m_pdwCrc32Table = NULL;
}

//***********************************************
inline void CCrc32Dynamic::CalcCrc32(const BYTE byte, DWORD &dwCrc32) const
{
	dwCrc32 = ((dwCrc32) >> 8) ^ m_pdwCrc32Table[(byte) ^ ((dwCrc32) & 0x000000FF)];
}

//***********************************************
bool CCrc32Dynamic::GetFileSizeQW(const HANDLE hFile, QWORD &qwSize)
{
	_ASSERTE(hFile != INVALID_HANDLE_VALUE);

	bool bSuccess = true;

	try
	{
		DWORD dwLo = 0, dwHi = 0;
		dwLo = GetFileSize(hFile, &dwHi);

		if(dwLo == INVALID_FILE_SIZE && GetLastError() != NO_ERROR)
		{
			bSuccess = false;
			qwSize = 0;
		}
		else
		{
			qwSize = MAKEQWORD(dwHi, dwLo);
		}
	}
	catch(...)
	{
		bSuccess = false;
	}

	return bSuccess;
}

//***********************************************
DWORD CCrc32Dynamic::StringCrc32(LPCTSTR szString, DWORD &dwCrc32) const
{
	_ASSERTE(szString);

	DWORD dwErrorCode = NO_ERROR;

	dwCrc32 = 0xFFFFFFFF;

	try
	{
		// Is the table initialized?
		if(m_pdwCrc32Table == NULL)
			throw 0;

		while(*szString != _T('\0'))
		{
			CalcCrc32((BYTE)*szString, dwCrc32);
			szString++;
		}
	}
	catch(...)
	{
		// An unknown exception happened, or the table isn't initialized
		dwErrorCode = ERROR_CRC;
	}

	dwCrc32 = ~dwCrc32;

	return dwErrorCode;
}

//***********************************************
DWORD CCrc32Dynamic::FileCrc32Streams(LPCTSTR szFilename, DWORD &dwCrc32) const
{
#if UNICODE || _UNICODE
	return ERROR_NOT_SUPPORTED;
#else
	_ASSERTE(szFilename);
	_ASSERTE(lstrlen(szFilename));

	DWORD dwErrorCode = NO_ERROR;
	ifstream file;

	dwCrc32 = 0xFFFFFFFF;

	try
	{
		// Is the table initialized?
		if(m_pdwCrc32Table == NULL)
			throw 0;

		// Open the file
		file.open(szFilename, ios::in | ios::nocreate | ios::binary, filebuf::sh_read);
		if(!file.is_open())
			dwErrorCode = file.fail();
		else
		{
			char buffer[MAX_BUFFER_SIZE];
			int nLoop, nCount;
			nCount = file.read(buffer, sizeof(buffer)).gcount();
			while(nCount)
			{
				for(nLoop = 0; nLoop < nCount; nLoop++)
					CalcCrc32(buffer[nLoop], dwCrc32);
				nCount = file.read(buffer, sizeof(buffer)).gcount();
			}

			file.close();
		}
	}
	catch(...)
	{
		// An unknown exception happened, or the table isn't initialized
		dwErrorCode = ERROR_CRC;
	}

	if(file.is_open()) file.close();

	dwCrc32 = ~dwCrc32;

	return dwErrorCode;
#endif
}

