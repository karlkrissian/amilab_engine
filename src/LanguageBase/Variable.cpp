
#include <iomanip>
#include <cassert>
#include "boost/format.hpp"


#include "DefineClass.hpp"
#include "Variable.hpp"

//#include "ParamBox.hpp"
/*
#include "ParamPanel.hpp"
#include "DessinImage.hpp"
#include "Viewer3D.hpp"
#include "ami_function.h"
#include "ami_class.h"
#include "ami_object.h"
#include "ami_cpp_object.h"
#include "wrapfunction_class.h"
#include "amilab_messages.h"
#include "VarArray.h"
*/

#include "ami_object.h"
#include "wrapfunction_class.h"

#include <string>
#include <vector>

using namespace std;

#include "CommonConfigure.h"
COMMON_VAR_IMPORT unsigned char GB_debug;

#include "LanguageBaseConfigure.h"

using namespace std;

// forward class declarations
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
class VarArray;

// declared in wrapfunction.cpp
bool get_next_param( BasicVariable::ptr& var, 
                    ParamList*p, int& num, bool required = false, bool quiet=false);

#include "VarArray.h"

#include <ostream>
void ToStream(std::ostream& o, const char* st)
{
 o << st;
}

#define VARTYPE_PROP(type,name,isnum) \
  template<> LanguageBase_EXPORT vartype GetVarType<type>()  { return name;     } \
  template<> LanguageBase_EXPORT bool IsNumerical  <type>()  { return isnum;    }


VARTYPE_PROP( bool,                 type_bool,            true);
VARTYPE_PROP( float,                type_float,           true);
VARTYPE_PROP( double,               type_double,          true); /// New (added: 24/05/2010)
VARTYPE_PROP( long,                 type_long,            true); /// New (added: 27/05/2010)
VARTYPE_PROP( unsigned long,        type_ulong,           true); /// New (added: 27/05/2010)
VARTYPE_PROP( int,                  type_int,             true);
VARTYPE_PROP( short,                type_short,           true);
VARTYPE_PROP( unsigned short,       type_ushort,          true);
VARTYPE_PROP( unsigned char,        type_uchar,           true)
VARTYPE_PROP( std::string,          type_string,          false)
VARTYPE_PROP( C_wrap_procedure,     type_c_procedure,     false)
VARTYPE_PROP( WrapClassMember,      type_class_member,    false)
//VARTYPE_PROP( C_wrap_imagefunction, type_c_image_function,false)
VARTYPE_PROP( C_wrap_varfunction,   type_c_function,      false)
VARTYPE_PROP( AMIFunction,          type_ami_function,    false)
VARTYPE_PROP( AMIClass,             type_ami_class,       false)
VARTYPE_PROP( AMIObject,            type_ami_object,      false)
//VARTYPE_PROP( ,         type_ami_cpp_object,  false)
VARTYPE_PROP( VarArray,             type_array,           false)

#undef VARTYPE_PROP


#define VARTYPE_STRING_DOUBLE(type,val1,val2) \
  template <> std::string LanguageBase_EXPORT Variable<type>::GetValueAsString() const { return (boost::format("%1%")%(val1)).str();} \
  template <> double      LanguageBase_EXPORT Variable<type>::GetValueAsDouble() const { return (double) (val2); } 

