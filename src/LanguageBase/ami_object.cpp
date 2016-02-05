
#include "ami_object.h"
//#include "wrapfunction_class.h"
#include <iostream>
#include "Variables.hpp"


BasicVariable::ptr Variables_AddVar(  boost::shared_ptr<Variables>& vars,
                                       const std::string& name, 
                                       BasicVariable* val, 
                                       const boost::shared_ptr<Variables>& context )
{
  return vars->AddVar(name,val,context);
}

BasicVariable::ptr Variables_AddVar(  boost::shared_ptr<Variables>& vars,
                                       const std::string& name, 
                                       BasicVariable::ptr& val, 
                                       const boost::shared_ptr<Variables>& context )
{
  return vars->AddVar(name,val,context);
}

BasicVariable::ptr Variables_AddVar(  boost::shared_ptr<Variables>& vars,
                                       BasicVariable::ptr& val, 
                                       const boost::shared_ptr<Variables>& context )
{
  return vars->AddVar(val,context);
}


void Variables_AddDefault(  boost::shared_ptr<Variables>& vars,
                            boost::shared_ptr<Variables>& defcontext )
{
  return vars->AddDefault(defcontext);
}


AMIObject::AMIObject()
{
  // _name     = "";
  _vars     = boost::shared_ptr<Variables>(new Variables);
}

/**
  * Destructor : empties the list of variables
  */
AMIObject::~AMIObject() 
{
  //CLASS_MESSAGE(boost::format("_wrapped_object count = %1%") % _wrapped_object->GetObjCounter() );
  _vars->EmptyVariables();
  //CLASS_MESSAGE(boost::format("_wrapped_object count = %1%") % _wrapped_object->GetObjCounter() );
}

void AMIObject::SetName( const std::string& fname)
{ 
//    _name = fname; 
    _vars->SetName(fname);
}

const std::string AMIObject::GetName() const
{ 
  return _vars->GetName();
}

//--------------------------------------------------------
void AMIObject::SetClass(AMIClass::ptr& amiclass)
{
    if (amiclass.get()!=NULL)
/*
      std::cout  << "will run the code of the class "
            << amiclass->GetName()
            << " for the object " 
            << GetName()
            << std::endl;
*/
    _class = amiclass;
}
