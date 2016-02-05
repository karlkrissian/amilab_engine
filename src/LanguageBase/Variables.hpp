
#ifndef _AMI_VARIABLES_H
#define _AMI_VARIABLES_H

// TODO: change and use STL ... !!!
//#define MAX_VARS     500

#include <list>
#include "BasicVariable.h"
#include "Variable.hpp"
#include "DefineClass.hpp"
#include "ami_format.h"
#include "Variable.hpp"
#include <vector>
#include <boost/shared_ptr.hpp>

#include "LanguageBaseConfigure.h"

/**
 * Variables for each context.
 **/
class LanguageBase_EXPORT Variables{

  DEFINE_CLASS(Variables);

 protected:
  std::vector<BasicVariable::ptr> _vars;
  std::string                     _context_name;
  bool                            _global_new;

  /// Default contexts to look for if the variable
  /// is not found in this context
  std::list<Variables::ptr>     _defaults;

 public:

  Variables() {
    _context_name = "unamed context";
    _global_new = false;
  }

  virtual ~Variables();

  BasicVariable::ptr operator [](int i)
  {
    if ((i>=0)&&(i<(int)GetSize()))
      return _vars[i];
    return BasicVariable::ptr();
  }

  //--------------------------------------------
  void AddDefault( Variables::ptr& defcontext )
  {
    _defaults.push_back(defcontext);
  }

  //--------------------------------------------
  void RemoveDefault( Variables::ptr& defcontext )
  {
    _defaults.remove(defcontext);
  }

  /**
   * @brief Adding as default the context of an AMIObject variable
   *
   * @param defvarcontext : variable of type AMIObject 
   * @return void
   **/
  void AddDefault( BasicVariable::ptr& defvarcontext );

  /**
   * @brief Removing from default the context of an AMIObject variable
   *
   * @param defvarcontext : variable of type AMIObject
   * @return void
   **/
  void RemoveDefault( BasicVariable::ptr& defvarcontext );

  //--------------------------------------------
  size_t GetSize()
  {
    return _vars.size();
  }

  
  std::string GetName() const { return _context_name; }
  void SetName( const std::string& name ) { _context_name = name; }

  bool GetGlobalNew() const { return _global_new; }
  void SetGlobalNew( const bool& gn ) { _global_new = gn; }

  std::string CheckVarName(const char* name);

  /**
   *  Add a new variable based on its type, name, pointer to the object information, and context.
   * @param name 
   * @param val 
   * @param context 
   * @return a smart pointer to the new variable (base class)
   */
  BasicVariable::ptr AddVar( const std::string& name, 
                             BasicVariable::ptr& val, 
                             const boost::shared_ptr<Variables>& context = boost::shared_ptr<Variables>() );

  
  /**
   *  Add a new variable based on its type, name, pointer to the object information, and context.
   * @param name 
   * @param val 
   * @param context 
   * @return a smart pointer to the new variable (base class)
   */
  BasicVariable::ptr AddVar( const std::string& name, 
                             BasicVariable* val, 
                             const boost::shared_ptr<Variables>& context = boost::shared_ptr<Variables>() );
  /**
   *  Add a new variable based on its type, name, pointer to the object information, and context.
   * @param type 
   * @param name 
   * @param val 
   * @param context 
   * @return a smart pointer to the new variable (base class)
   */
  template <class T>
  boost::shared_ptr<Variable<T> > AddVar(
        const std::string& name,
        boost::shared_ptr<Variable<T> >& val,
        const boost::shared_ptr<Variables>& context = boost::shared_ptr<Variables>() )
{
  {
    ami::format f(" %1%, in %2% ");
    CLASS_MESSAGE((f % name.c_str() % GetName().c_str()).GetString());
  }

  std::string resname = this->CheckVarName(name.c_str());
  boost::shared_ptr<Variable<T> > newvar(new Variable<T>(name,val->Pointer()));
  //std::cout << "  **  newvar =  " << newvar << std::endl;

  newvar->Rename(resname.c_str());
  newvar->SetContext(context);
  _vars.push_back(newvar);

  return newvar;
}

  template <class T>
  /**
   * Adds a variable of type T to the context, based on its name, a smart pointer to its value, and an optional context.
   * @param name 
   * @param val 
   * @param context 
   * @return smart pointer to the new variable.
   */
  boost::shared_ptr<Variable<T> > AddVar(
        const std::string& name,
        boost::shared_ptr<T >& val,
        const boost::shared_ptr<Variables>& context = boost::shared_ptr<Variables>() )
  {
/*    CLASS_MESSAGE(boost::format(" %1%, in %2% ") % name % GetName());*/
  
    std::string resname = this->CheckVarName(name.c_str());
    boost::shared_ptr<Variable<T> > newvar(new Variable<T>(name,val));
    //std::cout << "  **  newvar =  " << newvar << std::endl;
  
    newvar->Rename(resname.c_str());
    newvar->SetContext(context);
    _vars.push_back(newvar);
  
    return newvar;
  }

  /**
   *  Adds a new variable to the context based on a smart pointer to a variable
   * @param var 
   * @param context 
   * @return 
   */
  BasicVariable::ptr AddVar(BasicVariable::ptr& var, const Variables::ptr& context = Variables::ptr());

  /**
   *  Adds a new variable to the context based on a smart pointer to a variable
   * @param var 
   * @param context 
   * @return 
   */
//  BasicVariable::ptr AddVar(const BasicVariable::ptr& var, Variables::ptr context = Variables::ptr());

  bool ExistVar(const char* varname);

  bool ExistVar(BasicVariable::ptr& var);

  bool ExistVar(BasicVariable* var);

  void SearchCompletions( const std::string& varname, 
                          boost::shared_ptr<std::vector<std::string> >& completions);

  /**
   *  Search all variable of a given type within the object,
   *  and preprend the given string to the result.
   * @param type 
   * @param varlist 
   * @param preprend
   */
  void SearchVariables( const vartype& type,
                          boost::shared_ptr<std::vector<std::string> >& varlist,
                        const std::string& preprend = "");

  /**
   * Find a variable based on its name.
   * @param varname variable name
   * @return a smart pointer to the variable if found or an empty smart pointer otherwise
   */
  BasicVariable::ptr GetVar(const char* varname);

//  unsigned char GetVar(const char* varname, int* i);

  bool deleteVar(const char* varname);

  int deleteVars(const std::string& varmatch);

//  unsigned char deleteVar(int i);

  void EmptyVariables();

  void display();

};



/*
#include "Variable.hpp"
template <class T>
boost::shared_ptr<Variable<T> > Variables::AddVar(
      const std::string& name,
      boost::shared_ptr<Variable<T> >& val,
      boost::shared_ptr<Variables> context )
{
  CLASS_MESSAGE(boost::format(" %1%, in %2% ") % name % GetName());

  string resname = this->CheckVarName(name.c_str());
  boost::shared_ptr<Variable<T> > newvar(new Variable<T>(name,val->Pointer()));
  //std::cout << "  **  newvar =  " << newvar << std::endl;

  newvar->Rename(resname.c_str());
  newvar->SetContext(context);
  _vars.push_back(newvar);

  return newvar;
}
*/

// extern template
// boost::shared_ptr<Variable<AMIObject> > Variables::AddVar(
//         const std::string& name,
//         boost::shared_ptr<AMIObject >& val,
//         boost::shared_ptr<Variables> context = boost::shared_ptr<Variables>() );



#endif
