#pragma once
#ifndef _AMI_VARIABLE_HPP
#define _AMI_VARIABLE_HPP

//#include "ParamBox.hpp"
//#include "DessinImage.hpp"
//#include "Viewer3D.hpp"
//#include "paramlist.h"

#include "DefineClass.hpp"

#include <string>
//#include <iostream>
#include "amilab_messages.h"
#include "vartype.h"
//#include "paramlist.h"
#include "BasicVariable.h"
#include <limits>
#include "ami_format.h"

//#include <vector>
//#include <list>
#include <boost/pointer_cast.hpp>

// forward definition of Variables
//class Variables;
//class VarArray;

typedef enum {
  WT_UNSIGNED_CHAR,  /* Unsigned 8 bits */
  WT_UNSIGNED_SHORT, /* Unsigned 16 bits */
  WT_SIGNED_SHORT,   /* Signed 16 bits */
  WT_UNSIGNED_INT,   /* Unsigned 32 bits */
  WT_SIGNED_INT,     /* Signed 32 bits */
  WT_UNSIGNED_LONG,  /* Unsigned 64 bits */
  WT_SIGNED_LONG,    /* Signed 64 bits */
  WT_FLOAT,          /* Float 32 bits */
  WT_DOUBLE,         /* Float 64 bits */
  WT_RGB,            /* R, G, B, 8 bits each */
  WT_RGBA,           /* R, G, B, A, 8 bits each */
  WT_FLOAT_VECTOR,   /* Vector of 32 bit floats */
  WT_DOUBLE_VECTOR,   /* Vector of 64 bit floats */
  WT_UNKOWN_TYPE,
} WORDTYPE;



