
#ifndef _CommonBaseConfigure_h_
#define _CommonBaseConfigure_h_

#if defined(WIN32)
  //disable warnings on extern before template instantiation
  #pragma warning (disable : 4231)
  // annoying warning 4251, passing for now ...
  #pragma warning (disable : 4251)
#endif

//#define CommonBase_SHARED
#if defined(WIN32) && defined(CommonBase_SHARED)
  //#pragma warning ( disable : 4275 )
  #if defined(CommonBase_EXPORTS)
    #define CommonBase_EXPORT __declspec( dllexport ) 
    #define CommonBase_EXPIMP_TEMPLATE
  #else
    #define CommonBase_EXPORT __declspec( dllimport ) 
    #define CommonBase_EXPIMP_TEMPLATE extern
  #endif
#else
  #define CommonBase_EXPORT 
#endif

#if defined(WIN32) && defined(CommonBase_SHARED)
  //#pragma warning ( disable : 4275 )
  #if defined(CommonBase_EXPORTS)
    #define CommonBase_VAR_EXPORT __declspec( dllexport ) 
    #define CommonBase_VAR_IMPORT __declspec( dllexport ) extern
  #else
    #define CommonBase_VAR_IMPORT __declspec( dllimport ) 
  #endif
#else
  #define CommonBase_VAR_EXPORT 
  #define CommonBase_VAR_IMPORT extern
#endif


#endif // _CommonBaseConfigure_h_
