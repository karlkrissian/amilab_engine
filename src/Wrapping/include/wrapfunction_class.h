//
// C++ Interface: wrapfunction_class
//
// Description: Prototype for wrapping functions
// based on http://www.parashift.com/c++-faq-lite/pointers-to-members.html#faq-33.1
//
// Author: Karl Krissian <>, (C) 2010
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef _wrapfunction_class_h_
#define _wrapfunction_class_h_

#include "paramlist.h"
#include "DefineClass.hpp"
#include "WrapCommonConfigure.h"

// new includes needed for WrapClass<T>
#include "ami_object.h"
#include "Variable.hpp"

// if we don't want this include, we need to move code to wrapped cpp files
//#include "Variables.hpp"

#define STATIC_HELP \
    const std::string GetDescription() const { return StaticDescription();  }\
    const std::string GetFunctionName() const { return StaticFunctionName(); }\

/** Macro for adding a class that wraps a method.
  */
#define ADD_METHOD(classname,methodname,description_str) \
class wrap_##classname##methodname : public WrapClassMemberWithDoc { \
  protected:\
    classname::ptr _objectptr; \
  public: \
    wrap_##classname##methodname(const classname::ptr& pp) : \
     _objectptr(pp) { \
      Set_arg_failure(false);\
      Set_quiet(false);\
      SetParametersComments(); \
    } \
    void SetParametersComments(); \
    boost::shared_ptr<BasicVariable> CallMember(ParamList*, int stacklevel); \
    static const std::string StaticDescription()  { return description_str; }\
    static const std::string StaticFunctionName() \
    { return std::string(#classname)+"::"+#methodname; }\
    STATIC_HELP\
};

/** Macro for adding a nested class that wraps a method.
  * requires that the type '_parentclass_ptr' be defined as a smart pointer to
  * the parent class
  * and that the parent class has a method get_name() returning 
  * the name of the class (it is provided by the macro DEFINE_CLASS).
  * and a AMIObject:ptr amiobject member pointing to the corresponding wrapped object class
  */
#define ADD_CLASS_METHOD(methodname,description_str) \
class wrap_##methodname : public WrapClassMemberWithDoc { \
  protected:\
    _parentclass_ptr _objectptr; \
  public: \
    wrap_##methodname(const _parentclass_ptr& pp) : \
     _objectptr(pp) { \
      Set_arg_failure(false);\
      Set_quiet(false);\
      SetParametersComments(); \
    } \
    void SetParametersComments(); \
    boost::shared_ptr<BasicVariable> CallMember(ParamList*, int stacklevel); \
    static const std::string StaticDescription()  { return description_str; }\
    static const std::string StaticFunctionName() \
    { std::string classname(AMILabType<ObjectType>::name_as_string());\
      return classname+"::"+#methodname; }\
    STATIC_HELP\
}; \
\
void AddVar_##methodname(  const _parentclass_ptr& pc, const std::string& newname = #methodname) \
  {\
    boost::shared_ptr<WrapClassMember> tmp( (WrapClassMember*) new wrap_##methodname(pc));\
    AMIObject::ptr tmpobj(amiobject.lock()); \
    BasicVariable* newvar =  new Variable<WrapClassMember>(tmp);\
    Variables_AddVar(tmpobj->GetContext(),newname, newvar, tmpobj->GetContext()); \
  }
//      tmpobj->GetContext()->AddVar(newname, newvar, tmpobj->GetContext()); \

#define ADD_CLASS_METHOD_LIGHT(methodname,description_str) \
class wrap_##methodname : public WrapClassMember { \
  protected:\
    _parentclass_ptr _objectptr; \
  public: \
    wrap_##methodname(const _parentclass_ptr& pp) : \
     _objectptr(pp) { \
      Set_arg_failure(false);\
      Set_quiet(false);\
    } \
    boost::shared_ptr<BasicVariable> CallMember(ParamList*, int stacklevel); \
}; \
\
void AddVar_##methodname(  const _parentclass_ptr& pc, const std::string& newname = #methodname) {\
  AMIObject::ptr tmpobj(amiobject.lock()); \
  WrapClassMember* tmp = new wrap_##methodname(pc);\
  BasicVariable* newvar = new Variable<WrapClassMember>(tmp);\
  tmpobj->GetContext()->AddVar(newname, newvar, tmpobj->GetContext()); \
}
//    const boost::shared_ptr<ObjectType>& GetObj() const { return _objectptr->GetObj(); }  

