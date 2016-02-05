/*
    ==================================================
    Software : AMILab
    Authors  : Karl Krissian
    Email    : krissian@dis.ulpgc.es

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
#pragma once
#ifndef _ami_object_h_
#define _ami_object_h_

#include <string>
#include <boost/shared_ptr.hpp>
#include "BasicVariable.h"

//#include "Variables.hpp"
class Variables;
BasicVariable::ptr Variables_AddVar(  boost::shared_ptr<Variables>& vars,
                                       const std::string& name, 
                                       BasicVariable* val, 
                                       const boost::shared_ptr<Variables>& context = boost::shared_ptr<Variables>() );

BasicVariable::ptr Variables_AddVar(  boost::shared_ptr<Variables>& vars,
                                       const std::string& name, 
                                       BasicVariable::ptr& val, 
                                       const boost::shared_ptr<Variables>& context = boost::shared_ptr<Variables>() );

BasicVariable::ptr Variables_AddVar(  boost::shared_ptr<Variables>& vars,
                                       BasicVariable::ptr& val, 
                                       const boost::shared_ptr<Variables>& context = boost::shared_ptr<Variables>() );

void               Variables_AddDefault(  boost::shared_ptr<Variables>& vars,
                                          boost::shared_ptr<Variables>& defcontext );

#include "DefineClass.hpp"
#include "AmiInstructionBlock.h"
#include "ami_class.h"

// forward declaration of WrapClassBase
class  WrapClassBase;

#include "LanguageBaseConfigure.h"

/**
  The class AMIObject can be created either with or without a link to a class object.
  If a class object is present, it will create a context of variables by running the code
  present in the class object, otherwise it can be considered as a namespace.
*/
class LanguageBase_EXPORT AMIObject {

  DEFINE_CLASS(AMIObject);

private:

  /// Smart pointer to the corresponding class if any
  AMIClass::ptr   _class;

  /// Pointer to the class allowing C++ object wrapping
  boost::shared_ptr<WrapClassBase> _wrapped_object;

  // why should object have a name, while a variable has one
/*
  /// Object name
  std::string     _name;
*/

  // Set the constructor variable
  BasicVariable::ptr _constructor_var;

  // What happens with references here???
  /// Pointer to the language variable containing the object
  BasicVariable::ptr _var;

  /// Own list of variables
  boost::shared_ptr<Variables>  _vars;

 public:

  /**
   * Constructor: creates a smart pointer to the list of variables
   */
  AMIObject();
//     {
//      // _name     = "";
//       _vars     = boost::shared_ptr<Variables>(new Variables);
//     }

  /**
   * Destructor : empties the list of variables
   */
  virtual ~AMIObject() ;

  /**
   * Associates the class to the object
   * @param amiclass 
   */
  void SetClass(AMIClass::ptr& amiclass);
/*  {
    if (amiclass.get()!=NULL)
      std::cout  << "will run the code of the class "
            << amiclass->GetName()
            << " for the object " 
            << GetName()
            << std::endl;
    _class = amiclass;
  }
*/

  /**
   * Gets a smart pointer to the associated class if any
   * @return 
   */
  AMIClass::ptr& GetClass() { return _class;}


  /**
   * Associates the wrapped object 
   * @param amiclass 
   */
  void SetWrappedObject(boost::shared_ptr<WrapClassBase> wo)
  {
    _wrapped_object = boost::shared_ptr<WrapClassBase>(wo);
  }

  /**
   * Returns a smart pointer to the wrapped object
   * @return 
   */
  boost::shared_ptr<WrapClassBase> GetWrappedObject()
  {
    return _wrapped_object;
  }

  /**
   * Sets the object name
   * @param fname 
   */
  void SetName( const std::string& fname);

  const BasicVariable::ptr& GetConstructorVar() const 
  { 
    return _constructor_var;
  }

  void SetConstructorVar( const BasicVariable::ptr& cvar) 
  { 
    _constructor_var = cvar;
  }

  /**
   * Gets the object name
   * @return object name
   */
  const std::string GetName() const;
//   { 
//     return _vars->GetName();
//   }

  /**
   * Gets the list of variables 
   * @return object context (contains its variables)
   */
  boost::shared_ptr<Variables>& GetContext() { return _vars;}

}; // AMIObject


#endif // _ami_object_h_

