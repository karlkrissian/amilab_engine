#pragma once
#ifndef _DriverBase_h_
#define _DriverBase_h_

#include "LanguageBaseConfigure.h"
#include "DefineClass.hpp"
#include "BasicVariable.h"
#include "ami_function.h"
#include "paramlist.h"


LanguageBase_EXPORT void CB_delete_variable( void* var);
LanguageBase_EXPORT void CB_delete_varlist( void* var);

/**
  This class contains the main functionalities of Driver that we want to use from outside
  without including driver.h and all its dependencies.
*/
class LanguageBase_EXPORT DriverBase
{

  DEFINE_CLASS(DriverBase);

protected:
    /** 
     * Check if the current command is from the command line.
     * Kept for transition from C flex-bison code should be removed later
     **/
    bool in_console;

public:
  DriverBase(void);
  ~DriverBase(void);

  /** Write error message and information.
    Including current file, line number, last text parsed.
  */
  virtual void yyiperror(const char *s) {}

  virtual void res_print(const char* st) {}
  virtual void res_print(const std::string& st) {}

    /** Print error message to the output 
    which can be a message dialog.
  */
  virtual int  err_print(const char* st) { return 0;}

  /** Print error message to the output 
    which can be a message dialog.
  */
  virtual int  err_print(const std::string& st) { return 0;}

  /**
  * @brief write a command to the command history file.
  *
  * @param st ...
  * @return void
  **/
  virtual void ws_print(const char* st) { return; }

  /**
  * @brief write a command to the command history file.
  *
  * @param st ...
  * @return void
  **/
  virtual void ws_print(const std::string& st) { return; }

    /** Returns true if the current command is run from the console.
  */
  virtual bool InConsole() { return in_console; }

  virtual BasicVariable::ptr yyip_call_function( AMIFunction* v, 
    const ParamList::ptr& param = ParamList::ptr() ) { return BasicVariable::ptr(); }

  /** Invoke the scanner and parser on an input command line string
    * @param input input string
    * @param sname stream name for error messages
    * @return    true if successfully parsed
    */
  virtual bool parse_commandline(const std::string& input,
          const std::string& sname = "string stream") { return true; }
};

#endif //  _DriverBase_h_
