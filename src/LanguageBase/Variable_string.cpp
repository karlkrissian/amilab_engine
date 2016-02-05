
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

#include "StringUtils.hpp"

using namespace std;

//------------------------------------------------------
//------- Variable<string>
//------------------------------------------------------



/// Copy contents to new variable
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<std::string>::NewCopy() const
{
  string_ptr newval( new string(Value()));
  Variable<string>::ptr newvar(new Variable<string>(newval));
  return newvar;
}


// Arithmetic operators



/// a+b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<std::string>::operator +(const BasicVariable::ptr& b)
{
  if (b->Type()==type_string) {
    DYNAMIC_CAST_VARIABLE(std::string,b,var_st2);
    RETURN_VARPTR(std::string,Value()+var_st2->Value());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a+=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<string>::operator +=(const BasicVariable::ptr& b)
{ 
  if (b->Type()==type_string) {
    DYNAMIC_CAST_VARIABLE(std::string,b,var_st2);
    RETURN_VARPTR(std::string,RefValue()+=var_st2->Value());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a-b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<string>::operator -(const BasicVariable::ptr& b)
{
  if (b->Type()==type_string) {
    DYNAMIC_CAST_VARIABLE(std::string,b,var_st2);
    // TODO: avoid using char* here
    char* res = new char[Value().length()+1];
    strcpy(res,Value().c_str());
    RemoveEndString(res,var_st2->Value().c_str());
    std::string res_st(res);
    RETURN_VARPTR(std::string,res_st);
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a-=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<string>::operator -=(const BasicVariable::ptr& b)
{ 
  if (b->Type()==type_string) {
    DYNAMIC_CAST_VARIABLE(std::string,b,var_st2);
    // TODO: avoid using char* here
    char* res = new char[Value().length()+1];
    strcpy(res,Value().c_str());
    RemoveEndString(res,var_st2->Value().c_str());
    std::string res_st(res);
    RETURN_VARPTR(std::string,RefValue()=res_st);
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}


/// a%b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<string>::operator %(const BasicVariable::ptr& b)
{
  if (b->IsNumeric()) {
    // Should not always cast to double
    if (b->Type()==type_int) {
      DYNAMIC_CAST_VARIABLE(int,b,var_int);
      std::string res = (boost::format(Value())% (*var_int->Pointer())).str();
      RETURN_VARPTR(std::string,res);
    } else {
      std::string res = (boost::format(Value())%b->GetValueAsDouble()).str();
      RETURN_VARPTR(std::string,res);
    }
  } else
  if (b->Type()==type_string) {
    DYNAMIC_CAST_VARIABLE(std::string,b,var_st2);
    std::string res = (boost::format(Value())%var_st2->Value()).str();
    RETURN_VARPTR(std::string,res);
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}


//  Comparison Operators

/// a<b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<string>::operator <(const BasicVariable::ptr& b)
{ 
  if (b->Type()==type_string) {
    DYNAMIC_CAST_VARIABLE(std::string,b,var_st2);
//    RETURN_VARPTR(float,(float) (Value()<var_st2->Value()));
    RETURN_VARPTR(bool,(Value()<var_st2->Value()));
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a<=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<string>::operator <=(const BasicVariable::ptr& b)
{ 
  if (b->Type()==type_string) {
    DYNAMIC_CAST_VARIABLE(std::string,b,var_st2);
//    RETURN_VARPTR(float,(float) (Value()<=var_st2->Value()));
    RETURN_VARPTR(bool,(Value()<=var_st2->Value()));
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a>b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<string>::operator >(const BasicVariable::ptr& b)
{ 
  if (b->Type()==type_string) {
    DYNAMIC_CAST_VARIABLE(std::string,b,var_st2);
//    RETURN_VARPTR(float,(float) (Value()>var_st2->Value()));
    RETURN_VARPTR(bool,(Value()>var_st2->Value()));
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a>=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<string>::operator >=(const BasicVariable::ptr& b)
{ 
  if (b->Type()==type_string) {
    DYNAMIC_CAST_VARIABLE(std::string,b,var_st2);
//    RETURN_VARPTR(float, Value()>=var_st2->Value());
    RETURN_VARPTR(bool, Value()>=var_st2->Value());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}

/// a!=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<string>::operator !=(const BasicVariable::ptr& b)
{ 
  if (b->Type()==type_string) {
    DYNAMIC_CAST_VARIABLE(std::string,b,var_st2);
//    RETURN_VARPTR(float, Value()!=var_st2->Value());
    RETURN_VARPTR(bool, Value()!=var_st2->Value());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}


/// a==b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<string>::operator ==(const BasicVariable::ptr& b)
{ 
  if (b->Type()==type_string) {
    DYNAMIC_CAST_VARIABLE(std::string,b,var_st2);
//    RETURN_VARPTR(float, Value()==var_st2->Value());
    RETURN_VARPTR(bool, Value()==var_st2->Value());
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}




template<> AMI_DLLEXPORT 
BasicVariable::ptr Variable<string>::operator =(const BasicVariable::ptr& b)
{
  if (b->Type()==type_string) {
    DYNAMIC_CAST_VARIABLE(std::string,b,var_st2);
    RefValue() = var_st2->Value();
  } else
    CLASS_ERROR("operation not defined");
  return NewReference();
}

