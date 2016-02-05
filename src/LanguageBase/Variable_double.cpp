
#include <iomanip>
#include <cassert>
#include "boost/format.hpp"

#include "amilab_messages.h"
#include "DefineClass.hpp"
#include "Variable.hpp"
#include <math.h>

#define NEW_SMARTPTR(type, var, value) \
  boost::shared_ptr<type> var(new type(value));

#define RETURN_VARPTR(type,  value) \
  boost::shared_ptr<type> newval(new type(value)); \
  return Variable<type>::ptr( new Variable<type>(newval));


#include <boost/numeric/conversion/cast.hpp>  

// initialize conversions
std::vector<std::string> AMILabType<double>::conversion_types = 
        { "bool", "float", "long", "int", "unsigned char", "short" };

//------------------------------------------------------
//------- Variable<double>
//------------------------------------------------------

/// Copy contents to new variable
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::NewCopy() const
{
  boost::shared_ptr<double> newval( new double(Value()));
  Variable<double>::ptr newvar(new Variable<double>(newval));
  return newvar;
}


// Arithmetic operators

/// +a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::operator +()
{  RETURN_VARPTR(double,Value());}

/// prefix ++ operator ++a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::operator ++()
{
  //std::cout << "**" << std::endl;
  RETURN_VARPTR(double,++RefValue());
}

/// postfix ++ operator a++
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::operator ++(int)
{
  //std::cout << "**" << std::endl;
  RETURN_VARPTR(double,RefValue()++);
}

/// -a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::operator -()
{   RETURN_VARPTR(double,-Value());}

/// prefix -- operator --a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::operator --()
{  RETURN_VARPTR(double,--RefValue()); }

/// postfix -- operator a--
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::operator --(int)
{  RETURN_VARPTR(double,RefValue()--);  }



/// a+b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::operator +(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(double,Value()+b->GetValueAsDouble());
  }
  else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a+=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::operator +=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() += b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a-b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::operator -(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(double,Value()-b->GetValueAsDouble());
  }
  else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a-=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::operator -=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() -= b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a*b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::operator *(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(double,Value()*b->GetValueAsDouble());
  } 
  else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a*=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::operator *=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() *= b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a/b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::operator /(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(double,Value()/b->GetValueAsDouble());
  }
  else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a/=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::operator /=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() /= b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a%b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::operator %(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(double, ((int) round(Value())) % ((int) round(b->GetValueAsDouble())));
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a%=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::operator %=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() =  ((int) round(Value())) % ((int) round(b->GetValueAsDouble()));
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

//  Comparison Operators

/// a<b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::operator <(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()<b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a<=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::operator <=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()<=b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a>b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::operator >(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()>b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a>=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::operator >=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()>=b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a!=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::operator !=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()!=b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}


/// a==b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::operator ==(const BasicVariable::ptr& b)
{ 
  //std::cout << __func__ << std::endl;
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()==b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

// Logical operators

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::operator !() 
{
  RETURN_VARPTR(bool,!(Value()>0.5));
}

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::operator &&(const BasicVariable::ptr& b) 
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()&& (bool) (b->GetValueAsDouble()>0.5));
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::operator ||(const BasicVariable::ptr& b) 
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value() || (bool) (b->GetValueAsDouble()>0.5));
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

// Mathematical functions
#define VAR_IMPL_FUNC(type,fname,func) \
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<type>::m_##fname() \
{ \
    RETURN_VARPTR(double, func(Value())); \
}

VAR_IMPL_FUNC(double,  sin,  sin)
VAR_IMPL_FUNC(double,  cos,  cos)
VAR_IMPL_FUNC(double,  tan,  tan)
VAR_IMPL_FUNC(double,  asin, asin)
VAR_IMPL_FUNC(double,  acos, acos)
VAR_IMPL_FUNC(double,  atan, atan)
VAR_IMPL_FUNC(double,  fabs, fabs)
VAR_IMPL_FUNC(double,  round,round)
VAR_IMPL_FUNC(double,  floor,floor)
VAR_IMPL_FUNC(double,  exp,  exp)
//VAR_IMPL_FUNC(double,  log,  1.0/log(10.0)*log)
VAR_IMPL_FUNC(double,  log,  log10)
VAR_IMPL_FUNC(double,  ln,   log)
VAR_IMPL_FUNC(double,  norm, fabs)
VAR_IMPL_FUNC(double,  sqrt, sqrt)
//VAR_IMPL_FUNC(double,  pow,  pow)


//---------------------------------------------------
template<> AMI_DLLEXPORT
BasicVariable::ptr Variable<double>::TryCast(
    const std::string& type_string) const
{
  try
  {
    // cast to float
    if (type_string==AMILabType<float>::name_as_string()) {
      RETURN_VARPTR(float, boost::numeric_cast<float>(Value()));
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
      CLASS_ERROR((boost::format("No conversion available for variable %1% from double to %2%") % _name % type_string).str().c_str());
    }
  } catch (std::bad_cast &e)
  {
    CLASS_ERROR((boost::format("%1%, for variable %2% from double to %3%") % e.what() % _name % type_string).str().c_str());
    return BasicVariable::ptr();
  }
  return BasicVariable::ptr();
}

//
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<double>::BasicCast(const int& type)
{
  double res = Value();

  switch((WORDTYPE)type) {
    case WT_UNSIGNED_CHAR:  { RETURN_VARPTR(unsigned char,  (unsigned char)  res); }
    case WT_SIGNED_SHORT:   { RETURN_VARPTR(short,          (short)          res); }
    case WT_UNSIGNED_SHORT: { RETURN_VARPTR(unsigned short, (unsigned short) res); }
    case WT_SIGNED_INT:     { RETURN_VARPTR(int,            (int)            res); }
    case WT_UNSIGNED_INT:   res=(unsigned int) res;  break;
    case WT_FLOAT:          { RETURN_VARPTR(float,          (float)          res); }
    case WT_DOUBLE:         { RETURN_VARPTR(double,         (double)         res); } 
    default:
      CLASS_ERROR(( boost::format("Conversion to type %1% not available")%((WORDTYPE)type)).str().c_str());
  }
  RETURN_VARPTR(double, res);
}

//
template<> AMI_DLLEXPORT
BasicVariable::ptr Variable<double>::TernaryCondition(const BasicVariable::ptr& v1, const BasicVariable::ptr&v2)
{
  if (Value()>0.5) {
    return v1->NewReference();
  } else {
    return v2->NewReference();
  }
  return NewReference();
}

template<> AMI_DLLEXPORT
  BasicVariable::ptr Variable<double>::operator[](const BasicVariable::ptr& v)
{
  if (v->IsNumeric()) {
    double* pointer = this->Pointer().get();
    double res = pointer[(int)(v->GetValueAsDouble()+0.5)];
    return AMILabType<double>::CreateVar(res);
  } else
    CLASS_ERROR("operator[] only takes a numerical parameter");
  return NewReference();
}


template<> AMI_DLLEXPORT 
BasicVariable::ptr Variable<double>::operator =(const BasicVariable::ptr& b)
{
  if (IsNumeric()) {
    RefValue() = b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return NewReference();
}
