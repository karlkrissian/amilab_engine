/*

    IMAGE PROCESSING LANGUAGE

    Karl Krissian
    ULPGC 
    06 02 2001
 */


%{
 /*** C/C++ Declarations ***/
  //#include <stdlib.h>
  //#include <stdio.h>


// use NOMINMAX to avoid conflicts between windows.h min,max and std::min std::max ...
#ifndef NOMINMAX
  #define NOMINMAX
#endif

#include <iomanip>
#include <cassert>
#include "boost/format.hpp"

#ifndef WIN32
#include <unistd.h>
#endif

#include <iostream>
#include <locale.h>
#include <cstdlib>

#include "VarContexts.hpp"
#include "VarArray.h"
//#include "Duree.hpp"

#include "DefineClass.hpp"
#include <boost/shared_array.hpp>

#include "Variable.hpp"

//typedef std::vector<BasicVariable::ptr> VarVector;

//#include "wrap_varvector.h"

//-------
#include "driver.h"
#include "ami_function.h"
#include "ami_class.h"
#include "ami_object.h"
#include "IdentifierInfo.h"

//#include "amiengine_bison.tab.hpp"
#include "wrapfunction_class.h"

#ifndef __FLEX_LEXER_H
#define yyFlexLexer yyipFlexLexer
#include "FlexLexer.h"
#undef yyFlexLexer
#endif

#include "StringUtils.hpp"

#include "LanguageBaseConfigure.h"
LanguageBase_VAR_IMPORT VarContexts  Vars;
LanguageBase_VAR_IMPORT void CB_delete_variable( void* var);
LanguageBase_VAR_IMPORT void CB_delete_varlist( void* var);

#include "amilab_global_import.h"

#include "language_global_import.h"

#include "CommonConfigure.h"
COMMON_VAR_IMPORT unsigned char GB_debug;
COMMON_VAR_IMPORT unsigned char GB_verbose;
COMMON_VAR_IMPORT unsigned char GB_nofile;

// Declare std::string type
typedef std::string std_string;
#ifndef std_string_declared
  #define std_string_declared
  AMI_DECLARE_TYPE(std_string);
#endif

//#include "Wrapping/WrapCommon/Generated/wrap_std_string.h"

extern char program[80];

// //-------------------------------------------------------
// class wxWaitTimer : public wxTimer
// //    -----------
// {
//   public:
//     bool finished;
// 
//     wxWaitTimer() : finished(false) {}
//     //Called each time the timer's timeout expires
//     void Notify()     { finished = true; }
// };
// 
// 
// 
// //------------------------------------------------------
// class wxScheduleTimer : public wxTimer
// //    ---------------
// {
//   DEFINE_CLASS(wxScheduleTimer)
//   public:
//     wxScheduleTimer( Variable<AMIFunction>::ptr callback)
//     {
//       var = Variable<AMIFunction>::ptr(callback);
//     }
// 
//     ~wxScheduleTimer()
//     { 
//       //cout << "~wxScheduleTimer()" << std::endl; 
//     }
// 
//     //Called each time the timer's timeout expires
//     void Notify();
// 
//   private:
//     // variable of type type_ami_function
//     Variable<AMIFunction>::ptr var;
// };

// // create a array of shared pointers
// // to delete the wxScheduleTimer when necessary
// static std::list<wxScheduleTimer::ptr> schedule_timers;


#define GET_VARSTACK_VALUE(type,newvar) \
  boost::shared_ptr<type> newvar;\
  {\
    BasicVariable::ptr __v = driver.var_stack.GetLastBasicVar();\
    newvar = AMILabType<type>::GetValue(__v,0); \
    if (!newvar.get()) \
        std::cerr << "failed to get variable from stack " << std::endl; \
  }

/*! \def GET_VARSTACK_OBJECT
    \brief Gets the smart pointer to the wrapped object  (of type WrapClass_type) included in an AMIObject variable, taken from the stack of variables.
*/
#define GET_VARSTACK_OBJECT(type, obj) \
  boost::shared_ptr<type > obj; \
  {\
    Variable<AMIObject>::ptr objvar( \
      driver.var_stack.GetLastVar<AMIObject>()); \
    if (!objvar.get()) {  \
      driver.yyiperror(" Expecting an AMIObject variable."); \
      YYABORT; \
    } \
    WrapClassBase::ptr wrap_base( objvar->Pointer()->GetWrappedObject()); \
    WrapClass_##type::ptr wobj( boost::dynamic_pointer_cast<WrapClass_##type>(wrap_base));\
    if (!wobj.get()) {  \
      driver.yyiperror((boost::format(" Expecting an AMIObject variable of type %1%.")%(#type)).str().c_str()); \
      YYABORT; \
    } \
    obj = wobj->GetObj(); \
  }


/*! \def GET_VARSTACK_VAR_OBJECT
    \brief Gets the smart pointer to the wrapped object  (of type WrapClass_type) included in an AMIObject variable, taken from the stack of variables, and also the smart pointer to the variable.
*/
#define GET_VARSTACK_VAR_OBJECT(type, varname, obj) \
  Variable<AMIObject>::ptr varname( \
    driver.var_stack.GetLastVar<AMIObject>()); \
  if (!varname.get()) {  \
    driver.yyiperror(" Expecting an AMIObject variable."); \
    YYABORT; \
  } \
  WrapClass_##type::ptr wobj;\
  {\
    WrapClassBase::ptr wrap_base( varname->Pointer()->GetWrappedObject()); \
    wobj =  boost::dynamic_pointer_cast \
                <WrapClass_##type>(wrap_base);\
    if (!wobj.get()) {  \
      driver.yyiperror((boost::format(" Expecting an AMIObject variable of type %1%.")%(#type)).str().c_str()); \
      YYABORT; \
    } \
  } \
  boost::shared_ptr<type> obj(wobj->_obj);

/*! \def GET_VARSTACK_OBJECT2
    \brief Gets the smart pointer to the wrapped object  (of type WrapClass_type) included in an AMIObject variable, taken from the stack of variables. 
    Version where the wrapped typename is different from the type.
*/
#define GET_VARSTACK_OBJECT2(wtype, type, obj) \
  Variable<AMIObject>::ptr objvar( \
    driver.var_stack.GetLastVar<AMIObject>()); \
  if (!objvar.get()) {  \
    driver.yyiperror(" Expecting an AMIObject variable."); \
    YYABORT; \
  } \
  WrapClass_##wtype::ptr wobj; \
  { \
    WrapClassBase::ptr wrap_base( objvar->Pointer()->GetWrappedObject()); \
    wobj =  boost::dynamic_pointer_cast<WrapClass_##wtype>(wrap_base);\
    if (!wobj.get()) {  \
      driver.yyiperror((boost::format(" Expecting an AMIObject variable of type %1%.")%(#type)).str().c_str()); \
      YYABORT; \
    } \
  } \
  boost::shared_ptr<type > obj(wobj->_obj);

#define GET_VARSTACK_VAR_VAL(type,newvar, newval) \
  Variable<type>::ptr newvar(driver.var_stack.GetLastVar<type>()); \
  boost::shared_ptr<type> newval(newvar->Pointer());

#define ADD_VARSTACK_FLOAT(newval) \
    Variable<float>::ptr new_var(new Variable<float>(float_ptr(new float(newval)))); \
    driver.var_stack.AddVar(new_var);

/*! \def CHECK_VAR
    \brief Checks if the smart pointer really points to a variable, if not abort the current parsing
*/
#define CHECK_VAR(var) \
  if (!var.get()) {  \
    driver.yyiperror(" Empty variable in expression "); \
    YYABORT; }

/*! \def GET_CHECK_VARSTACK
    \brief Gets the last variable from the stack and 
        checks if the smart pointer really points to a variable, if not abort the current parsing
*/
#define GET_CHECK_VARSTACK(varname) \
  BasicVariable::ptr varname(driver.var_stack.GetLastBasicVar()); \
  if (!varname.get()) {  \
    driver.yyiperror(" Empty variable in expression "); \
    YYABORT; }

/**
  newval is a smart pointer to the new value to add
**/
#define ADD_VARSTACK_PTR(type,newval) \
    Variable<type>::ptr new_var(new Variable<type>(newval)); \
    driver.var_stack.AddVar(new_var);

/**
  newval is a pointer to the new value to add
**/
#define ADD_VARSTACK(type,newval) { \
    boost::shared_ptr<type> newval_ptr(newval); \
    Variable<type>::ptr new_var(new Variable<type>(newval_ptr)); \
    driver.var_stack.AddVar(new_var); }

#define UNARYOP_EXPR(operator,val,res)           \
  res=operator(val);




%}

/* write out a header file containing the token defines */
%defines

/* start symbol is named "start" */
%start start

/* use newer C++ skeleton file */
%skeleton "lalr1.cc"

/* namespace to enclose parser in */
%name-prefix="yyip"



/* set the parser's class identifier */
%define "parser_class_name" "Parser"

/* keep track of the current position within the input */
%locations

%initial-action
{
    // initialize the initial location object
    @$.begin.filename = @$.end.filename = &driver.streamname;
};

/* The driver is passed by reference to the parser and to the scanner. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class Driver& driver }

/* verbose error messages */
%error-verbose


%union {
  IdentifierInfo*         ident;
  char*                   astring;
  AmiInstructionBlock*    ablock;
  float                   afloat;
  double                  adouble;
  int                     aint;
  ParamList*              paramlist; // here smart pointer
                            // not allowed in union ...
  ParamListDecl*              paramlistdecl;
  std::list<std::string>*     string_list;
  std::vector<AMIClass::ptr>* class_list;
}

%token LEX_ERROR

%token      END      0  "end of file"

%token T_EXP
%token T_GT
%token T_LT
%token T_MULT
%token T_DIV
%token T_NOT
%token T_ADD
%token T_SUB
%token T_MOD

%token T_OP_PAR
%token T_CL_PAR
%token T_OP_BR
%token T_CL_BR

%token T_AND
%token T_OR

%token T_COMMA
%token T_QUEST
%token T_COLON

%token T_SEMICOLON


%token T_SetDebugOn
%token T_SetDebugOff
%token T_TraceScanning
%token T_TraceParsing
%token T_NoMessageDialog
%token T_SetVerboseOn
%token T_SetVerboseOff

%token T_SetProgress
%token T_SetStatusText
%token T_GetScriptsDir

%token T_argc
%token T_emptyargs

%token END_INSTRUCTION

%token SHOW HELP QUIT T_HIDE
%token PRINT PRINTN
%token T_InfoDialog
%token T_boost_format
%token T_SPRINT
%token ASHELL LS

%token T_GetObjectName

%token ASTRING ABLOCK NUMBER
%token IDENTIFIER
%token POINT_IDENTIFIER
%token PROCESSED_VAR
%token VAR_STRING

%token VAR_C_FUNCTION
%token VAR_C_PROCEDURE
%token VAR_CLASS_MEMBER

%token VAR_AMI_FUNCTION
%token VAR_AMI_CLASS
%token VAR_AMI_OBJECT

%token T_del
%token T_delvars
%token T_Comments
%token ENDOP

%token T_global
%token T_local
%token T_global_new
%token T_local_new

%token T_wait
%token T_schedule

%token RIGHT_ASSIGN LEFT_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN
%token MOD_ASSIGN AND_ASSIGN XOR_ASSIGN
%token OR_ASSIGN RIGHT_OP LEFT_OP INC_OP
%token DEC_OP PTR_OP AND_OP OR_OP LE_OP
%token GE_OP EQ_OP NE_OP
%token TRANSPOSE_OP POINTWISE_MULT
%token ASSIGN_OP

%token T_MAX
%token T_argmax
%token T_MIN
%token T_MEDIAN

%token T_RestartTime
%token T_InitTime
%token T_TimeSpent
%token T_EndTime

%token T_info

%token T_ProcessEvents

%token T_CHAR T_UCHAR T_SHORT T_USHORT T_INT T_UINT
%token T_BOOL   // New (added: 19/11/2010)
%token T_LONG   // New (added: 27/05/2010)
%token T_ULONG
%token T_FLOAT T_DOUBLE
%token T_RGB  T_FLOAT_VECTOR
%token T_BasicType

%token T_atof

%token T_LineNumber
%token CONST_PI
%token SIN  COS  TAN
%token ASIN ACOS ATAN
%token SINH COSH
%token EXP LN LOG
%token SQRT ABS ROUND FLOOR
%token NORM

%token FOR TO STEP ENDFOR T_IN
%token T_REPEAT T_UNTIL
%token T_WHILE
%token T_BREAK
%token IF THEN ELSE

%token VARIABLES
%token FUNCTION
%token T_eval

%token T_exists
%token T_FileExists
%token T_slice

%token T_GenRead

%token T_NUM
%token T_STRING
%token T_OBJECT
%token T_VAR

%token T_PROC
%token T_Class T_public

// Operators precedence
%nonassoc SHIFT_THERE
%nonassoc T_OP_PAR
%right ASSIGN_OP ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN LEFT_ASSIGN
%nonassoc T_COLON
%left OR_OP
%left T_EXP
%left AND_OP
%left T_OR
%left T_AND
%left NE_OP EQ_OP
%left GE_OP LE_OP T_GT T_LT
//%left T_SUB T_ADD
%left T_MOD T_DIV T_MULT
%right prefix
//%nonassoc INC_OP DEC_OP TRANSPOSE_OP T_OP_BR T_ADD T_SUB T_QUEST T_POINT
%nonassoc INC_OP DEC_OP TRANSPOSE_OP T_OP_BR  T_QUEST POINT_IDENTIFIER
%nonassoc postfix

%type <ident>          identifier
%type <ident>          IDENTIFIER
%type <ident>          POINT_IDENTIFIER
%type <aint>           basic_type
%type <astring>        ASTRING
%type <astring>        primary_expr_string
%type <astring>        expr_string
%type <ablock>         ABLOCK
%type <ablock>         instr_block
%type <adouble>         expr
//%type <adouble>         shift_expr
//%type <adouble>         prefix_expr
%type <adouble>         NUMBER
%type <paramlist>      param_list
%type <paramlistdecl>  param_list_decl
%type <string_list>    exprstringlist
%type <class_list>     var_ami_class_list

%destructor { delete [] $$; } ASTRING primary_expr_string expr_string
%destructor { delete  $$; } identifier IDENTIFIER POINT_IDENTIFIER
%destructor { delete  $$; } instr_block
%destructor { delete  $$; } exprstringlist
%destructor { delete  $$; } var_ami_class_list



%{

#include "driver.h"
#include "scanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex

%}

%%

start : /* empty */
    | list_commands END;

list_commands
          :
         end_instr | list_commands end_instr |
         command end_instr
         | list_commands command end_instr
         | loop_inst   | list_commands loop_inst
         | cond_inst   | list_commands cond_inst
         | func_inst   | list_commands func_inst
         | proc_decl   | list_commands proc_decl;
         | class_decl  | list_commands class_decl;
         | object_decl | list_commands object_decl;

end_instr :
        END_INSTRUCTION
        | T_SEMICOLON
        ;


loop_inst :
    FOR identifier ASSIGN_OP expr TO expr
    instr_block end_instr
    {
      int  previous_lineno=driver.yyiplineno;
      int  previous_lineno_lastparser=driver.yyiplineno_lastparser;
      AmiInstructionBlock::ptr block($7);
      IdentifierInfo::ptr ident($2);

      int_ptr varint(new int);
      Vars.AddVar<int>(ident,varint);
      //bool goon=true;

      for(*varint = (int) $4; *varint <= (int) $6; (*varint)++)
        {
          driver.yyiplineno = block->GetStartingLine();
          //goon=
          driver.parse_block(block);
        }
      Vars.deleteVar(ident->GetName().c_str());
      driver.yyiplineno=previous_lineno;
      driver.yyiplineno_lastparser=previous_lineno_lastparser;
    }
    |
    FOR identifier ASSIGN_OP expr TO expr STEP expr
    instr_block end_instr
    {
      int  previous_lineno=driver.yyiplineno;
      int  previous_lineno_lastparser=driver.yyiplineno_lastparser;
      AmiInstructionBlock::ptr block($9);
      IdentifierInfo::ptr ident($2);

      float_ptr var(new float);
      Vars.AddVar<float>(ident,var);
      bool goon=true;

      for(*var = $4; goon&&(*var <= $6); (*var)+=$8)
      {
        driver.yyiplineno = block->GetStartingLine();
        //driver.yyiplineno=previous_lineno;
        goon=driver.parse_block(block);
      }
      Vars.deleteVar(ident->GetName().c_str());
      driver.yyiplineno=previous_lineno;
      driver.yyiplineno_lastparser=previous_lineno_lastparser;
    }
    |
    FOR identifier T_IN exprstringlist
      instr_block end_instr
    {
    /**
      Description: 
          Iteration through a list of strings.
    **/

      std::list<std::string>* sl = $4;

      int  previous_lineno=driver.yyiplineno;
      int  previous_lineno_lastparser=driver.yyiplineno_lastparser;
      AmiInstructionBlock::ptr block($5);
      IdentifierInfo::ptr ident($2);

      // create the variable
      string_ptr tmp(new std::string());
      BasicVariable::ptr newvar = AMILabType<std::string>::CreateVarFromSmtPtr(tmp);

      BasicVariable::ptr var = Vars.AddVar(ident,newvar);
      //cout << " *** Create temporary variable " << ident->GetName() << std::endl;

      std::list<std::string>::iterator sl_it;
      bool goon=true;
      
      for (sl_it=sl->begin(); goon&&(sl_it!=sl->end()); sl_it++) {

        // assign new value to the variable
        //string_ptr newval( new std::string(*sl_it));
        *tmp = (*sl_it);

        driver.yyiplineno = block->GetStartingLine();
        //driver.yyiplineno=previous_lineno;
        goon = driver.parse_block(block);

      }
      // should not delete based on the name !!!
      bool res = Vars.deleteVar(ident->GetName().c_str());
      //cout << " *** Delete temporary variable " << ident->GetName() << std::endl;
      if (!res) {
       std::cout << "**********" << std::endl;
       std::cout << "**** Could not delete variable in loop"  << ident->GetName() << std::endl;
       std::cout << "**********" << std::endl;
      }
      driver.yyiplineno=previous_lineno;
      driver.yyiplineno_lastparser=previous_lineno_lastparser;

      // forced to delete the pointer to the list here
      delete $4;

    }
    |
    T_REPEAT instr_block
    {
    /**
      Description:
        Repeats a block of instructions, and stop when an error is generated.
        Use the command 'break' to leave the loop
      See Also:
        break
     **/
        int  previous_lineno=driver.yyiplineno;
        int  previous_lineno_lastparser=driver.yyiplineno_lastparser;
        AmiInstructionBlock::ptr block($2);
        int res;
    
        do {
  
            //driver.yyiplineno=previous_lineno;
            driver.yyiplineno = block->GetStartingLine();
            res=driver.parse_block(block);
  
        } while (res);
        driver.yyiplineno = previous_lineno;
        driver.yyiplineno_lastparser=previous_lineno_lastparser;
      }
      |
      T_WHILE variable instr_block
      {
      /**
        Description:
          Repeats the block while the variable value is higher than 0.5
      **/
        int  previous_lineno=driver.yyiplineno;
        int  previous_lineno_lastparser=driver.yyiplineno_lastparser;
        AmiInstructionBlock::ptr block($3);
        BasicVariable::ptr  var(driver.var_stack.GetLastBasicVar());
  
        float res;
        bool goon=true;
        if (var->IsNumeric()) 
          res = var->GetValueAsDouble();
        else {
          res = 0;
          driver.yyiperror(" while needs a numerical variable as condition \n");
        }
        goon=(res!=0);
  
        while (goon) {
          //driver.yyiplineno=previous_lineno;
          driver.yyiplineno = block->GetStartingLine();
          res=driver.parse_block(block);
          goon=res;
          res = var->GetValueAsDouble();
          goon=goon&&(res!=0);
        } 
        driver.yyiplineno = previous_lineno;
        driver.yyiplineno_lastparser = previous_lineno_lastparser;
      }
      ;


cond_inst :
    IF expr   instr_block end_instr
    {
      int  previous_lineno;
      AmiInstructionBlock::ptr block($3);

      // Pb with line numbers
      previous_lineno=driver.yyiplineno;
      int  previous_lineno_lastparser = driver.yyiplineno_lastparser;

        if ($2>0.5)
        {
          //driver.yyiplineno=previous_lineno;
          if (!driver.parse_block(block)) YYABORT;
          driver.yyiplineno = previous_lineno;
          driver.yyiplineno_lastparser = previous_lineno_lastparser;
        }
    }
    | IF expr  instr_block ELSE instr_block  end_instr
    {

      AmiInstructionBlock::ptr block_if(  $3);
      AmiInstructionBlock::ptr block_else($5);

      // Pb with line numbers
      int  previous_lineno = driver.yyiplineno;
      int  previous_lineno_lastparser = driver.yyiplineno_lastparser;

      bool res;
      if ($2>0.5)
        res = driver.parse_block(block_if);
      else
        res = driver.parse_block(block_else);
      if (!res) YYABORT;
      driver.yyiplineno = previous_lineno;
      driver.yyiplineno_lastparser = previous_lineno_lastparser;

    };


proc_decl:
    /**
      Description:
        Declare a new function
     **/
    T_PROC  identifier
    {
      GB_driver.procedure_declaration = true;
    }
        T_OP_PAR param_list_decl T_CL_PAR
        instr_block end_instr
    {
      AmiInstructionBlock::ptr body($7);
      IdentifierInfo::ptr ident($2);

      AMIFunction::ptr amifunc(new AMIFunction);

      amifunc->SetName(ident->GetName().c_str());
      amifunc->SetFileName(driver.current_file);
      amifunc->SetParamList($5);
      amifunc->SetBody(     body);

      if (GB_debug)
       std::cout  << ident->GetName()
              << " body = "
              << body->GetBody()  << std::endl;

      BasicVariable::ptr newvar = Vars.AddVar<AMIFunction>( ident, amifunc);
      if (newvar.get())
        amifunc->SetContext(newvar->GetContext());

      // desactivate the flag procedure_declaration
      // which allows not to accept variables as identifiers
      GB_driver.procedure_declaration = false;
    } 
    |
    /**
      Description:
        Change the body of an existing function
     **/
    T_PROC  VAR_AMI_FUNCTION
    {
      // allow overriding current functions
      GB_driver.procedure_declaration = true;
    }
        T_OP_PAR param_list_decl T_CL_PAR
        instr_block end_instr
    {
      AmiInstructionBlock::ptr body($7);

      GET_VARSTACK_VAR_VAL(AMIFunction, var, func);

      // Why delete and recreate previous variable ???
      // delete previous variable
//      std::string varname = var->Name();
//      int context = Vars.GetContext(boost::static_pointer_cast<BasicVariable>(var));
//      Vars.deleteVar(var);

      FILE_MESSAGE((boost::format("Redefining procedure %1%") % var->Name()).str().c_str()); 

//      AMIFunction::ptr amifunc( new AMIFunction);
      AMIFunction::ptr amifunc(func);

//      amifunc->SetName(varname.c_str());
      amifunc->SetFileName(driver.current_file);
      amifunc->SetParamList($5);
      amifunc->SetBody(     body);
      FILE_MESSAGE((boost::format("%1%: body = %2%")
                    % var->Name()  % body->GetBody()).str().c_str());

      // add the variable in the same context ...
//      BasicVariable::ptr newvar =
//        Vars.AddVar<AMIFunction>(
//                      varname,
//                     amifunc,
//                      context);
//      if (newvar.get())
//        amifunc->SetContext(newvar->GetContext());

      // desactivate the flag procedure_declaration
      // which allows not to accept variables as identifiers
      GB_driver.procedure_declaration = false;
    };


class_decl:
    /**
      Description:
        Declare a new class
     **/
    T_Class  identifier
        instr_block end_instr
    {
      AmiInstructionBlock::ptr body($3);
      IdentifierInfo::ptr ident($2);

      AMIClass::ptr amiclass( new AMIClass);

      amiclass->SetName(ident->GetName());
      amiclass->SetFileName(driver.current_file);
      amiclass->SetBody(     body);
      if (GB_debug) printf("%s body = %s\n", ident->GetName().c_str(),body->GetBody().c_str());

      Vars.AddVar<AMIClass>(ident, amiclass);

    }
/*  Create many shift/reduce conflicts: to check ...
  |
    //
      Description:
        Change the body of existing class
    //
    T_Class VAR_AMI_CLASS
        instr_block end_instr
    {
      AmiInstructionBlock::ptr body($3);

      Variable<AMIClass>::ptr var(driver.var_stack.GetLastVar<AMIClass>());
      AMIClass::ptr ac = var->Pointer();

      ac->SetFileName(driver.current_file);
      ac->SetBody(     body);
      if (GB_debug) printf("%s body = %s\n", ac->GetName().c_str(),body->GetBody().c_str());
    };
    */
    |
    /**
     *  Declare a new class with inheritance
     */
    T_Class  identifier T_COLON T_public var_ami_class_list
        instr_block end_instr
    {
      //Variable<AMIClass>::ptr var(driver.var_stack.GetLastVar<AMIClass>());
      //AMIClass::ptr parent = var->Pointer();
      std::vector<AMIClass::ptr>* classlist = $5;

      AmiInstructionBlock::ptr body($6);
      IdentifierInfo::ptr ident($2);

      AMIClass::ptr amiclass( new AMIClass);

      amiclass->SetName(ident->GetName());
      amiclass->SetFileName(driver.current_file);
      amiclass->Inherit(*classlist);
      amiclass->SetBody(     body);
      if (GB_debug) printf("%s body = %s\n", ident->GetName().c_str(),body->GetBody().c_str());

      Vars.AddVar<AMIClass>(ident, amiclass);
      //del classlist; Bison does it, no?

    };
    

object_decl:
VAR_AMI_CLASS  identifier
{
    Variable<AMIClass>::ptr var(driver.var_stack.GetLastVar<AMIClass>());
    AMIClass::ptr ac = var->Pointer();
    IdentifierInfo::ptr ident($2);

    //AMIObject::ptr amiobject;
    //amiobject = AMIObject::ptr(new AMIObject);
    AMIObject::ptr amiobject( new AMIObject);

    amiobject->SetName(ident->GetName());
    amiobject->SetClass(ac);

    // execute the code of the class with the variables of the object
    driver.yyip_instanciate_object(ac,amiobject);

    Vars.AddVar<AMIObject>(ident, amiobject);

};

func_inst :
FUNCTION expr_string end_instr
{
    //driver.res_print($2);
    driver.parse_script($2);
    delete [] $2;
}
/* disabled for the moment 
|
FUNCTION end_instr
{
    int res;
    std::string name;
    std::string inc_cmd; // increment the command line string

    //cout << "current wd = "  <<  wxGetCwd() << std::endl;
    res=AskScript(name);
    if (!res) {
        driver.yyiperror(" Need script \n");
        YYABORT;
    }
    //cout << "current wd = "  <<  wxGetCwd() << std::endl;

    driver.res_print(name.c_str());
    driver.res_print("\n");
    driver.parse_file(name.c_str());

    // convert path delimiters to avoid pbs with \ character
    wxFileName filename(GetwxStr(name.c_str()),wxPATH_NATIVE);
    filename.Normalize(wxPATH_NORM_ALL,wxEmptyString,wxPATH_UNIX);

    wxString newname(   filename.GetVolume()+filename.GetVolumeSeparator()+
    filename.GetPath(wxPATH_GET_VOLUME,wxPATH_UNIX)+
    filename.GetPathSeparator(wxPATH_UNIX)+
    filename.GetFullName());

    driver.res_print( newname);
    driver.res_print("\n");
    inc_cmd = str(boost::format(" \"%1%\" // from browser ") % newname.mb_str());
    if (driver.InConsole())
        GB_main_wxFrame->GetConsole()
        ->IncCommand(wxString(inc_cmd.c_str(),wxConvUTF8));
}
*/
|
T_eval expr_string
{
    boost::shared_array<char> input($2);
    std::string inputstring( input.get());
    driver.parse_string( inputstring,
    "'eval string' command");
}
;

command:
unprocessed_variable
{
    /**
      Description:
        Empty instruction.
    **/
    BasicVariable::ptr       var(driver.var_stack.GetLastBasicVar());
    if (var.get()) {
        // TODO: only do it from the command line ???
        //cout << "display var info" << std::endl;
        if (driver.InConsole())
            var->display(std::cout);
    }

}
|
expr_var
{
    /**
      Description:
        Empty instruction.
    **/
    BasicVariable::ptr       var(driver.var_stack.GetLastBasicVar());
    if (var.get()) {
        switch (var->Type()) {
            // TODO: ad hoc fix to improve here, result should be a usable variable ??
            /// C++ wrapped member
        case type_class_member: {
            DYNAMIC_CAST_VARIABLE(WrapClassMember,var,m);
            m->Pointer()->CallMember(NULL,0);
        }
        break;
        /// language function without parameters.
        case type_ami_function: {
            DYNAMIC_CAST_VARIABLE(AMIFunction,var,vf);
            AMIFunction::ptr f(vf->Pointer());
            driver.yyip_call_function(f);
        }
        break;
        default:
            ;
            // TODO: only do it from the command line ???
            //cout << "display var info" << std::endl;
            if (driver.InConsole())
                var->display(std::cout);
        }
    }

}
|
T_emptyargs {
    /**
     Description:
       Sets the number of command line arguments to 1 (name of the program)
     **/
    GB_argc = 1;
}
|
T_BREAK {
    /**
      Description:
        Calls YYABORT to leave the current instruction block.
      See Also:
        repeat
    **/
    YYABORT;
}
|
T_global
{
    /**
    Description:
     Set a global context for variables,
     creates new variables as global and can only
     access global variables

    See also:
     local, global_new
    **/
    Vars.SetGlobalContext();
}
|
T_global_new
{
    /**
    Description:
     Set a global context for new variables,
     creates new variables as global,
     but allow access to lobal variables

    See also:
     local, global
    **/
    Vars.SetGlobalNew(1);
}
|
T_local_new
{
    /**
    Description:
     Set a local context for new variables,
     creates new variables as local,
     and allow access to local variables

    See also:
     local, global, global_new
    **/
    Vars.SetGlobalNew(0);
}
|
T_local
{
    /**
    Description:
    Set a local context for variables
    **/
    Vars.SetLastContext();
    Vars.SetGlobalNew(0);
}
|
T_wait T_OP_PAR expr T_CL_PAR
{
    /**
    Description: waits the time given in milliseconds
    **/

    /*        int ms = (int) $3;
            wxWaitTimer w;
            w.Start(ms,wxTIMER_ONE_SHOT);
            while (!w.finished) {
              if (GB_wxApp->Pending()) {
                GB_wxApp->Dispatch();
              }
            } // end while*/
}
|
T_schedule T_OP_PAR expr T_COMMA VAR_AMI_FUNCTION T_CL_PAR
{
    /**
    Parameters:
        (3) time in ms
        (5) function to schedule
    **/

    /*        int ms = (int) $3;
            GET_VARSTACK_VAR_VAL(AMIFunction,var,val);

            wxScheduleTimer::ptr w = wxScheduleTimer::ptr(new wxScheduleTimer( var ));
            // add to the list of schedule timers
            schedule_timers.push_back(w);
            w->Start(ms,wxTIMER_ONE_SHOT);*/

}
|
identifier ASSIGN_OP T_AND unprocessed_variable
{
    /**
      Description:
        Creates a new variable that is a reference to an existing one.
      Parameters:
        - new variable name;
        - existing variable name.
    **/
    BasicVariable::ptr  var(driver.var_stack.GetLastBasicVar());
    IdentifierInfo::ptr ident($1);
    BasicVariable::ptr newvar( var->NewReference());
    Vars.AddVar(ident,newvar);
}
|
identifier ASSIGN_OP T_AND expr_var
{
    /**
      Description:
        Creates a new variable that is a reference to an existing one.
      Parameters:
        - new variable name;
        - existing variable name.
    **/
    BasicVariable::ptr  var(driver.var_stack.GetLastBasicVar());
    IdentifierInfo::ptr ident($1);
    if (var.get() && (var->HasPointer())  ) {
        if ((var->GetPtrCounter()==1)&&(var.use_count()==1)) {
            //cout << "var.use_count() = " << var.use_count() << std::endl;
            Vars.AddVar(ident,var);
            //cout << "var.use_count() = " << var.use_count() << std::endl;
        } else {
            BasicVariable::ptr newvar( var->NewReference());
            Vars.AddVar(ident,newvar);
        }
    } else {
        driver.err_print("identifier = &expr_var, no variable value");
        YYABORT;
    }
}
|
identifier ASSIGN_OP expr_var
{
    /**
      Description:
        Creates a new variable that is a copy of an existing one.
      Parameters:
        - new variable name;
        - existing variable name.
    **/
    BasicVariable::ptr  var(driver.var_stack.GetLastBasicVar());
    IdentifierInfo::ptr ident($1);
    // check counter of the value, not of the variable ...
    if (var.get() && (var->HasPointer())  ) {
        // only if both reference counters are equal to 1, we can avoid copy the variable
        if ((var->GetPtrCounter()==1)&&(var.use_count()==1)) {
            //BasicVariable::ptr ref = var->NewReference();
            // need to run on reference to avoid renaming the own variable !!!
            //Vars.AddVar(ident,ref);
            Vars.AddVar(ident,var);
        } else
        {
            BasicVariable::ptr copy = var->NewCopy();
            if (copy.get()) {
                Vars.AddVar(ident,copy);
            } else {
                driver.err_print("Copy failed for the variable in rule id = expr_var");
                YYABORT;
            }
        }
    } else {
        driver.err_print("identifier = expr_var, no variable value");
        YYABORT;
    }
}
|
identifier ASSIGN_OP expr_var T_COMMA expr_string
{
    /**
      Description:
        Creates a new variable that is a copy of an existing one, and sets its comments
      Parameters:
        - new variable name;
        - existing variable name.
    **/
    boost::shared_array<char> comments( $5);
    BasicVariable::ptr  var(driver.var_stack.GetLastBasicVar());
    IdentifierInfo::ptr ident($1);
    if (var.get() && (var->HasPointer())  ) {
        // only if both reference counters are equal to 1, we can avoid copy the variable
        if ((var->GetPtrCounter()==1)&&(var.use_count()==1)) {
            //BasicVariable::ptr ref = var->NewReference();
            // need to run on reference to avoid renaming the own variable !!!
            //Vars.AddVar(ident,ref);
            var->SetComments(comments.get());
            Vars.AddVar(ident,var);
        } else
        {
            BasicVariable::ptr copy = var->NewCopy();
            if (copy.get()) {
                copy->SetComments(comments.get());
                Vars.AddVar(ident,copy);
            } else {
                driver.err_print("Copy failed for the variable in rule id = expr_var");
                YYABORT;
            }
        }
    } else {
        driver.err_print("identifier = expr_var, no variable value");
        YYABORT;
    }
}
|
identifier ASSIGN_OP variable_without_assign
{
    /**
      Description:
        Creates a new variable that is a copy of an existing one.
      Parameters:
        - new variable name;
        - existing variable name.
    **/

    BasicVariable::ptr  var(driver.var_stack.GetLastBasicVar());
    IdentifierInfo::ptr ident($1);

    // first process exception cases
    if (var.get()) {
        if (var->Type()==type_class_member) {
            /// C++ wrapped member
            DYNAMIC_CAST_VARIABLE(WrapClassMember,var,m);
            ParamList::ptr param((ParamList*)NULL);
            BasicVariable::ptr res(m->Pointer()->CallMember(param.get(),0));
            if (!res.get()) {
                driver.yyiperror("Class member does not return a variable \n");
                YYABORT;
            }
            res->Rename(ident->GetName().c_str());
            Vars.AddVar(res,ident->GetCreationContext());
        }
        else
            // general case
            // for now always call new copy here, otherwise a = b would rename b to a, which is bad
            /*
                        if (var->GetPtrCounter()==1) {
                          IdentifierInfo::ptr ident($1);
                          Vars.AddVar(ident,var);
                        } else
            */
        {
            BasicVariable::ptr copy = var->NewCopy();
            Vars.AddVar(ident,copy);
        }
    } else {
        driver.err_print("identifier = variable, no variable value");
        YYABORT;
    }
}
|
identifier ASSIGN_OP T_BOOL T_OP_PAR expr T_CL_PAR
{
    /**
      Description:
        Creates a variable of type boolean
    **/
    IdentifierInfo::ptr ident($1);

    boost::shared_ptr<bool> varboolean (new bool((bool)$5));
    Vars.AddVar<bool>(ident,varboolean);
}
|
identifier ASSIGN_OP T_BOOL T_OP_PAR expr T_CL_PAR T_COMMA expr_string
{
    /**
    Parameters:
      - identifier: name of the new variable
      - expr: value of the new variable
      - expr_string: short description of the new variable
      Description:
        Creates a variable of type boolean
    **/
    IdentifierInfo::ptr ident($1);
    boost::shared_array<char> comments( $8);

    boost::shared_ptr<bool> varboolean (new bool((bool)$5));
    BasicVariable::ptr var=Vars.AddVar<bool>(ident,varboolean);
    if (var.get())
        var->SetComments(comments.get());
}
|
identifier ASSIGN_OP T_INT T_OP_PAR expr T_CL_PAR
{
    /**
      Description:
        Creates a variable of type int
    **/
    IdentifierInfo::ptr ident($1);

    int_ptr varint (new int((int)$5));
    Vars.AddVar<int>(ident,varint);
}
|
identifier ASSIGN_OP T_LONG T_OP_PAR expr T_CL_PAR
{
    /**
      Description:
        Creates a variable of type long
    **/
    IdentifierInfo::ptr ident($1);

    long_ptr varlong (new long((long)$5));
    Vars.AddVar<long>(ident,varlong);
}
|
identifier ASSIGN_OP T_ULONG T_OP_PAR expr T_CL_PAR
{
    /**
      Description:
        Creates a variable of type long
    **/
    IdentifierInfo::ptr ident($1);

    ulong_ptr varlong (new unsigned long((unsigned long)$5));
    Vars.AddVar<unsigned long>(ident,varlong);
}
|
identifier ASSIGN_OP T_SHORT T_OP_PAR expr T_CL_PAR
{
    /**
      Description:
        Creates a variable of type long
    **/
    IdentifierInfo::ptr ident($1);

    short_ptr var (new short((short)$5));
    Vars.AddVar<short>(ident,var);
}
|
identifier ASSIGN_OP T_USHORT T_OP_PAR expr T_CL_PAR
{
    /**
      Description:
        Creates a variable of type long
    **/
    IdentifierInfo::ptr ident($1);

    ushort_ptr var (new unsigned short((unsigned short)$5));
    Vars.AddVar<unsigned short>(ident,var);
}
|
identifier ASSIGN_OP T_DOUBLE T_OP_PAR expr T_CL_PAR
{
    /**
      Description:
        Creates a variable of type int
    **/
    IdentifierInfo::ptr ident($1);

    boost::shared_ptr<double> var (new double((double)$5));
    Vars.AddVar<double>(ident,var);
}
|
identifier ASSIGN_OP T_DOUBLE T_OP_PAR expr T_CL_PAR T_COMMA expr_string
{
    /**
      Description:
        Creates a variable of type int
    **/
    IdentifierInfo::ptr ident($1);
    boost::shared_array<char> comments( $8);

    boost::shared_ptr<double> vard (new double((double)$5));
    BasicVariable::ptr var=Vars.AddVar<double>(ident,vard);
    if (var.get())
        var->SetComments(comments.get());
}
|
identifier ASSIGN_OP T_INT T_OP_PAR expr T_CL_PAR T_COMMA expr_string
{
    /**
    Parameters:
      - identifier: name of the new variable
      - expr: value of the new variable
      - expr_string: short description of the new variable
      Description:
        Creates a variable of type int
    **/
    IdentifierInfo::ptr ident($1);
    boost::shared_array<char> comments( $8);

    int_ptr varint( new int((int)$5));
    BasicVariable::ptr var=Vars.AddVar<int>(ident,varint);
    if (var.get())
        var->SetComments(comments.get());
}
|
identifier ASSIGN_OP T_LONG T_OP_PAR expr T_CL_PAR T_COMMA expr_string
{
    /**
    Parameters:
      - identifier: name of the new variable
      - expr: value of the new variable
      - expr_string: short description of the new variable
      Description:
        Creates a variable of type long
    **/
    IdentifierInfo::ptr ident($1);
    boost::shared_array<char> comments( $8);

    long_ptr varlong( new long((long)$5));
    BasicVariable::ptr var=Vars.AddVar<long>(ident,varlong);
    if (var.get())
        var->SetComments(comments.get());
}
|
identifier ASSIGN_OP T_UCHAR T_OP_PAR expr T_CL_PAR
{
    /**
      Description:
        Creates a variable of type unsigned char (used for boolean type too)
    **/
    IdentifierInfo::ptr ident($1);
    uchar_ptr varuchar( new unsigned char((unsigned char)$5));
    Vars.AddVar<unsigned char>(ident,varuchar);
}
|
identifier ASSIGN_OP T_UCHAR T_OP_PAR expr  T_CL_PAR T_COMMA expr_string
{
    /**
    Parameters:
      - identifier: name of the new variable
      - expr: value of the new variable
      - expr_string: short description of the new variable
    Description:
      creates a variable of type unsigned char (used for boolean type too)
    **/
    IdentifierInfo::ptr ident($1);
    boost::shared_array<char> comments( $8);

    uchar_ptr varuchar(new unsigned char((unsigned char)$5));
    BasicVariable::ptr var=Vars.AddVar<unsigned char>(ident,varuchar);
    if (var.get())
        var->SetComments(comments.get());
}
|  T_SetDebugOn
{
    GB_debug = 1;
}
|  T_SetDebugOff
{
    GB_debug = 0;
}
|  T_TraceScanning expr
{
    driver.SetTraceScanning($2>0.5);
}
|  T_TraceParsing expr
{
    /**
     Description:
        Activate the debugging of the parser.
     Parameters:
        bool: 1:activate 0: desactivate
     **/
    driver.SetTraceParsing($2>0.5);
}
|  T_SetVerboseOn
{
    GB_verbose = 1;
}
|  T_SetVerboseOff
{
    GB_verbose = 0;
}
|  T_NoMessageDialog expr
{
    /**
     Description:
        Activate/Desactivate the display of message dialog in the language driver.
     Parameters:
        bool: 1:activate 0: desactivate
     **/
    driver.SetNoMessageDialog($2>0.5);
}
|  QUIT  {
    /*           GB_main_wxFrame->Close(true); */
}
| SHOW VARIABLES
{
    Vars.display();
}
| T_Comments T_OP_PAR variable T_COMMA  expr_string T_CL_PAR
{
    /**
      Parameters:
          variable: input variable
          string expression: comments
      Description: Set comments for a variable
    **/
    BasicVariable::ptr  var(driver.var_stack.GetLastBasicVar());
    boost::shared_array<char> comments( $5);
    var->SetComments(comments.get());
}
| T_del identifier
{
    /**
      Description:
        Delete an identifier: nothing to do ...
    **/
    IdentifierInfo::ptr ident($2);
}
| T_del variable
{
    /**
      Description:
        Delete the given variable
    **/
    /*Variable* var;

    if (Vars.GetVar($2->Name(),&var))
    Vars.deleteVar($2->Name());
    */
    BasicVariable::ptr var(driver.var_stack.GetLastBasicVar());
    Vars.deleteVar(var);
}
| T_delvars expr_string
{
    /**
      Description:
        Delete all variables that match the expression, where the expression can contain
        '*' and '?' characters
    **/
    boost::shared_array<char> varmatch( $2);
    Vars.deleteVars( varmatch.get());
}
| ASHELL expr_string
{
    /**
      Parameters:
        - string expression: command to call
      Description:
        calls a command from the system using std::system()
    **/
    boost::shared_array<char> cmd( $2);
    std::system( cmd.get());
}
| LS
{
    /**
      Description:
      Calls system 'ls' command (for unix systems)
    **/
    std::system("ls");
}
| HELP
{
    driver.res_print("Topics: \n");
    driver.res_print("\t var:  variables                 \n");
    driver.res_print("\t     image:     Help for image     variables\n");
    driver.res_print("\t     imagedraw: Help for imagedraw variables\n");
    driver.res_print("\t cmd:  commands                  \n");
    driver.res_print("\t fnc:  functions                 \n");
    driver.res_print("\t loop: loops                     \n");
    driver.res_print("\t cond: conditions                \n");
    driver.res_print("\t arit: arithmetical expressions  \n");
}
| HELP identifier
{
    IdentifierInfo::ptr ident($2);
    if (strcmp(ident->GetName().c_str(),"var")==0) {
        driver.res_print("var types: void image float int string imagedraw surface surfacedraw \n");
        driver.res_print("\t del varname\n");
        driver.res_print("\t\t\t - deletes a variable and frees its contents from memory \n");
    }
    else if (strcmp(ident->GetName().c_str(),"cmd")==0) {
        driver.res_print("commands:\n");
        driver.res_print("\t sh Quit Image Show Help ls print func filter normgrad discnormgrad OpImage EDPdilate EDPerode EDPopen EDPclose\n");
    }
    else if (strcmp(ident->GetName().c_str(),"fnc")==0) {
    }
    else if (strcmp(ident->GetName().c_str(),"loop")==0) {
        driver.res_print("loops:\n");
        driver.res_print("\t  for var=expr to expr { instructions } \n");
    }
    else if (strcmp(ident->GetName().c_str(),"cond")==0) {
        driver.res_print("loops:\n");
        driver.res_print("\t  if expr  { instructions } \n");
        driver.res_print("\t\t  [ else { instructions } ]\n");
    }
    else if (strcmp(ident->GetName().c_str(),"arit")==0) {
        driver.res_print("arithmetical expressions:\n");
        driver.res_print("\t  constants: Pi\n");
        driver.res_print("\n");
        driver.res_print("\t  functions:  cos()  sin()  tan() \n");
        driver.res_print("\t             acos() asin() atan() \n");
        driver.res_print("\t              exp()   ln()  log() \n");
        driver.res_print("\t             sinh() cosh()        \n");
        driver.res_print("\t  operators:\n");
        driver.res_print("\t            *, /\n");
        driver.res_print("\t            +, -\n");
        driver.res_print("\t            <, >, <=, >=\n");
        driver.res_print("\t            ==, != \n");
        driver.res_print("\t            & \n");
        driver.res_print("\t            ^ \n");
        driver.res_print("\t            | \n");
    }
}
| HELP VAR_C_FUNCTION
{
    /**
      Description:
        Displays the documentation relative to the wrapped image function.
    **/
    GET_VARSTACK_VALUE(C_wrap_varfunction, func);
    // call with NULL paramlist pointer to trigger help message
    (*func)(NULL);
}
| HELP VAR_C_PROCEDURE
{
    /**
      Description:
        Displays the documentation relative to the wrapped image function.
    **/
    GET_VARSTACK_VALUE(C_wrap_procedure, proc);
    // call with NULL paramlist pointer to trigger help message
    (*proc)(NULL);
}
| HELP VAR_CLASS_MEMBER
{
    /**
      Description:
        Displays the documentation relative to the wrapped c++ member.
    **/
    GET_VARSTACK_VALUE(WrapClassMember, m);
    m->ShowHelp();
}
| HELP ASTRING
{
    std::string  help_cmd;
    std::string  help_file;


    // Check for directory
    help_file = str( boost::format("%s/%s") % GB_help_dir.c_str() % $2);

    if( GB_debug )  fprintf(stderr,"3\n");
    help_cmd = str(boost::format("test -d %s") % help_file.c_str());
    if( (std::system(help_cmd.c_str()) == 0) ) {
    printf("\nAvailable help files in %s:\n",$2);
    help_cmd = str( boost::format("cd %s; ls *.amih ") % help_file.c_str());
    std::system(help_cmd.c_str());
    } else {

    if ( GB_debug )  fprintf(stderr,"4\n");
    // Check for file
    help_file = str( boost::format("%s/%s.amih") % GB_help_dir.c_str() %$2);

    help_cmd = str(boost::format("test -r %s") % help_file.c_str());
    if ( (std::system(help_cmd.c_str()) == 0) ) {
    help_cmd = str( boost::format("more %s") % help_file.c_str());
    std::system(help_cmd.c_str());
    } else {
    if ( GB_debug )  fprintf(stderr,"5\n");
    // Try to find it in any subdirectory of the help dir
    help_cmd = str(boost::format("test -r `find %s -name \"%s.amih\"` 2> /dev/null")
    % GB_help_dir.c_str()
    % $2);
    if ( std::system(help_cmd.c_str())==0 ) {
    help_cmd = str(boost::format("find %s -name \"%s.amih\" -exec ls {} \\; -exec more {} \\;")
    % GB_help_dir.c_str()
    % $2);
    std::system(help_cmd.c_str());
    } else {
    fprintf(stderr,"\nNo help file (%s) found for this command \n",
    help_file.c_str());
    printf("\nAvailable help directories:\n");
    help_cmd = str(boost::format("cd %s; find . -type d  ") % GB_help_dir.c_str());
    std::system(help_cmd.c_str());

    printf("\nAvailable help files:\n");
    help_cmd = str(boost::format("ls *.amih ") %
    std::system(help_cmd.c_str()));
    } // end if
    } // end if

    } // end if

    if ( GB_debug )  fprintf(stderr,"6\n");

}
| PRINT expr_var
{
    /**
     Description:
       Print a value of a variable, if the string conversion is defined, a message otherwise
     **/
    BasicVariable::ptr var(driver.var_stack.GetLastBasicVar());
    if (var.get())
        driver.res_print(var->GetValueAsString());
    else
        driver.err_print("empty variable");
}
| PRINTN expr_var
{
    /**
     Description:
       Print a value of a variable + newline, if the string conversion is defined, a message otherwise
     **/
    BasicVariable::ptr var(driver.var_stack.GetLastBasicVar());
    if (var.get())
        driver.res_print(var->GetValueAsString()+"\n");
    else
        driver.err_print("empty variable");
}
| T_InfoDialog expr_string
{
    /**
     Parameters:
       string expression: information text
     Description:
       Popup an Information Dialog with the given message
     **/
    driver.info_print($2);
    delete [] $2;
}
| VAR_AMI_OBJECT  T_info
{
    /**
      Description:
        Prints the object information
    **/
    GET_VARSTACK_VAR_VAL(AMIObject,varamio,o);

    if (o.get()) {
        std::cout << "var   name = " << varamio->Name() <<std::endl;
        if (o->GetClass().get()) {
            std::cout << "class name = " << o->GetClass()->GetName() <<std::endl;
        }
        o->GetContext()->display();
    }
}
|
T_ProcessEvents T_OP_PAR expr T_CL_PAR
{
    /**
      Description: dispatch the given number of events
    **/
    /* disabled for the moment
    int nb_event;

    nb_event = 0;
    while (nb_event<(int)$3) {
        if (GB_wxApp->Pending()) {
            GB_wxApp->Dispatch();
        }
        nb_event++;
    } // end while
    */
}
|
T_RestartTime
{
    driver.IP_time.InitCumul();
}
|
T_InitTime
{
    driver.IP_time.Debut();
}
|
T_EndTime
{
    driver.IP_time.Fin();
    std::cout << "time spent = " << driver.IP_time << std::endl;
}
;



var_ami_class_list:
VAR_AMI_CLASS
{
    Variable<AMIClass>::ptr var(driver.var_stack.GetLastVar<AMIClass>());
    AMIClass::ptr c = var->Pointer();
    std::vector<AMIClass::ptr>* cl = new std::vector<AMIClass::ptr>();
    cl->push_back(c);
    $$ = cl;
}
|
var_ami_class_list T_COMMA VAR_AMI_CLASS
{
    Variable<AMIClass>::ptr var(driver.var_stack.GetLastVar<AMIClass>());
    AMIClass::ptr c = var->Pointer();
    std::vector<AMIClass::ptr>* cl = $1;
    cl->push_back(c);
    $$ = cl;
}

exprstringlist:
expr_string
{
    std::list<std::string>* sl = new std::list<std::string>();
    sl->push_back(std::string($1));
    delete [] $1;
    $$ = sl;
}
|
exprstringlist T_COMMA expr_string
{
    std::list<std::string>* sl = $1;
    sl->push_back(std::string($3));
    delete [] $3;
    $$ = sl;
}


param_list:
{
    ParamList* pl = new ParamList();
    $$ = pl;
}
| unprocessed_variable
{
    /**
      Description: temporary rule, added to simplify conversion of scripts.
     **/
    BasicVariable::ptr       var(driver.var_stack.GetLastBasicVar());
    if (!var.get()) {
        driver.error("Empty Variable as parameter !");
        YYABORT;
    }
    ParamList* pl = new ParamList();
    // Creating a new variable that points to the same value, and a slightly different name (with added "_ref"), comments are also copied.
    BasicVariable::ptr newvar(var->NewReference());
    pl->AddParam(newvar);
    $$ = pl;
}
| param_list T_COMMA  unprocessed_variable
{
    /**
      Description: temporary rule, added to simplify conversion of scripts.
     **/
    BasicVariable::ptr       var(driver.var_stack.GetLastBasicVar());
    if (!var.get()) {
        driver.error("Empty Variable as parameter !");
        YYABORT;
    }
    ParamList* pl =  $1;

    // Creating a new variable that points to the same value, and a slightly different name (with added "_ref"), comments are also copied.
    BasicVariable::ptr newvar(var->NewReference());

    pl->AddParam(newvar);
    $$ = pl;
}
| T_AND expr_var
{
    BasicVariable::ptr       var(driver.var_stack.GetLastBasicVar());
    if (!var.get()) {
        driver.error("Empty Variable as parameter !");
        YYABORT;
    }

    ParamList* pl = new ParamList();
    // Creating a new variable that points to the same value, and a slightly different name (with added "_ref"), comments are also copied.
    BasicVariable::ptr newvar(var->NewReference());

    pl->AddParam(newvar);
    $$ = pl;
}
| param_list T_COMMA T_AND expr_var
{
    BasicVariable::ptr       var(driver.var_stack.GetLastBasicVar());
    if (!var.get()) {
        driver.error("Empty Variable as parameter !");
        YYABORT;
    }
    ParamList* pl =  $1;

    // Creating a new variable that points to the same value, and a slightly different name (with added "_ref"), comments are also copied.
    BasicVariable::ptr newvar(var->NewReference());

    pl->AddParam(newvar);
    $$ = pl;
}
| expr_var
{
    /**
      Description: it is now a new reference to the variable, so basically similar to &variable (should be removed?)...
    **/
    BasicVariable::ptr       var(driver.var_stack.GetLastBasicVar());
    if (!var.get()) {
        driver.error("Empty Variable as parameter !");
        YYABORT;
    }

    ParamList* pl = new ParamList();
    // Creating a new variable that points to the same value, and a slightly different name (with added "_ref"), comments are also copied.
    BasicVariable::ptr newvar(var->NewReference());

    pl->AddParam(newvar);
    $$ = pl;
    /* passing all by reference ...
     *          BasicVariable::ptr var(driver.var_stack.GetLastBasicVar());
              if (!var.get()) {
                driver.error("Empty Variable as parameter !");
                YYABORT;
              }
              ParamList* pl(new ParamList);
              BasicVariable::ptr newvar(var->NewCopy());
              if (newvar.get()) {
                newvar->Rename("Param0");
                pl->AddParam(newvar);
                $$ = pl;
              } else {
                driver.error(boost::format("Could not copy parameter 0 variable expression !").str().c_str());
                YYABORT;
              }
            */
}
| param_list T_COMMA expr_var
{
    /**
      Description: it is now a new reference to the variable, so basically similar to &variable (should be removed?)...
    **/

    BasicVariable::ptr       var(driver.var_stack.GetLastBasicVar());
    if (!var.get()) {
        driver.error("Empty Variable as parameter !");
        YYABORT;
    }
    ParamList* pl =  $1;

    // Creating a new variable that points to the same value, and a slightly different name (with added "_ref"), comments are also copied.
    BasicVariable::ptr newvar(var->NewReference());

    pl->AddParam(newvar);
    $$ = pl;

    /* passing all by reference
     *          BasicVariable::ptr var(driver.var_stack.GetLastBasicVar());
              if (!var.get()) {
                driver.error("Empty Variable as parameter !");
                YYABORT;
              }
              ParamList* pl =  $1;
              std::string paramname = (boost::format("Param%1%")%pl->GetNumParam()).str();
              BasicVariable::ptr newvar(var->NewCopy());
              if (newvar.get()) {
                newvar->Rename(paramname.c_str());
                pl->AddParam(newvar);
                $$ = pl;
              } else {
                driver.error((boost::format("Could not copy parameter %1% variable expression !") % pl->GetNumParam()).str().c_str());
                YYABORT;
              }
            */
}
;

param_list_decl:
{
    //      printf("no parameters \n");
    ParamListDecl* pl = new ParamListDecl;
    $$ = pl;
}
| T_NUM IDENTIFIER
{
    IdentifierInfo::ptr ident($2);
    //std::cout << "param_list_decl: T_NUM IDENTIFIER" << std::endl;
    //std::cout << ident->GetName().c_str() << std::endl;
    ParamListDecl* pl = new ParamListDecl;
    pl->AddParam(ident->GetName(),type_float);
    $$ = pl;
}
| T_OBJECT IDENTIFIER
{
    IdentifierInfo::ptr ident($2);
    ParamListDecl* pl = new ParamListDecl;
    pl->AddParam(ident->GetName(),type_ami_object);
    $$ = pl;
}
| T_VAR IDENTIFIER
{
    IdentifierInfo::ptr ident($2);
    ParamListDecl* pl = new ParamListDecl;
    pl->AddParam(ident->GetName(),type_any);
    $$ = pl;
}
| T_STRING IDENTIFIER
{
    IdentifierInfo::ptr ident($2);
    ParamListDecl* pl = new ParamListDecl;
    // type string is deprecated
    pl->AddParam(ident->GetName(),type_ami_object);
    $$ = pl;
}
| param_list_decl T_COMMA T_OBJECT IDENTIFIER
{
    IdentifierInfo::ptr ident($4);
    ParamListDecl* pl = (ParamListDecl*) $1;
    pl->AddParam(ident->GetName(),type_ami_object);
    $$ = pl;
}
| param_list_decl T_COMMA T_VAR IDENTIFIER
{
    IdentifierInfo::ptr ident($4);
    ParamListDecl* pl = (ParamListDecl*) $1;
    pl->AddParam(ident->GetName(),type_any);
    $$ = pl;
}
| param_list_decl T_COMMA T_NUM IDENTIFIER
{
    IdentifierInfo::ptr ident($4);
    ParamListDecl* pl = (ParamListDecl*) $1;
    pl->AddParam(ident->GetName(),type_float);
    $$ = pl;
}
| param_list_decl T_COMMA T_STRING IDENTIFIER
{
    IdentifierInfo::ptr ident($4);
    ParamListDecl* pl = (ParamListDecl*) $1;
    // type string is deprecated
    pl->AddParam(ident->GetName(),type_ami_object);
    $$ = pl;
}
;

primary_expr_string:
ASTRING
{
    $$=$1;
}
|
T_SPRINT T_OP_PAR expr_string T_COMMA expr T_CL_PAR
{
    char* res;
    //printf("expr_string=%s*\n",$3);
    //printf("expr=%f*\n",$5);
    res = new char[strlen($3)+20];
    sprintf(res,$3,$5);
    //          res[strlen($3)]=0;
    delete [] $3;
    //printf("res=%s*\n",res);
    $$=res;
}
|
T_TimeSpent
{
    long min,hour;
    float sec;

    driver.IP_time.Fin();
    driver.IP_time.AddCumul();
    driver.IP_time.GetCumul(hour,min,sec);
    std::string res;
    if (hour>0) {
        res = (boost::format("%3d h %2d min %2d sec")%(int)hour
        %(int)min %(int)sec).str();
    } else
        res = (boost::format("%2d min %2d sec")
        %(int)min %(int)sec).str();
    if (min>0) {
    } else
        res = (boost::format("%2.2f sec") %sec).str();

    char* reschar = new char[res.size()+1];
    strcpy(reschar,res.c_str());
    $$= reschar;
}
|
T_GetObjectName T_OP_PAR variable T_CL_PAR {
    /**
      Description:
        Returns the name of the object instance to which this variable belongs. If this variable does not belong to an object, returns an empty string.
    **/
    BasicVariable::ptr  var(driver.var_stack.GetLastBasicVar());
    boost::shared_ptr<Variables> context = var->GetContext();
    if (context.get()) {
        char* res = new char[strlen(context->GetName().c_str())+1];
        strcpy(res,context->GetName().c_str());
        $$= res;
    } else {
        char* empty_string;
        empty_string = new char[1];
        empty_string[0] = '\0';
        $$ = empty_string;
    }
}
|
T_GetScriptsDir
{
    char* res = new char[GB_scripts_dir.size()+1];
    strcpy(res,GB_scripts_dir.c_str());
    $$= res;
}
;


instr_block:
begin_block
ABLOCK
end_block
{
    $$=$2;
    if (GB_debug)
        std::cerr << boost::format("ablock : %s")
        % $2->GetBody()
        << std::endl;
};

begin_block:
;
end_block:
;

float_variable:
NUMBER
{
    ADD_VARSTACK_FLOAT($1)
}
| T_argc
{
    /**
    Description:
      returns the number of arguments in the command line
    **/
    ADD_VARSTACK_FLOAT(GB_argc-GB_num_arg_parsed)
}
| T_LineNumber
{
    /**
    Description:
      Line number in the current script
    **/
    ADD_VARSTACK_FLOAT(driver.yyiplineno)
}
| CONST_PI
{
    /**
    Description:
      the constant Pi is set to
       3.14159265358979323846
    **/
    ADD_VARSTACK_FLOAT(3.14159265358979323846)
}
|
|  T_atof T_OP_PAR expr_string T_CL_PAR
{
    setlocale(LC_NUMERIC, "C");
    float val=atof($3);
    ADD_VARSTACK_FLOAT(val);
    delete [] $3;
}
| T_exists T_OP_PAR identifier T_CL_PAR
{
    /**
    Description:
    Check for the existence of a variable, returns 0
    **/
    IdentifierInfo::ptr ident($3);
    float val=0;
    ADD_VARSTACK_FLOAT(val);
}
| T_exists T_OP_PAR variable T_CL_PAR
{
    /**
    Description:
    Check for the existence of a variable, returns 1
    **/
    BasicVariable::ptr  var(driver.var_stack.GetLastBasicVar());
    float val=1;
    ADD_VARSTACK_FLOAT(val);
}
| basic_type POINT_IDENTIFIER
{
    /**
      Description: returns the value of the pixel format type in float format,
      identifier must be equal to 'val'
    **/
    IdentifierInfo::ptr ident($2);
    if (ident->GetName()=="val") {
        float val = (int) $1;
        ADD_VARSTACK_FLOAT(val);
    }
}
;


expr    :
expr_var
{
    BasicVariable::ptr var(driver.var_stack.GetLastBasicVar());
    if (var.get())
        if (var->IsNumeric())
            $$=var->GetValueAsDouble();
        else {
            $$=var->GetValueAsDouble();
            std::string mess;
            mess = boost::format("Numerical expression from non-numerical variable expression").str();
            mess = mess + (boost::format("(check for recent changes like i[j] where i and j are images should now be rewritten as i[j.GetExtent] )")).str();
            mess = mess + (boost::format(" variable name : %1%") % var->Name()).str();
            mess = mess + (boost::format(" variable typename : %1%") % var->GetTypeName()).str();
            driver.err_print( mess.c_str());
            YYABORT;
        }
    else {
        driver.err_print("Expression from null variable ...");
        $$ = 0;
    }
}
;

expr_string:
expr_var
{
    /**
      Description:  This rule is created to avoid changing a lot of code in the process of converting string operation to operations on Variable\<std::string> ...
    **/


    BasicVariable::ptr var(driver.var_stack.GetLastBasicVar());
    boost::shared_ptr<std::string> string_ptr = AMILabType<std::string>::GetValue(var,0);

    if (string_ptr.get())
    {
        char* res;
        res = new char[string_ptr->length()+1];
        strcpy(res,string_ptr->c_str());
        $$= res;
    } else {
        driver.err_print("Expecting a string variable here ... \n");
        YYABORT;
    }
}
;


basic_type:
T_CHAR
{
    driver.err_print(" char format is not available: use unsigned char \n");
    $$=WT_UNSIGNED_CHAR;
}
| T_UCHAR
{
    $$=WT_UNSIGNED_CHAR;
}
| T_SHORT
{
    $$=WT_SIGNED_SHORT;
}
| T_USHORT
{
    $$=WT_UNSIGNED_SHORT;
}
| T_INT
{
    $$=WT_SIGNED_INT;
}
| T_UINT
{
    $$=WT_UNSIGNED_INT;
}
| T_LONG
{
    $$=WT_SIGNED_LONG;
}
| T_ULONG
{
    $$=WT_UNSIGNED_LONG;
}
| T_FLOAT
{
    $$=WT_FLOAT;
}
| T_DOUBLE
{
    $$=WT_DOUBLE;
}
| T_RGB
{
    $$=WT_RGB;
}
| T_FLOAT_VECTOR
{
    $$=WT_FLOAT_VECTOR;
}
| T_BasicType T_OP_PAR expr T_CL_PAR
{
    $$=(int)$3;
};

string_variable:
VAR_STRING
{
    /**
    Description: adds a reference to the variable in the stack
    **/
    BasicVariable::ptr  var(driver.var_stack.GetLastBasicVar());
    driver.var_stack.AddVar(var->NewReference());
}
|
primary_expr_string
{
    /**
      Description:
        primary_expr_string value to a string variable
      TODO: get completely rid of char* values
    **/
    string_ptr varstr(new std::string($1));
    BasicVariable::ptr new_var = AMILabType<std::string>::CreateVarFromSmtPtr(varstr);
    driver.var_stack.AddVar(new_var);
};


primary_var:
function_variable
|
VAR_AMI_OBJECT
|
PROCESSED_VAR
|
float_variable
|
string_variable
|
T_MAX T_OP_PAR expr_var T_COMMA expr_var T_CL_PAR
{
    /**
    Description:
      The 2 parameters can be either images or numbers,
      for 2 images:
        Returns the image corresponding to the pointwise maximum between 2 images.
      for 2 numbers:
        Returns the maximal value.


    See also:
            min, median
      **/

    BasicVariable::ptr param2(driver.var_stack.GetLastBasicVar());
    BasicVariable::ptr param1(driver.var_stack.GetLastBasicVar());

    if (param1.get()&&param2.get()) {
        if ((param1->IsNumeric())&&(param2->IsNumeric())) {
            double val1 = param1->GetValueAsDouble();
            double val2 = param2->GetValueAsDouble();
            double res = (val1>val2)?val1:val2;
            ADD_VARSTACK_FLOAT(res);
        }
        else {
            driver.err_print("max operator with these types of parameters not available");
            YYABORT;
        }
    }

}
|
T_MIN T_OP_PAR expr_var T_COMMA expr_var T_CL_PAR
{
    /**
    Description:
      The 2 parameters can be either images or numbers,
      for 2 images:
        Returns the image corresponding to the pointwise minimum between 2 images.
      for 2 numbers:
        Returns the minimal value.


    See also:
            max, median
      **/

    BasicVariable::ptr param2(driver.var_stack.GetLastBasicVar());
    BasicVariable::ptr param1(driver.var_stack.GetLastBasicVar());

    if (param1.get()&&param2.get()) {
        if ((param1->IsNumeric())&&(param2->IsNumeric())) {
            double val1 = param1->GetValueAsDouble();
            double val2 = param2->GetValueAsDouble();
            double res = (val1<val2)?val1:val2;
            ADD_VARSTACK_FLOAT(res);
        }
        else {
            driver.err_print("max operator with these types of parameters not available");
            YYABORT;
        }
    }

}
|
T_OP_PAR expr_var T_CL_PAR;

postfix_var:
primary_var %prec SHIFT_THERE
|
postfix_var POINT_IDENTIFIER %prec postfix
{
    /**
       Description:
       if the first variable is an AMIObject, then look for the variable
         corresponding to the identifier in its context.
       if the first variable is of IMAGE type, then apply on of the following
         functions:
     **/
    // todo ...
    // 1. check if identifier belongs to the object
    // 2. if so return corresponding variable
    IdentifierInfo::ptr ident($2);

    BasicVariable::ptr bvar(driver.var_stack.GetLastBasicVar());
    if (!bvar.get()) {
        driver.err_print("operator . (Element selection) empty variable");
        YYABORT;
    }

    // try to convert to AMIObject
    boost::shared_ptr<Variable<AMIObject> > var( boost::dynamic_pointer_cast<Variable<AMIObject> >(bvar));
    if (var.get()) {
        AMIObject::ptr object(var->Pointer());
        if (!object.get()) {
            driver.err_print("operator . object points to NULL.");
            YYABORT;
        }
        // here, need to do our own checking ...
        BasicVariable::ptr newvar(
            object->GetContext()->GetVar(ident->GetName().c_str()));

        if  ((!GB_driver.procedure_declaration)&& newvar.get())   {
            //cout << "returning variable" << std::endl;
            //newvar->display();
            driver.var_stack.AddVar(newvar);
        } else {
            // error message here
            driver.yyiperror("Identifier does not belong to object context \n");
            YYABORT;
            //driver.var_stack.AddVar(BasicVariable::ptr());
        }
    } 
}
|
postfix_var T_OP_PAR param_list T_CL_PAR
{
    /**
      Description:
        Call to a function, returning a variable
    **/
    //cout << "call to variable T_OP_PAR param_list T_CL_PAR end_instr" << std::endl;
    // 1. check the variable type
    GET_CHECK_VARSTACK(var)
    ParamList::ptr param($3);

    // TODO: run this with overloading from BasicVariable ...
    if (var->Type()==type_class_member) {
        ///    Call a wrapped C++ class member.
        DYNAMIC_CAST_VARIABLE(WrapClassMember,var, var1);
        BasicVariable::ptr res ((var1->Pointer())->CallMember(param.get(),0));
        /*
        if (!res.get()) {
          driver.yyiperror("Class member does not return a variable \n");
          YYABORT;
        }
        */
        driver.var_stack.AddVar(res);

    } else if (var->Type()==type_ami_function)
    {
        ///    Call a language function with its parameters.
        DYNAMIC_CAST_VARIABLE(AMIFunction,var, var1);
        AMIFunction::ptr f(var1->Pointer());
        BasicVariable::ptr res(driver.yyip_call_function(f,param));
        /* don't be so strict ...
        if (!res.get()) {
          driver.yyiperror("Ami function does not return a variable \n");
          YYABORT;
        }
        */
        driver.var_stack.AddVar(res);

    } else if (var->Type()==type_c_function)
    {
        DYNAMIC_CAST_VARIABLE(C_wrap_varfunction,var, func);
        BasicVariable::ptr  res;
        res = (*func->Pointer())(param.get());
        /*
        if (!res.get()) {
          driver.yyiperror(" function returns NULL \n");
          YYABORT;
        }
        */
        driver.var_stack.AddVar(res);
    } else if (var->Type()==type_c_procedure)
    {
        DYNAMIC_CAST_VARIABLE(C_wrap_procedure,var, func);
        BasicVariable::ptr  res;
        (*func->Pointer())(param.get());
        driver.var_stack.AddVar(res);
    } else if (var->Type()==type_ami_object)
    {
        ///    Call a wrapped C++ class member.
        DYNAMIC_CAST_VARIABLE(AMIObject,var, obj);
        // Check for () operator
        // Check for a constructor inside the context
        BasicVariable::ptr parop;
        BasicVariable::ptr constr;
        if (obj.get())  {
            Variables::ptr objcontext = obj->Pointer()->GetContext();
            //objcontext->display();
            parop = objcontext->GetVar("__parenthesis__");
            constr = obj->Pointer()->GetConstructorVar();
        }
        if (parop.get()) {
            // Call the () operator with the given parameters
            DYNAMIC_CAST_VARIABLE(WrapClassMember,parop, parop_member);
            BasicVariable::ptr res =  (parop_member->Pointer())->CallMember(param.get(),0);
            driver.var_stack.AddVar(res);
        } else {
            if (constr.get()) {
                // Call the constructor with the given parameters
                DYNAMIC_CAST_VARIABLE(WrapClassMember,constr, constr_member);
                BasicVariable::ptr res =  (constr_member->Pointer())->CallMember(param.get(),0);
                driver.var_stack.AddVar(res);
            } else {
                // error message here
                driver.yyiperror("failed to process () operator \n");
                driver.var_stack.AddVar(BasicVariable::ptr());
            }
        }

    } else
    {
        // error message here
        driver.yyiperror("variable is not of a function type \n");
        driver.var_stack.AddVar(BasicVariable::ptr());
    }
}
| postfix_var INC_OP %prec postfix
{
    /**
      Description: Postfix increment operator.
    **/
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar((*var)++);
}
| postfix_var DEC_OP %prec postfix
{
    /**
      Description: Postfix decrement operator.
    **/
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar((*var)--);
}
| postfix_var TRANSPOSE_OP %prec postfix
{
    /**
      Description: Transpose operator, usefull for matrices
    **/
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->Transpose());
}
|
postfix_var T_OP_BR  expr_var T_CL_BR
{
    /**
      Description: Array subscript operator.
    **/
    BasicVariable::ptr var2(driver.var_stack.GetLastBasicVar());
    BasicVariable::ptr var1(driver.var_stack.GetLastBasicVar());
    driver.var_stack.AddVar((*var1)[var2]);
}
;

prefix_var:
postfix_var %prec SHIFT_THERE
|
T_OP_PAR basic_type T_CL_PAR prefix_var %prec prefix
{
    /**
      Description: Cast operator.
    **/
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->BasicCast( $2));

}
| T_NOT prefix_var %prec prefix
{
    /**
      Description: Logical negation (NOT) operator.
    **/
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(!(*var));
}
| T_SUB  prefix_var %prec prefix
{
    //cout << "T_SUB  cast_var  " << std::endl;
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(-(*var));
}
| T_ADD  prefix_var %prec prefix
{
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(+(*var));
}
| INC_OP  postfix_var  %prec prefix
{
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(++(*var));
}
| DEC_OP  prefix_var %prec prefix
{
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(--(*var));
}
| T_MULT  postfix_var %prec prefix
{
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(*(*var));
}
| SIN    prefix_var %prec prefix
{
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_sin());
}
| COS    prefix_var %prec prefix
{
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_cos());
}
| SQRT   prefix_var %prec prefix
{
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_sqrt());
}
| ABS    prefix_var %prec prefix
{
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_fabs());
}
| ROUND  prefix_var %prec prefix
{
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_round());
}
| FLOOR  prefix_var %prec prefix
{
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_floor());
}
| TAN    prefix_var %prec prefix
{
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_tan());
}
| ASIN   prefix_var %prec prefix
{
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_asin());
}
| ACOS   prefix_var %prec prefix
{
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_acos());
}
| ATAN   prefix_var %prec prefix
{
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_atan());
}
| EXP    prefix_var %prec prefix
{
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_exp());
}
| LOG    prefix_var %prec prefix
{
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_log());
}
| LN     prefix_var %prec prefix
{
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_ln());
}
| NORM   prefix_var %prec prefix
{
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_norm());
}
;


