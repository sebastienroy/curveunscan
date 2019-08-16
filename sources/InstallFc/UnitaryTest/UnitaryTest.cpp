// UnitaryTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>

typedef	 LONG (CALLBACK* MAFONC)(HWND, LPLONG, LPSTR );


int main(int argc, char* argv[])
{
	long lpValue=19;
	char* lpszValue="tagada";
//	LONG  * MAFONC(HWND, LPLONG, LPSTR )maFonc;

	HINSTANCE hDll;
	MAFONC maFonc;

	printf("Hello World!\n");

	hDll=LoadLibrary("..\\..\\debug\\InstallFc");

	if(hDll!=NULL)
		{
		maFonc=(MAFONC)GetProcAddress(hDll,"SetFirstUse");
		if(maFonc)
			{
			LONG result=maFonc(NULL,&lpValue,lpszValue);
			}

		FreeLibrary(hDll);
		}

	return 0;

}

