/*
    ==================================================
    Software : AMILab
    Authors  : Karl Krissian
    Email    : karl@bwh.harvard.edu

    AMILab is a language for image processing
    ==================================================
    Copyright (C) 1996-2005  Karl Krissian

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    ================================================== 
   The full GNU Lesser General Public License file is in Devel/Sources/Prog/LesserGPL_license.txt
*/

#include "VarContexts.hpp"
#include "amilab_messages.h"

#include <iostream>
#include <boost/format.hpp>

#include "ami_object.h"
#include "wrapfunction_class.h"
#include "LanguageBaseConfigure.h"

#include "CommonConfigure.h"
COMMON_VAR_IMPORT unsigned char GB_debug;
using namespace std;

//======================================================================
// PUBLIC MEMBERS
//======================================================================

//--------------------------------------------------
VarContexts::VarContexts() {
  _context.push_back(Variables::ptr(new Variables()));
  _context[0]->SetName("Global context");
  _current_context = 0;
  _builtin_context = Variables::ptr(new Variables());
  _builtin_context->SetName("Builtin context");
}

//--------------------------------------------------
VarContexts::~VarContexts() {
  CLASS_MESSAGE("");
  // no need to delete, smart pointers ...
  while (_context.size()>1) {
    DeleteLastContext();
  }
  _builtin_context->EmptyVariables();
}

//--------------------------------------------------
// mapping class names with their contexts for typedef wrapping
void VarContexts::AddClassMap(std::string classname, 
                              BasicVariable::wptr classvar)
{
  std::map<std::string,BasicVariable::wptr>::iterator 
    it = classes_map.find(classname);
  if (it!=classes_map.end()) {
    BasicVariable::wptr var = it->second;
    if (!var.expired()) {
      std::cerr << "Adding twice the class " << classname << "!!!" << std::endl;
    }
    classes_map.erase(classname);
  }
  
  classes_map.insert(std::pair<std::string, BasicVariable::wptr>(classname,classvar));
}


//--------------------------------------------------
BasicVariable::wptr VarContexts::GetClassVar(std::string classname)
{
  std::map<std::string,BasicVariable::wptr>::iterator 
    it = classes_map.find(classname);
  if (it!=classes_map.end()) {
    return it->second;
  } else
    return BasicVariable::wptr();
}

//--------------------------------------------------
void VarContexts::ListClassMap()
{
  std::map<std::string,BasicVariable::wptr>::iterator it;
  for( it = classes_map.begin(); it!=classes_map.end(); it++)
  {
    std::cout << " class: " << it->first << std::endl;
  }
}


//--------------------------------------------------
void VarContexts::EmptyVariables() {
  //CLASS_MESSAGE("");
  for (int i=_context.size()-1; i>=0; i--)
    _context[i]->EmptyVariables();
  classes_map.clear();
}

//--------------------------------------------------
Variables::ptr VarContexts::NewContext(const char* name) {

  Variables::ptr newcontext = Variables::ptr(new Variables());
  newcontext->SetName(name);
  _context.push_back(newcontext);

  if (GB_debug) 
    std::cerr << "New context " << name << std::endl;

  return newcontext;
}

//--------------------------------------------------
bool VarContexts::DeleteLastContext() {

  CLASS_MESSAGE("Removing last context");
  if (_context.size()>1) {
    // no need to delete, smart pointer
    //Variables::ptr last_context = _context.back();
    //last_context->EmptyVariables();
    // delete last_context;
    // need to empty the variables first !!! because they contain a smart pointer to their own context ...
    _context[_context.size()-1]->EmptyVariables();
    _context.pop_back();
    SetLastContext();
    return true;
  }
  else {
    CLASS_ERROR("Cannot remove the main context ");
    return false;
  }
}

//--------------------------------------------------
void VarContexts::display() {

 std::cout  << "\n"
        << "Builtin Context "
        << "\n ------------- \n",
  _builtin_context->display();


  for (int i=_context.size()-1; i>=0; i--)
  {
   std::cout  << "\n"
          << "Context " << i 
          << " " << _context[i]->GetName()
          << "\n ------------- \n",
    _context[i]->display();
  }

}


//--------------------------------------------------
bool VarContexts::ExistVar(const char* varname) 
{

  for (int i=_context.size()-1; i>=0; i--)
    if (_context[i]->ExistVar(varname)) return true;
  if(_builtin_context->ExistVar(varname)) return true;

  return false;
}

//--------------------------------------------------
boost::shared_ptr<std::vector<std::string> > VarContexts::SearchCompletions(const std::string& varname) 
{
  boost::shared_ptr<std::vector<std::string> > completions;

  completions = boost::shared_ptr<std::vector<std::string> >(new std::vector<std::string> ());

  for (int i=_context.size()-1; i>=0; i--)
    _context[i]->SearchCompletions(varname,completions);

  _builtin_context->SearchCompletions(varname,completions);

  return completions;
}


