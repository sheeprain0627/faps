/*
 * MATLAB Compiler: 4.8 (R2008a)
 * Date: Wed Aug 31 22:28:25 2011
 * Arguments: "-B" "macro_default" "-B" "csharedlib:facewarp" "-W"
 * "lib:facewarp" "-T" "link:lib" "FaceWarp.m" 
 */

#ifndef __facewarp_h
#define __facewarp_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__SUNPRO_CC)
/* Solaris shared libraries use __global, rather than mapfiles
 * to define the API exported from a shared library. __global is
 * only necessary when building the library -- files including
 * this header file to use the library do not need the __global
 * declaration; hence the EXPORTING_<library> logic.
 */

#ifdef EXPORTING_facewarp
#define PUBLIC_facewarp_C_API __global
#else
#define PUBLIC_facewarp_C_API /* No import statement needed. */
#endif

#define LIB_facewarp_C_API PUBLIC_facewarp_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_facewarp
#define PUBLIC_facewarp_C_API __declspec(dllexport)
#else
#define PUBLIC_facewarp_C_API __declspec(dllimport)
#endif

#define LIB_facewarp_C_API PUBLIC_facewarp_C_API


#else

#define LIB_facewarp_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_facewarp_C_API 
#define LIB_facewarp_C_API /* No special import/export declaration */
#endif

extern LIB_facewarp_C_API 
bool MW_CALL_CONV facewarpInitializeWithHandlers(mclOutputHandlerFcn error_handler,
                                                 mclOutputHandlerFcn print_handler);

extern LIB_facewarp_C_API 
bool MW_CALL_CONV facewarpInitialize(void);

extern LIB_facewarp_C_API 
void MW_CALL_CONV facewarpTerminate(void);



extern LIB_facewarp_C_API 
void MW_CALL_CONV facewarpPrintStackTrace(void);


extern LIB_facewarp_C_API 
bool MW_CALL_CONV mlxFaceWarp(int nlhs, mxArray *plhs[],
                              int nrhs, mxArray *prhs[]);


extern LIB_facewarp_C_API bool MW_CALL_CONV mlfFaceWarp();

#ifdef __cplusplus
}
#endif

#endif
