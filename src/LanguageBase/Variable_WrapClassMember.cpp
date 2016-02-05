
#include <iomanip>
#include <cassert>
#include "boost/format.hpp"

#include "amilab_messages.h"
#include "DefineClass.hpp"
#include "Variable.hpp"
#include <math.h>
#include <boost/pointer_cast.hpp>
#include "ami_object.h"
#include "ami_function.h"
#include "paramlist.h"
#include "wrapfunction_class.h"
#include "wrapfunctions.hpp"

#include "DriverBase.h"
#include "LanguageBaseConfigure.h"
LanguageBase_VAR_IMPORT DriverBase::ptr  GB_DriverBase;

#define NEW_SMARTPTR(type, var, value) \
  boost::shared_ptr<type> var(new type(value));



//------------------------------------------------------------------------------
template<>  AMI_DLLEXPORT 
  Variable<WrapClassMember>::Variable(const boost::shared_ptr<WrapClassMember>& p)
{
  _type    = GetVarType<WrapClassMember>();
  _name    = "tmpvar";
  _pointer = boost::shared_ptr<WrapClassMember>(p);
}

//------------------------------------------------------------------------------
template<>  AMI_DLLEXPORT 
  Variable<WrapClassMember>::Variable( WrapClassMember* p)
{
  _type    = GetVarType<WrapClassMember>();
  _name    = "tmpvar";
  _pointer = boost::shared_ptr<WrapClassMember>(p);
}

//------------------------------------------------------------------------------
template<>  AMI_DLLEXPORT 
  Variable<WrapClassMember>::Variable(const std::string& name, 
           const boost::shared_ptr<WrapClassMember>& p)
{
  _type    = GetVarType<WrapClassMember>();
  _name    = name;
  _pointer = boost::shared_ptr<WrapClassMember>(p);
}

//------------------------------------------------------------------------------
template<>  AMI_DLLEXPORT bool Variable<WrapClassMember>::Equal( BasicVariable::ptr v)
{
  if (_type == v->Type()) {
    // convert pointer
    ptr newvar (boost::dynamic_pointer_cast<Variable<WrapClassMember> >(v));
    return ((_name     == newvar->_name) &&
            (_comments == newvar->_comments) &&
            (_pointer.get()  == newvar->_pointer.get()));

  }
  else return false;
}



//------------------------------------------------------
//------- Variable<WrapClassMember>
//------------------------------------------------------

/// Cast to a type based on its name as a string
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::TryCast(const std::string& type_string) const
{
  return BasicVariable::ptr();
}


// Arithmetic operators

/// +a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator +()
{
  return BasicVariable::ptr();
}

/// -a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator -()
{
  return BasicVariable::empty_variable;
}

/*

/// prefix -- operator --a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator --()
{  RETURN_VARPTR(WrapClassMember,--RefValue()); }


*/

/// prefix * operator *a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator *()
{
  return BasicVariable::empty_variable;
}

/// prefix ++ operator ++a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator ++()
{
  return BasicVariable::empty_variable;
}

/// postfix ++ operator a++
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator ++(int)
{
  return BasicVariable::empty_variable;
}

/// prefix -- operator --a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator --()
{
  return BasicVariable::empty_variable;
}

/// postfix -- operator a--
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator --(int)
{
  return BasicVariable::empty_variable;
}

/// a+b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator +(const BasicVariable::ptr& b)
{
  return BasicVariable::empty_variable;
}


/// a+=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator +=(const BasicVariable::ptr& b)
{ 
  return BasicVariable::empty_variable;
}

/// a-b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator -(const BasicVariable::ptr& b)
{
  return BasicVariable::empty_variable;
}

/// a-=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator -=(const BasicVariable::ptr& b)
{ 
  return BasicVariable::empty_variable;
}

/// a*b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator *(const BasicVariable::ptr& b)
{
  return BasicVariable::empty_variable;
}

/// a*=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator *=(const BasicVariable::ptr& b)
{ 
  return BasicVariable::empty_variable;
}

/// a/b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator /(const BasicVariable::ptr& b)
{
  return BasicVariable::empty_variable;
}

/// a/=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator /=(const BasicVariable::ptr& b)
{ 
  return BasicVariable::empty_variable;
}


/// a%b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator %(const BasicVariable::ptr& b)
{
  return BasicVariable::empty_variable;
}

