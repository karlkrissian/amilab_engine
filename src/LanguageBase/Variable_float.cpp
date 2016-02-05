
#include <iomanip>
#include <cassert>
#include "boost/format.hpp"

#include "amilab_messages.h"
#include "DefineClass.hpp"
#include "Variable.hpp"
#include <math.h>
#include <iostream>

#define NEW_SMARTPTR(type, var, value) \
  boost::shared_ptr<type> var(new type(value));

#define RETURN_VARPTR(type,  value) \
  boost::shared_ptr<type> newval(new type(value)); \
  return Variable<type>::ptr( new Variable<type>(newval));

#include <boost/numeric/conversion/cast.hpp>  


std::vector<std::string> AMILabType<float>::conversion_types = 
        {   "bool", "double", 
            "long", "int", "short", 
            "unsigned long", "unsigned short", 
            "unsigned char" };

//------------------------------------------------------
//------- Variable<float>
//------------------------------------------------------

/// Copy contents to new variable
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::NewCopy() const
{
  float_ptr newval( new float(Value()));
  Variable<float>::ptr newvar(new Variable<float>(newval));
  return newvar;
}


// Arithmetic operators

/// +a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::operator +()
{  RETURN_VARPTR(float,Value());}

/// prefix ++ operator ++a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::operator ++()
{
  //std::cout << "**" << std::endl;
  RETURN_VARPTR(float,++RefValue());
}

/// postfix ++ operator a++
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::operator ++(int)
{
  //std::cout << "**" << std::endl;
  RETURN_VARPTR(float,RefValue()++);
}

/// -a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::operator -()
{   RETURN_VARPTR(float,-Value());}

/// prefix -- operator --a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::operator --()
{  RETURN_VARPTR(float,--RefValue()); }

/// postfix -- operator a--
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::operator --(int)
{  RETURN_VARPTR(float,RefValue()--);  }



/// a+b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::operator +(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(float,Value()+b->GetValueAsDouble());
  }
  else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a+=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::operator +=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() += b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a-b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::operator -(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(float,Value()-b->GetValueAsDouble());
  }
  else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a-=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::operator -=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() -= b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a*b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::operator *(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(float,Value()*b->GetValueAsDouble());
  } 
  else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a*=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::operator *=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() *= b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a/b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::operator /(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(float,Value()/b->GetValueAsDouble());
  }
  else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a/=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::operator /=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() /= b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a%b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::operator %(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(float, ((int) round(Value())) % ((int) round(b->GetValueAsDouble())));
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a%=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::operator %=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() =  ((int) round(Value())) % ((int) round(b->GetValueAsDouble()));
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

//  Comparison Operators

/// a<b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::operator <(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()<b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a<=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::operator <=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()<=b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a>b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::operator >(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()>b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a>=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::operator >=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()>=b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a!=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::operator !=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()!=b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}


/// a==b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::operator ==(const BasicVariable::ptr& b)
{ 
  //std::cout << __func__ << std::endl;
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()==b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

// Logical operators

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::operator !() 
{
  RETURN_VARPTR(bool,!(Value()>0.5));
}

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::operator &&(const BasicVariable::ptr& b) 
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,(Value()>0.5)&& (bool) (b->GetValueAsDouble()>0.5));
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::operator ||(const BasicVariable::ptr& b) 
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,(Value()>0.5) || (bool) (b->GetValueAsDouble()>0.5));
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

// Mathematical functions
#define VAR_IMPL_FUNC(type,fname,func) \
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<type>::m_##fname() \
{ \
    RETURN_VARPTR(float, func(Value())); \
}

VAR_IMPL_FUNC(float,  sin,  sin)
VAR_IMPL_FUNC(float,  cos,  cos)
VAR_IMPL_FUNC(float,  tan,  tan)
VAR_IMPL_FUNC(float,  asin, asin)
VAR_IMPL_FUNC(float,  acos, acos)
VAR_IMPL_FUNC(float,  atan, atan)
VAR_IMPL_FUNC(float,  fabs, fabs)
VAR_IMPL_FUNC(float,  round,round)
VAR_IMPL_FUNC(float,  floor,floor)
VAR_IMPL_FUNC(float,  exp,  exp)
VAR_IMPL_FUNC(float,  log,  1.0/log(10.0)*log)
VAR_IMPL_FUNC(float,  ln,   log)
VAR_IMPL_FUNC(float,  norm, fabs)
VAR_IMPL_FUNC(float,  sqrt, sqrt)
//VAR_IMPL_FUNC(float,  pow,  pow)



