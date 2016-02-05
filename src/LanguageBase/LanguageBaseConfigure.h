#pragma once
#ifndef _LanguageBaseConfigure_h_
#define _LanguageBaseConfigure_h_

#if defined(WIN32)
  //disable warnings on extern before template instantiation
  #pragma warning (disable : 4231)
  // annoying warning 4251, passing for now ...
  #pragma warning (disable : 4251)
#endif

#define LanguageBase_SHARED
#if defined(WIN32) && defined(LanguageBase_SHARED)
  //#pragma warning ( disable : 4275 )
  #if defined(LanguageBase_EXPORTS)
    #define LanguageBase_EXPORT __declspec( dllexport ) 
    #define LanguageBase_EXPIMP_TEMPLATE
  #else
    #define LanguageBase_EXPORT __declspec( dllimport ) 
    #define LanguageBase_EXPIMP_TEMPLATE extern
  #endif
#else
  #define LanguageBase_EXPORT 
#endif

#if defined(WIN32) && defined(LanguageBase_SHARED)
  //#pragma warning ( disable : 4275 )
  #if defined(LanguageBase_EXPORTS)
    #define LanguageBase_VAR_EXPORT __declspec( dllexport ) 
    #define LanguageBase_VAR_IMPORT __declspec( dllexport ) extern
  #else
    #define LanguageBase_VAR_EXPORT 
    #define LanguageBase_VAR_IMPORT __declspec( dllimport ) 
  #endif
#else
  #define LanguageBase_VAR_EXPORT 
  #define LanguageBase_VAR_IMPORT extern
#endif


#endif // _LanguageBaseConfigure_h_