/// a%=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator %=(const BasicVariable::ptr& b)
{ 
  return BasicVariable::empty_variable;
}

/*

/// a*=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator *=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() *= b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}


/// a/=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator /=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() /= b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}
*/

//  Comparison Operators

/// a<b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator <(const BasicVariable::ptr& b)
{ 
  return BasicVariable::empty_variable;
}

/// a<=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator <=(const BasicVariable::ptr& b)
{ 
  return BasicVariable::empty_variable;
}

/// a>b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator >(const BasicVariable::ptr& b)
{ 
  return BasicVariable::empty_variable;
}

/// a>=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator >=(const BasicVariable::ptr& b)
{ 
  return BasicVariable::empty_variable;
}

/// a!=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator !=(const BasicVariable::ptr& b)
{ 
  return BasicVariable::empty_variable;
}

/// a==b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator ==(const BasicVariable::ptr& b)
{ 
  return BasicVariable::empty_variable;
}


// Logical operators

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator !() 
{
  return BasicVariable::empty_variable;
}

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator &&(const BasicVariable::ptr& b) 
{
  return BasicVariable::empty_variable;
}

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator ||(const BasicVariable::ptr& b) 
{
  return BasicVariable::empty_variable;
}

/// a^b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator ^(const BasicVariable::ptr& b)
{ 
  return BasicVariable::empty_variable;
}

/// a&b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator &(const BasicVariable::ptr& b)
{ 
  return BasicVariable::empty_variable;
}

/// a|b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator |(const BasicVariable::ptr& b)
{ 
  return BasicVariable::empty_variable;
}

///  norm(image)
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::m_norm() 
{ 
  return BasicVariable::empty_variable;
}

// Image Pixel Type Cast
template<> LanguageBase_EXPORT 
  BasicVariable::ptr 
    Variable<WrapClassMember>::BasicCast(const int& type)
{
  return BasicVariable::empty_variable; 
}

template<> LanguageBase_EXPORT  
  BasicVariable::ptr 
    Variable<WrapClassMember>::PointWiseMult(const BasicVariable::ptr& b)
{
  return BasicVariable::empty_variable; 
}

template<> LanguageBase_EXPORT 
  BasicVariable::ptr 
    Variable<WrapClassMember>::Transpose()
{
  return BasicVariable::empty_variable; 
}

// Mathematical functions

#define VAR_IMPL_FUNC(type,fname,func) \
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<type>::m_##fname() \
{ \
  return BasicVariable::empty_variable; \
}

VAR_IMPL_FUNC(WrapClassMember,  sin,  sin)
VAR_IMPL_FUNC(WrapClassMember,  cos,  cos)
VAR_IMPL_FUNC(WrapClassMember,  tan,  tan)
VAR_IMPL_FUNC(WrapClassMember,  asin, asin)
VAR_IMPL_FUNC(WrapClassMember,  acos, acos)
VAR_IMPL_FUNC(WrapClassMember,  atan, atan)
VAR_IMPL_FUNC(WrapClassMember,  fabs, fabs)
VAR_IMPL_FUNC(WrapClassMember,  round,round)
VAR_IMPL_FUNC(WrapClassMember,  floor,floor)
VAR_IMPL_FUNC(WrapClassMember,  exp,  exp)
VAR_IMPL_FUNC(WrapClassMember,  log,  log)
VAR_IMPL_FUNC(WrapClassMember,  ln,   log)
VAR_IMPL_FUNC(WrapClassMember,  sqrt, sqrt)


/**
 * Array subscript operator
 * @param v 
 * @return 
 */
template<>  BasicVariable::ptr Variable<WrapClassMember>::operator[](const BasicVariable::ptr& v)
{
  return BasicVariable::empty_variable;
}


//
template<> LanguageBase_EXPORT
  BasicVariable::ptr 
    Variable<WrapClassMember>::TernaryCondition(const BasicVariable::ptr& v1, 
                                          const BasicVariable::ptr&v2)
{
  return BasicVariable::empty_variable;
}


template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::operator =(const BasicVariable::ptr& b)
{
  return BasicVariable::ptr();
}


// TODO: put this code within a macro???
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<WrapClassMember>::left_assign(const BasicVariable::ptr& b)
{
  return BasicVariable::ptr();
}