multiplicative_var:
prefix_var %prec SHIFT_THERE
| multiplicative_var T_MULT prefix_var
{
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)*var2);
}
| multiplicative_var T_DIV  prefix_var
{
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)/var2);
}
| multiplicative_var T_MOD  prefix_var
{
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)%var2);
}
//  | multiplicative_var T_EXP  prefix_var
;

additive_var:
multiplicative_var %prec SHIFT_THERE
| additive_var T_ADD multiplicative_var
{
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    BasicVariable::ptr res(*var1+var2);
    driver.var_stack.AddVar(res);
}
| additive_var T_SUB multiplicative_var
{
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    BasicVariable::ptr res((*var1)-var2);
    driver.var_stack.AddVar(res);
}
;

shift_var:
additive_var %prec SHIFT_THERE
|
shift_var LEFT_OP additive_var
{
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)<<var2);
}
|
shift_var RIGHT_OP additive_var
{
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)>>var2);
}
;

relational_var:
shift_var %prec SHIFT_THERE
| relational_var T_LT  shift_var
{
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)<var2);
}
| relational_var T_GT  shift_var
{
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)>var2);
}
| relational_var LE_OP shift_var
{
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)<=var2);
}
| relational_var GE_OP shift_var
{
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)>=var2);
}
;

equality_var:
relational_var %prec SHIFT_THERE
| equality_var EQ_OP relational_var
{
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)==var2);
}
| equality_var NE_OP relational_var
{
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)!=var2);
}
;

