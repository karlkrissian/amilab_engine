
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
std::vector<std::string> AMILabType<bool>::conversion_types = 
        {   AMILabType<double>::name_as_string(), 
            "float", "long", "int", "unsigned char", "short" };


//------------------------------------------------------
//------- Variable<bool>
//------------------------------------------------------

/// Copy contents to new variable
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<bool>::NewCopy() const
{
  boost::shared_ptr<bool> newval( new bool(Value()));
  Variable<bool>::ptr newvar(new Variable<bool>(newval));
  return newvar;
}

// Logical operators

/// !a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<bool>::operator !()
{
  RETURN_VARPTR(bool,!(Value()));
}

/// a&&b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<bool>::operator &&(const BasicVariable::ptr& b)
{
  if (b->Type() == type_bool) {
    DYNAMIC_CAST_VARIABLE(bool,b,var_boolean);  
    RETURN_VARPTR(bool,(Value() && var_boolean->Value()));
  }
  else {
    if (b->IsNumeric()) {
      RETURN_VARPTR(bool,Value() && (bool)b->GetValueAsDouble());
    }
    else
      CLASS_ERROR("operation not defined");
  }
  return this->NewReference();
}

/// a||b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<bool>::operator ||(const BasicVariable::ptr& b)
{
  if (b->Type() == type_bool) {
    DYNAMIC_CAST_VARIABLE(bool,b,var_boolean);
    RETURN_VARPTR(bool,(Value() || var_boolean->Value()));
  }
  else {
    if (b->IsNumeric()) {
      RETURN_VARPTR(bool,Value() || (bool)b->GetValueAsDouble());
    }
    else
      CLASS_ERROR("operation not defined");
  }
  return this->NewReference();  
}

//  Comparison Operators

/// a!=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<bool>::operator !=(const BasicVariable::ptr& b)
{
  if (b->Type() == type_bool) {
    DYNAMIC_CAST_VARIABLE(bool,b,var_boolean);
    RETURN_VARPTR(bool,(Value() != var_boolean->Value()));
  }
  else {
    if (b->IsNumeric()) {
      RETURN_VARPTR(bool,Value() != (bool)b->GetValueAsDouble());
    }
    else
      CLASS_ERROR("operation not defined");
  }
  return this->NewReference();
}

/// a==b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<bool>::operator ==(const BasicVariable::ptr& b)
{
  if (b->Type() == type_bool) {
    DYNAMIC_CAST_VARIABLE(bool,b,var_boolean);
    RETURN_VARPTR(bool,(Value() == var_boolean->Value()));
  }
  else {
    if (b->IsNumeric()) {
      RETURN_VARPTR(bool,Value() == (bool)b->GetValueAsDouble());
    }
    else
      CLASS_ERROR("operation not defined");
  }
  return this->NewReference();
}


//---------------------------------------------------

/// Cast to a type based on its name as a string
template<> AMI_DLLEXPORT
BasicVariable::ptr Variable<bool>::TryCast(
    const std::string& type_string) const
{
  if (type_string==AMILabType<bool>::name_as_string())
    return NewCopy();
  try
  {
    // cast to double
    if (type_string==AMILabType<double>::name_as_string()) {
      RETURN_VARPTR(double, boost::numeric_cast<double>(Value()));
    } else 
    // cast to float
    if (type_string==AMILabType<float>::name_as_string()) {
      RETURN_VARPTR(float, boost::numeric_cast<float>(Value()));
    } else
    // cast to long
    if (type_string==AMILabType<long int>::name_as_string()) {
      RETURN_VARPTR(long int, boost::numeric_cast<long int>(Value()));
    } else       
    // cast to short
    if (type_string==AMILabType<short>::name_as_string()) {
      RETURN_VARPTR(short, boost::numeric_cast<short>(Value()));
    } else       
    // cast to int
    if (type_string==AMILabType<int>::name_as_string()) {
      RETURN_VARPTR(int, boost::numeric_cast<int>(Value()));
    } else 
    // cast to unsigned char
    if (type_string==AMILabType<unsigned char>::name_as_string()) {
      RETURN_VARPTR(unsigned char, boost::numeric_cast<unsigned char>(Value()));
    } else 
    {
      // make default conversion to bool??
      CLASS_ERROR((boost::format("No conversion available for variable %1% from bool to %2%") % _name % type_string).str().c_str());
    }
  } catch (std::bad_cast &e)
  {
    CLASS_ERROR((boost::format("%1%, for variable %2% from bool to %3%") % e.what() % _name % type_string).str().c_str());
    return BasicVariable::ptr();
  }
  return BasicVariable::ptr();
}

//
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<bool>::BasicCast(const int& type)
{
  bool res = Value();

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
  RETURN_VARPTR(bool, res);
}

//---------------------------------------------------
template<> AMI_DLLEXPORT
BasicVariable::ptr Variable<bool>::TernaryCondition(const BasicVariable::ptr& v1, const BasicVariable::ptr&v2)
{
  if (Value()) {
    return v1->NewReference();
  } else {
    return v2->NewReference();
  }
  return NewReference();
}

//---------------------------------------------------

/// Other operators
/// a=b
template<> AMI_DLLEXPORT 
BasicVariable::ptr Variable<bool>::operator =(const BasicVariable::ptr& b)
{
  if (IsNumeric()) {
    RefValue() = b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return NewReference();
}
