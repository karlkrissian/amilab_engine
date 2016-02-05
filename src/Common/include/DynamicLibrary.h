// DynamicLibrary.h
#ifndef DynamicLibrary_H
#define DynamicLibrary_H
 
#include <iostream>

#ifdef _WIN32
  #include<windows.h>
  typedef  HMODULE DynamicLibraryPtr;
#else
  #include<dlfcn.h>
  typedef void* DynamicLibraryPtr;
#endif

class DynamicLibrary
{
  
public:
  
  //----------------------------------------------------------------------------
  DynamicLibrary() : m_handle(0) {}

  //----------------------------------------------------------------------------
  DynamicLibrary(const char* libname) 
  {
    Load(libname);
  }

  //----------------------------------------------------------------------------
  ~DynamicLibrary() 
  {
    if (m_handle) Free();
  }
  
  //----------------------------------------------------------------------------
  DynamicLibraryPtr GetHandle()
  {
    return m_handle;
  }
  
  //----------------------------------------------------------------------------
  DynamicLibraryPtr Load(const char* libname)
  //                ----
  {
    if (m_handle)
      Free();
    #ifdef _WIN32
      m_handle = LoadLibraryA(libname);
    #else
      m_handle = dlopen( libname, RTLD_LAZY );
      if (!m_handle) {
          std::cerr << dlerror() << std::endl;
      }
    #endif
    return m_handle;
  }
  
  //----------------------------------------------------------------------------
  int Free()
  {
    // TODO: deal with errors
    int res = 0;
    if (m_handle)
    {
      #ifdef _WIN32
        res = FreeLibrary( m_handle );
        m_handle = 0;
      #else
        res = dlclose( m_handle );
        m_handle = 0;
      #endif
    }
    return res;
  }
  
  
  //----------------------------------------------------------------------------
  template<typename Func>
  Func GetFunc( const char *symbol )
  //   -------
  {
    // TODO: check for errors
    #ifdef _WIN32
      return (Func)GetProcAddress( m_handle, symbol );
    #else
      return (Func)dlsym( m_handle, symbol );
    #endif
  }
  
private:
  
  DynamicLibraryPtr m_handle;
  
};

 
#endif