and_var:
equality_var %prec SHIFT_THERE
| and_var T_AND equality_var
{
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)&var2);
}
;

exclusive_or_var:
and_var %prec SHIFT_THERE
;

inclusive_or_var:
exclusive_or_var %prec SHIFT_THERE
| inclusive_or_var T_OR exclusive_or_var
{
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)|var2);
}
;

logical_and_var:
inclusive_or_var %prec SHIFT_THERE
| logical_and_var AND_OP inclusive_or_var
{
    /**
      Descriptiopn: Logical AND operator
    **/
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)&&var2);
}
;

logical_xor_var:
logical_and_var %prec SHIFT_THERE
| logical_xor_var T_EXP logical_and_var
{
    /**
      Descriptiopn: Logical XOR operator, for vectorial images it defines the pointwise vectorial product.
    **/
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)^var2);
}
;

logical_or_var:
logical_xor_var %prec SHIFT_THERE
| logical_or_var OR_OP logical_xor_var
{
    /**
      Descriptiopn: Logical OR operator
    **/
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)||var2);
}
;

conditional_var:
logical_or_var %prec SHIFT_THERE
| logical_or_var T_QUEST primary_var T_COLON primary_var
{
    /**
      Descriptiopn: Operation (cond?a:b) like in C/C++.
    **/
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    BasicVariable::ptr var(driver.var_stack.GetLastBasicVar());
    driver.var_stack.AddVar(var->TernaryCondition(var1,var2));
}
;

