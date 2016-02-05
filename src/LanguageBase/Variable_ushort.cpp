
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

std::vector<std::string> AMILabType<unsigned short>::conversion_types = 
        {   "bool", "unsigned char", "double", "float",
            "int", "long", "short",
            "unsigned long" };


//------------------------------------------------------
//------- Variable<unsigned short>
//------------------------------------------------------

/// Copy contents to new variable
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::NewCopy() const
{
  boost::shared_ptr<unsigned short> newval( new unsigned short(Value()));
  Variable<unsigned short>::ptr newvar(new Variable<unsigned short>(newval));
  return newvar;
}


// Arithmetic operators

/// +a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::operator +()
{  RETURN_VARPTR(unsigned short int,Value());}

/// prefix ++ operator ++a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::operator ++()
{
  //std::cout << "**" << std::endl;
  RETURN_VARPTR(unsigned short int,++RefValue());
}

/// postfix ++ operator a++
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::operator ++(int)
{
  //std::cout << "**" << std::endl;
  RETURN_VARPTR(unsigned short int,RefValue()++);
}

/// -a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::operator -()
{   RETURN_VARPTR(unsigned short int,-Value());}

/// prefix -- operator --a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::operator --()
{  RETURN_VARPTR(unsigned short int,--RefValue()); }

/// postfix -- operator a--
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::operator --(int)
{  RETURN_VARPTR(unsigned short int,RefValue()--);  }



/// a+b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::operator +(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(unsigned short int,Value()+b->GetValueAsDouble());
  }
  else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a+=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::operator +=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() += b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a-b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::operator -(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(unsigned short int,Value()-b->GetValueAsDouble());
  }
  else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a-=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::operator -=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() -= b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a*b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::operator *(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(unsigned short int,Value()*b->GetValueAsDouble());
  } 
  else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a*=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::operator *=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() *= b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a/b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::operator /(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(unsigned short int,Value()/b->GetValueAsDouble());
  }
  else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a/=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::operator /=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() /= b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a%b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::operator %(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(unsigned short int, ((int) round(Value())) % ((int) round(b->GetValueAsDouble())));
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a%=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::operator %=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() =  ((int) round(Value())) % ((int) round(b->GetValueAsDouble()));
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

//  Comparison Operators

/// a<b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::operator <(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()<b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a<=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::operator <=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()<=b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a>b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::operator >(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()>b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a>=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::operator >=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()>=b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a!=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::operator !=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()!=b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}


/// a==b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::operator ==(const BasicVariable::ptr& b)
{ 
  //std::cout << __func__ << std::endl;
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()==b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

// Logical operators

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::operator !() 
{
  RETURN_VARPTR(bool,!(Value()>0.5));
}

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::operator &&(const BasicVariable::ptr& b) 
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()&& (bool) (b->GetValueAsDouble()>0.5));
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::operator ||(const BasicVariable::ptr& b) 
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
    RETURN_VARPTR(unsigned short int, func((double)Value())); \
}

// VAR_IMPL_FUNC(short int,  sin,  sin)
// VAR_IMPL_FUNC(short int,  cos,  cos)
// VAR_IMPL_FUNC(short int,  tan,  tan)
// VAR_IMPL_FUNC(short int,  asin, asin)
// VAR_IMPL_FUNC(short int,  acos, acos)
// VAR_IMPL_FUNC(short int,  atan, atan)
// VAR_IMPL_FUNC(short int,  fabs, fabs)
// VAR_IMPL_FUNC(short int,  round,round)
// VAR_IMPL_FUNC(short int,  floor,floor)
// VAR_IMPL_FUNC(short int,  exp,  exp)
// VAR_IMPL_FUNC(short int,  log,  1.0/log(10.0)*log)
// VAR_IMPL_FUNC(short int,  ln,   log)
// VAR_IMPL_FUNC(short int,  norm, fabs)
// VAR_IMPL_FUNC(short int,  sqrt, sqrt)

//---------------------------------------------------
template<> AMI_DLLEXPORT
BasicVariable::ptr Variable<unsigned short>::TryCast(
    const std::string& type_string) const
{
  if (type_string==AMILabType<unsigned short>::name_as_string()) 
    return NewCopy();
  try
  {
    #define TRYCAST(type)\
      if (type_string==AMILabType<type>::name_as_string()) {\
        RETURN_VARPTR(type, boost::numeric_cast<type>(Value()));\
      } else 
    TRYCAST(bool)
    TRYCAST(unsigned char)
    TRYCAST(double)
    TRYCAST(float)
    TRYCAST(int)
    TRYCAST(short)
    TRYCAST(long)
    TRYCAST(unsigned long)
    {
      // make default conversion to double??
      CLASS_ERROR((boost::format("No conversion available for variable %1% from int to %2%") % _name % type_string).str().c_str());
    }
  } catch (std::bad_cast &e)
  {
    CLASS_ERROR((boost::format("%1%, for variable %2% from int to %3%") % e.what() % _name % type_string).str().c_str());
    return BasicVariable::ptr();
  }
  return BasicVariable::ptr();
}


//
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned short>::BasicCast(const int& type)
{
  short int res = Value();

  switch((WORDTYPE)type) {
    case WT_UNSIGNED_CHAR:  res=(unsigned char) res; break;
    case WT_SIGNED_SHORT:   res=(short) res;  break;
    case WT_UNSIGNED_SHORT: res=(unsigned short) res;  break;
    case WT_SIGNED_INT:     res=(int) res;  break;
    case WT_UNSIGNED_INT:   res=(unsigned int) res;  break;
    case WT_FLOAT:          { RETURN_VARPTR(float, (float) res); }
    case WT_DOUBLE:         { RETURN_VARPTR(double, res); } /// New (added: 24/05/2010)
    default:
      CLASS_ERROR(( boost::format("Conversion to type %1% not available")%((WORDTYPE)type)).str().c_str());
  }
  RETURN_VARPTR(unsigned short, res);
}

//
template<> AMI_DLLEXPORT
BasicVariable::ptr Variable<unsigned short>::TernaryCondition(const BasicVariable::ptr& v1, const BasicVariable::ptr&v2)
{
  if (Value()>0.5) {
    return v1->NewReference();
  } else {
    return v2->NewReference();
  }

  return NewReference();
}

template<> AMI_DLLEXPORT
  BasicVariable::ptr Variable<unsigned short>::operator[](const BasicVariable::ptr& v)
{
  if (v->IsNumeric()) {
    unsigned short* pointer = this->Pointer().get();
    unsigned short res = pointer[(int)(v->GetValueAsDouble()+0.5)];
    return AMILabType<unsigned short>::CreateVar(res);
  } else
    CLASS_ERROR("operator[] only takes a numerical parameter");
  return NewReference();
}


template<> AMI_DLLEXPORT 
BasicVariable::ptr Variable<unsigned short>::operator =(const BasicVariable::ptr& b)
{
  if (IsNumeric()) {
    RefValue() = b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return NewReference();
}
