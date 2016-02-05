// A Bison parser, made by GNU Bison 3.0.2.

// Skeleton interface for Bison LALR(1) parsers in C++

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

/**
 ** \file /home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.hpp
 ** Define the yyip::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

#ifndef YY_YYIP_HOME_KARL_PROJECTS_SOURCEFORGE_AMILAB_AMILAB_ENGINE_SRC_LANGUAGE_GENERATEDFLEXBISON_AMIENGINE_BISON_TAB_HPP_INCLUDED
# define YY_YYIP_HOME_KARL_PROJECTS_SOURCEFORGE_AMILAB_AMILAB_ENGINE_SRC_LANGUAGE_GENERATEDFLEXBISON_AMIENGINE_BISON_TAB_HPP_INCLUDED


# include <vector>
# include <iostream>
# include <stdexcept>
# include <string>
# include "stack.hh"
# include "location.hh"


#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif


namespace yyip {
#line 113 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.hpp" // lalr1.cc:372





  /// A Bison parser.
  class Parser
  {
  public:
#ifndef YYSTYPE
    /// Symbol semantic values.
    union semantic_type
    {
    #line 292 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/amiengine_bison.y" // lalr1.cc:372

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

#line 141 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.hpp" // lalr1.cc:372
    };
#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m);
      location_type location;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        END = 0,
        LEX_ERROR = 258,
        T_EXP = 259,
        T_GT = 260,
        T_LT = 261,
        T_MULT = 262,
        T_DIV = 263,
        T_NOT = 264,
        T_ADD = 265,
        T_SUB = 266,
        T_MOD = 267,
        T_OP_PAR = 268,
        T_CL_PAR = 269,
        T_OP_BR = 270,
        T_CL_BR = 271,
        T_AND = 272,
        T_OR = 273,
        T_COMMA = 274,
        T_QUEST = 275,
        T_COLON = 276,
        T_SEMICOLON = 277,
        T_SetDebugOn = 278,
        T_SetDebugOff = 279,
        T_TraceScanning = 280,
        T_TraceParsing = 281,
        T_NoMessageDialog = 282,
        T_SetVerboseOn = 283,
        T_SetVerboseOff = 284,
        T_SetProgress = 285,
        T_SetStatusText = 286,
        T_GetScriptsDir = 287,
        T_argc = 288,
        T_emptyargs = 289,
        END_INSTRUCTION = 290,
        SHOW = 291,
        HELP = 292,
        QUIT = 293,
        T_HIDE = 294,
        PRINT = 295,
        PRINTN = 296,
        T_InfoDialog = 297,
        T_boost_format = 298,
        T_SPRINT = 299,
        ASHELL = 300,
        LS = 301,
        T_GetObjectName = 302,
        ASTRING = 303,
        ABLOCK = 304,
        NUMBER = 305,
        IDENTIFIER = 306,
        POINT_IDENTIFIER = 307,
        PROCESSED_VAR = 308,
        VAR_STRING = 309,
        VAR_C_FUNCTION = 310,
        VAR_C_PROCEDURE = 311,
        VAR_CLASS_MEMBER = 312,
        VAR_AMI_FUNCTION = 313,
        VAR_AMI_CLASS = 314,
        VAR_AMI_OBJECT = 315,
        T_del = 316,
        T_delvars = 317,
        T_Comments = 318,
        ENDOP = 319,
        T_global = 320,
        T_local = 321,
        T_global_new = 322,
        T_local_new = 323,
        T_wait = 324,
        T_schedule = 325,
        RIGHT_ASSIGN = 326,
        LEFT_ASSIGN = 327,
        ADD_ASSIGN = 328,
        SUB_ASSIGN = 329,
        MUL_ASSIGN = 330,
        DIV_ASSIGN = 331,
        MOD_ASSIGN = 332,
        AND_ASSIGN = 333,
        XOR_ASSIGN = 334,
        OR_ASSIGN = 335,
        RIGHT_OP = 336,
        LEFT_OP = 337,
        INC_OP = 338,
        DEC_OP = 339,
        PTR_OP = 340,
        AND_OP = 341,
        OR_OP = 342,
        LE_OP = 343,
        GE_OP = 344,
        EQ_OP = 345,
        NE_OP = 346,
        TRANSPOSE_OP = 347,
        POINTWISE_MULT = 348,
        ASSIGN_OP = 349,
        T_MAX = 350,
        T_argmax = 351,
        T_MIN = 352,
        T_MEDIAN = 353,
        T_RestartTime = 354,
        T_InitTime = 355,
        T_TimeSpent = 356,
        T_EndTime = 357,
        T_info = 358,
        T_ProcessEvents = 359,
        T_CHAR = 360,
        T_UCHAR = 361,
        T_SHORT = 362,
        T_USHORT = 363,
        T_INT = 364,
        T_UINT = 365,
        T_BOOL = 366,
        T_LONG = 367,
        T_ULONG = 368,
        T_FLOAT = 369,
        T_DOUBLE = 370,
        T_RGB = 371,
        T_FLOAT_VECTOR = 372,
        T_BasicType = 373,
        T_atof = 374,
        T_LineNumber = 375,
        CONST_PI = 376,
        SIN = 377,
        COS = 378,
        TAN = 379,
        ASIN = 380,
        ACOS = 381,
        ATAN = 382,
        SINH = 383,
        COSH = 384,
        EXP = 385,
        LN = 386,
        LOG = 387,
        SQRT = 388,
        ABS = 389,
        ROUND = 390,
        FLOOR = 391,
        NORM = 392,
        FOR = 393,
        TO = 394,
        STEP = 395,
        ENDFOR = 396,
        T_IN = 397,
        T_REPEAT = 398,
        T_UNTIL = 399,
        T_WHILE = 400,
        T_BREAK = 401,
        IF = 402,
        THEN = 403,
        ELSE = 404,
        VARIABLES = 405,
        FUNCTION = 406,
        T_eval = 407,
        T_exists = 408,
        T_FileExists = 409,
        T_slice = 410,
        T_GenRead = 411,
        T_NUM = 412,
        T_STRING = 413,
        T_OBJECT = 414,
        T_VAR = 415,
        T_PROC = 416,
        T_Class = 417,
        T_public = 418,
        SHIFT_THERE = 419,
        prefix = 420,
        postfix = 421
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Internal symbol number.
    typedef int symbol_number_type;

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Copy constructor.
      basic_symbol (const basic_symbol& other);

      /// Constructor for valueless symbols.
      basic_symbol (typename Base::kind_type t,
                    const location_type& l);

      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    const semantic_type& v,
                    const location_type& l);

      ~basic_symbol ();

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

      /// Copy constructor.
      by_type (const by_type& other);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// -1 when this symbol is empty.
      symbol_number_type type_get () const;

      /// The token.
      token_type token () const;

      enum { empty = 0 };

      /// The symbol type.
      /// -1 when this symbol is empty.
      token_number_type type;
    };

    /// "External" symbols: returned by the scanner.
    typedef basic_symbol<by_type> symbol_type;


    /// Build a parser object.
    Parser (class Driver& driver_yyarg);
    virtual ~Parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

  private:
    /// This class is not copyable.
    Parser (const Parser&);
    Parser& operator= (const Parser&);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yytoken   the lookahead token type, or yyempty_.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         symbol_number_type yytoken) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const short int yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (int t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short int yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const short int yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short int yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const short int yytable_[];

  static const short int yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned char yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned char yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if YYDEBUG
  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned short int yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    // Debugging.
    int yydebug_;
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state ();

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s);

      /// Copy constructor.
      by_state (const by_state& other);

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// "empty" when empty.
      symbol_number_type type_get () const;

      enum { empty = 0 };

      /// The state.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, symbol_type& sym);
      /// Assignment, needed by push_back.
      stack_symbol_type& operator= (const stack_symbol_type& that);
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    void yypop_ (unsigned int n = 1);

    // Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 1507,     ///< Last index in yytable_.
      yynnts_ = 49,  ///< Number of nonterminal symbols.
      yyempty_ = -2,
      yyfinal_ = 204, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 167  ///< Number of tokens.
    };


    // User arguments.
    class Driver& driver;
  };



} // yyip
#line 633 "/home/karl/projects/Sourceforge/amilab/amilab_engine/src/Language/GeneratedFlexBison/amiengine_bison.tab.hpp" // lalr1.cc:372




#endif // !YY_YYIP_HOME_KARL_PROJECTS_SOURCEFORGE_AMILAB_AMILAB_ENGINE_SRC_LANGUAGE_GENERATEDFLEXBISON_AMIENGINE_BISON_TAB_HPP_INCLUDED