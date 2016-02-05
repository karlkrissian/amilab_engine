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


//--------------------------------------------------
//template <class T>
//int VarContexts::GetContext(boost::shared_ptr<Variable<T> >& var)
//{
//  return GetContext(boost::static_pointer_cast<BasicVariable>(var));
//}


//--------------------------------------------------
template <class T>
bool VarContexts::deleteVar(boost::shared_ptr<Variable<T> >& var)
{
  return deleteVar(boost::static_pointer_cast<BasicVariable>(var));
}


//--------------------------------------------------
template <class T>
boost::shared_ptr<Variable<T> > VarContexts::AddVar(  
              const IdentifierInfo::ptr& info, 
              boost::shared_ptr<Variable<T> >& val)
{
  int context;
  context = info->GetCreationContext();

  return AddVar<T>(info->GetName().c_str(),val,context);

} // AddVar()

//--------------------------------------------------
template <class T>
boost::shared_ptr<Variable<T> > VarContexts::AddVar(  
              const IdentifierInfo::ptr& info, 
              boost::shared_ptr<T >& val)
{
  int context;
  context = info->GetCreationContext();

  boost::shared_ptr<Variable<T> > newvar(new Variable<T>(info->GetName(),val));

  return AddVar<T>(info->GetName().c_str(),newvar,context);

} // AddVar()

