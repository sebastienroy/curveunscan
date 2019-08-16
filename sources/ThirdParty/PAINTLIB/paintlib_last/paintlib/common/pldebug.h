/*
/--------------------------------------------------------------------
|
|      $Id: pldebug.h,v 1.2 2001/10/21 17:12:39 uzadow Exp $
|
|      Plattform-independent support for PLASSERT_VALID, PLTRACE and
|      PLASSERT.
|
|      Copyright (c) 1996-1998 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#ifndef INCL_PLDEBUG
#define INCL_PLDEBUG

//------------- PLASSERT_VALID
#ifdef _DEBUG
  #define PLASSERT_VALID(pOb) (pOb)->AssertValid()
#else
  #define PLASSERT_VALID(pOb) do{} while (0)
#endif

//------------- TRACE
#ifdef _DEBUG
  void PLTrace(const char * pszFormat, ...);
  #define PLTRACE ::PLTrace
#else
  // This will be optimized away in release mode and still allow TRACE
  // to take a variable amount of arguments :-).
  inline void PLTrace (const char *, ...) { }
  #define PLTRACE  1 ? (void)0 : ::PLTrace
#endif

//------------- ASSERT

#ifdef _DEBUG
  #ifdef _WINDOWS
    #define PLASSERT(f)            \
      if (!(f))                    \
        {                          \
          PLTRACE ("Assertion failed at %s, %i\n", __FILE__, __LINE__); \
          __asm { int 3 }          \
        }
  #else
    #define PLASSERT(f)            \
      if (!(f))                    \
        {                          \
          PLTRACE ("Assertion failed at %s, %i\n", __FILE__, __LINE__); \
          abort();                 \
        }
  #endif
#else
  #define PLASSERT(f) do{}while (0)
#endif


//------------- CompilerAssert template for conditional
//              compile time error generation.

#define PLCOMPILER_ASSERT(cond) (void)sizeof(int[bool(cond)?1:-1]);


#endif // INCL_PLDEBUG

/*
/--------------------------------------------------------------------
|
|      $Log: pldebug.h,v $
|      Revision 1.2  2001/10/21 17:12:39  uzadow
|      Added PSD decoder beta, removed BPPWanted from all decoders, added PLFilterPixel.
|
|      Revision 1.1  2001/09/16 19:03:22  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.3  2000/12/04 23:55:40  uzadow
|      no message
|
|      Revision 1.2  2000/12/04 13:28:17  uzadow
|      Changed PLASSERT to use int 3 in windows builds.
|
|      Revision 1.1  2000/01/17 23:45:07  Ulrich von Zadow
|      MFC-Free version.
|
|
\--------------------------------------------------------------------
*/
