#pragma once


//platform detection
#ifdef WIN32
    #define TODENGINE_PLATFORM_WIN32
    #define WIN32_LEAN_AND_MEAN

    #pragma warning(disable:4244)
#endif

#ifdef __APPLE__
    #define TODENGINE_PLATFORM_UNIX
    #if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
        #define TODENGINE_PLATFORM_IOS
    #elif defined(TARGET_OS_MAC)
        #define TODENGINE_PLATFORM_MAC    
    #endif
    #define sealed
#endif

#if defined(__GNUC__) || defined(__GNUG__)
    #define TODENGINE_PLATFORM_UNIX
#endif