///
#define DECLARE_CLASS_METHOD_LIGHT(methodname,description_str) \
class wrap_##methodname : public WrapClassMember { \
  protected:\
    _parentclass_ptr _objectptr; \
  public: \
    wrap_##methodname(const _parentclass_ptr& pp);\
    boost::shared_ptr<BasicVariable> CallMember(ParamList*, int stacklevel); \
}; \
\
void AddVar_##methodname(  const _parentclass_ptr& pc, const std::string& newname = #methodname)\
{\
  AMIObject::ptr tmpobj(amiobject.lock()); \
  WrapClassMember* tmp = new wrap_##methodname(pc);\
  BasicVariable* newvar =  new Variable<WrapClassMember>(tmp);\
  Variables_AddVar(tmpobj->GetContext(),newname, newvar, tmpobj->GetContext()); \
}
//  tmpobj->GetContext()->AddVar(newname, newvar, tmpobj->GetContext()); 

///
#define DEFINE_CLASS_METHOD_LIGHT(classname,methodname) \
WrapClass_##classname::wrap_##methodname::wrap_##methodname(const _parentclass_ptr& pp) : \
  _objectptr(pp) { \
  Set_arg_failure(false);\
  Set_quiet(false);\
} 

/*\
void WrapClass_##classname::AddVar_##methodname( const _parentclass_ptr& pc, const std::string& newname ) \
{\
  AMIObject::ptr tmpobj(amiobject.lock()); \
  WrapClassMember* tmp = new wrap_##methodname(pc);\
  BasicVariable* newvar =  new Variable<WrapClassMember>(tmp);\
  tmpobj->GetContext()->AddVar(newname, newvar, tmpobj->GetContext()); \
}
*/

/**
  Macro to wrap Set/Get methods
  */
