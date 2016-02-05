
#include "DefineClass.hpp"
#include "Variable.hpp"

#include <string>
//#include <ostream>
//#include <sstream>
//#include <limits>




//------------------------------------------------------------//  Variable
//------------------------------------------------------------
template<class T>
Variable<T>::Variable()
{
  _type         = type_void;
}


//------------------------------------------------
template<class T>
void Variable<T>::operator = (const Variable<T>& v)
{
    _comments     = v._comments;
    this->Init(v._name, v._pointer);

}


//------------------------------------------------
template<class T>
void Variable<T>::Init(const std::string& name, const boost::shared_ptr<T>& p)
{
  _type         = GetVarType<T>();
  _name         = name;
  _pointer      = boost::shared_ptr<T>(p); 

}


template<class T>
void Variable<T>::Delete() 
{
  if (!FreeMemory()) 
  {
/*    CLASS_MESSAGE(boost::format("Could not completely delete variable %s") % _name);*/
  }
  _type = type_void;
}

//---------------------------------------------------
template<class T>
BasicVariable::ptr Variable<T>::TryCast(const std::string& type_string) const
{
  // make default conversion to double??
  /*CLASS_ERROR(boost::format("Could not convert variable %1% to type %2%") % _name % type_string);*/
  return BasicVariable::ptr();
}

void LanguageBase_EXPORT ToStream(std::ostream& o, const char* st);

//---------------------------------------------------
template<class T>
std::ostream& operator<<(std::ostream& o, const Variable<T>& v)
//       -----------
{
  if (v.Type()==type_void) { ToStream(o, "deleted"); return o;}
  ami::format f("%1%\t<%2%>");
  ToStream(o , (f % v.Name().c_str() % v.GetTypeName().c_str()).GetString());

// TODO: take care of this functionality
//  o << ;
/*  switch(v.Type()) {
    //      case type_void     : printf("void";     break;
    case type_image           : o << "image    "; break;
    case type_bool            : o << "bool     "; break;
    case type_float           : o << "float    "; break;
    case type_int             : o << "int      "; break;
    case type_uchar           : o << "uchar    "; break;
    case type_string          : o << "string   "; break;
    case type_surfdraw        : o << "surfdraw "; break;
  //  case type_file            : o << "file     "; break;
  //  case type_c_function      : o << ("C function ";       break;
    case type_c_procedure     : o << "C procedure ";       break;
    case type_class_member : o << "C++ procedure member";       break;
    case type_c_image_function: o << "C image function ";  break;
    case type_c_function      : o << "C function ";        break;
    case type_ami_function    : o << "AMI function ";      break;
    case type_ami_class       : o << "AMI class ";         break;
    case type_ami_object      : o << "AMI Object ";         break;
    case type_matrix          : o << "matrix";             break;
    case type_gltransform     : o << "gltransform";        break;
    case type_array           : 
    {
// TODO ...
//      VarArray::ptr array =  *((VarArray::ptr*) v.Pointer());
//      o << format("array \t %d \n") % array->Size();
//      o << *array;

      break;
    }
    default                : o << "unknown type ";     break;
  }
*/
  //      o << ("\n");
  return o;
} // operator << Variable

template <class T>
void Variable<T>::display(std::ostream& o) const
{
  o << (*this);
}

/*
template <class T>
std::string Variable<T>::GetValueAsString() const
{
  // by default use the << operator to return the variable type
  std::stringstream tmpstr;
  tmpstr << "Variable of type " << *this << ", no string conversion available.";
  return tmpstr.str();
}
*/

/*
template <class T, class U>
BasicVariable::ptr operator +(const boost::shared_ptr<Variable<T> >& a, 
                              const boost::shared_ptr<Variable<U> >& b)
{
  std::cout << "Method a+b ..." << std::endl;
  // right now only float operations
  if ((std::numeric_limits<T>::is_specialized) && (std::numeric_limits<U>::is_specialized))
  {
    // TODO: keep the type that is more accurate ..., or always return float or double ???
    boost::shared_ptr<T> newval(new T(a->Value()+b->Value())); 
    return boost::shared_ptr<Variable<T> >( new Variable<T>(newval ));
  }
  else
  {
   std::cout << "Operation not defined, returning null float variable" << std::endl;
    return boost::shared_ptr<Variable<T> >();
  }
}
*/

//template BasicVariable::ptr operator +(const Variable<float>::ptr& a, const Variable<float>::ptr& b);

// templated  may not be virtual !!!
/*
template <class T>
template <class U>
BasicVariable::ptr Variable<T>::operator +(const Variable<U>& b)
{
  std::cout << __func__ << std::endl;
  // right now only float operations
  if (std::numeric_limits<T>::is_specialized && std::numeric_limits<U>::is_specialized)
  {
    // TODO: keep the type that is more accurate ..., or always return float or double ???
    boost::shared_ptr<T> newval(new T(Value()+b.Value())); 
    return Variable<T>::ptr( new Variable<T>(newval ));
  }
  else
  {
   std::cout << "Operation not defined, returning null float variable" << std::endl;
    return Variable<float>::ptr();
  }
}


template BasicVariable::ptr Variable<float>::operator +(const Variable<float>& b);
*/

/*

template<> BasicVariable::ptr Variable<FILE>::NewCopy()
{
  // don't copy a file, keep a reference ...
  CLASS_MESSAGE(boost::format("Don't copy a file, keep a reference to it ... for variable %1% ")
                      % Name());
  return NewReference();
}

*/
