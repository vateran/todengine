#pragma once
#include "todcore/platform.h"



//cross-platform



//lib export
#define TODEXPORT


//directives
#define OVERRIDE virtual
#define IN
#define OUT
#define INOUT


//helpers
#define SAFE_DELETE(p) if (p) { delete p; p = 0; }
#define SAFE_RELEASE(p) if (p) { p->release(); p = 0; }
#define TOD_TRACE() do { } while (0)


//STL helpers
#ifdef TODENGINE_PLATFORM_WIN32
    #define TOD_ERASE_LIST_ELEM(v, iterator) do { iterator = v.erase(iterator); } while (0)
#else
    #define TOD_ERASE_LIST_ELEM(v, iterator) v.erase(iterator++)
#endif

#ifdef TODENGINE_PLATFORM_WIN32
    #ifdef TOD_USING_UNICODE
        #define TOD_STRLEN wcslen
        #define TOD_STRCMP wcscmp
        #define TOD_SNPRINTF _snwprintf_s
        #define TOD_VSNPRINTF _vsnwprintf_s
    #else
        #define TOD_STRLEN strlen
        #define TOD_STRCMP strcmp
        #define TOD_SNPRINTF(buf, len, format, ...) _snprintf_s(buf, len, len, format, __VA_ARGS__)
        #define TOD_VSNPRINTF _vsnprintf_s
    #endif
#else
    #ifdef TOD_USING_UNICODE
    #else
        #define TOD_STRLEN strlen
        #define TOD_STRCMP strcmp
        #define TOD_SNPRINTF snprintf
        #define TOD_VSNPRINTF vsnprintf
    #endif
#endif