#define VARTYPE_DEFAULT(type) \
  template <> std::string LanguageBase_EXPORT Variable<type>::GetValueAsString() const { return (boost::format("%1%")%(#type)).str();} \
  template <> double      LanguageBase_EXPORT Variable<type>::GetValueAsDouble() const { return 0.0; } 


VARTYPE_STRING_DOUBLE( float,                Value(),                   Value())
VARTYPE_STRING_DOUBLE( double,               Value(),                   Value())
VARTYPE_STRING_DOUBLE( long,                 Value(),                   Value()) 
VARTYPE_STRING_DOUBLE( unsigned long,        Value(),                   Value()) 
VARTYPE_STRING_DOUBLE( bool,                 (Value()?"true":"false"),  (Value()?1:0)) /// New (added: 19/11/2010)
VARTYPE_STRING_DOUBLE( int,                  Value(),                   Value())
VARTYPE_STRING_DOUBLE( short,                Value(),                   Value())
VARTYPE_STRING_DOUBLE( unsigned short,       (int)Value(),              Value())
VARTYPE_STRING_DOUBLE( unsigned char,        (int)Value(),              Value())
//VARTYPE_STRING_DOUBLE( std::string,          Value(),                   0)

//template <> LanguageBase_EXPORT std::string Variable<std::string>::GetValueAsString() const { return Value();} 
//template <> LanguageBase_EXPORT double Variable<std::string>::GetValueAsDouble() const { return 0; } 


VARTYPE_DEFAULT( FILE)
VARTYPE_DEFAULT( C_wrap_procedure)
VARTYPE_DEFAULT( C_wrap_imagefunction)
VARTYPE_DEFAULT( C_wrap_varfunction)
VARTYPE_DEFAULT( AMIFunction)
VARTYPE_DEFAULT( AMIClass)
//VARTYPE_DEFAULT( AMIObject)
VARTYPE_DEFAULT( VarArray)
VARTYPE_DEFAULT( WrapClassMember)

template <> std::string LanguageBase_EXPORT Variable<AMIObject>::GetValueAsString() const 
{
  boost::shared_ptr<std::string> string_ptr;

  // try to cast as string
  boost::shared_ptr<WrapClassBase> object( this->Pointer()->GetWrappedObject());
  WrapClass<std::string>* wc = dynamic_cast<WrapClass<std::string>* >(object.get());
  if (wc!=NULL)  string_ptr = wc->GetObj();

  if (string_ptr.get())
  {
    return *string_ptr;
  } else
    return (boost::format("%1%")%("AMIObject")).str();
}

template <> double      LanguageBase_EXPORT Variable<AMIObject>::GetValueAsDouble() const 
{
  // try to cast as float
  return 0.0; 
}


#undef VARTYPE_STRING_DOUBLE

//------------------------------------------------------
//------- Variable<WrapClassMember>
//------------------------------------------------------

#include "wrapfunction_class.h"
template<> AMI_DLLEXPORT std::string Variable<WrapClassMember>::TreeCtrlInfo() const
{
  // limit size of description here ???
  return "";
  // should try to cast to WrapClassMemberWithDoc
  //Pointer()->GetDescription();
};

//------------------------------------------------------
//------- Variable<float>
//------------------------------------------------------


//#include "Variable_float.cpp"

//------------------------------------------------------
//------- Variable<unsigned char>
//------------------------------------------------------


//------------------------------------------------------
//------- Variable<string>
//------------------------------------------------------



// instantiate + operator
/*
template<> AMI_DLLEXPORT
BasicVariable::ptr operator +(const boost::shared_ptr<Variable<float> >& a, 
                              const boost::shared_ptr<Variable<float> >& b);
*/

/*
  template<> AMI_DLLEXPORT class AMILabType<float> { 
    
    static char const* name_as_string() { return "float"; } 
    
    static boost::shared_ptr<float> GetValue(BasicVariable::ptr var)  
    { 
      boost::shared_ptr<Variable<float> > tmp(      boost::dynamic_pointer_cast<Variable<float> >(var)); 
      if (tmp.get()) return tmp->Pointer(); 
      else return boost::shared_ptr<float>();
    } 
    
    static BasicVariable::ptr CreateVar(float& val)  
    { 
      boost::shared_ptr<float> valptr(new float(val));
      Variable<float>::ptr varres( new Variable<float>(valptr));
      return varres; 
    } 
    
  }; 
*/
#include "wrapfunction_class.h"
#include "ami_function.h"

AMI_DEFINE_BASICTYPE(bool);
AMI_DEFINE_BASICTYPE(unsigned char);
AMI_DEFINE_BASICTYPE(float);
AMI_DEFINE_BASICTYPE(double);
AMI_DEFINE_BASICTYPE(long);
AMI_DEFINE_BASICTYPE(int);
AMI_DEFINE_BASICTYPE(short);
AMI_DEFINE_BASICTYPE(unsigned long);
AMI_DEFINE_BASICTYPE(unsigned short);
//AMI_DEFINE_BASICTYPE(std::string);
AMI_DEFINE_BASICTYPE(AMIFunction);
AMI_DEFINE_BASICTYPE(AMIClass);
AMI_DEFINE_BASICTYPE(VarArray);


std::vector<std::string> AMILabType<AMIFunction>::conversion_types = { };
std::vector<std::string> AMILabType<AMIClass>::conversion_types = { };
std::vector<std::string> AMILabType<VarArray>::conversion_types = { };


#define AMI_DEFINE_BASICTYPE_NOCONSTRUCT(type) \
	std::string AMILabType<type>::name_as_string() { return std::string(#type); } \
    \
    boost::shared_ptr<type> AMILabType<type>::GetValue(BasicVariable::ptr var,int stacklevel, bool noconstr, bool quiet)  \
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
          /*FILE_ERROR(boost::format("Cannot be converted to type %2%.") % AMILabType<type>::name_as_string().c_str());*/\
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
    BasicVariable::ptr AMILabType<type>::CreateVar(const type& val)  \
    { \
      return BasicVariable::ptr(); \
    } 

AMI_DEFINE_BASICTYPE_NOCONSTRUCT(C_wrap_procedure);
AMI_DEFINE_BASICTYPE_NOCONSTRUCT(C_wrap_imagefunction);
AMI_DEFINE_BASICTYPE_NOCONSTRUCT(C_wrap_varfunction);



//AMI_DEFINE_LIMITED_TYPE(AMIObject);
//AMI_DEFINE_LIMITED_TYPE(WrapClassMember);
// abstract
//AMI_DEFINE_BASICTYPE_NOCONSTRUCT(WrapClassMember);

// At least have name_as_string here, define in their corresponding wrapping
//std::string AMILabType<AMIObject>::name_as_string() { return std::string("AMIObject"); } 
//std::string AMILabType<WrapClassMember>::name_as_string() { return std::string("WrapClassMember"); } 
