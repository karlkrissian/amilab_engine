//
// C++ Interface: ParamList
//
// Description: 
//
//
// Author: Karl Krissian <>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#pragma once
#ifndef PARAMLIST_H
#define PARAMLIST_H


#define MAX_PARAM 20

//#include "inrimage.hpp"
#include "DefineClass.hpp"
#include "AMILabEngineConfig.h"

#include "BasicVariable.h"
#include "amilab_messages.h"
//#include "Variable.hpp"

#include "CommonConfigure.h"
COMMON_VAR_IMPORT unsigned char GB_debug;


#include <string>
#include <vector>

#ifndef __APPLE__
//  extern template class __declspec(dllimport) std::vector<BasicVariable::ptr>;
#endif // __APPLE__


/**
 * Stores a list of parameters from the scripting language
 **/
#include "LanguageBaseConfigure.h"

class LanguageBase_EXPORT ParamList {

  DEFINE_CLASS(ParamList);

private:
  
  // use here a std::list of Variable, no need to care of the order the variables are deleted since they don't have inter-dependance
  std::vector<BasicVariable::ptr>     params;

  // reference to the variable: should not be deleted
  // not needed because of smart pointers ...
  // unsigned char reference[MAX_PARAM];

 public:


  /**
   * Constructor
   */
  ParamList();

//  ~ParamList();


  /**
   * 
   * @return the number of parameters
   */
  int GetNumParam();

  /**
   * 
   * @param i 
   * @return the type of the parameter i
   */
  vartype GetType( int i);

  bool AddParam( const BasicVariable::ptr& var);

  // cannot use & because may return a empty pointer, should have a static pointer to empty variable at hand
  BasicVariable::ptr GetParam(int i);

};


/**  Declaration of the parameters list
 **/
class ParamListDecl {

  int         num_param;
  std::string name[MAX_PARAM];
  vartype     type[MAX_PARAM];

 public:
  ParamListDecl();

  ~ParamListDecl();

  int GetNumParam();

  vartype GetType( int i);

  char* GetName( int i);

  unsigned char AddParam( const std::string& st, vartype t);

  unsigned char GetParam( int num, std::string& st, vartype& t, bool needed);

  bool CheckParam( ParamList* pl);

}; // class ParamListDecl

#endif
