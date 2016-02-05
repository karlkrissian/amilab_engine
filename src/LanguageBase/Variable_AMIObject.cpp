
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


// Declare std::string type
typedef std::string std_string;
#ifndef std_string_declared
  #define std_string_declared
  AMI_DECLARE_TYPE(std_string);
#endif

/**
 * \def APPLY_MEMBER_PARAM0
 * \brief applies the given variable member with no parameter
 **/
#define APPLY_MEMBER_NOPARAM(member_name, resvar) \
  AMIObject::ptr object(this->Pointer()); \
  BasicVariable::ptr member = object->GetContext()->GetVar(member_name); \
  BasicVariable::ptr resvar; \
  if (member.get()) { \
    if (member->Type()==type_class_member) { \
      DYNAMIC_CAST_VARIABLE(WrapClassMember,member, var1); \
      resvar = (var1->Pointer())->CallMember(NULL,0); \
    } else \
    if (member->Type()==type_ami_function) { \
      DYNAMIC_CAST_VARIABLE(AMIFunction,member, var1); \
      AMIFunction::ptr f(var1->Pointer()); \
      resvar = GB_DriverBase->yyip_call_function(f.get()); \
    } else \
    { \
      GB_DriverBase->yyiperror((boost::format("Class member '%1%' for this type is not available. ") % member_name ).str().c_str()); \
    } \
  }

/**
 * \def APPLY_MEMBER_PARAM1
 * \brief applies the given variable member with 1 parameter
 **/
#define APPLY_MEMBER_PARAM1(member_name, varparam, resvar) \
  AMIObject::ptr object(this->Pointer()); \
  BasicVariable::ptr member = object->GetContext()->GetVar(member_name); \
  BasicVariable::ptr resvar; \
  if (member.get()) { \
    ParamList::ptr param(new ParamList()); \
    param->AddParam(varparam->NewReference()); \
    if (member->Type()==type_class_member) { \
      DYNAMIC_CAST_VARIABLE(WrapClassMember,member, var1); \
      resvar = (var1->Pointer())->CallMember(param.get(),0); \
    } else \
    if (member->Type()==type_ami_function) { \
      DYNAMIC_CAST_VARIABLE(AMIFunction,member, var1); \
      AMIFunction::ptr f(var1->Pointer()); \
      resvar = GB_DriverBase->yyip_call_function(f.get(),param); \
    } else \
    { \
      GB_DriverBase->yyiperror((boost::format("Class member '%1%' for this type is not available. ") % member_name ).str().c_str()); \
    } \
  }

//------------------------------------------------------------------------------
template<>  AMI_DLLEXPORT 
  Variable<AMIObject>::Variable(const boost::shared_ptr<AMIObject>& p)
{
  _type    = GetVarType<AMIObject>();
  _name    = "tmpvar";
  _pointer = boost::shared_ptr<AMIObject>(p);
}

//------------------------------------------------------------------------------
template<>  AMI_DLLEXPORT 
  Variable<AMIObject>::Variable(const std::string& name, 
           const boost::shared_ptr<AMIObject>& p)
{
  _type    = GetVarType<AMIObject>();
  _name    = name;
  _pointer = boost::shared_ptr<AMIObject>(p);
}

//------------------------------------------------------------------------------
template<>  AMI_DLLEXPORT bool Variable<AMIObject>::Equal( BasicVariable::ptr v)
{
  if (_type == v->Type()) {
    // convert pointer
    ptr newvar (boost::dynamic_pointer_cast<Variable<AMIObject> >(v));
    return ((_name     == newvar->_name) &&
            (_comments == newvar->_comments) &&
            (_pointer.get()  == newvar->_pointer.get()));

  }
  else return false;
}


//------------------------------------------------------
//------- Variable<AMIObject>
//------------------------------------------------------

/// Cast to a type based on its name as a string
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::TryCast(const std::string& type_string) const
{
  string_ptr value( new std::string(type_string));
  BasicVariable::ptr b = AMILabType<std::string>::CreateVarFromSmtPtr(value);

  APPLY_MEMBER_PARAM1("try_cast", b, varres)
  if (varres.get())
    return varres;
  else
    return BasicVariable::ptr();
}

/// Copy contents to new variable
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::NewCopy() const
{
  APPLY_MEMBER_NOPARAM("__copy__", varres)
  if (varres.get()) return varres;
  {
    // for compatibility only
    APPLY_MEMBER_NOPARAM("copy", varres)
    if (varres.get()) return varres;
  }
  return BasicVariable::empty_variable;
}



/// new variable as a reference to the current variable
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::NewReference() const
{
  std::string resname = _name+"_ref";
  ptr ref(new Variable<AMIObject>(resname,_pointer));
  // copy the comments
  ref->SetComments(_comments);
  // give the oportunity to deal with this new reference
  // TODO: find a solution, are there too many variable references ???
  // could this slow down considerably amilab??
  // should we have a boolean saying that the reference needs special treatment?

  // disabled because of infinite loop and never used ...
  //APPLY_MEMBER_PARAM1("__reference__", ref, varres);
  return ref;
}

