/*
 * MATLAB Compiler: 4.8 (R2008a)
 * Date: Wed Aug 31 22:28:25 2011
 * Arguments: "-B" "macro_default" "-B" "csharedlib:facewarp" "-W"
 * "lib:facewarp" "-T" "link:lib" "FaceWarp.m" 
 */

#include <stdio.h>
#define EXPORTING_facewarp 1
#include "facewarp.h"
#ifdef __cplusplus
extern "C" {
#endif

extern mclComponentData __MCC_facewarp_component_data;

#ifdef __cplusplus
}
#endif


static HMCRINSTANCE _mcr_inst = NULL;


#if defined( _MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__) || defined(__LCC__)
#ifdef __LCC__
#undef EXTERN_C
#endif
#include <windows.h>

static char path_to_dll[_MAX_PATH];

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, void *pv)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        if (GetModuleFileName(hInstance, path_to_dll, _MAX_PATH) == 0)
            return FALSE;
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
    }
    return TRUE;
}
#endif
#ifdef __cplusplus
extern "C" {
#endif

static int mclDefaultPrintHandler(const char *s)
{
  return mclWrite(1 /* stdout */, s, sizeof(char)*strlen(s));
}

#ifdef __cplusplus
} /* End extern "C" block */
#endif

#ifdef __cplusplus
extern "C" {
#endif

static int mclDefaultErrorHandler(const char *s)
{
  int written = 0;
  size_t len = 0;
  len = strlen(s);
  written = mclWrite(2 /* stderr */, s, sizeof(char)*len);
  if (len > 0 && s[ len-1 ] != '\n')
    written += mclWrite(2 /* stderr */, "\n", sizeof(char));
  return written;
}

#ifdef __cplusplus
} /* End extern "C" block */
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_facewarp_C_API 
#define LIB_facewarp_C_API /* No special import/export declaration */
#endif

LIB_facewarp_C_API 
bool MW_CALL_CONV facewarpInitializeWithHandlers(
    mclOutputHandlerFcn error_handler,
    mclOutputHandlerFcn print_handler
)
{
  if (_mcr_inst != NULL)
    return true;
  if (!mclmcrInitialize())
    return false;
  if (!GetModuleFileName(GetModuleHandle("facewarp"), path_to_dll, _MAX_PATH))
    return false;
  if (!mclInitializeComponentInstanceWithEmbeddedCTF(&_mcr_inst,
                                                     &__MCC_facewarp_component_data,
                                                     true, NoObjectType,
                                                     LibTarget, error_handler,
                                                     print_handler, 1155652, path_to_dll))
    return false;
  return true;
}

LIB_facewarp_C_API 
bool MW_CALL_CONV facewarpInitialize(void)
{
  return facewarpInitializeWithHandlers(mclDefaultErrorHandler,
                                        mclDefaultPrintHandler);
}

LIB_facewarp_C_API 
void MW_CALL_CONV facewarpTerminate(void)
{
  if (_mcr_inst != NULL)
    mclTerminateInstance(&_mcr_inst);
}

LIB_facewarp_C_API 
void MW_CALL_CONV facewarpPrintStackTrace(void) 
{
  char** stackTrace;
  int stackDepth = mclGetStackTrace(_mcr_inst, &stackTrace);
  int i;
  for(i=0; i<stackDepth; i++)
  {
    mclWrite(2 /* stderr */, stackTrace[i], sizeof(char)*strlen(stackTrace[i]));
    mclWrite(2 /* stderr */, "\n", sizeof(char)*strlen("\n"));
  }
  mclFreeStackTrace(&stackTrace, stackDepth);
}


LIB_facewarp_C_API 
bool MW_CALL_CONV mlxFaceWarp(int nlhs, mxArray *plhs[],
                              int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "FaceWarp", nlhs, plhs, nrhs, prhs);
}

LIB_facewarp_C_API 
bool MW_CALL_CONV mlfFaceWarp()
{
  return mclMlfFeval(_mcr_inst, "FaceWarp", 0, 0, 0);
}
