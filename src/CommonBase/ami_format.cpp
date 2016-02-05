

#include "ami_format.h"
#include <boost/format.hpp>
#include <string>
//#include <stdio.h>


namespace ami {
  
  class AmiString {
    public:
      std::string _st;
  };
  
  //----------------------------------
  format::format(const char* st)
  {
     boost::format* f = new boost::format(st);
    // avoid exceptions
    f->exceptions( boost::io::all_error_bits ^ ( boost::io::too_many_args_bit | boost::io::too_few_args_bit )  );
    _boost_format = (void*) f;
    _st = new AmiString();
  }

  //----------------------------------
  format::~format()
  {
    delete static_cast<boost::format*>(_boost_format);
    delete _st;
  }

  //----------------------------------
  format& format::operator%(const char* st)
  {
    boost::format* f = static_cast<boost::format*>(_boost_format);

    (*f) = (*f) % st;
    return *this;
  }

  //----------------------------------
  format& format::operator%(const int& val)
  {
    boost::format* f = static_cast<boost::format*>(_boost_format);
    (*f) = (*f) % val;
    return *this;
  }

  //----------------------------------
  format& format::operator%(const float& val)
  {
    boost::format* f = static_cast<boost::format*>(_boost_format);
    (*f) = (*f) % val;
    return *this;
  }

  //----------------------------------
  format& format::operator%(const double& val)
  {
    boost::format* f = static_cast<boost::format*>(_boost_format);
    (*f) = (*f) % val;
    return *this;
  }

  //----------------------------------
  const char* format::GetString() const
  {
    boost::format* f = static_cast<boost::format*>(_boost_format);
    _st->_st = (*f).str();
    return _st->_st.c_str();
  }

  //----------------------------------
  const char* format::c_str() const
  {
    boost::format* f = static_cast<boost::format*>(_boost_format);
    _st->_st = (*f).str();
    return _st->_st.c_str();
  }
}