assignment_var:
conditional_var %prec SHIFT_THERE
| conditional_var ASSIGN_OP assignment_var
{
    //cout << "assignment_var" << std::endl;
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    if (var1->GetPtrCounter()==1) {
        // TODO: here ...
    }
    driver.var_stack.AddVar((*var1)=var2);
}
| conditional_var LEFT_ASSIGN assignment_var
{
    //cout << "assignment_var" << std::endl;
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1).left_assign(var2));
}
| conditional_var ADD_ASSIGN assignment_var
{
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)+=var2);
}
| conditional_var SUB_ASSIGN assignment_var
{
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)-=var2);
}
| conditional_var MUL_ASSIGN assignment_var
{
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)*=var2);
}
| conditional_var DIV_ASSIGN assignment_var
{
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)/=var2);
}
;

expr_var:
assignment_var
;


identifier
:
IDENTIFIER
;

/*
  Variable not included in variable expression
*/

/*
variable_with_assign:
         VAR_GLTRANSFORM;
*/

function_variable:
VAR_C_FUNCTION
| VAR_C_PROCEDURE
| VAR_CLASS_MEMBER
| VAR_AMI_FUNCTION
;

variable_without_assign:
VAR_AMI_CLASS
;


unprocessed_variable:
//variable_with_assign
//|
variable_without_assign