/*! \def DYNAMIC_CAST_VARIABLE
    \brief helper for dynamic cast from BasicVariable to Variable<newtype>
*/
#define DYNAMIC_CAST_VARIABLE(newtype,initvar,resvar) \
    Variable<newtype>::ptr resvar( \
          boost::dynamic_pointer_cast<Variable<newtype> >(initvar)); \
    if (!resvar.get()) {\
      ami::format f("DYNAMIC_CAST_VARIABLE( %1%,%2%,%3%) failed ...");\
      PrintError( f % #newtype % #initvar % #resvar ); \
    }


/*! \def GET_WRAPPED_OBJECT
    \brief gets the smart pointer to the object wrapped, from a smart pointer to a basic variable
*/
#define GET_WRAPPED_OBJECT(type,var,objname) \
    DYNAMIC_CAST_VARIABLE(AMIObject, var, varobj) \
    boost::shared_ptr<type> objname; \
    if (varobj.get()) { \
      WrapClassBase::ptr wrapped_base(varobj->Pointer()->GetWrappedObject()); \
      WrapClass_##type* wrapped_obj = dynamic_cast<WrapClass_##type*>(wrapped_base.get()); \
      if (wrapped_obj!=NULL)  objname = wrapped_obj->GetObj(); \
    }

/*       wrapped_obj( \
         boost::dynamic_pointer_cast<WrapClass_##type>(wrapped_base)); \
      if (wrapped_obj.get()) \
        objname = wrapped_obj->GetObj(); \
        */

#define GET_WRAPPED_OBJECT_QUIET(type,var,objname) \
  boost::shared_ptr<Variable<AMIObject> > tmp( boost::dynamic_pointer_cast<Variable<AMIObject> >(var)); \
  boost::shared_ptr<type> objname; \
  if (tmp.get()) {\
    WrapClassBase::ptr object( tmp->Pointer()->GetWrappedObject()); \
    WrapClass<type>* wc = dynamic_cast<WrapClass<type>* >(object.get()); \
    if (wc!=NULL)  objname = wc->GetObj(); \
  }\

class ParamList;

/**
 * This class will be specialized for each variable type used by amilab, either builtin type or wrapped type, allowing more flexible wrapping code.
 */
template<typename T> 
class AMILabType {
    public:
    static std::string name_as_string() { return std::string("unknown"); }
    static boost::shared_ptr<T> GetValue(BasicVariable::ptr var, int stacklevel, bool noconstr=false, bool quiet=false)
    { return boost::shared_ptr<T>(); }

    static BasicVariable::ptr CreateVarFromSmtPtr(const boost::shared_ptr<T>& val);

    static BasicVariable::ptr CreateVarFromSmtConstPtr(const boost::shared_ptr<T const>& val);

    static BasicVariable::ptr CreateVar(const T& val)
    { return BasicVariable::ptr(); }

    static BasicVariable::ptr CreateVar(T* val, bool nodeleter=false)
    { return BasicVariable::ptr(); }

    // double pointer
    static BasicVariable::ptr CreateVar(T** val, bool nodeleter=false)
    { return BasicVariable::ptr(); }

    /**
    * Function used to parse a variable of generic type in a list of parameters, and to give back a pointer to its value.
    */
    static bool get_val_param( 
                  T& arg,
                  ParamList*p,
                  int& num,
                  int stacklevel,
                  bool required=false,
                  bool noconstr=false,
                  bool quiet=false) 
    { return false; }

    /**
    * Function used to parse a variable of generic type in a list of parameters, and to give back a smart pointer to its value.
    */
    static bool get_val_smtptr_param(
                  boost::shared_ptr<T>& arg,
                  ParamList*p, int& num,
                  int stacklevel,
                  bool required=true,
                  bool noconstr=false,
                  bool quiet=false)
    { return false;}
};

//   template<> class LanguageBase_EXPORT AMILabType<type> 
//   { 
//     public: 
//       
//   };

// forward declaration of the specialization
#define AMI_DECLARE_LIMITED_TYPE_EXPORT(type) \
  template<> inline LanguageBase_EXPORT std::string AMILabType<type>::name_as_string() \
  { return std::string(#type); } 

#define AMI_DECLARE_TYPE_EXPORT(type) \
  template<> class LanguageBase_EXPORT AMILabType<type> \
  { \
    public: \
	    static std::string name_as_string();\
	    static std::vector<std::string> conversion_types; \
      static boost::shared_ptr<type> GetValue(BasicVariable::ptr var,int stacklevel, bool noconstr=false, bool quiet=false);\
      static BasicVariable::ptr CreateVarFromSmtPtr(const boost::shared_ptr<type>& val);\
      static BasicVariable::ptr CreateVarFromSmtConstPtr(const boost::shared_ptr<type const>& val);\
      static BasicVariable::ptr CreateVar(type* val, bool nodeleter=false);\
      static BasicVariable::ptr CreateVar(const type& val);\
      static BasicVariable::ptr CreateVar(type** val, bool nodeleter=false);\
      static bool get_val_param( \
                    type& arg,\
                    ParamList*p,\
                    int& num,\
                    int stacklevel,\
                    bool required=false,\
                    bool noconstr=false,\
                    bool quiet=false);\
      \
      static bool get_val_smtptr_param(\
                    boost::shared_ptr<type>& arg,\
                    ParamList*p, int& num,\
                    int stacklevel,\
                    bool required=true,\
                    bool noconstr=false,\
                    bool quiet=false);\
  };

#define AMI_DECLARE_WRAPPED_LIMITED_TYPE(type) \
  template<> boost::shared_ptr<type> AMILabType<type>::GetValue(BasicVariable::ptr var, bool noconstr, bool quiet);\
  template<> BasicVariable::ptr AMILabType<type>::CreateVarFromSmtPtr(const boost::shared_ptr<type>& val);\
  template<> BasicVariable::ptr AMILabType<type>::CreateVarFromSmtConstPtr(const boost::shared_ptr<type const>& val);\
  template<> BasicVariable::ptr AMILabType<type>::CreateVar(type* val, bool nodeleter);\
  template<> BasicVariable::ptr AMILabType<type>::CreateVar(const type& val);\
  template<> BasicVariable::ptr AMILabType<type>::CreateVar(type** val, bool nodeleter);\
  template<> bool AMILabType<type>::get_val_param( \
                    type& arg,\
                    ParamList*p,\
                    int& num,\
                    bool required,\
                    bool noconstr,\
                    bool quiet);\
      \
  template<> bool AMILabType<type>::get_val_smtptr_param(\
                    boost::shared_ptr<type>& arg,\
                    ParamList*p, int& num,\
                    int stacklevel,\
                    bool required,\
                    bool noconstr,\
                    bool quiet);
  
  
// forward declaration of the specialization
#define AMI_DECLARE_TYPE(type) \
  template<> class AMILabType<type> \
  { \
    public: \
	    static std::string name_as_string();\
      static std::vector<std::string> conversion_types; \
      static boost::shared_ptr<type> GetValue(BasicVariable::ptr var, int stacklevel, bool noconstr=false, bool quiet=false);\
      static BasicVariable::ptr CreateVarFromSmtPtr(const boost::shared_ptr<type>& val);\
      static BasicVariable::ptr CreateVarFromSmtConstPtr(const boost::shared_ptr<type const>& val);\
      static BasicVariable::ptr CreateVar(type* val, bool nodeleter=false);\
      static BasicVariable::ptr CreateVar(const type& val);\
      static BasicVariable::ptr CreateVar(type** val);\
      static bool get_val_param( \
                    type& arg,\
                    ParamList*p,\
                    int& num,\
                    int stacklevel,\
                    bool required=false,\
                    bool noconstr=false,\
                    bool quiet=false);\
      \
      static bool get_val_smtptr_param(\
                    boost::shared_ptr<type>& arg,\
                    ParamList*p, int& num,\
                    int stacklevel,\
                    bool required=true,\
                    bool noconstr=false,\
                    bool quiet=false);\
  };

// forward declaration of the specialization
#define AMI_DECLARE_TYPE_DLL(dll_import_export,type) \
  template<> class dll_import_export AMILabType<type> \
  { \
    public: \
      static std::string name_as_string();\
      static std::vector<std::string> conversion_types; \
      static boost::shared_ptr<type> GetValue(BasicVariable::ptr var, int stacklevel, bool noconstr=false, bool quiet=false);\
      static BasicVariable::ptr CreateVarFromSmtPtr(const boost::shared_ptr<type>& val);\
      static BasicVariable::ptr CreateVarFromSmtConstPtr(const boost::shared_ptr<type const>& val);\
      static BasicVariable::ptr CreateVar(type* val, bool nodeleter=false);\
      static BasicVariable::ptr CreateVar(const type& val);\
      static BasicVariable::ptr CreateVar(type** val);\
      static bool get_val_param( \
                    type& arg,\
                    ParamList*p,\
                    int& num,\
                    int stacklevel,\
                    bool required=false,\
                    bool noconstr=false,\
                    bool quiet=false);\
      \
      static bool get_val_smtptr_param(\
                    boost::shared_ptr<type>& arg,\
                    ParamList*p, int& num,\
                    int stacklevel,\
                    bool required=true,\
                    bool noconstr=false,\
                    bool quiet=false);\
  };

#define AMI_DEFINE_GETVALPARAM(type) \
    \
    bool AMILabType<type>::get_val_param( \
                    type& arg,\
                    ParamList*p,\
                    int& num,\
                    int stacklevel,\
                    bool required,\
                    bool noconstr,\
                    bool quiet)\
    { \
      BasicVariable::ptr varparam;\
      bool res = get_next_param(varparam,p,num,required,quiet);\
      if (!varparam.get())  return res;\
      boost::shared_ptr<type> val_ptr = AMILabType<type>::GetValue(varparam, stacklevel,noconstr,quiet);\
      if (!val_ptr.get()) {\
        if (!quiet) { \
          ami::format f("Problem with %1% parameter.");\
          FILE_ERROR( (f % num).GetString());\
        }\
        return false;\
      } else {\
        arg = *val_ptr;\
      }\
      return true;\
    } \

#define AMI_DEFINE_GETVALPARAM_SPECIALIZED(type) \
   template <> AMI_DEFINE_GETVALPARAM(type)

#define AMI_DEFINE_GETVALSMTPTRPARAM(type) \
    \
    bool AMILabType<type>::get_val_smtptr_param(\
        boost::shared_ptr<type>& arg,\
        ParamList*p, int& num,\
        int stacklevel,\
        bool required, bool noconstr, bool quiet)\
    {\
      BasicVariable::ptr temp;\
      bool res = get_next_param(temp,p,num,required,quiet);\
      if (!temp.get()) return res;\
      boost::shared_ptr<type> val_ptr = AMILabType<type>::GetValue(temp, stacklevel, noconstr,quiet);\
      if (!val_ptr.get()) {\
        if (!quiet) {\
          ami::format f("Parameter %1% failed.");\
          FILE_ERROR( ( f % num).GetString());\
        }\
        return false;\
      }\
      arg = val_ptr;\
      return true;\
    }

#define AMI_DEFINE_GETVALSMTPTRPARAM_SPECIALIZED(type) \
  template <> AMI_DEFINE_GETVALSMTPTRPARAM(type)

/*
#define AMI_DEFINE_LIMITED_TYPE(type) \
  template<> std::string AMILabType<type>::name_as_string() { return std::string(#type); } 
*/

#define AMI_DEFINE_BASICTYPE(type) \
	std::string AMILabType<type>::name_as_string() { return std::string(#type); } \
    \
    boost::shared_ptr<type> AMILabType<type>::GetValue(BasicVariable::ptr var, int stacklevel, bool noconstr, bool quiet)  \
    { \
      if (!var.get()) \
      {\
        FILE_ERROR("Variable not found");\
        return boost::shared_ptr<type>();\
      }\
      boost::shared_ptr<Variable<type> > tmp( boost::dynamic_pointer_cast<Variable<type> >(var)); \
      if (tmp.get()) \
        return tmp->Pointer(); \
      else {\
        BasicVariable::ptr converted = var->TryCast(AMILabType<type>::name_as_string());\
        if (!converted.get()) {\
          /*FILE_ERROR(boost::format("Cannot be converted to type %1%.") % AMILabType<type>::name_as_string());*/\
          return boost::shared_ptr<type>(); \
        } else { \
          boost::shared_ptr<Variable<type> > tmp( boost::dynamic_pointer_cast<Variable<type> >(converted)); \
          if (tmp.get()) \
            return tmp->Pointer(); \
          else \
            return boost::shared_ptr<type>(); \
        }\
      }\
    } \
    \
    BasicVariable::ptr AMILabType<type>::CreateVarFromSmtPtr(const boost::shared_ptr<type>& valptr)\
    {\
      return Variable<type>::ptr( new Variable<type>(valptr));\
    }\
    \
    BasicVariable::ptr AMILabType<type>::CreateVarFromSmtConstPtr(const boost::shared_ptr<type const>& valptr)\
    {\
      /* here we make a copy */ \
      return AMILabType<type>::CreateVar(new type(*valptr));\
    }\
    \
    BasicVariable::ptr AMILabType<type>::CreateVar(type* val, bool nodeleter)  \
    { \
      boost::shared_ptr<type> valptr; \
      if (nodeleter) \
        valptr = boost::shared_ptr<type>(val,smartpointer_nodeleter<type>());\
      else \
        valptr = boost::shared_ptr<type>(val);\
      return CreateVarFromSmtPtr(valptr); \
    } \
    \
    BasicVariable::ptr AMILabType<type>::CreateVar(const type& val)  \
    { \
      return AMILabType<type>::CreateVar(new type(val));\
    } \
    \
    AMI_DEFINE_GETVALPARAM(type) \
    AMI_DEFINE_GETVALSMTPTRPARAM(type)

#define AMI_DEFINE_WRAPPEDTYPE_COMMON(type) \
    std::string AMILabType<type>::name_as_string() { \
    std::string name = std::string("wrap_")+std::string(#type); \
      return name; \
    } \
    \
    boost::shared_ptr<type> AMILabType<type>::GetValue(BasicVariable::ptr var, int stacklevel, bool noconstr,bool quiet)  \
    { \
      if (!var.get()) \
      {\
        FILE_ERROR("Variable not found");\
        return boost::shared_ptr<type>();\
      }\
      GET_WRAPPED_OBJECT_QUIET(type,var,res) \
      if (res.get()) return res;\
      if (!noconstr) {\
        /* Try with the constructor */ \
        ParamList::ptr param(new ParamList()); \
        param->AddParam(var); \
        BasicVariable::ptr constr_res = WrapClass<type>::CreateVar(param.get(), stacklevel, quiet);\
        GET_WRAPPED_OBJECT_QUIET(type,constr_res,res) \
        if (res.get()) return res;\
      }\
      /*FILE_ERROR("Parameter conversion failed");*/ \
      return boost::shared_ptr<type>();\
    } \
    \
    \
    \
    AMI_DEFINE_GETVALSMTPTRPARAM(type)


/* Previous GetValue
 * 
 *    boost::shared_ptr<type> AMILabType<type>::GetValue(BasicVariable::ptr var, bool noconstr,bool quiet)  \
    { \
      if (!var.get()) \
      {\
        FILE_ERROR("Variable not found");\
        return boost::shared_ptr<type>();\
      }\
      boost::shared_ptr<Variable<AMIObject> > tmp( boost::dynamic_pointer_cast<Variable<AMIObject> >(var)); \
      if ((!tmp.get()) && (!noconstr)) {\
        // Try with the constructor  \
        ParamList::ptr param(new ParamList()); \
        param->AddParam(var); \
        BasicVariable::ptr constr_res = WrapClass<type>::CreateVar(param.get(),quiet);\
        tmp = boost::dynamic_pointer_cast<Variable<AMIObject> >(constr_res);\
      } else { FILE_MESSAGE("first cast ok"); }\
      if (tmp.get()) { \
        WrapClassBase::ptr object( tmp->Pointer()->GetWrappedObject()); \
        boost::shared_ptr<WrapClass<type> > wc( boost::dynamic_pointer_cast<WrapClass<type> >(object));\
        if (wc.get()) { \
          return wc->GetObj(); \
        } else { \
          ((FILE_ERROR("Could not cast dynamically the variable.");\
        } \
      }  else { \
        //FILE_ERROR("Need a wrapped object or compatible variable as parameter."); \
      } \
      return boost::shared_ptr<type>();\
    } \
  */  

/* previous GetValue for specialized
    template<> boost::shared_ptr<type> AMILabType<type>::GetValue(BasicVariable::ptr var, bool noconstr,bool quiet)  \
    { \
      if (!var.get()) \
      {\
        FILE_ERROR("Variable not found");\
        return boost::shared_ptr<type>();\
      }\
      boost::shared_ptr<Variable<AMIObject> > tmp( boost::dynamic_pointer_cast<Variable<AMIObject> >(var)); \
      if ((!tmp.get()) && (!noconstr)) {\
        // Try with the constructor  \
        ParamList::ptr param(new ParamList()); \
        param->AddParam(var); \
        BasicVariable::ptr constr_res = WrapClass<type>::CreateVar(param.get(),quiet);\
        tmp = boost::dynamic_pointer_cast<Variable<AMIObject> >(constr_res);\
      } else { FILE_MESSAGE("first cast ok"); }\
      if (tmp.get()) { \
        WrapClassBase::ptr object( tmp->Pointer()->GetWrappedObject()); \
        boost::shared_ptr<WrapClass<type> > wc( boost::dynamic_pointer_cast<WrapClass<type> >(object));\
        if (wc.get()) { \
          return wc->GetObj(); \
        } else { \
          FILE_MESSAGE("Could not cast dynamically the variable.") \
        } \
      }  else { \
        FILE_MESSAGE("Need a wrapped object or compatible variable as parameter.") \
      } \
      return boost::shared_ptr<type>();\
    } \
*/


#define AMI_DEFINE_WRAPPEDTYPE_COMMON_SPECIALIZED(type) \
    \
    template<> boost::shared_ptr<type> AMILabType<type>::GetValue(BasicVariable::ptr var, int stacklevel, bool noconstr,bool quiet)  \
    { \
      if (!var.get()) \
      {\
        FILE_ERROR("Variable not found");\
        return boost::shared_ptr<type>();\
      }\
      GET_WRAPPED_OBJECT_QUIET(type,var,res) \
      if (res.get()) return res;\
      if (!noconstr) {\
        /* Try with the constructor */ \
        ParamList::ptr param(new ParamList()); \
        param->AddParam(var); \
        BasicVariable::ptr constr_res = WrapClass<type>::CreateVar(param.get(),stacklevel,quiet);\
        GET_WRAPPED_OBJECT_QUIET(type,constr_res,res) \
        if (res.get()) return res;\
      }\
      /*FILE_ERROR("Parameter conversion failed");*/ \
      return boost::shared_ptr<type>();\
    } \
    \
    AMI_DEFINE_GETVALSMTPTRPARAM_SPECIALIZED(type)


#define AMI_DEFINE_WRAPPEDTYPE_NOCOPY(type) \
    AMI_DEFINE_WRAPPEDTYPE_COMMON(type)\
    \
    BasicVariable::ptr AMILabType<type>::CreateVar(const type& val)  \
    { \
      /* here we really need a value, but not very clean \
       * TODO: think about a better way to deal with const like using \
       * pointer to constant: for example create <T const> type with only \
       * constant methods */ \
      FILE_MESSAGE( "Using const_cast<> : could be dangerous.")  \
      type* val_ptr = const_cast<type*>(&val); \
      boost::shared_ptr<type > val_shptr( val_ptr,\
                                          smartpointer_nodeleter<type>());\
      return AMILabType<type>::CreateVarFromSmtPtr(val_shptr);\
    } 


#define AMI_DEFINE_WRAPPEDTYPE_NOCOPY_CREATEFROMPTR(type) \
    BasicVariable::ptr AMILabType<type>::CreateVar( type* val, bool nodeleter)  \
    { \
      boost::shared_ptr<type> obj_ptr(val,smartpointer_nodeleter<type>());\
      return AMILabType<type>::CreateVarFromSmtPtr(obj_ptr);\
    } 

#define AMI_DEFINE_WRAPPEDTYPE_HASCOPY(type) \
    AMI_DEFINE_WRAPPEDTYPE_COMMON(type)\
    \
    BasicVariable::ptr AMILabType<type>::CreateVar( type* val, bool nodeleter)  \
    { \
      boost::shared_ptr<type> obj_ptr; \
      if (nodeleter) \
        obj_ptr = boost::shared_ptr<type>(val,smartpointer_nodeleter<type>());\
      else \
        obj_ptr = boost::shared_ptr<type>(val);\
      return AMILabType<type>::CreateVarFromSmtPtr(obj_ptr);\
    } \
    \
    BasicVariable::ptr AMILabType<type>::CreateVar(const type& val)  \
    { \
      return AMILabType<type>::CreateVar(new type(val));\
    } 

#define AMI_DEFINE_WRAPPEDTYPE_HASCOPY_SPECIALIZED(type) \
    AMI_DEFINE_WRAPPEDTYPE_COMMON_SPECIALIZED(type)\
    \
    template<> BasicVariable::ptr AMILabType<type>::CreateVar( type* val, bool nodeleter)  \
    { \
      boost::shared_ptr<type> obj_ptr; \
      if (nodeleter) \
        obj_ptr = boost::shared_ptr<type>(val,smartpointer_nodeleter<type>());\
      else \
        obj_ptr = boost::shared_ptr<type>(val);\
      return AMILabType<type>::CreateVarFromSmtPtr(obj_ptr);\
    } \
    \
    template <> BasicVariable::ptr AMILabType<type>::CreateVar(const type& val)  \
    { \
      return AMILabType<type>::CreateVar(new type(val));\
    } 

// Abstract classes
#define AMI_DEFINE_WRAPPEDTYPE_ABSTRACT(type) \
    AMI_DEFINE_WRAPPEDTYPE_COMMON(type)\
    \
    BasicVariable::ptr AMILabType<type>::CreateVar( type* val, bool nodeleter)  \
    { \
      boost::shared_ptr<type> obj_ptr; \
      if (nodeleter) \
        obj_ptr = boost::shared_ptr<type>(val,smartpointer_nodeleter<type>());\
      else \
        obj_ptr = boost::shared_ptr<type>(val);\
      return AMILabType<type>::CreateVarFromSmtPtr(obj_ptr);\
    } \
    \
    BasicVariable::ptr AMILabType<type>::CreateVar(const type& val)  \
    { \
      return BasicVariable::ptr(); \
    }

#define AMI_DEFINE_WRAPPEDTYPE_ABSTRACT_SPECIALIZED(type) \
    AMI_DEFINE_WRAPPEDTYPE_COMMON_SPECIALIZED(type)\
    \
    template<> BasicVariable::ptr AMILabType<type>::CreateVar( type* val, bool nodeleter)  \
    { \
      boost::shared_ptr<type> obj_ptr; \
      if (nodeleter) \
        obj_ptr = boost::shared_ptr<type>(val,smartpointer_nodeleter<type>());\
      else \
        obj_ptr = boost::shared_ptr<type>(val);\
      return AMILabType<type>::CreateVarFromSmtPtr(obj_ptr);\
    } \
    \
    template<> BasicVariable::ptr AMILabType<type>::CreateVar(const type& val)  \
    { \
      return BasicVariable::ptr();\
    } 

#define AMI_DEFINE_VARFROMSMTPTR(type) \
  BasicVariable::ptr AMILabType<type>::CreateVarFromSmtPtr(const boost::shared_ptr<type>& obj_ptr) \
  { \
    return  WrapClass<type>::CreateVar(  new WrapClass_##type(obj_ptr));\
  } \
  \
  BasicVariable::ptr AMILabType<type>::CreateVarFromSmtConstPtr(const boost::shared_ptr<type const>& obj_ptr) \
  { \
    return  WrapClass<type>::CreateVar( new WrapClass_##type(obj_ptr,true));\
  } 

#define AMI_DEFINE_VARFROMSMTPTR_SPECIALIZED(type) \
  template <> \
  BasicVariable::ptr AMILabType<type>::CreateVarFromSmtPtr(const boost::shared_ptr<type>& obj_ptr) \
  { \
    return  WrapClass<type>::CreateVar(  new WrapClass_##type(obj_ptr));\
  } \
  \
  template <> \
  BasicVariable::ptr AMILabType<type>::CreateVarFromSmtConstPtr(const boost::shared_ptr<type const>& obj_ptr) \
  { \
    return  WrapClass<type>::CreateVar( new WrapClass_##type(obj_ptr,true));\
  } 

#define AMI_DEFINE_VARFROMSMTPTR_TEMPLATE(type1,name1,type2) \
  BasicVariable::ptr AMILabType<type1<type2> >::CreateVarFromSmtPtr(const boost::shared_ptr<type1<type2> >& obj_ptr) \
  { \
    return \
      WrapClass<type1<type2> >::CreateVar( \
        new WrapClass_##name1<type2>(obj_ptr));\
  } \
  \
  BasicVariable::ptr AMILabType<type1<type2> >::CreateVarFromSmtConstPtr(const boost::shared_ptr<type1<type2> const>& obj_ptr) \
  { \
    return \
      WrapClass<type1<type2> >::CreateVar( \
        new WrapClass_##name1<type2>(obj_ptr,true));\
  } \

#define AMI_DEFINE_VARFROMSMTPTR_TEMPLATE2(type1,type2) \
  BasicVariable::ptr AMILabType<type1 >::CreateVarFromSmtPtr(const boost::shared_ptr<type1 >& obj_ptr) \
  { \
    return \
      WrapClass<type1 >::CreateVar( \
        new WrapClass_##type2(obj_ptr));\
  } \
  \
  BasicVariable::ptr AMILabType<type1 >::CreateVarFromSmtConstPtr(const boost::shared_ptr<type1 const>& obj_ptr) \
  { \
    return \
      WrapClass<type1 >::CreateVar( \
        new WrapClass_##type2(obj_ptr,true));\
  } 

template<typename> 
struct to_string {
    // optionally, add other information, like the size
    // of the string.
    static char const* value() { return "unknown"; }
};


// TODO: the rest of convertions

/*
template<class T> 
std::ostream& PrintType(std::ostream& o, const Variable<T>& v);
*/

// forward declaration of ParamList;
class ParamList;

// forward declaration of InrImage;
class InrImage;

/// Getting variable type 
template<class T> vartype GetVarType();

/// Check numerical type
template<class T> bool IsNumerical();

/// type: pointer to a C wrapping procedure
typedef void      (C_wrap_procedure)(ParamList*);

/// type: pointer to a C wrapping image function
typedef InrImage* (C_wrap_imagefunction)(ParamList*);

/// type: pointer to a C wrapping variable function
typedef BasicVariable::ptr (C_wrap_varfunction)(ParamList*);

class WrapClassMember;
class AMIFunction;
class AMIClass;
class AMIObject;
class VarArray;

AMI_DECLARE_TYPE_EXPORT(bool);
AMI_DECLARE_TYPE_EXPORT(float);
AMI_DECLARE_TYPE_EXPORT(double);
AMI_DECLARE_TYPE_EXPORT(long);
AMI_DECLARE_TYPE_EXPORT(unsigned long);
AMI_DECLARE_TYPE_EXPORT(int);
AMI_DECLARE_TYPE_EXPORT(short);
AMI_DECLARE_TYPE_EXPORT(unsigned short);
AMI_DECLARE_TYPE_EXPORT(unsigned char);
//AMI_DECLARE_TYPE_EXPORT(InrImage);
//AMI_DECLARE_TYPE_EXPORT(std::string);
AMI_DECLARE_TYPE_EXPORT(C_wrap_procedure);
AMI_DECLARE_TYPE_EXPORT(C_wrap_imagefunction);
AMI_DECLARE_TYPE_EXPORT(C_wrap_varfunction);
AMI_DECLARE_TYPE_EXPORT(AMIFunction);
AMI_DECLARE_TYPE_EXPORT(AMIClass);
AMI_DECLARE_TYPE_EXPORT(VarArray);

// abstract classes, is it OK?
// TODO: check why to two following features where commented
// problem with WrapLanguage
// where a builtin type is wrapped, creates doubled defined functions
//   AMI_DECLARE_LIMITED_TYPE_EXPORT has been created to defined only 
//     name_as_string member


//#ifndef WIN32
//  #ifndef AMIObject_declared
//    #define AMIObject_declared
    AMI_DECLARE_LIMITED_TYPE_EXPORT(AMIObject);
//  #endif
//#endif

//#ifndef WrapClassMember_declared
//  #define WrapClassMember_declared
  AMI_DECLARE_LIMITED_TYPE_EXPORT(WrapClassMember);
//#endif


//----------------------------------------------------------------------
/**
 * Define one variable, which contains a generic pointer (void*) to a smart pointer
 * of the contained object.
 **/
template<class T>
class Variable : public BasicVariable {

//  DEFINE_TEMPLATE_CLASS1(Variable,T);

public:
  virtual char const* get_name() const { return "Variable<T>"; } 
	//  typedef typename Variable<T> VariableType;
  typedef typename boost::shared_ptr<Variable<T> >    ptr;
  typedef typename boost::weak_ptr<Variable<T> >      wptr;


private:
  boost::shared_ptr<T>        _pointer; 

private:

  bool FreeMemory()
  {
/*    if ((_pointer.use_count()>1)&&(GB_debug)) {
      CLASS_ERROR( boost::format("variable %1% is referenced %2% times")  % _name % _pointer.use_count() );
    }*/
    _pointer.reset();
    return true;
  }

public:

  static ptr DynCast(BasicVariable::ptr v) {
    return boost::dynamic_pointer_cast<Variable<T> >(v);
  }
  
  Variable();

  Variable(const boost::shared_ptr<T>& p)
  {
    _type    = GetVarType<T>();
    _name    = "tmpvar";
    _pointer = boost::shared_ptr<T>(p);
  }

  Variable( T* p)
  {
    _type    = GetVarType<T>();
    _name    = "tmpvar";
    _pointer = boost::shared_ptr<T>(p);
  }

  Variable(const std::string& name, 
           const boost::shared_ptr<T>& p)
  {
    _type    = GetVarType<T>();
    _name    = name;
    _pointer = boost::shared_ptr<T>(p);
  }
 
  virtual ~Variable()
  { 
    //ami::format f("Calling Variable<T> destructor ... for variable %1% ");
    //CLASS_MESSAGE( (f % Name().c_str()).GetString());
    this->Delete(); 
  }

  /**
    * Virtual Method that creates a new smart pointer to a basic variable coming from the same type
    * generic copy of variable, can be specialized per variable type
    */
  BasicVariable::ptr NewCopy() const
  {
    ami::format f("No default copy of variable contents, need to be specialized for this type of variable ... for variable %1% ");
    // don't copy a file, keep a reference ...
    CLASS_MESSAGE( (f % Name().c_str()).GetString());
    return NewReference();

/*    std::string resname = _name+"_copy";
    boost::shared_ptr<T> copy(new T(*_pointer));
    ptr res(new Variable<T>(resname,copy));
    return res;
*/
  }

  /**
    * Virtual Method that creates a new smart pointer to a basic variable coming from the same type
    * with a reference to the same value
    */
  BasicVariable::ptr NewReference() const
  {
    std::string resname = _name+"_ref";
		ptr res(new Variable<T>(resname,_pointer));
    // copy the comments
    res->SetComments(_comments);
    return res;
  }

  int GetPtrCounter() const
  {
    return _pointer.use_count();
  }

  bool HasPointer() const
  {
    return (_pointer.get()!=NULL);
  }

  virtual const std::string GetTypeName() const
  {
    return AMILabType<T>::name_as_string();
  };


  virtual std::string TreeCtrlInfo() const 
  {
    return _comments;
  };

  /**
   * Copy of variables
   * @param v 
   */
  void operator = (const Variable<T>& v);

  /**
   * Copy of variables
   * @param v 
   */
  void operator = (const ptr& v) 
  {
     (*this) = (*v);
      /*
      _type         = v->_type;
      _name         = v->_name;
      _comments     = v->_comments;
      // Problem: unsafe to copy pointers here
      _pointer      = v->_pointer;
    */
  }

  bool operator == ( BasicVariable* v) 
  {
    if (_type == v->Type()) {
      // convert pointer
      Variable<T>* newvar = dynamic_cast<Variable<T>*>(v);
      return ((_name     == newvar->_name) &&
              (_comments == newvar->_comments) &&
              (_pointer.get()  == newvar->_pointer.get()));

    }
    else return false;
  }

  bool SameContents(BasicVariable* v)
  {
    if (_type == v->Type()) {
      // convert pointer
      Variable<T>* newvar = dynamic_cast<Variable<T>*>(v);
      if (newvar)
        return (_pointer.get()  == newvar->_pointer.get());
      else return false;
    }
    else return false;
  }

  bool Equal( BasicVariable::ptr v) 
  {
    if (_type == v->Type()) {
      // convert pointer
      ptr newvar (boost::dynamic_pointer_cast<Variable<T> >(v));
      return ((_name     == newvar->_name) &&
              (_comments == newvar->_comments) &&
              (_pointer.get()  == newvar->_pointer.get()));

    }
    else return false;
  }

  bool operator == (const Variable<T>& v) 
  {
      return ((_type     == v._type) &&
              (_name     == v._name) &&
              (_comments == v._comments) &&
              (_pointer.get()  == v._pointer.get()));
  }

  /**
  * Get the pointer of the variable value, points to a smart pointer.
  * @return Pointer of the variable, points to a smart pointer
  */
  boost::shared_ptr<T> Pointer() const { return _pointer;}

  const T& Value() const { return *_pointer; }

  T& RefValue() { return *_pointer; }

  void Init(const std::string& name, 
            const boost::shared_ptr<T>& p);

  void Delete();

  //
/*
  friend 
  std::ostream& operator<< <>(std::ostream& o, const Variable<T>& v);
*/

/*
  friend 
  std::ostream& PrintType <>(std::ostream& o, const Variable<T>& v);
*/

  /**
   * Try to cast the variable to the type given as a string in parameter.
   * @param type_string : type as a string
   * @return smart pointer to a variable of the new type if success, empty smart pointer otherwise
   */
  virtual BasicVariable::ptr TryCast(const std::string& type_string) const;

  //
  void display(std::ostream& o) const;

  virtual double GetValueAsDouble() const;
  
  /*
   * 
   * @return A string containing the type of the variable.
   */
//  virtual std::string GetTypeAsString() const;

  /**
   * 
   * @return A string containing the value of the variable.
   */
  virtual std::string GetValueAsString() const;
  //const { return std::string(); }

  // allow access to private members of Variable class
//  friend class VarArray;


#define VAR_UNARYOP(op) \
  BasicVariable::ptr operator op() \
  { \
    return BasicVariable::empty_variable; \
  }

/*
#define VAR_OP_VAR(op) \
  BasicVariable::ptr operator op(const Variable<T>& b) \
  { std::cout << get_name() << "::operator " << __func__ << " not defined." << std::endl; \
    return this->NewReference(); }
*/

#define VAR_OP_BASICVAR(op) \
  BasicVariable::ptr operator op(const BasicVariable::ptr& b) \
  { \
    return BasicVariable::empty_variable; \
  }

/*
#define VAR_OP_VAR2(op) \
  BasicVariable::ptr operator op(const Variable<T>& b);
*/

//#define VAR_OP_VAR2(op) 
//  template<class U> 
//  BasicVariable::ptr operator op(const Variable<U>& b); 

#define VAR_COMP_OP_BASICVAR(op) \
  BasicVariable::ptr operator op(const BasicVariable::ptr& b) \
  { \
    return BasicVariable::empty_variable; \
  }

#define VAR_LOGIC_OP(op) \
  BasicVariable::ptr operator op() \
  { \
    return BasicVariable::empty_variable; \
  }

#define VAR_LOGIC_OP_VAR(op) \
  BasicVariable::ptr operator op(const BasicVariable::ptr& b) \
  { \
    return BasicVariable::empty_variable; \
  }

  /** @name ArithmeticOperators
   *  Variable Arithmetic Operators.
   */
  //@{
  // -------- Operators ---

  /// *T
  VAR_UNARYOP(*)

  /// +T
  VAR_UNARYOP(+)
  /// prefix ++ operator ++T 
  VAR_UNARYOP(++)
  /// postfix ++ operator T++ 
  BasicVariable::ptr operator ++(int)
  {
    return BasicVariable::empty_variable; 
  }

  /// -T
  VAR_UNARYOP(-)
  /// prefix -- operator --T 
  VAR_UNARYOP(--)
  /// postfix -- operator T-- 
  BasicVariable::ptr operator --(int)
  {
    return BasicVariable::empty_variable; 
  }

  /// a+b
  // can I keep the const here, no because we return a reference ... ???
  // question, should we create a new variable ????
  // in this case yes, and the rule should take care of choosing a+b or a+=b to avoid 
  // a new allocation
  VAR_OP_BASICVAR(+);
  VAR_OP_BASICVAR(+=);
  VAR_OP_BASICVAR(-);
  VAR_OP_BASICVAR(-=);
  VAR_OP_BASICVAR(*);
  VAR_OP_BASICVAR(*=);
  VAR_OP_BASICVAR(/);
  VAR_OP_BASICVAR(/=);
  VAR_OP_BASICVAR(%);
  VAR_OP_BASICVAR(%=);

  //@}

  /** @name ComparisonOperators
   *  Variable Comparison operators/Relational operators.
   */
  //@{
    VAR_COMP_OP_BASICVAR(<);
    VAR_COMP_OP_BASICVAR(<=);
    VAR_COMP_OP_BASICVAR(>);
    VAR_COMP_OP_BASICVAR(>=);
    VAR_COMP_OP_BASICVAR(!=);
    VAR_COMP_OP_BASICVAR(==);
  //@}

  /** @name LogicalOperators
   *  Variable Logical operators.
   */
  //@{
    VAR_LOGIC_OP(!);
    VAR_LOGIC_OP_VAR(&&);
    VAR_LOGIC_OP_VAR(||);
  //@}

  /** @name BitwiseOperators
   *  Variable Bitwise operators.
   */
  //@{
    VAR_LOGIC_OP_VAR(^);
    VAR_LOGIC_OP_VAR(|);
    VAR_LOGIC_OP_VAR(&);
  //@}

  /** @name OtherOperators
   *  Variable Other operators.
   */
  //@{
    VAR_OP_BASICVAR(=);

    VAR_OP_BASICVAR(<<);
    VAR_OP_BASICVAR(>>);

    /**
    * left_assign is operator <<=, force assignation of new variable, even if a new pointer to the object needs to be created
    * @param b 
    * @return 
    */
    BasicVariable::ptr left_assign(const BasicVariable::ptr& b) 
    { 
    return BasicVariable::empty_variable; 
    }


    /// Transpose
    BasicVariable::ptr Transpose()
    {
    return BasicVariable::empty_variable; 
    }

    /// Pointwise multiplication 
    BasicVariable::ptr PointWiseMult(const BasicVariable::ptr& b)
    {
    return BasicVariable::empty_variable; 
    }
  //@}

#define VAR_FUNC(func) \
  BasicVariable::ptr m_##func() \
  { \
    return BasicVariable::empty_variable; \
  }

  /** @name Mathematical functions
   *  Mathematical functions.
   */
  //@{
    VAR_FUNC(sin)
    VAR_FUNC(cos)
    VAR_FUNC(tan)
    VAR_FUNC(asin)
    VAR_FUNC(acos)
    VAR_FUNC(atan)
    VAR_FUNC(fabs)
    VAR_FUNC(round)
    VAR_FUNC(floor)
    VAR_FUNC(exp)
    VAR_FUNC(log)
    VAR_FUNC(ln)
    VAR_FUNC(norm)
    VAR_FUNC(sqrt)
//    VAR_FUNC(pow)
  //@}


  BasicVariable::ptr BasicCast(const int& type)
  {
/*    ami::format f(" %1% %2% not defined.");
    PrintWarning( f % get_name() % __func__ );
    return this->NewReference(); */
    return BasicVariable::empty_variable; 
  }

  BasicVariable::ptr operator[](const BasicVariable::ptr& v)
  {
    return BasicVariable::empty_variable; 
  }


  BasicVariable::ptr TernaryCondition(const BasicVariable::ptr& v1, const BasicVariable::ptr&v2) 
  {
    return BasicVariable::empty_variable; 
  }

}; // class Variable



template<class T>  
std::ostream& operator<<(std::ostream& o, const Variable<T>& v);

/*
/// Variable Cast Operator Class

class CastVariableBase
{
  virtual BasicVariable::ptr operator()( const BasicVariable::ptr& varin) = 0;
};

template<class T, class U>
class CastVariable: public CastVariableBase
{
  BasicVariable::ptr operator()( const BasicVariable::ptr& varin)
  { 
    std::cout << "Cast operation not defined ... :(" << std::endl;
    return varin->NewReference(); 
  }
};
*/

#ifndef __GCCXML__
  #include "Variable.tpp"
#endif // __GCCXML__

//#include "Variable.cpp"

/*
class InrImage;
class DessinImage;


class Viewer3D;
//class C_wrap_procedure;
class WrapClassMember;
//class C_wrap_imagefunction;
//class C_wrap_varfunction;
class AMIFunction;
class AMIClass;
class AMIObject;
class AMICPPObject;
class FloatMatrix;
class GLTransfMatrix;
class VarArray;
*/

// Mathematical functions, 
#define VAR_DECL_FUNC(type,fname) \
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<type>::m_##fname();

// Cannot wrap those lines in GCCXML: internal compiler error
#ifndef __GCCXML__ 
  #include "Variable_float.h"
  #include "Variable_bool.h"   /// New (added: 19/11/2010)
  #include "Variable_double.h" /// New (added: 24/05/2010)
  #include "Variable_long.h"   /// New (added: 27/05/2010)
  #include "Variable_ulong.h"   /// New (added: 27/05/2010)
  #include "Variable_int.h"
  #include "Variable_short.h"
  #include "Variable_ushort.h"
  #include "Variable_uchar.h"
//  #include "Variable_string.h"
  #include "Variable_AMIObject.h"
  #include "Variable_WrapClassMember.h"
#endif //__GCCXML__

template<> std::string Variable<WrapClassMember>::TreeCtrlInfo() const;
/*
{
  return Pointer()->GetDescription();
};
*/

#endif
