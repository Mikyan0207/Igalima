#ifndef _IGALIMA_H
#define _IGALIMA_H

#if defined(_MSC_VER)
  #ifdef IGALIMA_EXPORTS
    #define IGALIMA_API __declspec(dllexport)
  #else
    #define IGALIMA_API __declspec(dllimport)
  #endif
#elif defined(__GNUC__)
  #ifdef IGALIMA_EXPORTS
    #define IGALIMA_API __attribute__((visibility("default")))
  #else
    #define IGALIMA_API
  #endif
#else
  #define IGALIMA_API
  #pragma warning Unknown dynamic link semantics.
#endif

#endif //_IGALIMA_H
