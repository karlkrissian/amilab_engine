// A Bison parser, made by GNU Bison 3.0.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2013 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Take the name prefix into account.
#define yylex   yyiplex

// First part of user declarations.
#line 11 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:399

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





#line 284 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:399

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "amiengine_bison.tab.hpp"

// User implementation prologue.
#line 499 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:407


#include "driver.h"
#include "scanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex


#line 310 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:407


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyempty = true)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yyip {
#line 396 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:474

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (class Driver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  Parser::by_type::by_type ()
     : type (empty)
  {}

  inline
  Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.type = empty;
  }

  inline
  int
  Parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.state = empty;
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    return state == empty ? 0 : yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.type_get ())
    {
            case 48: // ASTRING

#line 491 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:599
        { delete [] (yysym.value.astring); }
#line 615 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:599
        break;

      case 51: // IDENTIFIER

#line 492 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:599
        { delete  (yysym.value.ident); }
#line 622 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:599
        break;

      case 52: // POINT_IDENTIFIER

#line 492 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:599
        { delete  (yysym.value.ident); }
#line 629 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:599
        break;

      case 180: // var_ami_class_list

#line 495 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:599
        { delete  (yysym.value.class_list); }
#line 636 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:599
        break;

      case 181: // exprstringlist

#line 494 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:599
        { delete  (yysym.value.string_list); }
#line 643 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:599
        break;

      case 184: // primary_expr_string

#line 491 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:599
        { delete [] (yysym.value.astring); }
#line 650 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:599
        break;

      case 185: // instr_block

#line 493 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:599
        { delete  (yysym.value.ablock); }
#line 657 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:599
        break;

      case 190: // expr_string

#line 491 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:599
        { delete [] (yysym.value.astring); }
#line 664 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:599
        break;

      case 210: // identifier

#line 492 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:599
        { delete  (yysym.value.ident); }
#line 671 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:599
        break;


      default:
        break;
    }
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    /// Whether yyla contains a lookahead.
    bool yyempty = true;

    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 278 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:725
{
    // initialize the initial location object
    yyla.location.begin.filename = yyla.location.end.filename = &driver.streamname;
}

#line 808 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:725

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyempty)
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
        yyempty = false;
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Discard the token being shifted.
    yyempty = true;

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 22:
#line 538 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
      int  previous_lineno=driver.yyiplineno;
      int  previous_lineno_lastparser=driver.yyiplineno_lastparser;
      AmiInstructionBlock::ptr block((yystack_[1].value.ablock));
      IdentifierInfo::ptr ident((yystack_[6].value.ident));

      int_ptr varint(new int);
      Vars.AddVar<int>(ident,varint);
      //bool goon=true;

      for(*varint = (int) (yystack_[4].value.adouble); *varint <= (int) (yystack_[2].value.adouble); (*varint)++)
        {
          driver.yyiplineno = block->GetStartingLine();
          //goon=
          driver.parse_block(block);
        }
      Vars.deleteVar(ident->GetName().c_str());
      driver.yyiplineno=previous_lineno;
      driver.yyiplineno_lastparser=previous_lineno_lastparser;
    }
#line 941 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 23:
#line 561 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
      int  previous_lineno=driver.yyiplineno;
      int  previous_lineno_lastparser=driver.yyiplineno_lastparser;
      AmiInstructionBlock::ptr block((yystack_[1].value.ablock));
      IdentifierInfo::ptr ident((yystack_[8].value.ident));

      float_ptr var(new float);
      Vars.AddVar<float>(ident,var);
      bool goon=true;

      for(*var = (yystack_[6].value.adouble); goon&&(*var <= (yystack_[4].value.adouble)); (*var)+=(yystack_[2].value.adouble))
      {
        driver.yyiplineno = block->GetStartingLine();
        //driver.yyiplineno=previous_lineno;
        goon=driver.parse_block(block);
      }
      Vars.deleteVar(ident->GetName().c_str());
      driver.yyiplineno=previous_lineno;
      driver.yyiplineno_lastparser=previous_lineno_lastparser;
    }
#line 966 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 24:
#line 584 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description: 
          Iteration through a list of strings.
    **/

      std::list<std::string>* sl = (yystack_[2].value.string_list);

      int  previous_lineno=driver.yyiplineno;
      int  previous_lineno_lastparser=driver.yyiplineno_lastparser;
      AmiInstructionBlock::ptr block((yystack_[1].value.ablock));
      IdentifierInfo::ptr ident((yystack_[4].value.ident));

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
      delete (yystack_[2].value.string_list);

    }
#line 1020 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 25:
#line 635 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
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
        AmiInstructionBlock::ptr block((yystack_[0].value.ablock));
        int res;
    
        do {
  
            //driver.yyiplineno=previous_lineno;
            driver.yyiplineno = block->GetStartingLine();
            res=driver.parse_block(block);
  
        } while (res);
        driver.yyiplineno = previous_lineno;
        driver.yyiplineno_lastparser=previous_lineno_lastparser;
      }
#line 1048 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 26:
#line 660 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
      /**
        Description:
          Repeats the block while the variable value is higher than 0.5
      **/
        int  previous_lineno=driver.yyiplineno;
        int  previous_lineno_lastparser=driver.yyiplineno_lastparser;
        AmiInstructionBlock::ptr block((yystack_[0].value.ablock));
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
#line 1084 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 27:
#line 696 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
      int  previous_lineno;
      AmiInstructionBlock::ptr block((yystack_[1].value.ablock));

      // Pb with line numbers
      previous_lineno=driver.yyiplineno;
      int  previous_lineno_lastparser = driver.yyiplineno_lastparser;

        if ((yystack_[2].value.adouble)>0.5)
        {
          //driver.yyiplineno=previous_lineno;
          if (!driver.parse_block(block)) YYABORT;
          driver.yyiplineno = previous_lineno;
          driver.yyiplineno_lastparser = previous_lineno_lastparser;
        }
    }
#line 1105 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 28:
#line 713 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {

      AmiInstructionBlock::ptr block_if(  (yystack_[3].value.ablock));
      AmiInstructionBlock::ptr block_else((yystack_[1].value.ablock));

      // Pb with line numbers
      int  previous_lineno = driver.yyiplineno;
      int  previous_lineno_lastparser = driver.yyiplineno_lastparser;

      bool res;
      if ((yystack_[4].value.adouble)>0.5)
        res = driver.parse_block(block_if);
      else
        res = driver.parse_block(block_else);
      if (!res) YYABORT;
      driver.yyiplineno = previous_lineno;
      driver.yyiplineno_lastparser = previous_lineno_lastparser;

    }
#line 1129 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 29:
#line 740 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
      GB_driver.procedure_declaration = true;
    }
#line 1137 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 30:
#line 745 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
      AmiInstructionBlock::ptr body((yystack_[1].value.ablock));
      IdentifierInfo::ptr ident((yystack_[6].value.ident));

      AMIFunction::ptr amifunc(new AMIFunction);

      amifunc->SetName(ident->GetName().c_str());
      amifunc->SetFileName(driver.current_file);
      amifunc->SetParamList((yystack_[3].value.paramlistdecl));
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
#line 1166 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 31:
#line 775 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
      // allow overriding current functions
      GB_driver.procedure_declaration = true;
    }
#line 1175 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 32:
#line 781 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
      AmiInstructionBlock::ptr body((yystack_[1].value.ablock));

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
      amifunc->SetParamList((yystack_[3].value.paramlistdecl));
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
    }
#line 1216 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 33:
#line 826 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
      AmiInstructionBlock::ptr body((yystack_[1].value.ablock));
      IdentifierInfo::ptr ident((yystack_[2].value.ident));

      AMIClass::ptr amiclass( new AMIClass);

      amiclass->SetName(ident->GetName());
      amiclass->SetFileName(driver.current_file);
      amiclass->SetBody(     body);
      if (GB_debug) printf("%s body = %s\n", ident->GetName().c_str(),body->GetBody().c_str());

      Vars.AddVar<AMIClass>(ident, amiclass);

    }
#line 1235 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 34:
#line 865 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
      //Variable<AMIClass>::ptr var(driver.var_stack.GetLastVar<AMIClass>());
      //AMIClass::ptr parent = var->Pointer();
      std::vector<AMIClass::ptr>* classlist = (yystack_[2].value.class_list);

      AmiInstructionBlock::ptr body((yystack_[1].value.ablock));
      IdentifierInfo::ptr ident((yystack_[5].value.ident));

      AMIClass::ptr amiclass( new AMIClass);

      amiclass->SetName(ident->GetName());
      amiclass->SetFileName(driver.current_file);
      amiclass->Inherit(*classlist);
      amiclass->SetBody(     body);
      if (GB_debug) printf("%s body = %s\n", ident->GetName().c_str(),body->GetBody().c_str());

      Vars.AddVar<AMIClass>(ident, amiclass);
      //del classlist; Bison does it, no?

    }
