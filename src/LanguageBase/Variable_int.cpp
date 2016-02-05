
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


std::vector<std::string> AMILabType<int>::conversion_types = 
        {   "bool", "double", "float",
            "long", "short", 
            "unsigned long", "unsigned short", 
            "unsigned char" };


//------------------------------------------------------
//------- Variable<int>
//------------------------------------------------------

//------------------------------------------------------------------------------
template<>  AMI_DLLEXPORT 
  Variable<int>::Variable(const boost::shared_ptr<int>& p)
{
  _type    = GetVarType<int>();
  _name    = "tmpvar";
  _pointer = boost::shared_ptr<int>(p);
}

//------------------------------------------------------------------------------
template<>  AMI_DLLEXPORT 
  Variable<int>::Variable(const std::string& name, 
           const boost::shared_ptr<int>& p)
{
  _type    = GetVarType<int>();
  _name    = name;
  _pointer = boost::shared_ptr<int>(p);
}

//------------------------------------------------------------------------------
template<>  AMI_DLLEXPORT bool Variable<int>::Equal( BasicVariable::ptr v)
{
  if (_type == v->Type()) {
    // convert pointer
    ptr newvar (boost::dynamic_pointer_cast<Variable<int> >(v));
    return ((_name     == newvar->_name) &&
            (_comments == newvar->_comments) &&
            (_pointer.get()  == newvar->_pointer.get()));

  }
  else return false;
}


/// Copy contents to new variable
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::NewCopy() const
{
  int_ptr newval( new int(Value()));
  Variable<int>::ptr newvar(new Variable<int>(newval));
  return newvar;
}


// Arithmetic operators

/// +a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator +()
{  RETURN_VARPTR(int,Value());}

/// prefix ++ operator ++a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator ++()
{
  RETURN_VARPTR(int,++RefValue());
}

/// postfix ++ operator a++
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator ++(int)
{
  RETURN_VARPTR(int,RefValue()++);
}

/// -a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator -()
{   RETURN_VARPTR(int,-Value());}

/// prefix -- operator --a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator --()
{  RETURN_VARPTR(int,--RefValue()); }

/// postfix -- operator a--
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator --(int)
{  RETURN_VARPTR(int,RefValue()--);  }



