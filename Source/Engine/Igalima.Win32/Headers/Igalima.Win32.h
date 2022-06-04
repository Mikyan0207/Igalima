#pragma once

#if defined(_MSC_VER)
    #ifdef IGALIMA_WIN32_EXPORTS
        #define IGALIMA_WIN32_API __declspec(dllexport)
    #else
        #define IGALIMA_WIN32_API __declspec(dllimport)
    #endif
#elif defined(__GNUC__)
    #ifdef IGALIMA_WIN32_EXPORTS
        #define IGALIMA_WIN32_API __attribute__((visibility("default")))
    #else
        #define IGALIMA_WIN32_API
    #endif
#else
    #define IGALIMA_WIN32_API
    #pragma warning Unknown dynamic link semantics.
#endif