/*
  Variable included in variable expression
*/
processed_variable:
VAR_AMI_OBJECT
|
PROCESSED_VAR
|
VAR_STRING
/* VAR_STRING */
;

variable:
unprocessed_variable
|
processed_variable
|
function_variable
;

%%
#include <stdio.h>



int is_space(char c)
{
    return ((c==' ')||(c=='\n')||(c=='\t'));
}




void yyip::Parser::error(const Parser::location_type& l,
                         const std::string& m)
{
    driver.error(l, m);
}


/*
//------------------------------------------------------
void wxScheduleTimer::Notify()
//   -----------------------
{
    //cout << "Notify()" << std::endl;
    GB_driver.yyip_call_function(var->Pointer().get());

    std::list<wxScheduleTimer::ptr>::iterator Iter;
    for (Iter  = schedule_timers.begin();
            Iter != schedule_timers.end()  ;  )
    {
        if ((*Iter).use_count()) {
            if (Iter->get() == this)
                Iter = schedule_timers.erase(Iter);
            else
                ++Iter;
        } else
            ++Iter;
    }
} // wxScheduleTimer::Notify()
*/

//------------------------------------------------------------------------------
void CallAmiFunction(AMIFunction* f, const ParamList::ptr& p)
{
    //cout << "CB_ParamWin pointer is " << func_ptr << std::endl;
    GB_driver.yyip_call_function(f,p);
} // CallAmiFunction( void* cd )