/// a+b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator +(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(int,Value()+b->GetValueAsDouble());
  }
  else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a+=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator +=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() += b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a-b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator -(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(int,Value()-b->GetValueAsDouble());
  }
  else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a-=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator -=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() -= b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a*b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator *(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(int,Value()*b->GetValueAsDouble());
  } 
  else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a*=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator *=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() *= b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a/b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator /(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(int,Value()/b->GetValueAsDouble());
  }
  else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a/=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator /=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() /= b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a%b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator %(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(int, ((int) round(Value())) % ((int) round(b->GetValueAsDouble())));
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a%=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator %=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() =  ((int) round(Value())) % ((int) round(b->GetValueAsDouble()));
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

//  Comparison Operators

/// a<b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator <(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()<b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a<=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator <=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()<=b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a>b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator >(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()>b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a>=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator >=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()>=b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a!=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator !=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()!=b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}


/// a==b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator ==(const BasicVariable::ptr& b)
{ 
  //std::cout << __func__ << std::endl;
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,Value()==b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

// Logical operators

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator !() 
{
  RETURN_VARPTR(bool,!(Value()>0.5));
}

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator &&(const BasicVariable::ptr& b) 
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,(Value()>0.5)&& (bool) (b->GetValueAsDouble()>0.5));
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator ||(const BasicVariable::ptr& b) 
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(bool,(Value()>0.5) || (bool) (b->GetValueAsDouble()>0.5));
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator ^(const BasicVariable::ptr& b) 
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(int,Value() ^ (int) b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator |(const BasicVariable::ptr& b) 
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(int,Value() | (int) b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::operator &(const BasicVariable::ptr& b) 
{
  if (b->IsNumeric()) {
    RETURN_VARPTR(int,Value() & (int) b->GetValueAsDouble());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

// Mathematical functions
// TODO: improve type conversions here ...
#define VAR_IMPL_FUNC(type,fname,func) \
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<type>::m_##fname() \
{ \
    RETURN_VARPTR(int, (int) func((double)Value())); \
}

/*
VAR_IMPL_FUNC(int,  sin,  sin)
VAR_IMPL_FUNC(int,  cos,  cos)
VAR_IMPL_FUNC(int,  tan,  tan)
VAR_IMPL_FUNC(int,  asin, asin)
VAR_IMPL_FUNC(int,  acos, acos)
VAR_IMPL_FUNC(int,  atan, atan)
*/
VAR_IMPL_FUNC(int,  fabs, fabs)
/*
VAR_IMPL_FUNC(int,  round,round)
VAR_IMPL_FUNC(int,  floor,floor)
VAR_IMPL_FUNC(int,  exp,  exp)
VAR_IMPL_FUNC(int,  log,  1.0/log(10.0)*log)
VAR_IMPL_FUNC(int,  ln,   log)
*/
VAR_IMPL_FUNC(int,  norm, fabs)
VAR_IMPL_FUNC(int,  sqrt, sqrt)
//VAR_IMPL_FUNC(int,  pow,  pow)


//---------------------------------------------------
template<> AMI_DLLEXPORT
BasicVariable::ptr Variable<int>::TryCast(
    const std::string& type_string) const
{
  if (type_string==AMILabType<int>::name_as_string()) 
    return NewCopy();
  try
  {
    #define TRYCAST(type)\
      if (type_string==AMILabType<type>::name_as_string()) {\
        RETURN_VARPTR(type, boost::numeric_cast<type>(Value()));\
      } else 
    TRYCAST(double)
    TRYCAST(float)
    TRYCAST(long)
    TRYCAST(unsigned long)
    TRYCAST(short)
    TRYCAST(unsigned short)
    TRYCAST(unsigned char)
    TRYCAST(bool)
    {
      // make default conversion to double??
      CLASS_ERROR(
        (boost::format("No conversion available for variable %1% from int to %2%") 
          % _name % type_string).str().c_str());
    }
  } catch (std::bad_cast &e)
  {
    CLASS_ERROR((boost::format("%1%, for variable %2% from int to %3%") 
                  % e.what() % _name % type_string).str().c_str());
    return BasicVariable::ptr();
  }
  return BasicVariable::ptr();
}


//---------------------------------------
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<int>::BasicCast(const int& type)
{
  try
  {
    switch((WORDTYPE)type) {
      case WT_SIGNED_INT:  break; // int to int: nothing to do ...
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
      case WT_UNSIGNED_CHAR:
      {
          RETURN_VARPTR(unsigned char, boost::numeric_cast<unsigned char>(Value()));
      }
      case WT_UNSIGNED_INT:  //res=(unsigned char) res; break;
      case WT_SIGNED_SHORT:   //res=(short) res;  break;
      case WT_UNSIGNED_SHORT: //res=(unsigned short) res;  break;
      default:
        CLASS_ERROR((boost::format("Conversion to type %1% not available")%((WORDTYPE)type)).str().c_str());
    }
  } catch (std::bad_cast &e)
  {
    CLASS_ERROR((boost::format("%1%, for variable %2% from float to WORDTYPE %3%") % e.what() % _name % (WORDTYPE)type ).str().c_str());
    return BasicVariable::ptr();
  }

  RETURN_VARPTR(int, Value());

}

//
template<>
BasicVariable::ptr Variable<int>::TernaryCondition(const BasicVariable::ptr& v1, const BasicVariable::ptr&v2)
{
  if (Value()>0.5) {
    return v1->NewReference();
  } else {
    return v2->NewReference();
  }
  return NewReference();
}

template<> AMI_DLLEXPORT
  BasicVariable::ptr Variable<int>::operator[](const BasicVariable::ptr& v)
{
  if (v->IsNumeric()) {
    int* pointer = this->Pointer().get();
    //std::cout << "Size of array " << ARRAY_SIZE(pointer) << std::endl;
    // at the user own risk
    int res = pointer[(int)(v->GetValueAsDouble()+0.5)];
    return AMILabType<int>::CreateVar(res);
  } else
    CLASS_ERROR("operator[] only takes a numerical parameter");
  return NewReference();
}


template<> 
BasicVariable::ptr Variable<int>::operator =(const BasicVariable::ptr& b)
{
  // TODO: better conversion here !!!
  try
  {
    if (IsNumeric()) {
      RefValue() = boost::numeric_cast<int>(b->GetValueAsDouble());
    } else
      CLASS_ERROR("operation not defined");
  }
  catch (std::bad_cast &e)
  {
    CLASS_ERROR((boost::format("%1%, for variable %2% to 'int'") % e.what() % b->Name() ).str().c_str());
  }
  return NewReference();
}