#define ADD_CLASS_SETGET(type,varname,description_str) \
class wrap_Set##varname : public WrapClassMemberWithDoc { \
  protected:\
    _parentclass_ptr _objectptr; \
  public: \
    wrap_Set##varname(const _parentclass_ptr& pp) : \
     _objectptr(pp) { \
      Set_arg_failure(false);\
      Set_quiet(false);\
      ADDPARAMCOMMENT_TYPE(type,description_str); \
    } \
    boost::shared_ptr<BasicVariable> CallMember(ParamList* p, int stacklevel) { \
      int n=0;\
      type val; \
      if (!get_val_param<type>( val, p, n)) ClassHelpAndReturn; \
      _objectptr->GetObj()->Set##varname(val); \
      return boost::shared_ptr<BasicVariable>(); \
    } \
    static const std::string StaticDescription()  \
    { return std::string("Sets ")+description_str; }\
    static const std::string StaticFunctionName() \
    { std::string classname(AMILabType<ObjectType>::name_as_string());\
      return classname+"::Set"+#varname; }\
    STATIC_HELP\
}; \
\
class wrap_Get##varname : public WrapClassMemberWithDoc { \
  protected:\
    _parentclass_ptr _objectptr; \
  public: \
    wrap_Get##varname(_parentclass_ptr& pp) : \
     _objectptr(pp) { \
      Set_arg_failure(false);\
      Set_quiet(false);\
      ami::format f("Returns a variable of type %1%."); \
      return_comments = (f % AMILabType<type>::name_as_string().c_str()).GetString(); \
    } \
    boost::shared_ptr<BasicVariable> CallMember(ParamList*, int stacklevel) { \
      type val = this->_objectptr->GetObj()->Get##varname(); \
      RETURN_VAR(type,val); \
    } \
    static const std::string StaticDescription()  \
    { return std::string("Gets ")+description_str; }\
    static const std::string StaticFunctionName() \
    { std::string classname(AMILabType<ObjectType>::name_as_string());\
      return classname+"::Get"+#varname; }\
    STATIC_HELP\
}; \
\
void AddVar_SetGet##varname(  _parentclass_ptr& pc) {\
  boost::shared_ptr<WrapClassMember> tmp; \
  AMIObject::ptr tmpobj(amiobject.lock()); \
  tmp = boost::shared_ptr<WrapClassMember>( (WrapClassMember*) new wrap_Set##varname(pc));\
  tmpobj->GetContext()->AddVar<WrapClassMember>(\
    std::string("Set")+#varname, tmp,tmpobj->GetContext()); \
  tmp = boost::shared_ptr<WrapClassMember>( (WrapClassMember*) new wrap_Get##varname(pc));\
  tmpobj->GetContext()->AddVar<WrapClassMember>(\
    std::string("Get")+#varname, tmp,tmpobj->GetContext()); \
} \

/** Macro for adding the class constructor with a static function
  to create the variable
  */
#define ADD_CLASS_CONSTRUCTOR(methodname,description_str) \
class wrap_##methodname : public WrapClassMemberWithDoc { \
  public: \
    wrap_##methodname() { \
      Set_arg_failure(false);\
      Set_quiet(false);\
      SetParametersComments(); \
    } \
    void SetParametersComments(); \
    boost::shared_ptr<BasicVariable> CallMember(ParamList* p, int stacklevel); \
    static const std::string StaticDescription()  { return description_str; }\
    static const std::string StaticFunctionName() \
    { std::string classname(AMILabType<ObjectType>::name_as_string());\
      return classname+"::"+#methodname; }\
    STATIC_HELP\
}; \
\
static void AddVar_##methodname(  boost::shared_ptr<Variables>& _context, const std::string& newname = #methodname) {\
  BasicVariable* tmp = new Variable<WrapClassMember>(new wrap_##methodname()); \
  Variables_AddVar(_context, newname, tmp, _context); \
}


/** Macro for adding the class constructor with a static function
  to create the variable
  */
#define DECLARE_CLASS_CONSTRUCTOR(methodname) \
class wrap_##methodname : public WrapClassMemberWithDoc { \
  public: \
    wrap_##methodname();\
    void SetParametersComments(); \
    boost::shared_ptr<BasicVariable> CallMember(ParamList* p, int stacklevel); \
    static const std::string StaticDescription();\
    static const std::string StaticFunctionName();\
    STATIC_HELP\
}; \
\
static const boost::shared_ptr<BasicVariable> AddVar_##methodname(  \
                              boost::shared_ptr<Variables>& _context, \
                              const std::string& newname = #methodname);

/** Macro for adding the class constructor with a static function
  to create the variable
  */
#define DEFINE_CLASS_CONSTRUCTOR(classname,methodname,description_str) \
WrapClass_##classname::wrap_##methodname::wrap_##methodname() { \
      Set_arg_failure(false);\
      Set_quiet(false);\
      SetParametersComments(); \
} \
\
const std::string WrapClass_##classname::wrap_##methodname::StaticDescription() \
{ return description_str; }\
\
const std::string WrapClass_##classname::wrap_##methodname::StaticFunctionName() \
{ std::string classname(AMILabType<ObjectType>::name_as_string());\
  return classname+"::"+#methodname; }\
\
const boost::shared_ptr<BasicVariable> WrapClass_##classname::AddVar_##methodname(  \
                                  boost::shared_ptr<Variables>& _context, \
                                  const std::string& newname ) {\
  WrapClassMember* tmp = new wrap_##methodname();\
  BasicVariable* newvar = new Variable<WrapClassMember>(tmp);\
  return Variables_AddVar(_context,newname, newvar, _context); \
}

//  return _context->AddVar(newname, newvar, _context); 

/** Macro for adding the class static method with a static function
  */
#define ADD_CLASS_STATICMETHOD(methodname,description_str) \
/**\
 * description_str\
 **/\
class wrap_static_##methodname : public WrapClassMemberWithDoc { \
  public: \
    wrap_static_##methodname() { \
      Set_arg_failure(false);\
      Set_quiet(false);\
      SetParametersComments(); \
    } \
    void SetParametersComments(); \
    boost::shared_ptr<BasicVariable> CallMember(ParamList* p, int stacklevel); \
    static const std::string StaticDescription()  { return description_str; }\
    static const std::string StaticFunctionName() \
    { std::string classname(AMILabType<ObjectType>::name_as_string());\
      return classname+"::"+#methodname; }\
    STATIC_HELP\
}; \
\
static void AddVar_##methodname(  boost::shared_ptr<Variables>& _context, const std::string& newname = #methodname) {\
  WrapClassMember* tmp = new wrap_static_##methodname();\
  BasicVariable* newvar = new Variable<WrapClassMember>(tmp);\
  Variables_AddVar(_context,newname, newvar, _context); \
}
//  _context->AddVar(newname, newvar, _context); 

/**
    Macro for adding the members to a class.
 */
