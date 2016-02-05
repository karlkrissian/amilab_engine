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

#include <iomanip>
#include <cassert>
#include "boost/format.hpp"

#include "Variables.hpp"
#include "style.hpp"

#include <iostream>
#include "amilab_messages.h"

#include "ami_object.h"

//extern unsigned char       GB_debug;
//extern yyip::Driver GB_driver;

//======================================================================
// PRIVATE METHODS
//======================================================================


/*
//--------------------------------------------------
unsigned char Variables::deleteVar(int i)
{

  if (GB_debug)
    fprintf(stderr,"Variables::deleteVar(%d)\n",i);

  if (i<_num) {
    if (GB_debug) fprintf(stderr,"Variables::deleteVar(%d) call to Delete()\n",i);
    _vars[i]->Delete();
    AddFreePosition(i);
  }
  else
    fprintf(stderr,"deleteVar(%i) variable not found \n", i);
  
  return true;
}
*/

//======================================================================
// PUBLIC METHODS
//======================================================================

// template
// boost::shared_ptr<Variable<AMIObject> > Variables::AddVar(
//         const std::string& name,
//         boost::shared_ptr<AMIObject >& val,
//         boost::shared_ptr<Variables> context = boost::shared_ptr<Variables>() );


//--------------------------------------------------
Variables::~Variables()
{
  CLASS_MESSAGE((boost::format("Deleting context %1% ") % _context_name.c_str()).str().c_str());
  EmptyVariables();
}

//--------------------------------------------------
void Variables::AddDefault( BasicVariable::ptr& defvarcontext )
{
  DYNAMIC_CAST_VARIABLE(AMIObject,defvarcontext,var1);
  if (!var1.get()) {
    CLASS_MESSAGE((boost::format(" Variable %1% is not of type AMIObject") 
                    % defvarcontext->get_name()).str().c_str());
    return;
  }
  _defaults.push_back(var1->Pointer()->GetContext());
}

//--------------------------------------------------
void Variables::RemoveDefault( BasicVariable::ptr& defvarcontext )
{
  DYNAMIC_CAST_VARIABLE(AMIObject,defvarcontext,var1);
  if (!var1.get()) {
    CLASS_MESSAGE((boost::format(" Variable %1% is not of type AMIObject") 
                    % defvarcontext->get_name()).str().c_str());
    return;
  }
  _defaults.remove(var1->Pointer()->GetContext());
}

//--------------------------------------------------
std::string Variables::CheckVarName(const char* name)
{
  std::string resname(name);

  // Check if the variable exists,
  // if it exists try to delete it,
  // if it cannot be delete, change the name
  if (ExistVar(name)) {
    if (!deleteVar(name)) {
      // otherwise create a new name
      int i = 1;
      Repeter
        resname = (boost::format("%s_%d") % name %i).str();
        i++;
      JusquA Non(ExistVar(resname.c_str())) FinRepeter;
    }
  }
  return resname;
}


//--------------------------------------------------
BasicVariable::ptr Variables::AddVar( 
          const std::string& name, 
          BasicVariable::ptr& val, 
          const boost::shared_ptr<Variables>& context)
{
  CLASS_MESSAGE((boost::format(" %1%, in %2% ") % name % GetName()).str().c_str());

  std::string resname = this->CheckVarName(name.c_str());
  BasicVariable::ptr newvar(val);
  //std::cout << "  **  newvar =  " << newvar << std::endl;

  newvar->Rename(resname.c_str());
  newvar->SetContext(context);
  _vars.push_back(newvar);

  return newvar;
}

//--------------------------------------------------
BasicVariable::ptr Variables::AddVar( 
          const std::string& name, 
          BasicVariable* val, 
          const boost::shared_ptr<Variables>& context)
{
  CLASS_MESSAGE((boost::format(" %1%, in %2% ") % name % GetName()).str().c_str());

  std::string resname = this->CheckVarName(name.c_str());
  BasicVariable::ptr newvar(val);
  //std::cout << "  **  newvar =  " << newvar << std::endl;

  newvar->Rename(resname.c_str());
  newvar->SetContext(context);
  _vars.push_back(newvar);

  return newvar;
}



//--------------------------------------------------
BasicVariable::ptr Variables::AddVar( BasicVariable::ptr& var, const Variables::ptr& context )
{

  CLASS_MESSAGE((boost::format(" %s ") % var->Name()).str().c_str());

  std::string resname = this->CheckVarName(var->Name().c_str());
  // TODO: fix the following code, maybe not so easy ...
  // should we copy the contents here ??
  // why do we create a reference here ???
  BasicVariable::ptr newvar(var);
//  BasicVariable::ptr newvar(var->NewReference());
  newvar->Rename(resname.c_str());
  newvar->SetContext(context);
  _vars.push_back(newvar);

  return newvar;
}


// TODO
//--------------------------------------------------
void Variables::SearchCompletions(const std::string& varname, 
    boost::shared_ptr<std::vector<std::string> >& completions)
{
   std::string name;
   std::vector<BasicVariable::ptr>::iterator Iter;
 
   for (Iter  = _vars.begin();
        Iter != _vars.end()  ; Iter++ )
   {
     name = (*Iter)->Name();
     if (name.substr(0,varname.size()) == varname) 
         completions->push_back(name);
   }
   
   
   // search in default contexts
   for( auto def_it:_defaults)
   {
     def_it->SearchCompletions(varname,completions);
   }
}


