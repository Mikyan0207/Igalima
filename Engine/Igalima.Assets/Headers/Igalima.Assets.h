#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#if defined(_MSC_VER)
    #ifdef IGALIMA_ASSETS_EXPORTS
        #define IGALIMA_ASSETS_API __declspec(dllexport)
    #else
        #define IGALIMA_ASSETS_API __declspec(dllimport)
    #endif
#elif defined(__GNUC__)
    #ifdef IGALIMA_ASSETS_EXPORTS
        #define IGALIMA_ASSETS_API __attribute__((visibility("default")))
    #else
        #define IGALIMA_ASSETS_API
    #endif
#else
    #define IGALIMA_ASSETS_API
    #pragma warning Unknown dynamic link semantics.
#endif
