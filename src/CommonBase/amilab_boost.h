//
// C++ Interface: amilab_boost
//
// Description: utility for boost
//
//
// Author: Karl Krissian <>, (C) 2010
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef _amilab_boost_h_
#define _amilab_boost_h_

//#include "Variable.hpp"
//#include "paramlist.h"
#include <boost/shared_ptr.hpp>
#include <stdio.h>

/// Generic class with operator for creating smart pointers
template<class T>
class CreateSmartPointer
{
  public:
  boost::shared_ptr<T> operator() (T* p) 
  {
    return boost::shared_ptr<T>(p);
  }
};

typedef boost::shared_ptr<float>           float_ptr;
typedef boost::shared_ptr<int>             int_ptr;
typedef boost::shared_ptr<long>            long_ptr;
typedef boost::shared_ptr<unsigned long>   ulong_ptr;
typedef boost::shared_ptr<short>           short_ptr;
typedef boost::shared_ptr<unsigned short>  ushort_ptr;
typedef boost::shared_ptr<unsigned char>   uchar_ptr;
typedef boost::shared_ptr<std::string>     string_ptr;
typedef boost::shared_ptr<FILE>            FILE_ptr;

/// FILE deleter
class file_deleter
{
  public:
    void operator()(FILE * p)
    {
      if (p!=NULL)
        if (p!=stdout)
          fclose(p);
    }
};

// for files opened with popen
class pfile_deleter
{
  public:
    void operator()(FILE * p)
    {
      if (p!=NULL)
        if (p!=stdout)
          #ifdef _MSC_VER
            _pclose(p);
          #else
            pclose(p);
          #endif
    }
};

/// Specialization for FILE
template<>
class CreateSmartPointer<FILE>
{
  public:
  boost::shared_ptr<FILE> operator() (FILE* p) 
  {
    return boost::shared_ptr<FILE>(p,file_deleter());
  }
};

/// smart pointer without deleter
template<class T>
class smartpointer_nodeleter
  {
  public:
    void operator()(T * p)  {  }
  };


/*
/// Specialization for C_wrap_varfunction
template<>
class CreateSmartPointer<C_wrap_varfunction>
{
  public:
  boost::shared_ptr<C_wrap_varfunction> operator() (C_wrap_varfunction* p) 
  {
    return boost::shared_ptr<C_wrap_varfunction>
            (p,smartpointer_nodeleter<C_wrap_varfunction>());
  }
};

/// Specialization for C_wrap_procedure
template<>
class CreateSmartPointer<C_wrap_procedure>
{
  public:
  boost::shared_ptr<C_wrap_procedure> operator() (C_wrap_procedure* p) 
  {
    return boost::shared_ptr<C_wrap_procedure>(p,
                  smartpointer_nodeleter<C_wrap_procedure>());
  }
};

/// Specialization for C_wrap_imagefunction
template<>
class CreateSmartPointer<C_wrap_imagefunction>
{
  public:
  boost::shared_ptr<C_wrap_imagefunction> operator() (C_wrap_imagefunction* p) 
  {
    return boost::shared_ptr<C_wrap_imagefunction>(p,
              smartpointer_nodeleter<C_wrap_imagefunction>());
  }
};
*/

#endif
// _amilab_boost_h_
