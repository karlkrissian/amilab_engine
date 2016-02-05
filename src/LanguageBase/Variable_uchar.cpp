
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


  
std::vector<std::string> AMILabType<unsigned char>::conversion_types = 
        {   "bool", "double", "float",
            "int", "long", "short",
            "unsigned long", "unsigned short" };
  
//------------------------------------------------------
//------- Variable<unsigned char>
//------------------------------------------------------

/// Copy contents to new variable
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::NewCopy() const
{
  uchar_ptr newval( new unsigned char(Value()));
  Variable<unsigned char>::ptr newvar(new Variable<unsigned char>(newval));
  return newvar;
}


// Arithmetic operators

/// +a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::operator +()
{  RETURN_VARPTR(unsigned char,Value());}

/// prefix ++ operator ++a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::operator ++()
{
  RETURN_VARPTR(unsigned char,++RefValue());
}

/// postfix ++ operator a++
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::operator ++(int)
{
  RETURN_VARPTR(unsigned char,RefValue()++);
}

/// -a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::operator -()
{   RETURN_VARPTR(unsigned char,-Value());}

/// prefix -- operator --a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::operator --()
{  RETURN_VARPTR(unsigned char,--RefValue()); }

/// postfix -- operator a--
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::operator --(int)
{  RETURN_VARPTR(unsigned char,RefValue()--);  }



/// a+b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::operator +(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(unsigned char,Value()+b->GetValueAsDouble());
  }
  else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a+=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::operator +=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() += b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a-b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::operator -(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(unsigned char,Value()-b->GetValueAsDouble());
  }
  else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a-=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::operator -=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() -= b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a*b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::operator *(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(unsigned char,Value()*b->GetValueAsDouble());
  } 
  else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a*=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::operator *=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() *= b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a/b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::operator /(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(unsigned char,Value()/b->GetValueAsDouble());
  }
  else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a/=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::operator /=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() /= b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a%b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::operator %(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(unsigned char, ((int) round(Value())) % ((int) round(b->GetValueAsDouble())));
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a%=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::operator %=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() =  ((int) round(Value())) % ((int) round(b->GetValueAsDouble()));
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

//  Comparison Operators

/// a<b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::operator <(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()<b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a<=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::operator <=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()<=b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a>b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::operator >(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()>b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a>=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::operator >=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()>=b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a!=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::operator !=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()!=b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}


/// a==b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::operator ==(const BasicVariable::ptr& b)
{ 
  //std::cout << __func__ << std::endl;
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()==b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

// Logical operators

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::operator !() 
{
  RETURN_VARPTR(bool,!(Value()>0.5));
}

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::operator &&(const BasicVariable::ptr& b) 
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,(Value()>0.5)&& (bool) (b->GetValueAsDouble()>0.5));
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::operator ||(const BasicVariable::ptr& b) 
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,(Value()>0.5) || (bool) (b->GetValueAsDouble()>0.5));
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

// Mathematical functions
// TODO: improve type conversions here ...
#define VAR_IMPL_FUNC(type,fname,func) \
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<type>::m_##fname() \
{ \
    RETURN_VARPTR(unsigned char, (int) func((double)Value())); \
}

/*
VAR_IMPL_FUNC(unsigned char,  sin,  sin)
VAR_IMPL_FUNC(unsigned char,  cos,  cos)
VAR_IMPL_FUNC(unsigned char,  tan,  tan)
VAR_IMPL_FUNC(unsigned char,  asin, asin)
VAR_IMPL_FUNC(unsigned char,  acos, acos)
VAR_IMPL_FUNC(unsigned char,  atan, atan)
*/
VAR_IMPL_FUNC(unsigned char,  fabs, fabs)
/*
VAR_IMPL_FUNC(unsigned char,  round,round)
VAR_IMPL_FUNC(unsigned char,  floor,floor)
VAR_IMPL_FUNC(unsigned char,  exp,  exp)
VAR_IMPL_FUNC(unsigned char,  log,  1.0/log(10.0)*log)
VAR_IMPL_FUNC(unsigned char,  ln,   log)
*/
VAR_IMPL_FUNC(unsigned char,  norm, fabs)
VAR_IMPL_FUNC(unsigned char,  sqrt, sqrt)