//--------------------------------------------------
boost::shared_ptr<std::vector<std::string> > VarContexts::SearchVariables(const vartype type, bool recursive)
{
  boost::shared_ptr<std::vector<std::string> > completions;
  completions = boost::shared_ptr<std::vector<std::string> >(new std::vector<std::string> ());

  if (!recursive) {
    for (int i=_context.size()-1; i>=1; i--)
      _context[i]->SearchVariables(type,completions);

    // global context, prepend "global::"
    _context[0]->SearchVariables(type,completions,"global::");

    // global context, prepend "global::"
    _builtin_context->SearchVariables(type,completions);
  } else {
    // global context, prepend "global::"
    SearchVariablesRecursive(type,completions,_context[0],"global::",0);

    // global context, prepend "global::"
    SearchVariablesRecursive(type,completions,_builtin_context,"",0);
    
  }

  return completions;
}

#define MAX_RECURSION_LEVEL 10

//--------------------------------------------------
void VarContexts::SearchVariablesRecursive( const vartype& type,
                                   boost::shared_ptr<std::vector<std::string> >& variables,
                                   const Variables::ptr& context,
                                   std::string const & prefix,
                                   int rec_level
                                          ) const
{
  if (rec_level>MAX_RECURSION_LEVEL) {
    CLASS_ERROR("Maximum level of recursion reached!")
    return;
  }
  std::string new_prefix;

  for(int i=0;i<(int)context->GetSize();i++) {
    BasicVariable::ptr m_var = (*context)[i];

    if (m_var.get()) {
      if (m_var->Type() == type) {
        new_prefix = prefix + m_var->Name();
        variables->push_back(new_prefix);
      } else {
        if ((m_var->Type() == type_ami_object))
        {
          // get the pointer to the objet
          DYNAMIC_CAST_VARIABLE(AMIObject,m_var,varobj);
          AMIObject::ptr obj( varobj->Pointer());
          new_prefix = prefix + m_var->Name() + ".";
          SearchVariablesRecursive(type, variables, obj->GetContext(), 
                                   new_prefix, rec_level+1);
        }
      }
    }
  }
}

//--------------------------------------------------
boost::shared_ptr<std::vector<std::string> > VarContexts::SearchAMIObjectTypeVariables(const std::string& type)
{
  boost::shared_ptr<std::vector<std::string> > completions;
  completions = boost::shared_ptr<std::vector<std::string> >(new std::vector<std::string> ());

  SearchAMIObjectTypeVariablesRecursive(type,completions,_context[0],"global::");

  return completions;
}

//--------------------------------------------------
void VarContexts::SearchAMIObjectTypeVariablesRecursive( const std::string & type_string,
                                    boost::shared_ptr<std::vector<std::string> >& variables,
                                    const Variables::ptr& context,
                                    std::string const & prefix,
                                    int rec_level) const
{
  if (rec_level>MAX_RECURSION_LEVEL) {
    CLASS_ERROR("Maximum level of recursion reached!")
    return;
  }
  std::string new_prefix;
  
  for(int i=0;i<(int)context->GetSize();i++) {
    BasicVariable::ptr m_var = (*context)[i];
    
    if (m_var.get()) {              
      if (m_var->Type() == type_ami_object) {
        new_prefix = prefix + m_var->Name();
        // get the pointer to the objet
        DYNAMIC_CAST_VARIABLE(AMIObject,m_var,varobj);
        AMIObject::ptr obj( varobj->Pointer());
        boost::shared_ptr<WrapClassBase> TheObject( varobj->Pointer()->GetWrappedObject());
        if(TheObject.get()) {
          //Filter by type.
          if(TheObject->get_name()==std::string("WrapClass_")+type_string) {
            variables->push_back(new_prefix);
          }
        }// if(TheObject.get())
        else {
          // search for ami classes, but would need to separe them from wrapped
          // c++ classes, we add (ami) add the beginning ...
          AMIClass::ptr oclass = varobj->Pointer()->GetClass();
          if (oclass.get()) {
            if (std::string("(ami)")+oclass->GetName()==type_string) {
              variables->push_back(new_prefix);
            }
          }
        }
        new_prefix += ".";
        SearchAMIObjectTypeVariablesRecursive(type_string, variables, 
                                              obj->GetContext(), 
                                              new_prefix,
                                              rec_level+1
                                             );
      } // if (m_var->Type() == type_ami_object)      
    } //if (m_var.get())
  } //for
} // SearchAMIObjectTypeVariables

