/*
** $Id: lprefix.h $
** Definitions for Lua code that must come before any other header file
** See Copyright Notice in lua.h
*/

#ifndef lprefix_h
#define lprefix_h


/*
** Allows POSIX/XSI stuff
*/
#if !defined(LUA_USE_C89)	/* { */

#if !defined(_XOPEN_SOURCE)
#define _XOPEN_SOURCE           600
#elif _XOPEN_SOURCE == 0
#undef _XOPEN_SOURCE  /* use -D_XOPEN_SOURCE=0 to undefine it */
#endif

/*
** Allows manipulation of large files in gcc and some other compilers
*/
#if !defined(LUA_32BITS) && !defined(_FILE_OFFSET_BITS)
#define _LARGEFILE_SOURCE       1
#define _FILE_OFFSET_BITS       64
#endif

#endif				/* } */


/*
** Windows stuff
*/
#if defined(_WIN32) 	/* { */

#if !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS  /* avoid warnings about ISO C functions */
#endif

#endif			/* } */

/*
** Compat stuff
*/

#include <complex.h>
// #include <math.h>

// NOTE: snippet copy-pasted from Taisei
// In case the C11 CMPLX macro is not present, try our best to provide a substitute
#if !defined CMPLX
  #undef HAS_BUILTIN_COMPLEX

  #if defined __has_builtin
    #if __has_builtin(__builtin_complex)
      #define HAS_BUILTIN_COMPLEX
    #endif
  #else
    #if defined __GNUC__ && defined __GNUC_MINOR__
      #if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7))
        #define HAS_BUILTIN_COMPLEX
      #endif
    #endif
  #endif

  #if defined HAS_BUILTIN_COMPLEX
    #define CMPLX(re,im) __builtin_complex((double)(re), (double)(im))
  #elif defined __clang__
    #define CMPLX(re,im) (__extension__ (_Complex double){(double)(re), (double)(im)})
  #elif defined _Imaginary_I
    #define CMPLX(re,im) (_Complex double)((double)(re) + _Imaginary_I * (double)(im))
  #else
    #define CMPLX(re,im) (_Complex double)((double)(re) + _Complex_I * (double)(im))
  #endif

  #undef HAS_BUILTIN_COMPLEX
#elif defined __EMSCRIPTEN__ && defined __clang__
  // CMPLX from emscripten headers uses the clang-specific syntax without __extension__
  #pragma clang diagnostic ignored "-Wcomplex-component-init"
#endif

#endif
