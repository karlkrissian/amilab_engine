
#ifndef _AMILabConfigure_h_
#define _AMILabConfigure_h_

#if defined(WIN32)
  //disable warnings on extern before template instantiation
  #pragma warning (disable : 4231)
  // annoying warning 4251, passing for now ...
  #pragma warning (disable : 4251)
#endif

//#define AMILab_SHARED
#if defined(WIN32) && defined(AMILab_SHARED)
  //#pragma warning ( disable : 4275 )
  #if defined(AMILab_EXPORTS)
    #define AMILab_EXPORT __declspec( dllexport ) 
    #define AMILab_EXPIMP_TEMPLATE
  #else
    #define AMILab_EXPORT __declspec( dllimport ) 
    #define AMILab_EXPIMP_TEMPLATE extern
  #endif
#else
  #define AMILab_EXPORT 
#endif

#if defined(WIN32) && defined(AMILab_SHARED)
  //#pragma warning ( disable : 4275 )
  #if defined(AMILab_EXPORTS)
    #define AMILab_VAR_EXPORT __declspec( dllexport ) 
    #define AMILab_VAR_IMPORT __declspec( dllexport ) extern
  #else
    #define AMILab_VAR_EXPORT 
    #define AMILab_VAR_IMPORT __declspec( dllimport ) 
  #endif
#else
  #define AMILab_VAR_EXPORT 
  #define AMILab_VAR_IMPORT extern
#endif


#endif // _AMILabConfigure_h_