//---------------------------------------------------
template<> AMI_DLLEXPORT
BasicVariable::ptr Variable<float>::TryCast(
    const std::string& type_string) const
{
  try
  {
    // cast to double
    if (type_string==AMILabType<double>::name_as_string()) {
      RETURN_VARPTR(double, boost::numeric_cast<double>(Value()));
    } else
    // cast to int
    if (type_string==AMILabType<int>::name_as_string()) {
      RETURN_VARPTR(int, boost::numeric_cast<int>(Value()));
    } else 
    // cast to long
    if (type_string==AMILabType<long>::name_as_string()) {
      RETURN_VARPTR(long, boost::numeric_cast<long>(Value()));
    } else 
    // cast to unsigned long
    if (type_string==AMILabType<unsigned long>::name_as_string()) {
      RETURN_VARPTR(unsigned long, boost::numeric_cast<unsigned long>(Value()));
    } else 
    // cast to short
    if (type_string==AMILabType<short>::name_as_string()) {
      RETURN_VARPTR(short, boost::numeric_cast<short>(Value()));
    } else 
    // cast to unsigned short
    if (type_string==AMILabType<unsigned short>::name_as_string()) {
      RETURN_VARPTR(unsigned short, boost::numeric_cast<unsigned short>(Value()));
    } else 
    // cast to unsigned char
    if (type_string==AMILabType<unsigned char>::name_as_string()) {
      RETURN_VARPTR(unsigned char, boost::numeric_cast<unsigned char>(Value()));
    } else
    // cast to bool
    if (type_string==AMILabType<bool>::name_as_string()) {
      RETURN_VARPTR(bool, boost::numeric_cast<bool>(Value()));
    } else
    {
      // make default conversion to double??
      CLASS_ERROR((boost::format("No conversion available for variable %1% from float to %2%") % _name % type_string).str().c_str());
    }
  } catch (std::bad_cast &e)
  {
    CLASS_ERROR((boost::format("%1%, for variable %2% from float to %3%") % e.what() % _name % type_string).str().c_str());
    return BasicVariable::ptr();
  }
  return BasicVariable::ptr();
}


//
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<float>::BasicCast(const int& type)
{
#define NUMCAST(amitype,type) \
      case amitype:  { RETURN_VARPTR(type, boost::numeric_cast<type>(Value())); }

  try
  {
    switch((WORDTYPE)type) {
      NUMCAST( WT_UNSIGNED_CHAR,  unsigned char )
      NUMCAST( WT_SIGNED_SHORT,   short         )
      NUMCAST( WT_UNSIGNED_SHORT, unsigned short)
      NUMCAST( WT_SIGNED_INT,     int           )
      NUMCAST( WT_SIGNED_LONG,    long          )
      NUMCAST( WT_FLOAT,          float         )
      NUMCAST( WT_DOUBLE,         double        )
      case WT_UNSIGNED_INT: { RETURN_VARPTR(float, (unsigned int) Value()); }
      default:
        CLASS_ERROR(( boost::format("Conversion to type %1% not available")%((WORDTYPE)type)).str().c_str());
    }
  } catch (std::bad_cast &e)
  {
    CLASS_ERROR((boost::format("%1%, for variable %2% from float to WORDTYPE %3%") % e.what() % _name % (WORDTYPE)type ).str().c_str());
    return BasicVariable::ptr();
  }

  RETURN_VARPTR(float, Value());

}

//
template<> AMI_DLLEXPORT
BasicVariable::ptr Variable<float>::TernaryCondition(const BasicVariable::ptr& v1, const BasicVariable::ptr&v2)
{

  if (Value()>0.5) {
    return v1->NewReference();
  } else {
    return v2->NewReference();
  }
  return NewReference();
}

#if !defined(ARRAY_SIZE)
    #define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#endif

template<> AMI_DLLEXPORT
  BasicVariable::ptr Variable<float>::operator[](const BasicVariable::ptr& v)
{
  if (v->IsNumeric()) {
    float* pointer = this->Pointer().get();
    //std::cout << "Size of array " << ARRAY_SIZE(pointer) << std::endl;
    // at the user own risk
    float res = pointer[(int)(v->GetValueAsDouble()+0.5)];
    return AMILabType<float>::CreateVar(res);
  } else
    CLASS_ERROR("operator[] only takes a numerical parameter");
  return NewReference();
}

template<> AMI_DLLEXPORT 
BasicVariable::ptr Variable<float>::operator =(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RefValue() = b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return NewReference();
}
