/** 
 * \file VarContexts.hpp
 * \author Karl Krissian
 * Create several contexts for variables: 
 * allow local variables in functions for example
 * later will be used for object oriented programming
 */

 
#ifndef _AMI_VARCONTEXTS_HPP
#define _AMI_VARCONTEXTS_HPP

#include <stack>
#include <map>
#include "Variables.hpp"
#include "IdentifierInfo.h"

#include "DefineClass.hpp"
#include "ami_format.h"
#include "LanguageBaseConfigure.h"

#define NEWVAR_CONTEXT -1
#define OBJECT_CONTEXT_NUMBER -10

/** VarContexts
 *  is a stack of contexts, 
 *  where each context contains a set of variables
 **/
class LanguageBase_EXPORT VarContexts {

  DEFINE_CLASS(VarContexts);

private:
  /// _current_context is the number of contexts used
  int        _current_context;
 
  /// A context is an array of variables
  std::vector<Variables::ptr> _context;

  /// built-in context for variable accessible everywhere
  Variables::ptr _builtin_context;

  /// points to the current object context
  Variables::ptr _object_context;
  
  /// map types with the variable containing their constructors
  std::map<std::string,BasicVariable::wptr> classes_map;

public:

  /// Constructor
  VarContexts();

  /// Destructor
  virtual ~VarContexts();

  /// mapping class names with their contexts for typedef wrapping
  void AddClassMap(std::string classname, BasicVariable::wptr classvar);

  /// find the variable that contains a class constructor
  BasicVariable::wptr GetClassVar(std::string classname);

  /// print the list of classes to standard ouput
  void ListClassMap();
  
  /// Remove all the variables
  void EmptyVariables();

  /// Creates a new context of variables
  int GetNewVarContext();

  /// Sets the current object context
  void SetObjectContext(const Variables::ptr& ocontext)
  {
    _object_context = ocontext;
  }

  /**
   * @return a reference to the current object context
   */
  Variables::ptr& GetObjectContext() 
  { 
    return _object_context;
  }

  /**
   * @return The builtin context
   */
  Variables::ptr& GetBuiltinContext() 
  { 
    return _builtin_context;
  }

  /**
   * @return The global context
   */
  Variables::ptr& GetGlobalContext() 
  { 
    return _context[0];
  }

  /**
   * Activate/Desactivate the creation of new variables as global
   * @param gn 
   */
  void SetGlobalNew(bool gn)  {  _context[_current_context]->SetGlobalNew(gn);}

  /**
   * @return the current context number
   */
  int GetCurrentContextNumber() {
    return _current_context;
  }

  /**
   * Sets the current context number
   * @param  
   */
  void SetCurrentContextNumber( int context) {
    if ((context>=0)&&(context<(int)_context.size()))
      _current_context = context;
  }
  
  /**
   * 
   */
  void SetGlobalContext();
  void SetLastContext();

  Variables::ptr GetCurrentContext() {
    return _context[_current_context];
  }

  /**
   * Creates a new context
   * @param name of the new context
   * @return smart pointer to the new context
   */
  Variables::ptr NewContext(const char* name);

  bool DeleteLastContext();

  void display();

  bool ExistVar(const char* varname);

  boost::shared_ptr<std::vector<std::string> > SearchCompletions(const std::string& varname);

  /**
   * \brief Search all variables of a given type.
   * \param type variable type
   * \param recursive recursively go through all the objects of the context
   * \return shared pointer of the array of resulting strings
   */
  boost::shared_ptr<std::vector<std::string> > SearchVariables(const vartype type, bool recursive=false);

  void SearchVariablesRecursive( const vartype& type,
                        boost::shared_ptr<std::vector<std::string> >& variables,
                        const Variables::ptr& context,
                        std::string const & prefix,
                        int rec_level=0
                               ) const;

  /**
   * \brief Search all AMIObject variables of a given type.
   * \param type variable type
   * \return shared pointer of the array of resulting strings
   */
  boost::shared_ptr<std::vector<std::string> > SearchAMIObjectTypeVariables(const std::string & type);
                        
  void SearchAMIObjectTypeVariablesRecursive( const std::string & type_string,
                        boost::shared_ptr<std::vector<std::string> >& variables,
                        const Variables::ptr& context,
                        std::string const & prefix,
                        int rec_level=0
                                            ) const;

