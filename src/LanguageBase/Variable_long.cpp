
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

std::vector<std::string> AMILabType<long>::conversion_types = 
        {   "bool", "double", "float",
            "int", "short", 
            "unsigned long", "unsigned short", 
            "unsigned char" };

//------------------------------------------------------
//------- Variable<long>
//------------------------------------------------------

/// Copy contents to new variable
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::NewCopy() const
{
  boost::shared_ptr<long> newval( new long(Value()));
  Variable<long>::ptr newvar(new Variable<long>(newval));
  return newvar;
}


// Arithmetic operators

/// +a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::operator +()
{  RETURN_VARPTR(long int,Value());}

/// prefix ++ operator ++a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::operator ++()
{
  //std::cout << "**" << std::endl;
  RETURN_VARPTR(long int,++RefValue());
}

/// postfix ++ operator a++
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::operator ++(int)
{
  //std::cout << "**" << std::endl;
  RETURN_VARPTR(long int,RefValue()++);
}

/// -a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::operator -()
{   RETURN_VARPTR(long int,-Value());}

/// prefix -- operator --a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::operator --()
{  RETURN_VARPTR(long int,--RefValue()); }

/// postfix -- operator a--
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::operator --(int)
{  RETURN_VARPTR(long int,RefValue()--);  }



/// a+b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::operator +(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(long int,Value()+b->GetValueAsDouble());
  }
  else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a+=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::operator +=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() += b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a-b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::operator -(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(long int,Value()-b->GetValueAsDouble());
  }
  else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a-=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::operator -=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() -= b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a*b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::operator *(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(long int,Value()*b->GetValueAsDouble());
  } 
  else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a*=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::operator *=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() *= b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a/b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::operator /(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(long int,Value()/b->GetValueAsDouble());
  }
  else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a/=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::operator /=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() /= b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a%b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::operator %(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(long int, ((int) round(Value())) % ((int) round(b->GetValueAsDouble())));
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a%=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::operator %=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() =  ((int) round(Value())) % ((int) round(b->GetValueAsDouble()));
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

//  Comparison Operators

/// a<b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::operator <(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()<b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a<=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::operator <=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()<=b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a>b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::operator >(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()>b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a>=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::operator >=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()>=b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a!=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::operator !=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()!=b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}


/// a==b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::operator ==(const BasicVariable::ptr& b)
{ 
  //std::cout << __func__ << std::endl;
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()==b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

// Logical operators

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::operator !() 
{
  RETURN_VARPTR(bool,!(Value()>0.5));
}

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::operator &&(const BasicVariable::ptr& b) 
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()&& (bool) (b->GetValueAsDouble()>0.5));
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::operator ||(const BasicVariable::ptr& b) 
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
    RETURN_VARPTR(long int, func((double)Value())); \
}

// VAR_IMPL_FUNC(long int,  sin,  sin)
// VAR_IMPL_FUNC(long int,  cos,  cos)
// VAR_IMPL_FUNC(long int,  tan,  tan)
// VAR_IMPL_FUNC(long int,  asin, asin)
// VAR_IMPL_FUNC(long int,  acos, acos)
// VAR_IMPL_FUNC(long int,  atan, atan)
// VAR_IMPL_FUNC(long int,  fabs, fabs)
// VAR_IMPL_FUNC(long int,  round,round)
// VAR_IMPL_FUNC(long int,  floor,floor)
// VAR_IMPL_FUNC(long int,  exp,  exp)
// VAR_IMPL_FUNC(long int,  log,  1.0/log(10.0)*log)
// VAR_IMPL_FUNC(long int,  ln,   log)
// VAR_IMPL_FUNC(long int,  norm, fabs)
// VAR_IMPL_FUNC(long int,  sqrt, sqrt)

//---------------------------------------------------
template<> AMI_DLLEXPORT
BasicVariable::ptr Variable<long>::TryCast(
    const std::string& type_string) const
{
  if (type_string==AMILabType<long>::name_as_string()) 
    return NewCopy();
  try
  {
    #define TRYCAST(type)\
      if (type_string==AMILabType<type>::name_as_string()) {\
        RETURN_VARPTR(type, boost::numeric_cast<type>(Value()));\
      } else 
    TRYCAST(unsigned char)
    TRYCAST(bool)
    TRYCAST(double)
    TRYCAST(float)
    TRYCAST(int)
    TRYCAST(short)
    TRYCAST(unsigned long)
    TRYCAST(unsigned short)
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
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<long>::BasicCast(const int& type)
{
  long int res = Value();

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
  RETURN_VARPTR(long, res);
}

//
template<> AMI_DLLEXPORT
BasicVariable::ptr Variable<long>::TernaryCondition(const BasicVariable::ptr& v1, const BasicVariable::ptr&v2)
{
  if (Value()>0.5) {
    return v1->NewReference();
  } else {
    return v2->NewReference();
  }

  return NewReference();
}

template<> AMI_DLLEXPORT
  BasicVariable::ptr Variable<long>::operator[](const BasicVariable::ptr& v)
{
  if (v->IsNumeric()) {
    long* pointer = this->Pointer().get();
    //std::cout << "Size of array " << ARRAY_SIZE(pointer) << std::endl;
    // at the user own risk
    long res = pointer[(int)(v->GetValueAsDouble()+0.5)];
    return AMILabType<long>::CreateVar(res);
  } else
    CLASS_ERROR("operator[] only takes a numerical parameter");
  return NewReference();
}




template<> AMI_DLLEXPORT 
BasicVariable::ptr Variable<long>::operator =(const BasicVariable::ptr& b)
{
  if (IsNumeric()) {
    RefValue() = b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return NewReference();
}