#define ADDMEMBER(str_name,classname,proc_name) \
  {\
    boost::shared_ptr<WrapClassMember> tmp( (WrapClassMember*) new wrap_##classname##proc_name(objectptr));\
    Vars.AddVar<WrapClassMember>(str_name,  \
                tmp, \
                OBJECT_CONTEXT_NUMBER); \
  }


/** Shows help and returns 
*/
// TODO:mettre un message plus explicite avec le numero et le nom du paramete ...
#define ClassHelpAndReturn { \
    if (!quiet) this->ShowHelp();\
    return boost::shared_ptr<BasicVariable>();\
  }

// simple return with empty variable for a class member
#define ClassReturnEmptyVar  {\
    Set_arg_failure(true);\
    Set_quiet(false);\
    return boost::shared_ptr<BasicVariable>();\
    }

/**
 * Add the comments for the next parameter for a wrapped class member.
 **/
#define ADDPARAMCOMMENT(c) \
   this->parameters_comments.push_back(c); \
   this->paramtypes.push_back("var");

/**
 * Add the comments for the next parameter for a wrapped class member.
 **/
#define ADDPARAMCOMMENT_TYPE(type,c) \
   this->parameters_comments.push_back(c); \
   this->paramtypes.push_back(AMILabType<type>::name_as_string());

/*! \def GET_PARAM
    \brief Extracts the value of the next parameter from the list.
*/
#define GET_PARAM(type,varname,defaultval) \
  type varname = defaultval; \
  if (!get_val_param<type>( varname, p, n)) \
    ClassHelpAndReturn;

/*! \def GET_PARAM
    \brief Extracts a smart pointer of the next parameter from the list.
*/
#define GET_SMTPTR_PARAM(type,varname) \
  boost::shared_ptr<type> varname; \
  if (!get_val_smtptr_param<type>( varname, p, n)) \
    ClassHelpAndReturn;


class AMIObject;

// needed to compare objects pointers
class GenericPointer{
  void* p;
  public:
    GenericPointer(void* p1)
    {
      p=p1;
    }
    void* GetPointer() const { return p;}
    bool operator == ( const GenericPointer  & gp1){
      return p==gp1.GetPointer();
    }
};

std::string GetPointerAsString(void*);

/**
 Base class for class wrapping
 **/
class WrapCommon_DECLARE WrapClassBase
{
  DEFINE_CLASS(WrapClassBase);

  public:

    // import to declare virtual destructor here !!!
    virtual ~WrapClassBase() {}

    /// use weak pointer here to prevent blocking the object from being deleted
    boost::weak_ptr<AMIObject> amiobject;

    void SetAMIObject(boost::shared_ptr<AMIObject> obj) 
    {
      amiobject = boost::weak_ptr<AMIObject>(obj);
    }

    virtual int GetObjCounter() { return 0; }

// what was the problem of this command, why can't I get the type of an object??
//#ifdef __GNUC__
    virtual std::string ObjPointerAsString() { return ""; }
//#endif
    
//    virtual GenericPointer GetGenericPointer() { return GenericPointer(NULL); }

};

// is it useful to add this intermediate class?
/**
 Base Template class for class wrapping.
 Allows including some static member for the construction and the management of the wrapped class.
 **/
template<class T>
class WrapClass: public virtual WrapClassBase
{

  protected:  
    // for nested classes
    typedef boost::shared_ptr<WrapClass<T> > _parentclass_ptr;
    typedef T ObjectType;

  public:
    //typedef T objtype;
    //typedef boost::shared_ptr<T> objtype_ptr;
    typedef boost::shared_ptr<WrapClass<T> > ptr;


    /// Return the pointer to the wrapped object
    boost::shared_ptr<T>      _obj;
    /// have a const pointer too to deal with const objects ...
    boost::shared_ptr<T const> _const_obj;
    
    const boost::shared_ptr<T>&       GetObj()      const { return _obj; }

    const boost::shared_ptr<T const> GetConstObj() const 
    { 
      if (_obj.get())
        return _obj;
      else
        return _const_obj;
    }

// ambiguity pb
//    virtual GenericPointer GetGenericPointer() { return GenericPointer((void*)GetObj().get()); }

    virtual int GetObjCounter() const
    {
      return _obj.use_count();
    }

    virtual std::string ObjPointerAsString()
    {
      return GetPointerAsString((void*)_obj.get());
    }

    /// Constructor without parameters, needed for special case of multiple inheritance??
    WrapClass<T>() {}

