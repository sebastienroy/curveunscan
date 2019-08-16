//////////////////////////////////////////////////////////////////////
// SetFirstUse.h

#if !defined(_SETFIRSTUSE_H)
#define _SETFIRSTUSE_H


LONG APIENTRY SetFirstUse(HWND hwnd, LPLONG lpIValue, LPSTR lpszValue);

int createDateKey();
bool WriteRegistryString(HKEY hKey, const CString strEntry, const CString strValue);
CString GetRegistryString(HKEY hKey, CString strValueName);


#endif // !defined(_SETFIRSTUSE_H)