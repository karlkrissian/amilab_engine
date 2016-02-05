
#ifndef _LanguageConfigure_h_
#define _LanguageConfigure_h_

#if defined(WIN32)
  //disable warnings on extern before template instantiation
  #pragma warning (disable : 4231)
  // annoying warning 4251, passing for now ...
  #pragma warning (disable : 4251)
#endif

//#define Language_SHARED
#if defined(WIN32) && defined(Language_SHARED)
  //#pragma warning ( disable : 4275 )
  #if defined(Language_EXPORTS)
    #define Language_EXPORT __declspec( dllexport ) 
    #define Language_EXPIMP_TEMPLATE
  #else
    #define Language_EXPORT __declspec( dllimport ) 
    #define Language_EXPIMP_TEMPLATE extern
  #endif
#else
  #define Language_EXPORT 
#endif

#if defined(WIN32) && defined(Language_SHARED)
  //#pragma warning ( disable : 4275 )
  #if defined(Language_EXPORTS)
    #define Language_VAR_EXPORT __declspec( dllexport ) 
    #define Language_VAR_IMPORT __declspec( dllexport ) extern
  #else
    #define Language_VAR_EXPORT 
    #define Language_VAR_IMPORT __declspec( dllimport ) 
  #endif
#else
  #define Language_VAR_EXPORT 
  #define Language_VAR_IMPORT extern
#endif


#endif // _LanguageConfigure_h_