// Arithmetic operators

/// +a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator +()
{
  APPLY_MEMBER_NOPARAM("__plus__", varres)
  if (varres.get()) return varres;
  return BasicVariable::ptr();
}

/// -a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator -()
{
  APPLY_MEMBER_NOPARAM("__minus__", varres)
  if (varres.get()) return varres;
  return BasicVariable::empty_variable;
}

/*

/// prefix -- operator --a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator --()
{  RETURN_VARPTR(AMIObject,--RefValue()); }


*/

/// prefix * operator *a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator *()
{
  APPLY_MEMBER_NOPARAM("__indirection__", varres)
  if (varres.get()) return varres;
  return BasicVariable::empty_variable;
}

/// prefix ++ operator ++a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator ++()
{
  APPLY_MEMBER_NOPARAM("__preinc__", varres)
  if (varres.get()) return varres;
  return BasicVariable::empty_variable;
}

/// postfix ++ operator a++
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator ++(int)
{
  APPLY_MEMBER_NOPARAM("__postinc__", varres)
  if (varres.get()) return varres;
  return BasicVariable::empty_variable;
}

/// prefix -- operator --a
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator --()
{
  APPLY_MEMBER_NOPARAM("__predec__", varres)
  if (varres.get()) return varres;
  return BasicVariable::empty_variable;
}

/// postfix -- operator a--
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator --(int)
{
  APPLY_MEMBER_NOPARAM("__postdec__", varres)
  if (varres.get()) return varres;
  return BasicVariable::empty_variable;
}

/// a+b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator +(const BasicVariable::ptr& b)
{
  APPLY_MEMBER_PARAM1("__add__", b, varres)
  if (varres.get()) return varres;
  {
    // for compatibility only
    APPLY_MEMBER_PARAM1("add", b, varres)
    if (varres.get()) return varres;
  }
  return BasicVariable::empty_variable;
}


/// a+=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator +=(const BasicVariable::ptr& b)
{ 
  APPLY_MEMBER_PARAM1("__add_assign__", b, varres)
  if (varres.get()) return varres;
  {
    // for compatibility only
    APPLY_MEMBER_PARAM1("add_assign", b, varres)
    if (varres.get()) return varres;
  }
  return BasicVariable::empty_variable;
}

/// a-b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator -(const BasicVariable::ptr& b)
{
  APPLY_MEMBER_PARAM1("__substract__", b, varres)
  if (varres.get()) return varres;
  {
    // for compatibility only
    APPLY_MEMBER_PARAM1("substract", b, varres)
    if (varres.get()) return varres;
  }
  return BasicVariable::empty_variable;
}

/// a-=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator -=(const BasicVariable::ptr& b)
{ 
  APPLY_MEMBER_PARAM1("__sub_assign__", b, varres)
  if (varres.get()) return varres;
  {
    // for compatibility only
    APPLY_MEMBER_PARAM1("sub_assign", b, varres)
    if (varres.get()) return varres;
  }
  return BasicVariable::empty_variable;
}

/// a*b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator *(const BasicVariable::ptr& b)
{
  APPLY_MEMBER_PARAM1("__mult__", b, varres)
  if (varres.get()) return varres;
  return BasicVariable::empty_variable;
}

/// a*=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator *=(const BasicVariable::ptr& b)
{ 
  APPLY_MEMBER_PARAM1("__mult_assign__", b, varres)
  if (varres.get()) return varres;
  return BasicVariable::empty_variable;
}

/// a/b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator /(const BasicVariable::ptr& b)
{
  APPLY_MEMBER_PARAM1("__div__", b, varres)
  if (varres.get()) return varres;
  return BasicVariable::empty_variable;
}

/// a/=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator /=(const BasicVariable::ptr& b)
{ 
  APPLY_MEMBER_PARAM1("__div_assign__", b, varres)
  if (varres.get()) return varres;
  return BasicVariable::empty_variable;
}


/// a%b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator %(const BasicVariable::ptr& b)
{
  APPLY_MEMBER_PARAM1("__mod__", b, varres)
  if (varres.get()) return varres;
  return BasicVariable::empty_variable;
}

/// a%=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator %=(const BasicVariable::ptr& b)
{ 
  APPLY_MEMBER_PARAM1("__mod_assign__", b, varres)
  if (varres.get()) return varres;
  return BasicVariable::empty_variable;
}

