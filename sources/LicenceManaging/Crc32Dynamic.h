#ifndef _CRC32DYNAMIC_H_
#define _CRC32DYNAMIC_H_

#ifndef _QWORD_DEFINED
#define _QWORD_DEFINED
typedef __int64 QWORD, *LPQWORD;
#endif

#define MAKEQWORD(a, b)	\
	((QWORD)( ((QWORD) ((DWORD) (a))) << 32 | ((DWORD) (b))))

#define LODWORD(l) \
	((DWORD)(l))
#define HIDWORD(l) \
	((DWORD)(((QWORD)(l) >> 32) & 0xFFFFFFFF))

// Read 4K of data at a time (used in the C++ streams, Win32 I/O, and assembly functions)
#define MAX_BUFFER_SIZE	4096

// Map a "view" size of 10MB (used in the filemap function)
#define MAX_VIEW_SIZE	10485760

class CCrc32Dynamic
{
public:
	CCrc32Dynamic();
	virtual ~CCrc32Dynamic();


	DWORD StringCrc32(LPCTSTR szString, DWORD &dwCrc32) const;
	DWORD FileCrc32Streams(LPCTSTR szFilename, DWORD &dwCrc32) const;

protected:
	void Init(void);
	void Free(void);
	static bool GetFileSizeQW(const HANDLE hFile, QWORD &qwSize);
	inline void CalcCrc32(const BYTE byte, DWORD &dwCrc32) const;

	DWORD *m_pdwCrc32Table;
};

#endif