    /// Constructor
    WrapClass<T>(boost::shared_ptr<T> si):  _obj(si)
    {}

    /// Constructor from const
    WrapClass<T>(boost::shared_ptr<T const> si, bool constant=true):  _const_obj(si)
    {}

    // import to declare virtual destructor here !!!
    virtual ~WrapClass<T>()
    {
//      std::cout << "~WrapClass<" << AMILabType<T>::name_as_string() << ">" << std::endl;
//      std::cout << "_obj.use_count() = " << _obj.use_count() << std::endl;
    }

    /// Constructor without parameters to deal with inheritance
    /// and avoid multiple smart pointers inside

    // Will call the constructor based on a ParamList
    static boost::shared_ptr<BasicVariable> CreateVar(ParamList*, int stacklevel, bool quiet=false);
    
    //
    virtual void AddMethods(boost::shared_ptr<WrapClass<T> > this_ptr ) = 0;
    
    /**
    * Create a Wrapped object
    * @param objectptr input smart pointer to a WrapClass<T>
    * @return smart pointer to an AMIObject class
    */
    static AMIObject::ptr AddWrap( boost::shared_ptr<WrapClass<T> >& objectptr)
    {
      // Create new instance of the class
      AMIObject::ptr amiobject( new AMIObject);
      amiobject->SetName(AMILabType<T>::name_as_string());
      amiobject->SetWrappedObject(objectptr);
      objectptr->SetAMIObject(amiobject);
      objectptr->AddMethods( objectptr);
      return amiobject;
    }
  
    /**
    * Create a Wrapped object
    * @param si_ptr input smart pointer to the template class T
    * @return smart pointer to an AMIObject class
    */
    static Variable<AMIObject>::ptr CreateVar( WrapClass<T>* _objp)
    {
      boost::shared_ptr<WrapClass<T> > obj_smtptr(_objp);
      AMIObject::ptr amiobject(AddWrap(obj_smtptr));
      boost::shared_ptr<Variable<AMIObject> > varres(
          new Variable<AMIObject>( amiobject));
      return varres;
    }

};

//------------------------------------------------------------------------------
/**
 * Basic class for wrapping class function members.
 **/
class WrapCommon_DECLARE WrapClassMember {

  //DEFINE_CLASS(WrapClassMember);

  protected:
    bool arg_failure;
    bool quiet;
    // disable the call of constructors to fit arguments
    bool noconstr;

  public:
    WrapClassMember(): noconstr(false) {}
    virtual ~WrapClassMember() {}
    virtual void SetParametersComments()          {};
    virtual boost::shared_ptr<BasicVariable> CallMember(ParamList*, int stacklevel)  
    { return boost::shared_ptr<BasicVariable>(); };

    /**
     * Display the function help in an information dialog.
     */
    virtual void ShowHelp() {}

    void Set_arg_failure(bool const & f) { arg_failure=f;}
    bool Get_arg_failure() const { return arg_failure;}

    void Set_quiet(bool const & q) { quiet=q;}
    bool Get_quiet() const { return quiet; } 

    void Set_noconstr(bool const& nc) { noconstr=nc; }
    bool Get_noconstr() const { return noconstr; } 
};
 

//------------------------------------------------------------------------------
class WrapCommon_DECLARE WrapClassMemberWithDoc : public WrapClassMember {

  //DEFINE_CLASS(WrapClassMemberWithDoc);

  protected:
    std::vector<std::string> parameters_comments;
    std::vector<std::string> paramtypes;
    std::string return_comments;
    std::string return_type;

  public:
    virtual ~WrapClassMemberWithDoc() {}
    virtual void SetParametersComments()          {};
    virtual boost::shared_ptr<BasicVariable> CallMember(ParamList*, int stacklevel)  
    { return boost::shared_ptr<BasicVariable>(); };

    /**
     * Display the function help in an information dialog.
     */
    void ShowHelp();
    
    // for access in scripting language
    std::string get_return_comments() const { return return_comments; }
    std::string get_return_type() const { return return_type;}
    size_t get_parameters_comments_size() const { return parameters_comments.size(); }
    std::string get_parameters_comments( int n) const { return parameters_comments[n]; }
    std::string get_paramtypes( int n)  const { return paramtypes[n]; }

    virtual const std::string GetDescription() const { return std::string();};
    virtual const std::string GetFunctionName() const { return std::string();};
};



#endif 
// _wrapfunction_class_h_