#line 1260 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 35:
#line 889 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    Variable<AMIClass>::ptr var(driver.var_stack.GetLastVar<AMIClass>());
    AMIClass::ptr ac = var->Pointer();
    IdentifierInfo::ptr ident((yystack_[0].value.ident));

    //AMIObject::ptr amiobject;
    //amiobject = AMIObject::ptr(new AMIObject);
    AMIObject::ptr amiobject( new AMIObject);

    amiobject->SetName(ident->GetName());
    amiobject->SetClass(ac);

    // execute the code of the class with the variables of the object
    driver.yyip_instanciate_object(ac,amiobject);

    Vars.AddVar<AMIObject>(ident, amiobject);

}
#line 1283 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 36:
#line 910 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    //driver.res_print($2);
    driver.parse_script((yystack_[1].value.astring));
    delete [] (yystack_[1].value.astring);
}
#line 1293 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 37:
#line 954 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    boost::shared_array<char> input((yystack_[0].value.astring));
    std::string inputstring( input.get());
    driver.parse_string( inputstring,
    "'eval string' command");
}
#line 1304 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 38:
#line 964 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
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
#line 1323 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 39:
#line 980 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
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
#line 1360 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 40:
#line 1013 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
     Description:
       Sets the number of command line arguments to 1 (name of the program)
     **/
    GB_argc = 1;
}
#line 1372 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 41:
#line 1021 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description:
        Calls YYABORT to leave the current instruction block.
      See Also:
        repeat
    **/
    YYABORT;
}
#line 1386 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 42:
#line 1032 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
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
#line 1403 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 43:
#line 1046 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
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
#line 1420 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 44:
#line 1060 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
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
#line 1437 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 45:
#line 1074 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
    Description:
    Set a local context for variables
    **/
    Vars.SetLastContext();
    Vars.SetGlobalNew(0);
}
#line 1450 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 46:
#line 1084 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
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
#line 1469 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 47:
#line 1100 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
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
#line 1490 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 48:
#line 1118 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description:
        Creates a new variable that is a reference to an existing one.
      Parameters:
        - new variable name;
        - existing variable name.
    **/
    BasicVariable::ptr  var(driver.var_stack.GetLastBasicVar());
    IdentifierInfo::ptr ident((yystack_[3].value.ident));
    BasicVariable::ptr newvar( var->NewReference());
    Vars.AddVar(ident,newvar);
}
#line 1508 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 49:
#line 1133 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description:
        Creates a new variable that is a reference to an existing one.
      Parameters:
        - new variable name;
        - existing variable name.
    **/
    BasicVariable::ptr  var(driver.var_stack.GetLastBasicVar());
    IdentifierInfo::ptr ident((yystack_[3].value.ident));
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
#line 1537 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 50:
#line 1159 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description:
        Creates a new variable that is a copy of an existing one.
      Parameters:
        - new variable name;
        - existing variable name.
    **/
    BasicVariable::ptr  var(driver.var_stack.GetLastBasicVar());
    IdentifierInfo::ptr ident((yystack_[2].value.ident));
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
#line 1575 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 51:
#line 1194 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description:
        Creates a new variable that is a copy of an existing one, and sets its comments
      Parameters:
        - new variable name;
        - existing variable name.
    **/
    boost::shared_array<char> comments( (yystack_[0].value.astring));
    BasicVariable::ptr  var(driver.var_stack.GetLastBasicVar());
    IdentifierInfo::ptr ident((yystack_[4].value.ident));
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
#line 1615 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 52:
#line 1231 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description:
        Creates a new variable that is a copy of an existing one.
      Parameters:
        - new variable name;
        - existing variable name.
    **/

    BasicVariable::ptr  var(driver.var_stack.GetLastBasicVar());
    IdentifierInfo::ptr ident((yystack_[2].value.ident));

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
#line 1664 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 53:
#line 1277 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description:
        Creates a variable of type boolean
    **/
    IdentifierInfo::ptr ident((yystack_[5].value.ident));

    boost::shared_ptr<bool> varboolean (new bool((bool)(yystack_[1].value.adouble)));
    Vars.AddVar<bool>(ident,varboolean);
}
#line 1679 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 54:
#line 1289 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
    Parameters:
      - identifier: name of the new variable
      - expr: value of the new variable
      - expr_string: short description of the new variable
      Description:
        Creates a variable of type boolean
    **/
    IdentifierInfo::ptr ident((yystack_[7].value.ident));
    boost::shared_array<char> comments( (yystack_[0].value.astring));

    boost::shared_ptr<bool> varboolean (new bool((bool)(yystack_[3].value.adouble)));
    BasicVariable::ptr var=Vars.AddVar<bool>(ident,varboolean);
    if (var.get())
        var->SetComments(comments.get());
}
#line 1701 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 55:
#line 1308 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description:
        Creates a variable of type int
    **/
    IdentifierInfo::ptr ident((yystack_[5].value.ident));

    int_ptr varint (new int((int)(yystack_[1].value.adouble)));
    Vars.AddVar<int>(ident,varint);
}
#line 1716 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 56:
#line 1320 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description:
        Creates a variable of type long
    **/
    IdentifierInfo::ptr ident((yystack_[5].value.ident));

    long_ptr varlong (new long((long)(yystack_[1].value.adouble)));
    Vars.AddVar<long>(ident,varlong);
}
#line 1731 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 57:
#line 1332 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description:
        Creates a variable of type long
    **/
    IdentifierInfo::ptr ident((yystack_[5].value.ident));

    ulong_ptr varlong (new unsigned long((unsigned long)(yystack_[1].value.adouble)));
    Vars.AddVar<unsigned long>(ident,varlong);
}
#line 1746 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 58:
#line 1344 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description:
        Creates a variable of type long
    **/
    IdentifierInfo::ptr ident((yystack_[5].value.ident));

    short_ptr var (new short((short)(yystack_[1].value.adouble)));
    Vars.AddVar<short>(ident,var);
}
#line 1761 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 59:
#line 1356 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description:
        Creates a variable of type long
    **/
    IdentifierInfo::ptr ident((yystack_[5].value.ident));

    ushort_ptr var (new unsigned short((unsigned short)(yystack_[1].value.adouble)));
    Vars.AddVar<unsigned short>(ident,var);
}
#line 1776 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 60:
#line 1368 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description:
        Creates a variable of type int
    **/
    IdentifierInfo::ptr ident((yystack_[5].value.ident));

    boost::shared_ptr<double> var (new double((double)(yystack_[1].value.adouble)));
    Vars.AddVar<double>(ident,var);
}
#line 1791 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 61:
#line 1380 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description:
        Creates a variable of type int
    **/
    IdentifierInfo::ptr ident((yystack_[7].value.ident));
    boost::shared_array<char> comments( (yystack_[0].value.astring));

    boost::shared_ptr<double> vard (new double((double)(yystack_[3].value.adouble)));
    BasicVariable::ptr var=Vars.AddVar<double>(ident,vard);
    if (var.get())
        var->SetComments(comments.get());
}
#line 1809 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 62:
#line 1395 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
    Parameters:
      - identifier: name of the new variable
      - expr: value of the new variable
      - expr_string: short description of the new variable
      Description:
        Creates a variable of type int
    **/
    IdentifierInfo::ptr ident((yystack_[7].value.ident));
    boost::shared_array<char> comments( (yystack_[0].value.astring));

    int_ptr varint( new int((int)(yystack_[3].value.adouble)));
    BasicVariable::ptr var=Vars.AddVar<int>(ident,varint);
    if (var.get())
        var->SetComments(comments.get());
}
#line 1831 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 63:
#line 1414 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
    Parameters:
      - identifier: name of the new variable
      - expr: value of the new variable
      - expr_string: short description of the new variable
      Description:
        Creates a variable of type long
    **/
    IdentifierInfo::ptr ident((yystack_[7].value.ident));
    boost::shared_array<char> comments( (yystack_[0].value.astring));

    long_ptr varlong( new long((long)(yystack_[3].value.adouble)));
    BasicVariable::ptr var=Vars.AddVar<long>(ident,varlong);
    if (var.get())
        var->SetComments(comments.get());
}
#line 1853 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 64:
#line 1433 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description:
        Creates a variable of type unsigned char (used for boolean type too)
    **/
    IdentifierInfo::ptr ident((yystack_[5].value.ident));
    uchar_ptr varuchar( new unsigned char((unsigned char)(yystack_[1].value.adouble)));
    Vars.AddVar<unsigned char>(ident,varuchar);
}
#line 1867 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 65:
#line 1444 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
    Parameters:
      - identifier: name of the new variable
      - expr: value of the new variable
      - expr_string: short description of the new variable
    Description:
      creates a variable of type unsigned char (used for boolean type too)
    **/
    IdentifierInfo::ptr ident((yystack_[7].value.ident));
    boost::shared_array<char> comments( (yystack_[0].value.astring));

    uchar_ptr varuchar(new unsigned char((unsigned char)(yystack_[3].value.adouble)));
    BasicVariable::ptr var=Vars.AddVar<unsigned char>(ident,varuchar);
    if (var.get())
        var->SetComments(comments.get());
}
#line 1889 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 66:
#line 1462 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GB_debug = 1;
}
#line 1897 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 67:
#line 1466 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GB_debug = 0;
}
#line 1905 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 68:
#line 1470 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    driver.SetTraceScanning((yystack_[0].value.adouble)>0.5);
}
#line 1913 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 69:
#line 1474 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
     Description:
        Activate the debugging of the parser.
     Parameters:
        bool: 1:activate 0: desactivate
     **/
    driver.SetTraceParsing((yystack_[0].value.adouble)>0.5);
}
#line 1927 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 70:
#line 1484 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GB_verbose = 1;
}
#line 1935 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 71:
#line 1488 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GB_verbose = 0;
}
#line 1943 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 72:
#line 1492 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
     Description:
        Activate/Desactivate the display of message dialog in the language driver.
     Parameters:
        bool: 1:activate 0: desactivate
     **/
    driver.SetNoMessageDialog((yystack_[0].value.adouble)>0.5);
}
#line 1957 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 73:
#line 1501 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /*           GB_main_wxFrame->Close(true); */
}
#line 1965 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 74:
#line 1505 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    Vars.display();
}
#line 1973 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 75:
#line 1509 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Parameters:
          variable: input variable
          string expression: comments
      Description: Set comments for a variable
    **/
    BasicVariable::ptr  var(driver.var_stack.GetLastBasicVar());
    boost::shared_array<char> comments( (yystack_[1].value.astring));
    var->SetComments(comments.get());
}
#line 1989 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 76:
#line 1521 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description:
        Delete an identifier: nothing to do ...
    **/
    IdentifierInfo::ptr ident((yystack_[0].value.ident));
}
#line 2001 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 77:
#line 1529 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
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
#line 2019 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 78:
#line 1543 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description:
        Delete all variables that match the expression, where the expression can contain
        '*' and '?' characters
    **/
    boost::shared_array<char> varmatch( (yystack_[0].value.astring));
    Vars.deleteVars( varmatch.get());
}
#line 2033 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 79:
#line 1553 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Parameters:
        - string expression: command to call
      Description:
        calls a command from the system using std::system()
    **/
    boost::shared_array<char> cmd( (yystack_[0].value.astring));
    std::system( cmd.get());
}
#line 2048 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 80:
#line 1564 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description:
      Calls system 'ls' command (for unix systems)
    **/
    std::system("ls");
}
#line 2060 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 81:
#line 1572 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
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
#line 2076 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 82:
#line 1584 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    IdentifierInfo::ptr ident((yystack_[0].value.ident));
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
#line 2121 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 83:
#line 1625 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description:
        Displays the documentation relative to the wrapped image function.
    **/
    GET_VARSTACK_VALUE(C_wrap_varfunction, func);
    // call with NULL paramlist pointer to trigger help message
    (*func)(NULL);
}
#line 2135 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 84:
#line 1635 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description:
        Displays the documentation relative to the wrapped image function.
    **/
    GET_VARSTACK_VALUE(C_wrap_procedure, proc);
    // call with NULL paramlist pointer to trigger help message
    (*proc)(NULL);
}
#line 2149 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 85:
#line 1645 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description:
        Displays the documentation relative to the wrapped c++ member.
    **/
    GET_VARSTACK_VALUE(WrapClassMember, m);
    m->ShowHelp();
}
#line 2162 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 86:
#line 1654 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    std::string  help_cmd;
    std::string  help_file;


    // Check for directory
    help_file = str( boost::format("%s/%s") % GB_help_dir.c_str() % (yystack_[0].value.astring));

    if( GB_debug )  fprintf(stderr,"3\n");
    help_cmd = str(boost::format("test -d %s") % help_file.c_str());
    if( (std::system(help_cmd.c_str()) == 0) ) {
    printf("\nAvailable help files in %s:\n",(yystack_[0].value.astring));
    help_cmd = str( boost::format("cd %s; ls *.amih ") % help_file.c_str());
    std::system(help_cmd.c_str());
    } else {

    if ( GB_debug )  fprintf(stderr,"4\n");
    // Check for file
    help_file = str( boost::format("%s/%s.amih") % GB_help_dir.c_str() %(yystack_[0].value.astring));

    help_cmd = str(boost::format("test -r %s") % help_file.c_str());
    if ( (std::system(help_cmd.c_str()) == 0) ) {
    help_cmd = str( boost::format("more %s") % help_file.c_str());
    std::system(help_cmd.c_str());
    } else {
    if ( GB_debug )  fprintf(stderr,"5\n");
    // Try to find it in any subdirectory of the help dir
    help_cmd = str(boost::format("test -r `find %s -name \"%s.amih\"` 2> /dev/null")
    % GB_help_dir.c_str()
    % (yystack_[0].value.astring));
    if ( std::system(help_cmd.c_str())==0 ) {
    help_cmd = str(boost::format("find %s -name \"%s.amih\" -exec ls {} \\; -exec more {} \\;")
    % GB_help_dir.c_str()
    % (yystack_[0].value.astring));
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
#line 2220 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 87:
#line 1708 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
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
#line 2236 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 88:
#line 1720 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
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
#line 2252 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 89:
#line 1732 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
     Parameters:
       string expression: information text
     Description:
       Popup an Information Dialog with the given message
     **/
    driver.info_print((yystack_[0].value.astring));
    delete [] (yystack_[0].value.astring);
}
#line 2267 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 90:
#line 1743 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
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
#line 2287 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 91:
#line 1760 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
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
#line 2308 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 92:
#line 1778 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    driver.IP_time.InitCumul();
}
#line 2316 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 93:
#line 1783 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    driver.IP_time.Debut();
}
#line 2324 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 94:
#line 1788 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    driver.IP_time.Fin();
    std::cout << "time spent = " << driver.IP_time << std::endl;
}
#line 2333 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 95:
#line 1798 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    Variable<AMIClass>::ptr var(driver.var_stack.GetLastVar<AMIClass>());
    AMIClass::ptr c = var->Pointer();
    std::vector<AMIClass::ptr>* cl = new std::vector<AMIClass::ptr>();
    cl->push_back(c);
    (yylhs.value.class_list) = cl;
}
#line 2345 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 96:
#line 1807 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    Variable<AMIClass>::ptr var(driver.var_stack.GetLastVar<AMIClass>());
    AMIClass::ptr c = var->Pointer();
    std::vector<AMIClass::ptr>* cl = (yystack_[2].value.class_list);
    cl->push_back(c);
    (yylhs.value.class_list) = cl;
}
#line 2357 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 97:
#line 1817 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    std::list<std::string>* sl = new std::list<std::string>();
    sl->push_back(std::string((yystack_[0].value.astring)));
    delete [] (yystack_[0].value.astring);
    (yylhs.value.string_list) = sl;
}
#line 2368 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 98:
#line 1825 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    std::list<std::string>* sl = (yystack_[2].value.string_list);
    sl->push_back(std::string((yystack_[0].value.astring)));
    delete [] (yystack_[0].value.astring);
    (yylhs.value.string_list) = sl;
}
#line 2379 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 99:
#line 1834 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    ParamList* pl = new ParamList();
    (yylhs.value.paramlist) = pl;
}
#line 2388 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 100:
#line 1839 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
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
    (yylhs.value.paramlist) = pl;
}
#line 2408 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 101:
#line 1855 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description: temporary rule, added to simplify conversion of scripts.
     **/
    BasicVariable::ptr       var(driver.var_stack.GetLastBasicVar());
    if (!var.get()) {
        driver.error("Empty Variable as parameter !");
        YYABORT;
    }
    ParamList* pl =  (yystack_[2].value.paramlist);

    // Creating a new variable that points to the same value, and a slightly different name (with added "_ref"), comments are also copied.
    BasicVariable::ptr newvar(var->NewReference());

    pl->AddParam(newvar);
    (yylhs.value.paramlist) = pl;
}
#line 2430 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 102:
#line 1873 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
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
    (yylhs.value.paramlist) = pl;
}
#line 2449 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 103:
#line 1888 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    BasicVariable::ptr       var(driver.var_stack.GetLastBasicVar());
    if (!var.get()) {
        driver.error("Empty Variable as parameter !");
        YYABORT;
    }
    ParamList* pl =  (yystack_[3].value.paramlist);

    // Creating a new variable that points to the same value, and a slightly different name (with added "_ref"), comments are also copied.
    BasicVariable::ptr newvar(var->NewReference());

    pl->AddParam(newvar);
    (yylhs.value.paramlist) = pl;
}
#line 2468 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 104:
#line 1903 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
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
    (yylhs.value.paramlist) = pl;
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
#line 2507 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 105:
#line 1938 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description: it is now a new reference to the variable, so basically similar to &variable (should be removed?)...
    **/

    BasicVariable::ptr       var(driver.var_stack.GetLastBasicVar());
    if (!var.get()) {
        driver.error("Empty Variable as parameter !");
        YYABORT;
    }
    ParamList* pl =  (yystack_[2].value.paramlist);

    // Creating a new variable that points to the same value, and a slightly different name (with added "_ref"), comments are also copied.
    BasicVariable::ptr newvar(var->NewReference());

    pl->AddParam(newvar);
    (yylhs.value.paramlist) = pl;

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
#line 2549 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 106:
#line 1978 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    //      printf("no parameters \n");
    ParamListDecl* pl = new ParamListDecl;
    (yylhs.value.paramlistdecl) = pl;
}
#line 2559 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 107:
#line 1984 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    IdentifierInfo::ptr ident((yystack_[0].value.ident));
    //std::cout << "param_list_decl: T_NUM IDENTIFIER" << std::endl;
    //std::cout << ident->GetName().c_str() << std::endl;
    ParamListDecl* pl = new ParamListDecl;
    pl->AddParam(ident->GetName(),type_float);
    (yylhs.value.paramlistdecl) = pl;
}
#line 2572 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 108:
#line 1993 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    IdentifierInfo::ptr ident((yystack_[0].value.ident));
    ParamListDecl* pl = new ParamListDecl;
    pl->AddParam(ident->GetName(),type_ami_object);
    (yylhs.value.paramlistdecl) = pl;
}
#line 2583 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 109:
#line 2000 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    IdentifierInfo::ptr ident((yystack_[0].value.ident));
    ParamListDecl* pl = new ParamListDecl;
    pl->AddParam(ident->GetName(),type_any);
    (yylhs.value.paramlistdecl) = pl;
}
#line 2594 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 110:
#line 2007 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    IdentifierInfo::ptr ident((yystack_[0].value.ident));
    ParamListDecl* pl = new ParamListDecl;
    // type string is deprecated
    pl->AddParam(ident->GetName(),type_ami_object);
    (yylhs.value.paramlistdecl) = pl;
}
#line 2606 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 111:
#line 2015 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    IdentifierInfo::ptr ident((yystack_[0].value.ident));
    ParamListDecl* pl = (ParamListDecl*) (yystack_[3].value.paramlistdecl);
    pl->AddParam(ident->GetName(),type_ami_object);
    (yylhs.value.paramlistdecl) = pl;
}
#line 2617 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 112:
#line 2022 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    IdentifierInfo::ptr ident((yystack_[0].value.ident));
    ParamListDecl* pl = (ParamListDecl*) (yystack_[3].value.paramlistdecl);
    pl->AddParam(ident->GetName(),type_any);
    (yylhs.value.paramlistdecl) = pl;
}
#line 2628 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 113:
#line 2029 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    IdentifierInfo::ptr ident((yystack_[0].value.ident));
    ParamListDecl* pl = (ParamListDecl*) (yystack_[3].value.paramlistdecl);
    pl->AddParam(ident->GetName(),type_float);
    (yylhs.value.paramlistdecl) = pl;
}
#line 2639 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 114:
#line 2036 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    IdentifierInfo::ptr ident((yystack_[0].value.ident));
    ParamListDecl* pl = (ParamListDecl*) (yystack_[3].value.paramlistdecl);
    // type string is deprecated
    pl->AddParam(ident->GetName(),type_ami_object);
    (yylhs.value.paramlistdecl) = pl;
}
#line 2651 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 115:
#line 2047 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    (yylhs.value.astring)=(yystack_[0].value.astring);
}
#line 2659 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 116:
#line 2052 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    char* res;
    //printf("expr_string=%s*\n",$3);
    //printf("expr=%f*\n",$5);
    res = new char[strlen((yystack_[3].value.astring))+20];
    sprintf(res,(yystack_[3].value.astring),(yystack_[1].value.adouble));
    //          res[strlen($3)]=0;
    delete [] (yystack_[3].value.astring);
    //printf("res=%s*\n",res);
    (yylhs.value.astring)=res;
}
#line 2675 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 117:
#line 2065 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
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
    (yylhs.value.astring)= reschar;
}
#line 2702 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 118:
#line 2088 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description:
        Returns the name of the object instance to which this variable belongs. If this variable does not belong to an object, returns an empty string.
    **/
    BasicVariable::ptr  var(driver.var_stack.GetLastBasicVar());
    boost::shared_ptr<Variables> context = var->GetContext();
    if (context.get()) {
        char* res = new char[strlen(context->GetName().c_str())+1];
        strcpy(res,context->GetName().c_str());
        (yylhs.value.astring)= res;
    } else {
        char* empty_string;
        empty_string = new char[1];
        empty_string[0] = '\0';
        (yylhs.value.astring) = empty_string;
    }
}
#line 2725 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 119:
#line 2108 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    char* res = new char[GB_scripts_dir.size()+1];
    strcpy(res,GB_scripts_dir.c_str());
    (yylhs.value.astring)= res;
}
#line 2735 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 120:
#line 2120 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    (yylhs.value.ablock)=(yystack_[1].value.ablock);
    if (GB_debug)
        std::cerr << boost::format("ablock : %s")
        % (yystack_[1].value.ablock)->GetBody()
        << std::endl;
}
#line 2747 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 123:
#line 2135 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    ADD_VARSTACK_FLOAT((yystack_[0].value.adouble))
}
#line 2755 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 124:
#line 2139 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
    Description:
      returns the number of arguments in the command line
    **/
    ADD_VARSTACK_FLOAT(GB_argc-GB_num_arg_parsed)
}
#line 2767 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 125:
#line 2147 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
    Description:
      Line number in the current script
    **/
    ADD_VARSTACK_FLOAT(driver.yyiplineno)
}
#line 2779 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 126:
#line 2155 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
    Description:
      the constant Pi is set to
       3.14159265358979323846
    **/
    ADD_VARSTACK_FLOAT(3.14159265358979323846)
}
#line 2792 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 128:
#line 2165 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    setlocale(LC_NUMERIC, "C");
    float val=atof((yystack_[1].value.astring));
    ADD_VARSTACK_FLOAT(val);
    delete [] (yystack_[1].value.astring);
}
#line 2803 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 129:
#line 2172 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
    Description:
    Check for the existence of a variable, returns 0
    **/
    IdentifierInfo::ptr ident((yystack_[1].value.ident));
    float val=0;
    ADD_VARSTACK_FLOAT(val);
}
#line 2817 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 130:
#line 2182 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
    Description:
    Check for the existence of a variable, returns 1
    **/
    BasicVariable::ptr  var(driver.var_stack.GetLastBasicVar());
    float val=1;
    ADD_VARSTACK_FLOAT(val);
}
#line 2831 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 131:
#line 2192 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description: returns the value of the pixel format type in float format,
      identifier must be equal to 'val'
    **/
    IdentifierInfo::ptr ident((yystack_[0].value.ident));
    if (ident->GetName()=="val") {
        float val = (int) (yystack_[1].value.aint);
        ADD_VARSTACK_FLOAT(val);
    }
}
#line 2847 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 132:
#line 2208 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    BasicVariable::ptr var(driver.var_stack.GetLastBasicVar());
    if (var.get())
        if (var->IsNumeric())
            (yylhs.value.adouble)=var->GetValueAsDouble();
        else {
            (yylhs.value.adouble)=var->GetValueAsDouble();
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
        (yylhs.value.adouble) = 0;
    }
}
#line 2872 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 133:
#line 2232 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
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
        (yylhs.value.astring)= res;
    } else {
        driver.err_print("Expecting a string variable here ... \n");
        YYABORT;
    }
}
#line 2897 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 134:
#line 2257 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    driver.err_print(" char format is not available: use unsigned char \n");
    (yylhs.value.aint)=WT_UNSIGNED_CHAR;
}
#line 2906 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 135:
#line 2262 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    (yylhs.value.aint)=WT_UNSIGNED_CHAR;
}
#line 2914 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 136:
#line 2266 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    (yylhs.value.aint)=WT_SIGNED_SHORT;
}
#line 2922 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 137:
#line 2270 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    (yylhs.value.aint)=WT_UNSIGNED_SHORT;
}
#line 2930 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 138:
#line 2274 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    (yylhs.value.aint)=WT_SIGNED_INT;
}
#line 2938 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 139:
#line 2278 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    (yylhs.value.aint)=WT_UNSIGNED_INT;
}
#line 2946 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 140:
#line 2282 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    (yylhs.value.aint)=WT_SIGNED_LONG;
}
#line 2954 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 141:
#line 2286 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    (yylhs.value.aint)=WT_UNSIGNED_LONG;
}
#line 2962 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 142:
#line 2290 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    (yylhs.value.aint)=WT_FLOAT;
}
#line 2970 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 143:
#line 2294 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    (yylhs.value.aint)=WT_DOUBLE;
}
#line 2978 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 144:
#line 2298 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    (yylhs.value.aint)=WT_RGB;
}
#line 2986 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 145:
#line 2302 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    (yylhs.value.aint)=WT_FLOAT_VECTOR;
}
#line 2994 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 146:
#line 2306 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    (yylhs.value.aint)=(int)(yystack_[1].value.adouble);
}
#line 3002 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 147:
#line 2312 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
    Description: adds a reference to the variable in the stack
    **/
    BasicVariable::ptr  var(driver.var_stack.GetLastBasicVar());
    driver.var_stack.AddVar(var->NewReference());
}
#line 3014 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 148:
#line 2321 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description:
        primary_expr_string value to a string variable
      TODO: get completely rid of char* values
    **/
    string_ptr varstr(new std::string((yystack_[0].value.astring)));
    BasicVariable::ptr new_var = AMILabType<std::string>::CreateVarFromSmtPtr(varstr);
    driver.var_stack.AddVar(new_var);
}
#line 3029 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 154:
#line 2345 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
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
#line 3065 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 155:
#line 2378 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
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
#line 3101 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 158:
#line 2416 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
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
    IdentifierInfo::ptr ident((yystack_[0].value.ident));

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
#line 3149 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 159:
#line 2461 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description:
        Call to a function, returning a variable
    **/
    //cout << "call to variable T_OP_PAR param_list T_CL_PAR end_instr" << std::endl;
    // 1. check the variable type
    GET_CHECK_VARSTACK(var)
    ParamList::ptr param((yystack_[1].value.paramlist));

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
#line 3248 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 160:
#line 2556 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description: Postfix increment operator.
    **/
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar((*var)++);
}
#line 3260 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 161:
#line 2564 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description: Postfix decrement operator.
    **/
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar((*var)--);
}
#line 3272 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 162:
#line 2572 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description: Transpose operator, usefull for matrices
    **/
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->Transpose());
}
#line 3284 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 163:
#line 2581 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description: Array subscript operator.
    **/
    BasicVariable::ptr var2(driver.var_stack.GetLastBasicVar());
    BasicVariable::ptr var1(driver.var_stack.GetLastBasicVar());
    driver.var_stack.AddVar((*var1)[var2]);
}
#line 3297 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 165:
#line 2595 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description: Cast operator.
    **/
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->BasicCast( (yystack_[2].value.aint)));

}
#line 3310 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 166:
#line 2604 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Description: Logical negation (NOT) operator.
    **/
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(!(*var));
}
#line 3322 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 167:
#line 2612 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    //cout << "T_SUB  cast_var  " << std::endl;
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(-(*var));
}
#line 3332 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 168:
#line 2618 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(+(*var));
}
#line 3341 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 169:
#line 2623 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(++(*var));
}
#line 3350 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 170:
#line 2628 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(--(*var));
}
#line 3359 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 171:
#line 2633 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(*(*var));
}
#line 3368 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 172:
#line 2638 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_sin());
}
#line 3377 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 173:
#line 2643 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_cos());
}
#line 3386 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 174:
#line 2648 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_sqrt());
}
#line 3395 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 175:
#line 2653 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_fabs());
}
#line 3404 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 176:
#line 2658 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_round());
}
#line 3413 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 177:
#line 2663 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_floor());
}
#line 3422 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 178:
#line 2668 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_tan());
}
#line 3431 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 179:
#line 2673 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_asin());
}
#line 3440 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 180:
#line 2678 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_acos());
}
#line 3449 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 181:
#line 2683 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_atan());
}
#line 3458 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 182:
#line 2688 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_exp());
}
#line 3467 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 183:
#line 2693 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_log());
}
#line 3476 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 184:
#line 2698 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_ln());
}
#line 3485 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 185:
#line 2703 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var)
    driver.var_stack.AddVar(var->m_norm());
}
#line 3494 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 187:
#line 2713 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)*var2);
}
#line 3504 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 188:
#line 2719 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)/var2);
}
#line 3514 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 189:
#line 2725 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)%var2);
}
#line 3524 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 191:
#line 2736 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    BasicVariable::ptr res(*var1+var2);
    driver.var_stack.AddVar(res);
}
#line 3535 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 192:
#line 2743 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    BasicVariable::ptr res((*var1)-var2);
    driver.var_stack.AddVar(res);
}
#line 3546 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 194:
#line 2755 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)<<var2);
}
#line 3556 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 195:
#line 2762 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)>>var2);
}
#line 3566 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 197:
#line 2772 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)<var2);
}
#line 3576 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 198:
#line 2778 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)>var2);
}
#line 3586 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 199:
#line 2784 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)<=var2);
}
#line 3596 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 200:
#line 2790 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)>=var2);
}
#line 3606 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 202:
#line 2800 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)==var2);
}
#line 3616 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 203:
#line 2806 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)!=var2);
}
#line 3626 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 205:
#line 2816 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)&var2);
}
#line 3636 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 208:
#line 2830 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)|var2);
}
#line 3646 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 210:
#line 2840 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Descriptiopn: Logical AND operator
    **/
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)&&var2);
}
#line 3659 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 212:
#line 2853 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Descriptiopn: Logical XOR operator, for vectorial images it defines the pointwise vectorial product.
    **/
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)^var2);
}
#line 3672 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 214:
#line 2866 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Descriptiopn: Logical OR operator
    **/
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)||var2);
}
#line 3685 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 216:
#line 2879 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    /**
      Descriptiopn: Operation (cond?a:b) like in C/C++.
    **/
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    BasicVariable::ptr var(driver.var_stack.GetLastBasicVar());
    driver.var_stack.AddVar(var->TernaryCondition(var1,var2));
}
#line 3699 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 218:
#line 2893 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    //cout << "assignment_var" << std::endl;
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    if (var1->GetPtrCounter()==1) {
        // TODO: here ...
    }
    driver.var_stack.AddVar((*var1)=var2);
}
#line 3713 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 219:
#line 2903 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    //cout << "assignment_var" << std::endl;
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1).left_assign(var2));
}
#line 3724 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 220:
#line 2910 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)+=var2);
}
#line 3734 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 221:
#line 2916 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)-=var2);
}
#line 3744 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 222:
#line 2922 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)*=var2);
}
#line 3754 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;

  case 223:
