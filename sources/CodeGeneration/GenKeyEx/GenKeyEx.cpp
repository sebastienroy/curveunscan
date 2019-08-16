#include "stdafx.h"

#include <string.h>
#include <windows.h>

#include "GenKeyEx.h"
#include "KeyGenerator.h"

#include "key_intf.h"

#include "ArgsParser.h"

#define DLLEXPORT __declspec( dllexport )


/* generate a key from the supplied input
 * 4000 bytes of memory have been allocated for each result 
 * you should ensure that your output does not get longer ! */
extern "C" DLLEXPORT int __stdcall
GenKeyEx(char * args[], char *result1, char *result2)
{
	try
	{
		CArgsParser parser(args);
		
		CKeyGenerator generator(&parser,result1,result2);
		return generator.generate();
	}
	catch(...)
	{
		strcpy(result1,"unexpected error during the key generation...");
		return ERC_INTERNAL;
	}
}

/* DLL init/cleaup code goes here */
int WINAPI
DllEntryPoint(HINSTANCE hinstDLL, unsigned long fdwReason, void * lpvReserved)
{
  switch(fdwReason)
  {
    case DLL_PROCESS_ATTACH: /* init */
    break;

    case DLL_PROCESS_DETACH: /* cleanup */
    break;
  };
  return TRUE;
};
