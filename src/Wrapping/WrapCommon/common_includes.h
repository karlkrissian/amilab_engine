#pragma once

#include <vector>
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <set>
#include <string>
#include <complex>
#include "PluginManager.h"
#include <boost/format.hpp>
#include "ami_format.h"
#include <boost/algorithm/string.hpp>
//#include <boost/predef.h>
#include "AMILabEngineConfig.h"

class myformat: public boost::format
{
  myformat(const char* st) : boost::format(st)
  {
  }
  myformat&  operator%(const char* v)     {    *this%v;    return *this;  }
  myformat&  operator%(double& v)         {    *this%v;    return *this;  }
  myformat&  operator%(unsigned int& v)   {    *this%v;    return *this;  }
  myformat&  operator%(long& v)           {    *this%v;    return *this;  }
  myformat&  operator%(int& v)            {    *this%v;    return *this;  }
};

#ifdef __GCCXML__
 
  //----------------------------------------------------------------------------
  // std::vector of basic types
  template class std::vector<double>;
  template class std::vector<float>;
  template class std::vector<int>;
  template class std::vector<long>;
  template class std::vector<unsigned long>;
  template class std::vector<std::string>;

  // short names
  typedef std::vector<double>         vector_double;
  typedef std::vector<float>          vector_float;
  typedef std::vector<int>            vector_int;
  typedef std::vector<long>           vector_long;
  typedef std::vector<unsigned long>  vector_ulong;
  typedef std::vector<std::string>    vector_string;
  
  // instanciate iterators
  vector_double::iterator vdi;
  vector_float ::iterator vfi;
  vector_int   ::iterator vii;
  vector_long  ::iterator vli;
  vector_ulong ::iterator vuli;
  vector_string::iterator vsi;

  //----------------------------------------------------------------------------
  // std::set of basic types
  template class std::set<std::string>;
  template class std::set<int>;

  // short names
  // todo: improve all this ...
  typedef std::set<std::string>                             set_string;
  typedef std::set<std::string>::iterator                   set_string_iterator;
  typedef std::pair<std::set<std::string>::iterator, bool>  set_string_pair_iterator_bool;

  typedef std::set<int>          set_int;
  
  // instanciate iterators
  set_string_iterator           ssi;
  set_string_pair_iterator_bool sspib;
  
  std::set<int>        ::iterator sii;
  
  //----------------------------------------------------------------------------
  //std::ostream std_ostream_obj;
  std::stringstream string_stream_obj;
//  std::iostream io_stream_obj;
  
  template class std::complex<float>;
  


  // use std::string operators
  template std::string  std::operator+ (const std::string&, const std::string&);
  template bool         std::operator==(const std::string&, const std::string&);
  template bool         std::operator!=(const std::string&, const std::string&);
  template bool         std::operator< (const std::string&, const std::string&);
  template bool         std::operator<=(const std::string&, const std::string&);
  template bool         std::operator> (const std::string&, const std::string&);
  template bool         std::operator>=(const std::string&, const std::string&);
  
  // boost format
//   template class boost::basic_format<char>;
//   template boost::basic_format<char>&   boost::basic_format<char>::operator%<char*>(char*&);
//   template boost::basic_format<char>&   boost::basic_format<char>::operator%<float>(float&);
  void Test()
  {
    boost::format f("%1%");
    std::cout << f % "test";
  }
  
  
  
  
  // boost string algorithms
   template std::string boost::algorithm::to_upper_copy(const std::string&,const std::locale& Loc=std::locale());
   template std::string boost::algorithm::to_lower_copy(const std::string&,const std::locale& Loc=std::locale());
  
  // problem with gccxml to wrap template member in template class 
  // so create an inherited class ...
  
  
  
//  template boost::basic_format<char>&   boost::basic_format<char>::operator%(double&);
//  template boost::basic_format<char>&   boost::basic_format<char>::operator%(unsigned int&);
//  template boost::basic_format<char>&   boost::basic_format<char>::operator%(long&);
  
#endif // __GCCXML__

#include <boost/filesystem.hpp>
  
// // trying iostream maybe should be moved from Algorithms to here ...
// #include <iostream>
// #include <sstream>
// #include <string>

