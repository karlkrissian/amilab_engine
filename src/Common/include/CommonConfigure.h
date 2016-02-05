
#ifndef _CommonConfigure_h_
#define _CommonConfigure_h_

#if defined(WIN32)
  //disable warnings on extern before template instantiation
  #pragma warning (disable : 4231)
  // annoying warning 4251, passing for now ...
  #pragma warning (disable : 4251)
#endif

//#define COMMON_SHARED
#if defined(WIN32) && defined(COMMON_SHARED)
  //#pragma warning ( disable : 4275 )
  #if defined(COMMON_EXPORTS)
    #define COMMON_EXPORT __declspec( dllexport ) 
    #define COMMON_EXPIMP_TEMPLATE
  #else
    #define COMMON_EXPORT __declspec( dllimport ) 
    #define COMMON_EXPIMP_TEMPLATE extern
  #endif
#else
  #define COMMON_EXPORT 
#endif

#if defined(WIN32) && defined(COMMON_SHARED)
  //#pragma warning ( disable : 4275 )
  #if defined(COMMON_EXPORTS)
    #define COMMON_VAR_EXPORT __declspec( dllexport ) 
    #define COMMON_VAR_IMPORT __declspec( dllexport ) extern
  #else
    #define COMMON_VAR_IMPORT __declspec( dllimport ) 
  #endif
#else
  #define COMMON_VAR_EXPORT 
  #define COMMON_VAR_IMPORT extern
#endif


#endif // _CommonConfigure_h_