#line 2928 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:847
    {
    GET_CHECK_VARSTACK(var2)
    GET_CHECK_VARSTACK(var1)
    driver.var_stack.AddVar((*var1)/=var2);
}
#line 3764 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
    break;


#line 3768 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:847
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state,
                                           yyempty ? yyempty_ : yyla.type_get ()));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyempty)
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyempty = true;
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyempty)
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyempty)
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, symbol_number_type yytoken) const
  {
    std::string yyres;
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yytoken) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (yytoken != yyempty_)
      {
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short int Parser::yypact_ninf_ = -237;

  const signed char Parser::yytable_ninf_ = -100;

  const short int
  Parser::yypact_[] =
  {
     403,  1354,  1239,  1239,  1239,  1239,  -237,  -237,  -237,  1239,
    1239,  1239,  -237,  -237,  -237,  -237,  -237,  -237,  -121,     4,
    -237,  1239,  1239,  1239,    -3,  1239,  -237,    19,  -237,  -237,
    -237,  -237,  -237,  -237,  -237,  -237,  -237,    21,   -53,   173,
    1239,    44,  -237,  -237,  -237,  -237,    67,    70,  1354,  1239,
      75,    78,  -237,  -237,  -237,  -237,    81,  -237,  -237,  -237,
    -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,    91,
      93,  -237,  -237,  1239,  1239,  1239,  1239,  1239,  1239,  1239,
    1239,  1239,  1239,  1239,  1239,  1239,  1239,    21,  -237,   195,
    -237,  1239,  1239,  1239,   110,   -24,    21,   133,   559,  -237,
    -237,  -237,  -237,  -237,  -237,  -237,     6,  -237,  -237,    82,
    -237,  -237,   109,  -237,    89,    32,   -28,    14,   -25,   118,
    -237,   119,    53,   136,   -16,   -27,  -237,  -237,    48,  -237,
    -237,  -237,  1239,  -237,   112,  -237,  -237,  -237,    10,   129,
    -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,
    -237,  -237,  -237,  -237,  1239,  -237,   195,  -237,  -237,  -237,
    -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,   195,
    1239,  1239,   112,  -237,  1239,  1239,  1239,  1239,  1239,  -237,
    -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,
    -237,  -237,  -237,   -78,  -237,   100,  -237,  -237,     6,  -237,
     173,  -237,  -237,   131,  -237,  -237,  -237,  -237,  -237,  -237,
    -237,  -237,  -237,     6,  -237,  -237,   715,  1239,  -237,  -237,
    -237,  -237,  1239,  1239,  1239,  1239,  1239,  1239,  1239,  1239,
    1239,  1239,  1239,  1239,  1239,  1239,  1239,  1239,  1239,  1354,
    1239,  1239,  1239,  1239,  1239,  1239,  1239,   846,  1239,  -237,
     134,   146,   143,   149,   151,   152,   157,   154,   163,   169,
    1239,  1239,  -237,  -237,   -21,  -237,   171,   172,   137,   174,
       2,     6,  -237,  1239,    16,  -237,  -237,   175,  -237,  -237,
    -237,    89,    89,    32,    32,   -28,   -28,   -28,   -28,    14,
      14,   -25,  -237,   119,    53,   167,   136,  -237,  -237,  -237,
    -237,  -237,  -237,  1108,   176,   177,   184,   185,   186,   187,
     192,   193,   188,  -237,  -237,  1239,  -237,  1239,  -237,   150,
    1239,  1239,  -237,  -237,  -237,    71,   196,  -237,  -237,  -237,
    -237,  -237,  -237,   -12,   -12,   153,  -237,  -237,  -237,   977,
    -237,  1354,  -237,  -237,  1239,  1239,  1239,  1239,  1239,  1239,
    1239,  1239,  1239,   200,   204,   205,   206,   207,  1239,  1239,
       6,     6,   183,   190,   191,   194,    37,    49,  -237,   203,
    1239,  -237,  -237,  -237,   209,   221,   222,   223,   225,   229,
     230,   232,  -237,  -237,  -237,  -237,  -237,  -237,   120,  -237,
    -237,  -237,  -237,  -237,  -237,  -237,  -237,    -1,  -237,   208,
       6,  -237,   243,  -237,  -237,   244,   245,   246,  -237,   247,
    1239,     6,     6,   217,   218,   219,   220,     6,  -237,  -237,
    1239,  1239,  1239,  1239,  1239,  -237,  -237,  -237,  -237,  -237,
    -237,  -237,  -237,  -237,  -237,  -237,  -237,  -237,     6,  -237
  };

  const unsigned char
  Parser::yydefact_[] =
  {
     127,   127,   127,   127,   127,   127,    21,    66,    67,   127,
     127,   127,    70,    71,   119,   124,    40,    20,     0,    81,
      73,   127,   127,   127,     0,   127,    80,     0,   115,   123,
     225,   151,   147,   226,   227,   228,   229,   230,   150,     0,
     127,     0,    42,    45,    43,    44,     0,     0,   127,   127,
       0,     0,    92,    93,   117,    94,     0,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,     0,
       0,   125,   126,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,     0,   121,     0,
      41,   127,   127,   127,     0,     0,     0,     0,   127,     4,
       8,    10,    14,    16,    18,    12,     0,   148,   152,     0,
     153,   157,   164,   186,   190,   193,   196,   201,   204,   206,
     207,   209,   211,   213,   215,   217,   224,    39,     0,   149,
     231,    38,   127,   150,   171,   166,   168,   167,     0,     0,
      68,   132,    69,    72,    74,    86,    83,    84,    85,    82,
      87,    88,    89,   133,   127,    79,     0,    35,    90,   233,
     234,   230,   232,    76,   237,   235,   236,    77,    78,     0,
     127,   127,   169,   170,   127,   127,   127,   127,   127,   172,
     173,   178,   179,   180,   181,   182,   184,   183,   174,   175,
     176,   177,   185,     0,    25,     0,   121,   121,     0,    37,
       0,    31,    29,   121,     1,     3,     5,     9,    11,    15,
      17,    19,    13,     0,     6,   131,   127,   127,   158,   160,
     161,   162,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   156,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     127,   127,   122,    26,     0,    36,     0,     0,     0,     0,
       0,     0,     7,   127,     0,   104,   100,     0,   187,   188,
     189,   191,   192,   195,   194,   198,   197,   199,   200,   202,
     203,   205,   208,   210,   212,     0,   214,   219,   220,   221,
     222,   223,   218,   127,   135,   136,   137,   138,     0,   140,
     141,   143,    50,    52,   165,   127,   118,   127,    46,     0,
     127,   127,    91,   146,   128,     0,   121,    97,   120,   121,
      27,   129,   130,   106,   106,     0,    33,   102,   159,   127,
     163,   127,    49,    48,   127,   127,   127,   127,   127,   127,
     127,   127,   127,     0,     0,     0,     0,     0,   127,   127,
       0,     0,     0,     0,     0,     0,     0,     0,    95,   121,
     127,   105,   101,   216,     0,     0,     0,     0,     0,     0,
       0,     0,    51,   116,    75,    47,   154,   155,   121,    98,
      24,    28,   107,   110,   108,   109,   121,     0,   121,     0,
       0,   103,    64,    58,    59,    55,    53,    56,    57,    60,
     127,     0,     0,     0,     0,     0,     0,     0,    96,    34,
     127,   127,   127,   127,   127,   121,    22,    32,   113,   114,
     111,   112,    30,    65,    62,    54,    63,    61,     0,    23
  };

  const short int
  Parser::yypgoto_[] =
  {
    -237,  -237,  -237,   -62,   178,   179,   180,  -237,  -237,   181,
     182,   189,   197,  -237,  -237,  -237,   -60,  -237,  -185,  -237,
    -237,  -237,    -4,   -23,   267,  -237,  -236,    25,    35,  -140,
    -128,   -50,  -104,    40,  -237,    45,    47,    50,    42,  -237,
    -237,  -167,     0,    -6,   -31,    38,     9,  -237,   -74
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,    97,    98,    99,   100,   101,   102,   269,   268,   103,
     104,   105,   106,   369,   326,   274,   366,   107,   194,   195,
     328,   108,   140,   152,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   141,   128,   129,   130,   165,   166,   167
  };

  const short int
  Parser::yytable_[] =
  {
     127,     6,   155,   295,   239,   139,   142,   143,   164,   131,
     154,   263,   264,   149,    17,   196,   260,   168,   271,   229,
     230,   150,   151,   153,   248,   153,   134,    30,     6,   144,
     338,   157,   156,   163,   201,   339,   206,   135,   136,   137,
     153,    17,   225,   226,   214,   241,   242,   243,   244,   245,
     158,   396,   145,   227,   228,    30,   397,   169,   164,   146,
     147,   148,   215,   398,   261,   233,   234,   246,   397,   198,
     199,   240,    30,   172,   297,   298,   299,   300,   301,   302,
     170,   193,   251,   171,   173,   281,   282,   197,   174,   202,
     203,   175,   153,   153,   176,   252,   222,   223,   127,   283,
     284,   224,   231,   232,   177,   373,   178,   131,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   216,   200,   217,   164,   267,   217,   329,   289,
     290,   250,   139,   204,   215,   235,   265,   236,   164,   237,
     238,   360,   247,   249,   361,   362,   363,   364,   365,   262,
     333,   272,   270,   315,   153,   259,   413,   414,   415,   416,
     316,   218,   317,   318,   218,   335,   253,   254,   322,   164,
     319,   320,   257,   258,   255,   256,   321,   323,   153,   285,
     286,   287,   288,   324,   400,   331,   332,   334,   341,   344,
     345,   340,   219,   220,   266,   219,   220,   346,   347,   348,
     349,   221,   330,   411,   221,   350,   351,   352,   355,   336,
     358,   412,   368,   417,   383,   359,   275,   277,   384,   385,
     386,   387,   399,   402,    30,   276,   159,   160,    33,    34,
      35,    36,   161,   162,   392,   403,   404,   405,   327,   406,
     438,   393,   394,   407,   408,   395,   409,   312,   159,   160,
      33,    34,    35,    36,   161,   162,   325,   278,   279,   280,
     410,   153,   420,   421,   422,   423,   424,   418,   428,   429,
     430,   431,   138,   337,   367,   291,   207,   208,   209,   210,
     211,   292,   296,   314,   293,   313,     0,   212,   294,     0,
       0,     0,     0,     0,   354,   213,     0,     0,   390,   391,
       0,     0,     0,   342,     0,     0,     0,     0,     0,     0,
       0,   353,   343,     0,     0,     0,     0,   153,     0,     0,
     356,   357,     0,     0,     0,     0,     0,     0,     0,   382,
       0,     0,     0,     0,     0,     0,   389,     0,   419,   371,
     374,   375,   376,   377,   378,   379,   380,   381,   372,   426,
     427,     0,   153,     0,   388,   432,     0,     0,     0,   153,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     401,     0,     0,     0,     0,     0,   439,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   433,   434,   435,
     436,   437,     0,    -2,     0,     0,   425,     0,     0,     0,
       1,     0,     2,     3,     4,     0,     5,     0,     0,     0,
     153,   153,   153,   153,   153,     6,     7,     8,     9,    10,
      11,    12,    13,     0,     0,    14,    15,    16,    17,    18,
      19,    20,     0,    21,    22,    23,     0,    24,    25,    26,
      27,    28,     0,    29,    30,     0,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,     0,    42,    43,
      44,    45,    46,    47,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    48,    49,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,     0,
      51,     0,    52,    53,    54,    55,     0,    56,    57,    58,
      59,    60,    61,    62,     0,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,     0,     0,    79,    80,    81,    82,    83,    84,    85,
      86,    87,     0,     0,     0,     0,    88,     0,    89,    90,
      91,     0,     0,     0,    92,    93,    94,     0,     0,   205,
       0,     0,     0,     0,    95,    96,     1,     0,     2,     3,
       4,     0,     5,     0,     0,     0,     0,     0,     0,     0,
       0,     6,     7,     8,     9,    10,    11,    12,    13,     0,
       0,    14,    15,    16,    17,    18,    19,    20,     0,    21,
      22,    23,     0,    24,    25,    26,    27,    28,     0,    29,
      30,     0,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,     0,    42,    43,    44,    45,    46,    47,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    48,    49,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    50,     0,    51,     0,    52,    53,
      54,    55,     0,    56,    57,    58,    59,    60,    61,    62,
       0,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,     0,     0,    79,
      80,    81,    82,    83,    84,    85,    86,    87,     0,     0,
       0,     0,    88,     0,    89,    90,    91,     0,     0,     0,
      92,    93,    94,     0,     0,     0,     0,     0,     0,     0,
      95,    96,     1,     0,     2,     3,     4,     0,     5,   -99,
       0,     0,   273,     0,   -99,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    14,    15,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    24,
       0,     0,    27,    28,     0,    29,     0,     0,    31,    32,
      33,    34,    35,    36,   161,   133,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,    49,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,     0,    51,     0,     0,     0,    54,     0,     0,     0,
      57,    58,    59,    60,    61,    62,     0,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,     0,     0,    79,    80,    81,    82,    83,
      84,    85,    86,     1,     0,     2,     3,     4,     0,     5,
       0,     0,     0,   303,     0,     0,     0,     0,    94,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    14,    15,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      24,     0,     0,    27,    28,     0,    29,     0,     0,    31,
      32,    33,    34,    35,    36,   161,   133,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    50,     0,    51,     0,     0,     0,    54,     0,     0,
       0,    57,   304,   305,   306,   307,    62,   308,   309,   310,
      65,   311,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,     0,     0,    79,    80,    81,    82,
      83,    84,    85,    86,     1,     0,     2,     3,     4,     0,
       5,     0,     0,     0,   370,     0,     0,     0,     0,    94,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    14,
      15,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    24,     0,     0,    27,    28,     0,    29,     0,     0,
      31,    32,    33,    34,    35,    36,   161,   133,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      48,    49,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,     0,    51,     0,     0,     0,    54,     0,
       0,     0,    57,    58,    59,    60,    61,    62,     0,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,     0,     0,    79,    80,    81,
      82,    83,    84,    85,    86,     1,     0,     2,     3,     4,
       0,     5,     0,     0,     0,     0,     0,     0,     0,     0,
      94,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      14,    15,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    24,     0,     0,    27,    28,     0,    29,     0,
       0,    31,    32,    33,    34,    35,    36,   161,   133,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    50,     0,    51,     0,     0,     0,    54,
       0,     0,     0,    57,    58,    59,    60,    61,    62,     0,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,     0,     0,    79,    80,
      81,    82,    83,    84,    85,    86,     1,     0,     2,     3,
       4,     0,     5,     0,     0,     0,     0,     0,     0,     0,
       0,    94,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    14,    15,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    24,     0,     0,    27,    28,     0,    29,
       0,     0,    31,    32,    33,    34,    35,    36,     0,   133,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    48,    49,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    50,     0,    51,     0,     0,     0,
      54,     0,     0,     0,    57,    58,    59,    60,    61,    62,
       0,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,   132,     0,    79,
      80,    81,    82,    83,    84,    85,    86,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    14,    15,     0,     0,
       0,     0,    94,     0,     0,     0,     0,     0,    24,     0,
       0,    27,    28,     0,    29,     0,     0,    31,    32,    33,
      34,    35,    36,     0,   133,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    50,
       0,    51,     0,     0,     0,    54,     0,     0,     0,    57,
      58,    59,    60,    61,    62,     0,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    94
  };

  const short int
  Parser::yycheck_[] =
  {
       0,    22,    25,   239,    20,     5,    10,    11,    39,     0,
      13,   196,   197,    19,    35,    89,    94,    40,   203,     5,
       6,    21,    22,    23,    14,    25,     1,    51,    22,   150,
      14,    37,    13,    39,    58,    19,    98,     2,     3,     4,
      40,    35,    10,    11,   106,    72,    73,    74,    75,    76,
     103,    14,    48,    81,    82,    51,    19,    13,    89,    55,
      56,    57,    52,    14,   142,    90,    91,    94,    19,    92,
      93,    87,    51,    48,   241,   242,   243,   244,   245,   246,
      13,    87,   156,    13,    49,   225,   226,    91,    13,    95,
      96,    13,    92,    93,    13,   169,     7,     8,    98,   227,
     228,    12,    88,    89,    13,   341,    13,    98,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    13,    13,    15,   156,   200,    15,   149,   233,
     234,   154,   132,     0,    52,    17,   198,    18,   169,    86,
       4,   326,    94,    14,   329,   157,   158,   159,   160,    49,
      13,   213,    21,    19,   154,   178,   157,   158,   159,   160,
      14,    52,    19,    14,    52,   163,   170,   171,    14,   200,
      19,    19,   176,   177,   174,   175,    19,    14,   178,   229,
     230,   231,   232,    14,   369,    14,    14,    13,    21,    13,
      13,    16,    83,    84,   200,    83,    84,    13,    13,    13,
      13,    92,   264,   388,    92,    13,    13,    19,    58,   271,
     139,   396,    59,   398,    14,    19,   216,   217,    14,    14,
      14,    14,    19,    14,    51,   216,    53,    54,    55,    56,
      57,    58,    59,    60,    51,    14,    14,    14,   261,    14,
     425,    51,    51,    14,    14,    51,    14,   247,    53,    54,
      55,    56,    57,    58,    59,    60,   260,   222,   223,   224,
     140,   261,    19,    19,    19,    19,    19,    59,    51,    51,
      51,    51,     5,   273,   334,   235,    98,    98,    98,    98,
      98,   236,   240,   248,   237,   247,    -1,    98,   238,    -1,
      -1,    -1,    -1,    -1,   317,    98,    -1,    -1,   360,   361,
      -1,    -1,    -1,   303,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   315,   303,    -1,    -1,    -1,    -1,   317,    -1,    -1,
     320,   321,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   352,
      -1,    -1,    -1,    -1,    -1,    -1,   359,    -1,   400,   339,
     344,   345,   346,   347,   348,   349,   350,   351,   339,   411,
     412,    -1,   352,    -1,   358,   417,    -1,    -1,    -1,   359,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     370,    -1,    -1,    -1,    -1,    -1,   438,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   420,   421,   422,
     423,   424,    -1,     0,    -1,    -1,   410,    -1,    -1,    -1,
       7,    -1,     9,    10,    11,    -1,    13,    -1,    -1,    -1,
     420,   421,   422,   423,   424,    22,    23,    24,    25,    26,
      27,    28,    29,    -1,    -1,    32,    33,    34,    35,    36,
      37,    38,    -1,    40,    41,    42,    -1,    44,    45,    46,
      47,    48,    -1,    50,    51,    -1,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    -1,    65,    66,
      67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    83,    84,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,    -1,
      97,    -1,    99,   100,   101,   102,    -1,   104,   105,   106,
     107,   108,   109,   110,    -1,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,    -1,    -1,   130,   131,   132,   133,   134,   135,   136,
     137,   138,    -1,    -1,    -1,    -1,   143,    -1,   145,   146,
     147,    -1,    -1,    -1,   151,   152,   153,    -1,    -1,     0,
      -1,    -1,    -1,    -1,   161,   162,     7,    -1,     9,    10,
      11,    -1,    13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    22,    23,    24,    25,    26,    27,    28,    29,    -1,
      -1,    32,    33,    34,    35,    36,    37,    38,    -1,    40,
      41,    42,    -1,    44,    45,    46,    47,    48,    -1,    50,
      51,    -1,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    -1,    65,    66,    67,    68,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    95,    -1,    97,    -1,    99,   100,
     101,   102,    -1,   104,   105,   106,   107,   108,   109,   110,
      -1,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,    -1,    -1,   130,
     131,   132,   133,   134,   135,   136,   137,   138,    -1,    -1,
      -1,    -1,   143,    -1,   145,   146,   147,    -1,    -1,    -1,
     151,   152,   153,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     161,   162,     7,    -1,     9,    10,    11,    -1,    13,    14,
      -1,    -1,    17,    -1,    19,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      -1,    -1,    47,    48,    -1,    50,    -1,    -1,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    84,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      95,    -1,    97,    -1,    -1,    -1,   101,    -1,    -1,    -1,
     105,   106,   107,   108,   109,   110,    -1,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,    -1,    -1,   130,   131,   132,   133,   134,
     135,   136,   137,     7,    -1,     9,    10,    11,    -1,    13,
      -1,    -1,    -1,    17,    -1,    -1,    -1,    -1,   153,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    -1,    -1,    47,    48,    -1,    50,    -1,    -1,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,
      84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    95,    -1,    97,    -1,    -1,    -1,   101,    -1,    -1,
      -1,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,    -1,    -1,   130,   131,   132,   133,
     134,   135,   136,   137,     7,    -1,     9,    10,    11,    -1,
      13,    -1,    -1,    -1,    17,    -1,    -1,    -1,    -1,   153,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    -1,    -1,    47,    48,    -1,    50,    -1,    -1,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    95,    -1,    97,    -1,    -1,    -1,   101,    -1,
      -1,    -1,   105,   106,   107,   108,   109,   110,    -1,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,    -1,    -1,   130,   131,   132,
     133,   134,   135,   136,   137,     7,    -1,     9,    10,    11,
      -1,    13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     153,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    -1,    -1,    47,    48,    -1,    50,    -1,
      -1,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    -1,    97,    -1,    -1,    -1,   101,
      -1,    -1,    -1,   105,   106,   107,   108,   109,   110,    -1,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,    -1,    -1,   130,   131,
     132,   133,   134,   135,   136,   137,     7,    -1,     9,    10,
      11,    -1,    13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   153,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    44,    -1,    -1,    47,    48,    -1,    50,
      -1,    -1,    53,    54,    55,    56,    57,    58,    -1,    60,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    95,    -1,    97,    -1,    -1,    -1,
     101,    -1,    -1,    -1,   105,   106,   107,   108,   109,   110,
      -1,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,    13,    -1,   130,
     131,   132,   133,   134,   135,   136,   137,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    -1,    -1,
      -1,    -1,   153,    -1,    -1,    -1,    -1,    -1,    44,    -1,
      -1,    47,    48,    -1,    50,    -1,    -1,    53,    54,    55,
      56,    57,    58,    -1,    60,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,
      -1,    97,    -1,    -1,    -1,   101,    -1,    -1,    -1,   105,
     106,   107,   108,   109,   110,    -1,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   153
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     7,     9,    10,    11,    13,    22,    23,    24,    25,
      26,    27,    28,    29,    32,    33,    34,    35,    36,    37,
      38,    40,    41,    42,    44,    45,    46,    47,    48,    50,
      51,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    65,    66,    67,    68,    69,    70,    83,    84,
      95,    97,    99,   100,   101,   102,   104,   105,   106,   107,
     108,   109,   110,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   143,   145,
     146,   147,   151,   152,   153,   161,   162,   168,   169,   170,
     171,   172,   173,   176,   177,   178,   179,   184,   188,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,    13,    60,   194,   195,   195,   195,   191,   209,
     189,   209,   189,   189,   150,    48,    55,    56,    57,   210,
     209,   209,   190,   209,    13,   190,    13,   210,   103,    53,
      54,    59,    60,   210,   211,   213,   214,   215,   190,    13,
      13,    13,   194,   195,    13,    13,    13,    13,    13,   195,
     195,   195,   195,   195,   195,   195,   195,   195,   195,   195,
     195,   195,   195,   210,   185,   186,   215,   189,   190,   190,
      13,    58,   210,   210,     0,     0,   170,   171,   172,   173,
     176,   177,   178,   179,   170,    52,    13,    15,    52,    83,
      84,    92,     7,     8,    12,    10,    11,    81,    82,     5,
       6,    88,    89,    90,    91,    17,    18,    86,     4,    20,
      87,    72,    73,    74,    75,    76,    94,    94,    14,    14,
     190,   215,   215,   189,   189,   209,   209,   189,   189,   190,
      94,   142,    49,   185,   185,   170,   210,   215,   175,   174,
      21,   185,   170,    17,   182,   209,   213,   209,   195,   195,
     195,   196,   196,   197,   197,   198,   198,   198,   198,   199,
     199,   200,   202,   203,   204,   193,   205,   208,   208,   208,
     208,   208,   208,    17,   106,   107,   108,   109,   111,   112,
     113,   115,   209,   212,   195,    19,    14,    19,    14,    19,
      19,    19,    14,    14,    14,   189,   181,   190,   187,   149,
     170,    14,    14,    13,    13,   163,   170,   209,    14,    19,
      16,    21,   209,   213,    13,    13,    13,    13,    13,    13,
      13,    13,    19,   189,   190,    58,   209,   209,   139,    19,
     185,   185,   157,   158,   159,   160,   183,   183,    59,   180,
      17,   209,   213,   193,   189,   189,   189,   189,   189,   189,
     189,   189,   190,    14,    14,    14,    14,    14,   189,   190,
     170,   170,    51,    51,    51,    51,    14,    19,    14,    19,
     185,   209,    14,    14,    14,    14,    14,    14,    14,    14,
     140,   185,   185,   157,   158,   159,   160,   185,    59,   170,
      19,    19,    19,    19,    19,   189,   170,   170,    51,    51,
      51,    51,   170,   190,   190,   190,   190,   190,   185,   170
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,   167,   168,   168,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     170,   170,   171,   171,   171,   171,   171,   172,   172,   174,
     173,   175,   173,   176,   176,   177,   178,   178,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   180,   180,   181,   181,   182,
     182,   182,   182,   182,   182,   182,   183,   183,   183,   183,
     183,   183,   183,   183,   183,   184,   184,   184,   184,   184,
     185,   186,   187,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   189,   190,   191,   191,   191,   191,   191,   191,
     191,   191,   191,   191,   191,   191,   191,   192,   192,   193,
     193,   193,   193,   193,   193,   193,   193,   194,   194,   194,
     194,   194,   194,   194,   195,   195,   195,   195,   195,   195,
     195,   195,   195,   195,   195,   195,   195,   195,   195,   195,
     195,   195,   195,   195,   195,   195,   196,   196,   196,   196,
     197,   197,   197,   198,   198,   198,   199,   199,   199,   199,
     199,   200,   200,   200,   201,   201,   202,   203,   203,   204,
     204,   205,   205,   206,   206,   207,   207,   208,   208,   208,
     208,   208,   208,   208,   209,   210,   211,   211,   211,   211,
     212,   213,   214,   214,   214,   215,   215,   215
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     0,     2,     1,     2,     2,     3,     1,     2,
       1,     2,     1,     2,     1,     2,     1,     2,     1,     2,
       1,     1,     8,    10,     6,     2,     3,     4,     6,     0,
       8,     0,     8,     4,     7,     2,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     6,     4,     4,
       3,     5,     3,     6,     8,     6,     6,     6,     6,     6,
       6,     8,     8,     8,     6,     8,     1,     1,     2,     2,
       1,     1,     2,     1,     2,     6,     2,     2,     2,     2,
       1,     1,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     4,     1,     1,     1,     1,     3,     1,     3,     0,
       1,     3,     2,     4,     1,     3,     0,     2,     2,     2,
       2,     4,     4,     4,     4,     1,     6,     1,     4,     1,
       3,     0,     0,     1,     1,     1,     1,     0,     4,     4,
       4,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     1,     1,     1,
       1,     1,     1,     1,     6,     6,     3,     1,     2,     4,
       2,     2,     2,     4,     1,     4,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     1,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     5,     1,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "LEX_ERROR", "T_EXP", "T_GT",
  "T_LT", "T_MULT", "T_DIV", "T_NOT", "T_ADD", "T_SUB", "T_MOD",
  "T_OP_PAR", "T_CL_PAR", "T_OP_BR", "T_CL_BR", "T_AND", "T_OR", "T_COMMA",
  "T_QUEST", "T_COLON", "T_SEMICOLON", "T_SetDebugOn", "T_SetDebugOff",
  "T_TraceScanning", "T_TraceParsing", "T_NoMessageDialog",
  "T_SetVerboseOn", "T_SetVerboseOff", "T_SetProgress", "T_SetStatusText",
  "T_GetScriptsDir", "T_argc", "T_emptyargs", "END_INSTRUCTION", "SHOW",
  "HELP", "QUIT", "T_HIDE", "PRINT", "PRINTN", "T_InfoDialog",
  "T_boost_format", "T_SPRINT", "ASHELL", "LS", "T_GetObjectName",
  "ASTRING", "ABLOCK", "NUMBER", "IDENTIFIER", "POINT_IDENTIFIER",
  "PROCESSED_VAR", "VAR_STRING", "VAR_C_FUNCTION", "VAR_C_PROCEDURE",
  "VAR_CLASS_MEMBER", "VAR_AMI_FUNCTION", "VAR_AMI_CLASS",
  "VAR_AMI_OBJECT", "T_del", "T_delvars", "T_Comments", "ENDOP",
  "T_global", "T_local", "T_global_new", "T_local_new", "T_wait",
  "T_schedule", "RIGHT_ASSIGN", "LEFT_ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN",
  "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN",
  "OR_ASSIGN", "RIGHT_OP", "LEFT_OP", "INC_OP", "DEC_OP", "PTR_OP",
  "AND_OP", "OR_OP", "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "TRANSPOSE_OP",
  "POINTWISE_MULT", "ASSIGN_OP", "T_MAX", "T_argmax", "T_MIN", "T_MEDIAN",
  "T_RestartTime", "T_InitTime", "T_TimeSpent", "T_EndTime", "T_info",
  "T_ProcessEvents", "T_CHAR", "T_UCHAR", "T_SHORT", "T_USHORT", "T_INT",
  "T_UINT", "T_BOOL", "T_LONG", "T_ULONG", "T_FLOAT", "T_DOUBLE", "T_RGB",
  "T_FLOAT_VECTOR", "T_BasicType", "T_atof", "T_LineNumber", "CONST_PI",
  "SIN", "COS", "TAN", "ASIN", "ACOS", "ATAN", "SINH", "COSH", "EXP", "LN",
  "LOG", "SQRT", "ABS", "ROUND", "FLOOR", "NORM", "FOR", "TO", "STEP",
  "ENDFOR", "T_IN", "T_REPEAT", "T_UNTIL", "T_WHILE", "T_BREAK", "IF",
  "THEN", "ELSE", "VARIABLES", "FUNCTION", "T_eval", "T_exists",
  "T_FileExists", "T_slice", "T_GenRead", "T_NUM", "T_STRING", "T_OBJECT",
  "T_VAR", "T_PROC", "T_Class", "T_public", "SHIFT_THERE", "prefix",
  "postfix", "$accept", "start", "list_commands", "end_instr", "loop_inst",
  "cond_inst", "proc_decl", "$@1", "$@2", "class_decl", "object_decl",
  "func_inst", "command", "var_ami_class_list", "exprstringlist",
  "param_list", "param_list_decl", "primary_expr_string", "instr_block",
  "begin_block", "end_block", "float_variable", "expr", "expr_string",
  "basic_type", "string_variable", "primary_var", "postfix_var",
  "prefix_var", "multiplicative_var", "additive_var", "shift_var",
  "relational_var", "equality_var", "and_var", "exclusive_or_var",
  "inclusive_or_var", "logical_and_var", "logical_xor_var",
  "logical_or_var", "conditional_var", "assignment_var", "expr_var",
  "identifier", "function_variable", "variable_without_assign",
  "unprocessed_variable", "processed_variable", "variable", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   514,   514,   515,   519,   519,   520,   521,   522,   522,
     523,   523,   524,   524,   525,   525,   526,   526,   527,   527,
     530,   531,   536,   559,   582,   634,   659,   695,   712,   740,
     739,   775,   774,   824,   863,   888,   909,   953,   963,   979,
    1013,  1021,  1031,  1045,  1059,  1073,  1083,  1099,  1117,  1132,
    1158,  1193,  1230,  1276,  1288,  1307,  1319,  1331,  1343,  1355,
    1367,  1379,  1394,  1413,  1432,  1443,  1461,  1465,  1469,  1473,
    1483,  1487,  1491,  1501,  1504,  1508,  1520,  1528,  1542,  1552,
    1563,  1571,  1583,  1624,  1634,  1644,  1653,  1707,  1719,  1731,
    1742,  1759,  1777,  1782,  1787,  1797,  1806,  1816,  1824,  1834,
    1838,  1854,  1872,  1887,  1902,  1937,  1978,  1983,  1992,  1999,
    2006,  2014,  2021,  2028,  2035,  2046,  2051,  2064,  2088,  2107,
    2117,  2128,  2130,  2134,  2138,  2146,  2154,  2163,  2164,  2171,
    2181,  2191,  2207,  2231,  2256,  2261,  2265,  2269,  2273,  2277,
    2281,  2285,  2289,  2293,  2297,  2301,  2305,  2311,  2320,  2334,
    2336,  2338,  2340,  2342,  2344,  2377,  2410,  2413,  2415,  2460,
    2555,  2563,  2571,  2580,  2592,  2594,  2603,  2611,  2617,  2622,
    2627,  2632,  2637,  2642,  2647,  2652,  2657,  2662,  2667,  2672,
    2677,  2682,  2687,  2692,  2697,  2702,  2711,  2712,  2718,  2724,
    2734,  2735,  2742,  2752,  2754,  2761,  2770,  2771,  2777,  2783,
    2789,  2798,  2799,  2805,  2814,  2815,  2824,  2828,  2829,  2838,
    2839,  2851,  2852,  2864,  2865,  2877,  2878,  2891,  2892,  2902,
    2909,  2915,  2921,  2927,  2936,  2942,  2955,  2956,  2957,  2958,
    2962,  2969,  2975,  2977,  2979,  2984,  2986,  2988
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166
    };
    const unsigned int user_token_number_max_ = 421;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yyip
#line 4739 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.cpp" // lalr1.cc:1155
#line 2991 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:1156

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