//---------------------------------------------------
template<> AMI_DLLEXPORT
BasicVariable::ptr Variable<unsigned char>::TryCast(
    const std::string& type_string) const
{
  if (type_string==AMILabType<unsigned char>::name_as_string()) 
    return NewCopy();
  try
  {
    #define TRYCAST(type)\
      if (type_string==AMILabType<type>::name_as_string()) {\
        RETURN_VARPTR(type, boost::numeric_cast<type>(Value()));\
      } else 
    TRYCAST(bool)
    TRYCAST(double)
    TRYCAST(float)
    TRYCAST(int)
    TRYCAST(short)
    TRYCAST(long)
    TRYCAST(unsigned long)
    TRYCAST(unsigned short)
    {
      // make default conversion to double??
      CLASS_ERROR((boost::format("No conversion available for variable %1% from 'unsigned char' to %2%") % _name % type_string).str().c_str());
    }
  } catch (std::bad_cast &e)
  {
    CLASS_ERROR((boost::format("%1%, for variable %2% from 'unsigned char' to %3%") % e.what() % _name % type_string).str().c_str());
    return BasicVariable::ptr();
  }
  return BasicVariable::ptr();
}


//---------------------------------------
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<unsigned char>::BasicCast(const int& type)
{
  try
  {
    switch((WORDTYPE)type) {
      case WT_UNSIGNED_CHAR:  break; // uchar to uchar: nothing to do ...
      case WT_SIGNED_INT:
      {
          RETURN_VARPTR(int, boost::numeric_cast<int>(Value()));
      }
      case WT_SIGNED_LONG:
      {
          RETURN_VARPTR(long, boost::numeric_cast<long>(Value()));
      }
      case WT_FLOAT:
      {
          RETURN_VARPTR(float, boost::numeric_cast<float>(Value()));
      }
      case WT_DOUBLE: 
      {
          RETURN_VARPTR(double, boost::numeric_cast<double>(Value()));
      }
      case WT_SIGNED_SHORT:   //res=(short) res;  break;
      case WT_UNSIGNED_SHORT: //res=(unsigned short) res;  break;
      default:
        CLASS_ERROR((boost::format("Conversion to type %1% not available")%((WORDTYPE)type)).str().c_str());
    }
  } catch (std::bad_cast &e)
  {
    CLASS_ERROR((boost::format("%1%, for variable %2% from 'unsigned char' to WORDTYPE %3%") % e.what() % _name % (WORDTYPE)type ).str().c_str());
    return BasicVariable::ptr();
  }

  RETURN_VARPTR(unsigned char, Value());

}

//
template<>
BasicVariable::ptr Variable<unsigned char>::TernaryCondition(const BasicVariable::ptr& v1, const BasicVariable::ptr&v2)
{
  if (Value()>0.5) {
    return v1->NewReference();
  } else {
    return v2->NewReference();
  }
  return NewReference();
}

template<> AMI_DLLEXPORT
  BasicVariable::ptr Variable<unsigned char>::operator[](const BasicVariable::ptr& v)
{
  if (v->IsNumeric()) {
    unsigned char* pointer = this->Pointer().get();
    //std::cout << "Size of array " << ARRAY_SIZE(pointer) << std::endl;
    // at the user own risk
    unsigned char res = pointer[(int)(v->GetValueAsDouble()+0.5)];
    return AMILabType<unsigned char>::CreateVar(res);
  } else
    CLASS_ERROR("operator[] only takes a numerical parameter");
  return NewReference();
}


template<> 
BasicVariable::ptr Variable<unsigned char>::operator =(const BasicVariable::ptr& b)
{
  // TODO: better conversion here !!!
  try
  {
    if (IsNumeric()) {
      RefValue() = boost::numeric_cast<unsigned char>(b->GetValueAsDouble());
    } else
      CLASS_ERROR("operation not defined");
  }
  catch (std::bad_cast &e)
  {
    CLASS_ERROR((boost::format("%1%, for variable %2% to 'unsigned char'") % e.what() % b->Name() ).str().c_str());
  }
  return NewReference();
}