/*

/// a*=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator *=(const BasicVariable::ptr& b)
{ 
  if (b->IsNumeric()) {
    RefValue() *= b->GetValueAsDouble();
  } else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}


/// a/=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator /=(const BasicVariable::ptr& b)
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
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator <(const BasicVariable::ptr& b)
{ 
  APPLY_MEMBER_PARAM1("__lowerthan__", b, varres)
  if (varres.get()) return varres;
  return BasicVariable::empty_variable;
}

/// a<=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator <=(const BasicVariable::ptr& b)
{ 
  APPLY_MEMBER_PARAM1("__lowerorequalthan__", b, varres)
  if (varres.get()) return varres;
  return BasicVariable::empty_variable;
}

/// a>b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator >(const BasicVariable::ptr& b)
{ 
  APPLY_MEMBER_PARAM1("__greaterthan__", b, varres)
  if (varres.get()) return varres;
  return BasicVariable::empty_variable;
}

/// a>=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator >=(const BasicVariable::ptr& b)
{ 
  APPLY_MEMBER_PARAM1("__greaterorequalthan__", b, varres)
  if (varres.get()) return varres;
  return BasicVariable::empty_variable;
}

/// a!=b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator !=(const BasicVariable::ptr& b)
{ 
  APPLY_MEMBER_PARAM1("__notequal__", b, varres)
  if (varres.get()) return varres;
  return BasicVariable::empty_variable;
}

/// a==b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator ==(const BasicVariable::ptr& b)
{ 
  APPLY_MEMBER_PARAM1("__equal__", b, varres)
  if (varres.get()) return varres;
  return BasicVariable::empty_variable;
}


// Logical operators

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator !() 
{
  // TODO
  return BasicVariable::empty_variable;
}

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator &&(const BasicVariable::ptr& b) 
{
  // TODO
  return BasicVariable::empty_variable;
}

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator ||(const BasicVariable::ptr& b) 
{
  // TODO
  return BasicVariable::empty_variable;
}

/// a^b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator ^(const BasicVariable::ptr& b)
{ 
  // TODO
  return BasicVariable::empty_variable;
}

/// a&b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator &(const BasicVariable::ptr& b)
{ 
  // TODO
  return BasicVariable::empty_variable;
}

/// a|b
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator |(const BasicVariable::ptr& b)
{ 
  // TODO
  return BasicVariable::empty_variable;
}

///  norm(image)
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::m_norm() 
{ 
  // TODO
  return BasicVariable::empty_variable;
}
//VAR_IMPL_FUNC(AMIObject,  norm, fabs)


// Image Pixel Type Cast
template<> LanguageBase_EXPORT 
  BasicVariable::ptr 
    Variable<AMIObject>::BasicCast(const int& type)
{
  return BasicVariable::empty_variable; 
}

template<> LanguageBase_EXPORT  
  BasicVariable::ptr 
    Variable<AMIObject>::PointWiseMult(const BasicVariable::ptr& b)
{
  return BasicVariable::empty_variable; 
}

template<> LanguageBase_EXPORT 
  BasicVariable::ptr 
    Variable<AMIObject>::Transpose()
{
  return BasicVariable::empty_variable; 
}

// Mathematical functions

#define VAR_IMPL_FUNC(type,fname,func) \
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<type>::m_##fname() \
{ \
  return BasicVariable::empty_variable; \
}

VAR_IMPL_FUNC(AMIObject,  sin,  sin)
VAR_IMPL_FUNC(AMIObject,  cos,  cos)
VAR_IMPL_FUNC(AMIObject,  tan,  tan)
VAR_IMPL_FUNC(AMIObject,  asin, asin)
VAR_IMPL_FUNC(AMIObject,  acos, acos)
VAR_IMPL_FUNC(AMIObject,  atan, atan)
VAR_IMPL_FUNC(AMIObject,  fabs, fabs)
VAR_IMPL_FUNC(AMIObject,  round,round)
VAR_IMPL_FUNC(AMIObject,  floor,floor)
VAR_IMPL_FUNC(AMIObject,  exp,  exp)
VAR_IMPL_FUNC(AMIObject,  log,  log)
VAR_IMPL_FUNC(AMIObject,  ln,   log)
VAR_IMPL_FUNC(AMIObject,  sqrt, sqrt)


/**
 * Array subscript operator
 * @param v 
 * @return 
 */