// TODO
//--------------------------------------------------
void Variables::SearchVariables( const vartype& type,
                      boost::shared_ptr<std::vector<std::string> >& varlist,
                      const std::string& prepend)
{
   std::string name;
   std::vector<BasicVariable::ptr>::iterator Iter;
 
   for (Iter  = _vars.begin();
        Iter != _vars.end()  ; Iter++ )
   {
     if ((*Iter)->Type()==type) {
       name = prepend+(*Iter)->Name();
       varlist->push_back(name);
     }
   }
} // SearchVariables()


//--------------------------------------------------
bool Variables::ExistVar(const char* varname)
{
  std::vector<BasicVariable::ptr>::iterator Iter;
  for (Iter  = _vars.begin();
       Iter != _vars.end()  ; Iter++ )
  {
    if ((*Iter)->HasName(varname)) return true;
  }

  return false;
}


//--------------------------------------------------
bool Variables::ExistVar(BasicVariable::ptr& var)
{
  std::vector<BasicVariable::ptr>::iterator Iter;
  for (Iter  = _vars.begin();
       Iter != _vars.end()  ; Iter++ )
  {
    if ( (*Iter)->Equal(var) ) return true;
  }
  return false;
}

//--------------------------------------------------
bool Variables::ExistVar(BasicVariable* var)
{
  std::vector<BasicVariable::ptr>::iterator Iter;
  for (Iter  = _vars.begin();
       Iter != _vars.end()  ; Iter++ )
  {
    if ( *(*Iter) == var ) return true;
  }
  return false;
}


//--------------------------------------------------
BasicVariable::ptr Variables::GetVar(const char* varname)
{
  std::vector<BasicVariable::ptr>::iterator Iter;
  for (Iter  = _vars.begin();
       Iter != _vars.end()  ; Iter++ )
  {
    if ((*Iter)->HasName(varname)) {
      return BasicVariable::ptr(*Iter);
    }
  }

  // if variable not found, try with default contexts
  std::list<Variables::ptr>::iterator Iter2;
  for (Iter2  = _defaults.begin();
       Iter2 != _defaults.end()  ; Iter2++ )
  {
    // TODO: deal with possible loops !!!
    BasicVariable::ptr res = (*Iter2)->GetVar(varname);
    if (res.get()) 
    {
      return res;
    }
  }

  return BasicVariable::ptr();
}

/*
//--------------------------------------------------
unsigned char Variables::GetVar(const char* varname, int* i)
{
  
  (*i)=0;
  while (((*i)<_num)&&(!_vars[*i]->HasName(varname)))
    {
      //  printf("%s %s\n",(char*) _vars[i]->Name(),varname);
      (*i)++;
      }
  if ((*i)<_num) {
    return 1;
  }
  else {
    return 0;
      }
} // Variables::GetVar()
*/

//--------------------------------------------------
bool Variables::deleteVar(const char* varname)
{
  CLASS_MESSAGE( (boost::format("Variables::deleteVar(%s) for %s") % varname % GetName()).str().c_str());

  std::vector<BasicVariable::ptr>::iterator Iter;
  for (Iter  = _vars.begin();
       Iter != _vars.end()  ; Iter++ )
  {
    if ((*Iter)->HasName(varname)) {
      //delete (*Iter); // not needed anymore
      //(*Iter)->Delete();

      CLASS_MESSAGE( (boost::format("removing variable from the list (use_count = %1%)") %  (*Iter).use_count()).str().c_str());
      Iter = _vars.erase(Iter);
      return true;
    }
  }
  CLASS_ERROR( (boost::format("deleteVar(%s) variable not found") % varname).str().c_str());
  return false;

} // Variables::deleteVar()


//--------------------------------------------------
int Variables::deleteVars(const std::string& varmatch)
{
//   // convert string to wxString
//   wxString wxvarmatch(varmatch.c_str(), wxConvUTF8);
//   int count=0;
// 
//   std::vector<BasicVariable::ptr>::iterator Iter;
//   Iter  = _vars.begin();
//   while(Iter != _vars.end())
//   {
//     // convert name to wxString
//     wxString wxvarname((*Iter)->Name().c_str(), wxConvUTF8);
//     if (wxvarname.Matches(wxvarmatch)) {
//       // why seg fault ??
//       // delete *Iter; // try to delete the variable here // not needed anymore
//       //(*Iter)->Delete();
//       Iter = _vars.erase(Iter);
//       count++;
//     } else
//       Iter++;
//   }
//   return count;
  return 0;
} // Variables::deleteVars()


//--------------------------------------------------
void Variables::display()
{
  std::cout << "VARIABLES:" << std::endl;
  std::vector<BasicVariable::ptr>::iterator Iter;
  for (Iter  = _vars.begin();
       Iter != _vars.end()  ; Iter++ )
  {
    (*Iter)->display(std::cout);
    std::cout << std::endl;
  }
} // Variables::display()


//--------------------------------------------------
void Variables::EmptyVariables()
{
  if (_vars.size()==0) return;
  CLASS_MESSAGE((boost::format("  in %1% ") % GetName()).str().c_str());
  std::vector<BasicVariable::ptr>::iterator Iter;
  //std::cout << "_vars.size() = " << _vars.size() << std::endl;
  Iter  = _vars.begin();
  while ( Iter != _vars.end())
  {
    Iter = _vars.erase(Iter);
  }
  //std::cout << "done" << std::endl;

} // Variables::EmptyVariables()