  /**
  * 
  * @param type variable type
  * @param name variable name
  * @param val is a pointer to the variable type
  * @param context NEWVAR_CONTEXT (-1) means the current context | OBJECT_CONTEXT_NUMBER (-10) 
  * @return 
  */
  template <class T>
  boost::shared_ptr<Variable<T> > AddVar(const char* name, 
                                         boost::shared_ptr<Variable<T> >& val, 
                                         int context=NEWVAR_CONTEXT)
#ifdef __GCCXML__
    ;
#else
  {
      if (context==OBJECT_CONTEXT_NUMBER) {
        if (_object_context.get()) {
          ami::format f("adding object of type %1%, name %2% into object context ");
          CLASS_MESSAGE(( f
                          % val->GetTypeName().c_str()
                          % name).GetString());
          return _object_context->AddVar<T>(name,val, _object_context);
      }
      else {
        CLASS_ERROR("Calling object variable without any object context");
        return boost::shared_ptr<Variable<T> >();
      }
    }
  
    if (context==NEWVAR_CONTEXT) context = GetNewVarContext();
    return _context[context]->AddVar<T>(name,val,_context[context]);
  }
#endif

  ///
  template <class T>
  boost::shared_ptr<Variable<T> > AddVar(const std::string& name, boost::shared_ptr<T>& val, int context=NEWVAR_CONTEXT)
#ifdef __GCCXML__
    ;
#else
  {
      if (context==OBJECT_CONTEXT_NUMBER) {
        if (_object_context.get()) {
          ami::format f("adding object name %1% into object context ");
          CLASS_MESSAGE( (f % name.c_str()).GetString());
          boost::shared_ptr<Variable<T> > newvar ( 
            new Variable<T>(name,val));
          return _object_context->AddVar<T>(name,newvar, _object_context);
      }
      else {
        CLASS_ERROR("Calling object variable without any object context");
        return boost::shared_ptr<Variable<T> >();
      }
    }
  
    if (context==NEWVAR_CONTEXT) context = GetNewVarContext();
    //boost::shared_ptr<Variable<T> > newvar( new Variable<T>(name,val));
    return _context[context]->AddVar<T>(name,val,_context[context]);
  }
#endif


  BasicVariable::ptr AddVar(const char* name, BasicVariable::ptr& val, int context=NEWVAR_CONTEXT)
#ifdef __GCCXML__
    ;
#else
  {
      if (context==OBJECT_CONTEXT_NUMBER) {
        if (_object_context.get()) {
          ami::format f("adding object of type %1%, name %2% into object context ");
          CLASS_MESSAGE((f % val->GetTypeName().c_str() 
                           % name).GetString());
          return _object_context->AddVar(name,val, _object_context);
      }
      else {
        CLASS_ERROR("Calling object variable without any object context");
        return BasicVariable::ptr();
      }
    }
  
    if (context==NEWVAR_CONTEXT) context = GetNewVarContext();
    return _context[context]->AddVar(name,val,_context[context]);
  }
#endif

  /**
   * Adds a new variable based on a smart pointer to a variable and a context id.
   * @param var 
   * @param context 
   * @return smart pointer to the resulting variable
   */
  BasicVariable::ptr AddVar(BasicVariable::ptr var, int context=NEWVAR_CONTEXT);

  template <class T>
  boost::shared_ptr<Variable<T> > AddVar(  
                const IdentifierInfo::ptr& info, 
                boost::shared_ptr<Variable<T> >& val);

  template <class T>
  boost::shared_ptr<Variable<T> > AddVar(  
                const IdentifierInfo::ptr& info, 
                boost::shared_ptr<T >& val);

  BasicVariable::ptr AddVar(  
              const IdentifierInfo::ptr& info, 
              BasicVariable::ptr& val);

  /**
   * Find a variable based on its name, if context is -1, look for variable in the local context
   * @param varname name of the variable
   * @param context possible values: -1, 0--contexts, OBJECT_CONTEXT_NUMBER
   * @return resulting smart pointer to the variable if any
   */
  BasicVariable::ptr GetVar( const char* varname, int context=NEWVAR_CONTEXT);

  bool deleteVar(const char* varname);

  int deleteVars(const std::string& varmatch);

  int GetContext(BasicVariable::ptr var);

//  template <class T>
//  int GetContext(boost::shared_ptr<Variable<T> >& var);

  bool deleteVar(BasicVariable::ptr var);
  bool deleteVar(BasicVariable* var);

  template <class T>
  bool deleteVar(boost::shared_ptr<Variable<T> >& var);
};

// no need to include .tpp when parsing with gccxml
#ifndef __GCCXML__
  #include "VarContexts.tpp"
#endif

#endif //_AMI_VARCONTEXTS_HPP