//--------------------------------------------------
int VarContexts::GetNewVarContext()
{
  if (this->_context[_current_context]->GetGlobalNew())
    return 0; 
  else 
    return _current_context;
} // GetNewVarContext()




//--------------------------------------------------
BasicVariable::ptr VarContexts::AddVar(  
              const IdentifierInfo::ptr& info, 
              BasicVariable::ptr& val)
{
 int context;
 context = info->GetCreationContext();
 std::string idname = info->GetName();
 BasicVariable::ptr res =  
  AddVar(
          idname.c_str(),
          val,
          context);
  
 return res;
} // AddVar()

//--------------------------------------------------
BasicVariable::ptr VarContexts::AddVar(BasicVariable::ptr var, int context)
{

  if (context==OBJECT_CONTEXT_NUMBER) {
    CLASS_MESSAGE("object context");
    if (_object_context.get()) {
      CLASS_MESSAGE("adding variable reference into object context ");
      return _object_context->AddVar(var, _object_context);
    }
    else {
      CLASS_ERROR("Calling object variable without any object context");
      return BasicVariable::ptr();
    }
  }

  if (context==NEWVAR_CONTEXT) 
    context = GetNewVarContext();

  CLASS_MESSAGE((boost::format("Context number %d ")% context).str().c_str());
  return _context[context]->AddVar(var,_context[context]);
}

//--------------------------------------------------
BasicVariable::ptr VarContexts::GetVar(const char* varname, int context)
{
  if (context==-1) {
    // TODO: limit to last context, if nothing else is specified !!!
    //for(int i=_context.size()-1;i>=0;i--)
    //  if (_context[i]->GetVar(varname,var)) return true;

    // TODO: all these manipulation within the global variables are not thread-safe, to improve ....
    BasicVariable::ptr var = _context[GetCurrentContextNumber()]->GetVar(varname);
//    BasicVariable::ptr var = _context[_context.size()-1]->GetVar(varname);
    if (var.get()) 
      return var;
    else
      return _builtin_context->GetVar(varname);
  }
  else 
    if ((context>=0)&&(context<=_current_context))
      return _context[context]->GetVar(varname);
  else
    if ((context==OBJECT_CONTEXT_NUMBER)&&(_object_context.get())) {
      //CLASS_MESSAGE(boost::format("Looking in object context for %1% ... %2% ") % varname % res );
      //_object_context->display();
      return _object_context->GetVar(varname);
    }

  return BasicVariable::ptr();
}


//--------------------------------------------------
bool VarContexts::deleteVar(const char* varname)
{
  int i;
  for(i=_current_context;i>=0;i--)
    if (_context[i]->deleteVar(varname)) {
      if (GB_debug) 
        std::cerr << "Deleted Var in context number " << i << std::endl;
      return true;
    }
  return false;
}


//--------------------------------------------------
int VarContexts::GetContext(BasicVariable::ptr var)
{
  // check first for object context
  if (var->GetContext().get()) {
      return OBJECT_CONTEXT_NUMBER;
  }
  for(int i=_current_context;i>=0;i--)
    if (_context[i]->ExistVar(var)) 
      return i;
  return -1;
}


//--------------------------------------------------
bool VarContexts::deleteVar(BasicVariable::ptr var)
{

  // Check for object context
  if (var->GetContext().get()) {
    var->GetContext()->deleteVar(var->Name().c_str());
    return true;
  }

  for(int i=_current_context;i>=0;i--)
    if (_context[i]->ExistVar(var)) {
      if (GB_debug) 
        std::cerr << "Deleted Var in context number " << i << std::endl;
      // TODO: improve efficiency by not going twice through the variables
      _context[i]->deleteVar(var->Name().c_str());
      return true;
    }
  return false;
}

//--------------------------------------------------
bool VarContexts::deleteVar(BasicVariable* var)
{

  // Check for object context
  if (var->GetContext().get()) {
    var->GetContext()->deleteVar(var->Name().c_str());
    return true;
  }

  for(int i=_current_context;i>=0;i--)
    if (_context[i]->ExistVar(var)) {
      if (GB_debug) 
        std::cerr << "Deleted Var in context number " << i << std::endl;
      // TODO: improve efficiency by not going twice through the variables
      _context[i]->deleteVar(var->Name().c_str());
      return true;
    }
  return false;
}

//--------------------------------------------------
int VarContexts::deleteVars(const std::string& varmatch)
{
  int count =0;

  int i;
  for(i=_current_context;i>=0;i--)
    count += _context[i]->deleteVars(varmatch);

  return count;
  
}

//--------------------------------------------------
void VarContexts::SetGlobalContext() {
  _current_context = 0;
}


//--------------------------------------------------
void VarContexts::SetLastContext() {
  _current_context = _context.size()-1;
}