template<>  BasicVariable::ptr Variable<AMIObject>::operator[](const BasicVariable::ptr& v)
{

/*
        // 1. check the variable type
        GET_CHECK_VARSTACK(var)
        ParamList::ptr param($3);

        // TODO: run this with overloading from BasicVariable ...
        if (var->Type()==type_class_member) {
          ///    Call a wrapped C++ class member.
          DYNAMIC_CAST_VARIABLE(WrapClassMember,var, var1);
          BasicVariable::ptr res ((var1->Pointer())->CallMember(param.get()));
          driver.var_stack.AddVar(res);

        } else
        if (var->Type()==type_ami_function) 
        {
          ///    Call a language function with its parameters.
          DYNAMIC_CAST_VARIABLE(AMIFunction,var, var1);
          AMIFunction::ptr f(var1->Pointer());
          BasicVariable::ptr res(driver.yyip_call_function(f,param));
          driver.var_stack.AddVar(res);

        } else
        if (var->Type()==type_c_function) 
        {
          DYNAMIC_CAST_VARIABLE(C_wrap_varfunction,var, func);
          BasicVariable::ptr  res;
          res = (*func->Pointer())(param.get());
          driver.var_stack.AddVar(res);
        } else
        if (var->Type()==type_c_procedure) 
        {
          DYNAMIC_CAST_VARIABLE(C_wrap_procedure,var, func);
          BasicVariable::ptr  res;
          (*func->Pointer())(param.get());
          driver.var_stack.AddVar(res);
        } else
        if (var->Type()==type_c_image_function) 
        {
          DYNAMIC_CAST_VARIABLE(C_wrap_imagefunction,var, func);
          InrImage::ptr  im((*func->Pointer())(param.get()));
          if (!im.get()) {
            driver.yyiperror(" image function returns NULL \n");
            YYABORT;
          }
          Variable<InrImage>::ptr res(new Variable<InrImage>(im));
          driver.var_stack.AddVar(res);
        } else
        {
          // error message here
          driver.yyiperror("variable is not of a function type \n");
          driver.var_stack.AddVar(BasicVariable::ptr());
        }
      }
*/
  // todo ... 
  // 1. check if identifier belongs to the object
  // 2. if so return corresponding variable
  AMIObject::ptr object(this->Pointer());

  // looking for function member named at
  BasicVariable::ptr member = object->GetContext()->GetVar("at");
  if (!member.get()) {
    member = object->GetContext()->GetVar("__at__");
  }

  if (member.get()) {
    // Create a paramlist from the parameter
    ParamList::ptr param(new ParamList());
    BasicVariable::ptr newvar(v->NewReference());
    param->AddParam(newvar);

    // check the type of the member variable
    if (member->Type()==type_class_member) {
      ///    Call a wrapped C++ class member.
      DYNAMIC_CAST_VARIABLE(WrapClassMember,member, var1);
      BasicVariable::ptr res ((var1->Pointer())->CallMember(param.get(),0));
      return res;
    } else 
    if (member->Type()==type_ami_function) { 
      DYNAMIC_CAST_VARIABLE(AMIFunction,member, var1); 
      AMIFunction::ptr f(var1->Pointer()); 
      return GB_DriverBase->yyip_call_function(f.get(),param); 
    } else {
      GB_DriverBase->yyiperror(" operator[], class member 'at' (or '__at__') of this type is not available. \n");
      return BasicVariable::empty_variable; 
    }
  } else
  {
    return BasicVariable::empty_variable;
  }
}


//
template<> LanguageBase_EXPORT
  BasicVariable::ptr 
    Variable<AMIObject>::TernaryCondition(const BasicVariable::ptr& v1, 
                                          const BasicVariable::ptr&v2)
{
  CLASS_ERROR("operation not defined");
  return BasicVariable::empty_variable;
}

/*

/// Other operators
/// a=b
template<> 
BasicVariable::ptr Variable<AMIObject>::operator =(const BasicVariable::ptr& b)
{
  CLASS_MESSAGE("begin");
  if (b->IsNumeric()) {
    Pointer()->InitImage(b->GetValueAsDouble());
  }
  else
    CLASS_ERROR("operation not defined");
  return this->NewReference(); 
}
*/

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator =(const BasicVariable::ptr& b)
{
  APPLY_MEMBER_PARAM1("__assign__", b, varres)
  if (varres.get()) return varres;
  {
    // for compatibility only
    APPLY_MEMBER_PARAM1("assign", b, varres)
    if (varres.get()) return varres;
  }
  return BasicVariable::ptr();
}

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator <<(const BasicVariable::ptr& b)
{
  APPLY_MEMBER_PARAM1("__leftshift__", b, varres)
  if (varres.get()) return varres;
  return BasicVariable::ptr();
}

template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::operator >>(const BasicVariable::ptr& b)
{
  APPLY_MEMBER_PARAM1("__rightshift__", b, varres)
  if (varres.get()) return varres;
  return BasicVariable::ptr();
}


// TODO: put this code within a macro???
template<> AMI_DLLEXPORT BasicVariable::ptr Variable<AMIObject>::left_assign(const BasicVariable::ptr& b)
{
  APPLY_MEMBER_PARAM1("__left_assign__", b, varres)
  if (varres.get()) return varres;
  {
    // for compatibility only
    APPLY_MEMBER_PARAM1("left_assign", b, varres)
    if (varres.get()) return varres;
  }
  return BasicVariable::ptr();
}
