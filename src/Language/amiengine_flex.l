%{

// use NOMINMAX to avoid conflicts between windows.h min,max and std::min std::max ...
#ifndef NOMINMAX
  #define NOMINMAX
#endif

#include "IdentifierInfo.h"
//#include "Variable.hpp"
#include "AmiInstructionBlock.h"
#include "driver.h"

#include "scanner.h"

extern yyip::Driver GB_driver;

/* import the parser's token type into a local typedef */
typedef yyip::Parser::token token;
typedef yyip::Parser::token_type token_type;

/* By default yylex returns int, we use token_type. Unfortunately yyterminate
 * by default returns 0, which is not of token_type. */
#define yyterminate() return token::END

/* This disables inclusion of unistd.h, which is not available under Visual C++
 * on Win32. The C++ scanner uses STL streams instead. */
#define YY_NO_UNISTD_H


#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
//#include "messages.h"
//#include "fonctions.h"

#include "IdentifierInfo.h"
#include "Variable.hpp"
#include "AmiInstructionBlock.h"

#include "amiengine_bison.tab.hpp"
#include "VarContexts.hpp"
//#include "ami_function.h"
#include "VarArray.h"
#include <string>

#define LEX_DEBUG(expr) if (GB_debug) {expr}


//int          yyiplineno = 0;
//std::string  GB_current_file;

int yycharno = 0;
bool LexError = 0;

//extern  void yyiperror(const char*);
#include "LanguageBaseConfigure.h"
LanguageBase_VAR_IMPORT VarContexts  Vars;

yyip::Parser::token::yytokentype checkvar(
      yyip::Parser::semantic_type* yylval,
      const char* varname, int context=-1);

BasicVariable::ptr IsObject(  const char* varname, int context=-1);

using namespace std;


string* cpp_string;
//char string_buf[256];
//char *string_buf_ptr;

//#define MAXSIZE_BLOCK 10000
//char block_buf[MAXSIZE_BLOCK];
//char *block_buf_ptr;


AmiInstructionBlock* ami_block;

int  block_level = 0;
int comment_caller;



extern int       GB_argc;
extern std::string*  GB_argv;
extern int       GB_num_arg_parsed;


%}

/* enable c++ scanner class generation */
%option c++

%option prefix="yyip"
%option noyywrap
%option verbose

WS      [ \t]

%x str
%x block
%x block_str
%x comment
%x point

/* The following paragraph suffices to track locations accurately. Each time
 * yylex is invoked, the begin position is moved onto the end position. */
%{
#define YY_USER_ACTION  yylloc->columns(yyleng);
%}


identifier [a-zA-Z_]([A-Za-z0-9_])*

varid {identifier}(<{identifier}(,{identifier})*>)?

%%

 /* code to place at the beginning of yylex() */
%{
    // reset location
    yylloc->step();
%}

">>="                   return(token::RIGHT_ASSIGN);   /*{>>=,RIGHT_ASSIGN}*/
"<<="                   return(token::LEFT_ASSIGN);    /*{<<=,LEFT_ASSIGN}*/
"+="                    return(token::ADD_ASSIGN);     /*{+=,ADD_ASSIGN}*/
"-="                    return(token::SUB_ASSIGN);     /*{-=,SUB_ASSIGN}*/
"*="                    return(token::MUL_ASSIGN);     /*{*=,MUL_ASSIGN}*/
"/="                    {  return(token::DIV_ASSIGN); } /*{/=,DIV_ASSIGN}*/
"%="                    {  return(token::MOD_ASSIGN); } /*{%=,MOD_ASSIGN}*/
"&="                    {  return(token::AND_ASSIGN); } /*{&=,AND_ASSIGN}*/
"^="                    {  return(token::XOR_ASSIGN); } /*{ ^=,XOR_ASSIGN}*/
"|="                    {  return(token::OR_ASSIGN); } /*{|=,OR_ASSIGN}*/
">>"                    {  return(token::RIGHT_OP); } /*{>>,RIGHT_OP}*/
"<<"                    {  return(token::LEFT_OP); } /*{<<,LEFT_OP}*/
"++"                    {  return(token::INC_OP); } /*{++,INC_OP}*/
"--"                    {  return(token::DEC_OP); } /*{--,DEC_OP}*/
"->"                    {  return(token::PTR_OP); } /*{->,PTR_OP}*/
"&&"                    {  return(token::AND_OP); } /*{&&,AND_OP}*/
"||"                    {  return(token::OR_OP); } /*{||,OR_OP}*/
"<="                    {  return(token::LE_OP); } /*{<=,LE_OP}*/
">="                    {  return(token::GE_OP); } /*{>=,GE_OP}*/
"=="                    {  return(token::EQ_OP); } /*{==,EQ_OP}*/
"!="                    {  return(token::NE_OP); } /*{!=,NE_OP}*/


"'"  return(token::TRANSPOSE_OP); /*{',TRANSPOSE_OP}*/
"^"  return(token::T_EXP);  /*{^,T_EXP}*/
">"  return(token::T_GT);   /*{>,T_GT}*/
"<"  return(token::T_LT);   /*{<,T_LT}*/
"*"  return(token::T_MULT); /*{*,T_MULT}*/
".*"  return(token::POINTWISE_MULT);
"/"  return(token::T_DIV);  /*{/,T_DIV}*/
"!"  return(token::T_NOT); /*{!,T_NOT}*/
"+"  return(token::T_ADD); /*{+,T_ADD}*/
"-"  return(token::T_SUB); /*{-,T_SUB}*/
"%"  return(token::T_MOD); /*{%,T_MOD}*/

"="  return(token::ASSIGN_OP); /*{=,ASSIGN_OP}*/
"("  return(token::T_OP_PAR); /*{(,T_OP_PAR}*/
")"  return(token::T_CL_PAR); /*{),T_CL_PAR}*/
"["  return(token::T_OP_BR);  /*{[,T_OP_BR}*/
"]"  return(token::T_CL_BR);  /*{],T_CL_BR}*/
"&"  return(token::T_AND);    /*{&,T_AND}*/
"|"  return(token::T_OR);     /*{|,T_OR}*/

","  return(token::T_COMMA); /*{,,T_COMMA}*/
"?"  return(token::T_QUEST);  /*{?,T_QUEST}*/
":"  return(token::T_COLON); /*{:,T_COLON}*/


";"  return(token::T_SEMICOLON);  /*{;,T_SEMICOLON}*/


"."  {
  BEGIN(point);
}


<point>[[:blank:]] {
  yylloc->step();
}

<point>\\(\r\n|[\n\r]) {
  yylloc->lines(1);
  // yylloc->step();
  GB_driver.yyiplineno++;
}

<point>{identifier}   {
  BEGIN(0);
  yylval->ident = new IdentifierInfo;
  yylval->ident->SetName( YYText());
  yylval->ident->SetCreationContext(-1);
  return(token::POINT_IDENTIFIER);
}

LineNumber      return(token::T_LineNumber); /*{LineNumber,T_LineNumber}*/

BasicType        return(token::T_BasicType); /*{BasicType,T_BasicType}*/


GetObjectName  return(token::T_GetObjectName); /*{GetObjectName,T_GetObjectName}*/


CHAR          return(token::T_CHAR); /*{CHAR,T_CHAR}*/
UCHAR         return(token::T_UCHAR); /*{UCHAR,T_UCHAR}*/
SHORT         return(token::T_SHORT); /*{SHORT,T_SHORT}*/
USHORT        return(token::T_USHORT); /*{USHORT,T_USHORT}*/
INT           return(token::T_INT); /*{INT,T_INT}*/
UINT          return(token::T_UINT); /*{UINT,T_UINT}*/
FLOAT         return(token::T_FLOAT); /*{FLOAT,T_FLOAT}*/
LONG          return(token::T_LONG); /*{LONG,T_LONG}*/ /// New (added: 27/05/2010)
ULONG         return(token::T_ULONG); /*{ULONG,T_ULONG}*/ /// New (added: 27/05/2010)
BOOL          return(token::T_BOOL); /*{BOOL,T_BOOL}*/ /// New (added: 19/11/2010)
DOUBLE        return(token::T_DOUBLE); /*{DOUBLE,T_DOUBLE}*/
RGB           return(token::T_RGB); /*{RGB,T_RGB}*/
FLOAT_VECTOR  return(token::T_FLOAT_VECTOR); /*{FLOAT_VECTOR,T_FLOAT_VECTOR}*/
Comments      return(token::T_Comments); /*{Comments,T_Comments}*/

NUM           return(token::T_NUM); /*{NUM,T_NUM}*/
STRING        return(token::T_STRING); /*{STRING,T_STRING}*/
OBJECT        return(token::T_OBJECT); /*{OBJECT,T_OBJECT}*/
VAR           return(token::T_VAR); /*{VAR,T_VAR}*/

global        return(token::T_global);     /*{global,T_global}*/
global_new    return(token::T_global_new); /*{global_new,T_global_new}*/
local_new     return(token::T_local_new); /*{local_new,T_local_new}*/
local         return(token::T_local);      /*{local,T_local}*/
wait          return(token::T_wait);       /*{wait,T_wait}*/

Pi    {
//
//============================ Parse constants ====================
//
 return(token::CONST_PI);
} /*{Pi,CONST_P}*/


sin    {
//
//============================ Parse Math functions ====================
//
return(token::SIN);
} /*{sin,SIN}*/
cos    return(token::COS); /*{cos,COS}*/
tan    return(token::TAN); /*{tan,TAN}*/
asin   return(token::ASIN); /*{asin,ASIN}*/
acos   return(token::ACOS); /*{acos,ACOS}*/
atan   return(token::ATAN); /*{atan,ATAN}*/
exp    return(token::EXP); /*{exp,EXP}*/
ln     return(token::LN); /*{ln,LN}*/
log    return(token::LOG); /*{log,LOG}*/
cosh   return(token::COSH); /*{cosh,COSH}*/
sinh   return(token::SINH); /*{sinh,SINH}*/
sqrt   return(token::SQRT); /*{sqrt,SQRT}*/
abs    return(token::ABS); /*{abs,ABS}*/
norm   return(token::NORM); /*{norm,NORM}*/
round  return(token::ROUND); /*{round,ROUND}*/
floor  return(token::FLOOR); /*{floor,FLOOR}*/

proc       return(token::T_PROC);   /*{proc,T_PROC}*/
Class      return(token::T_Class);  /*{Class,T_Class}*/
public     return(token::T_public);  /*{public,T_public}*/

for    {
//
//============================ Parse Loops and Conditions ===============
//
return(token::FOR);
} /*{for,FOR}*/
in     return(token::T_IN); /*{in,T_IN}*/
to     return(token::TO); /*{to,TO}*/
step     return(token::STEP); /*{step,STEP}*/
endfor return(token::ENDFOR); /*{endfor,ENDFOR}*/

repeat return(token::T_REPEAT); /*{repeat,T_REPEAT}*/
while  return(token::T_WHILE); /*{while,T_WHILE}*/
until  return(token::T_UNTIL); /*{until,T_UNTIL}*/
break  return(token::T_BREAK); /*{break,T_BREAK}*/

if      return(token::IF); /*{if,IF}*/
else    return(token::ELSE); /*{else,ELSE}*/

sh                {
//
//============================ Parse Commands ===============
//
return(token::ASHELL);
} /*{sh,ASHELL}*/

SetDebugOn         return(token::T_SetDebugOn); /*{SetDebugOn,T_SetDebugOn}*/
SetDebugOff        return(token::T_SetDebugOff); /*{SetDebugOff,T_SetDebugOff}*/
TraceScanning      return(token::T_TraceScanning); /*{TraceScanning,T_TraceScanning}*/
TraceParsing       return(token::T_TraceParsing); /*{TraceParsing,T_TraceParsing}*/
SetVerboseOn       return(token::T_SetVerboseOn); /*{SetVerboseOn,T_SetVerboseOn}*/
SetVerboseOff      return(token::T_SetVerboseOff); /*{SetVerboseOff,T_SetVerboseOff}*/
NoMessageDialog    return(token::T_NoMessageDialog); /*{NoMessageDialog,T_NoMessageDialog}*/

GetScriptsDir      return(token::T_GetScriptsDir); /*{GetScriptDir,T_GetScriptDir}*/
SetProgress        return(token::T_SetProgress); /*{SetProgress,T_SetProgress}*/
SetStatusText      return(token::T_SetStatusText); /*{SetStatusText,T_SetStatusText}*/
Quit               return(token::QUIT); /*{Quit,QUIT}*/
quit               return(token::QUIT);


show               return(token::SHOW); /*Hide               return(token::T_HIDE); {Hide,T_HIDE}*/
hide               return(token::T_HIDE);
Help               return(token::HELP); /*{Help,HELP}*/
help               return(token::HELP);
ls                 return(token::LS); /*{ls,LS}*/
print              return(token::PRINT); /*{print,PRINT}*/
printn             return(token::PRINTN); /*{printn,PRINTN}*/
boost_format       return(token::T_boost_format); /*{boost_format,T_boost_format}*/
sprint             return(token::T_SPRINT); /*{sprint,T_SPRINT}*/
vars               return(token::VARIABLES); /*{vars,VARIABLES}*/
func               return(token::FUNCTION); /*{func,FUNCTION}*/
eval               return(token::T_eval); /*{eval,T_eval}*/

RestartTime       return(token::T_RestartTime); /*{RestartTime,T_RestartTime}*/
InitTime          return(token::T_InitTime); /*{InitTime,T_InitTime}*/
TimeSpent         return(token::T_TimeSpent); /*{TimeSpent,T_TimeSpent}*/
EndTime           return(token::T_EndTime); /*{EndTime,T_EndTime}*/ 

ProcessEvents    return(token::T_ProcessEvents); /*{ProcessEvents,T_ProcessEvents}*/

info              return(token::T_info); /*{info,T_info}*/

del               return(token::T_del); /*{del,T_del}*/
delvars           return(token::T_delvars); /*{delvars,T_delvars}*/

exists            { return(token::T_exists);       //FileExists        return(token::T_FileExists);  
// {FileExists,T_FileExists} 
} /*{exists,T_exists}*/

InfoDialog        return(token::T_InfoDialog); /*{InfoDialog,T_InfoDialog}*/

slice             return(token::T_slice);        /*{slice,T_slice}*/

argc              return(token::T_argc);         /*{argc,T_argc}*/
emptyargs         return(token::T_emptyargs);    /*{emptyargs,T_emptyargs}*/


([0-9]+"."[0-9]+((e|E)("+"|"-")?[0-9]+)?)|([0-9]+((e|E)("+"|"-")?[0-9]+))   {
//
//============================ Parse float ====================
//
//  setlocale(LC_NUMERIC,"C");
  setlocale(LC_NUMERIC, "C");
  yylval->adouble=atof(YYText());
  return(token::NUMBER);
}


[0-9]+   {
//
//============================ Parse interger ====================
//
//  setlocale(LC_NUMERIC,"C");
  setlocale(LC_NUMERIC, "C");
  char* endstr;
  yylval->adouble=strtol(YYText(),&endstr,0);
  return(token::NUMBER);
}

0x[0-9a-fA-F]+   {
//
//============================ Parse interger ====================
//
//  setlocale(LC_NUMERIC,"C");
  setlocale(LC_NUMERIC, "C");
  char* endstr;
  yylval->adouble=strtol(YYText(),&endstr,0);
  return(token::NUMBER);
}



\"          {
//
//
//============================ Parse string ====================
//
 cpp_string = new string();
 BEGIN(str);
 }

<str>\"      {
  // end of string
  // Not thread safe ...
  BEGIN(0);
  // add the \0 character, why ???...
  cpp_string->append(1,'\0');

  if((yylval->astring = new char[cpp_string->length()+1])==NULL) {
    GB_driver.yyiperror("string allocation error");
    return token::LEX_ERROR;
  }
  // first conversion, we keep char* for astring for now
  strcpy(yylval->astring, cpp_string->c_str());
  delete cpp_string;
  cpp_string = NULL;
  return(token::ASTRING);
}

<str>[\n\r]  {
  GB_driver.yyiperror("string termination error");
}

<str>\\n cpp_string->append(1,'\n');
<str>\\t cpp_string->append(1,'\t');
<str>\\r cpp_string->append(1,'\r');
<str>\\b cpp_string->append(1,'\b');
<str>\\f cpp_string->append(1,'\f');

<str>\\(.|\n\r) cpp_string->append(1,YYText()[1]);

<str>\# {
  cpp_string->append(YYText());
}

<str>[^\\\n\r\"]+ {
  cpp_string->append(YYText());
/*
  char *yptr = YYText();

  while (*yptr)
    *string_buf_ptr++ = *yptr++;
*/
}


"$#"  {
  yylval->adouble=GB_argc-GB_num_arg_parsed;
  return(token::NUMBER);
}

\$[0-9]   {
  // TODO allow more than 10 arguments!!
  int n,pos;
  n = YYText()[1]-'0';
  // TODO: check the position, improve the code here
  pos = n+GB_num_arg_parsed-1;

  if ((pos>=GB_argc)||(pos<0)) {
    boost::format fmt =
        boost::format("improcess.l \t invalid argument number %d / %d\n");
#ifdef str
  #undef str
      GB_driver.yyiperror( str(fmt % n % (GB_argc-GB_num_arg_parsed)).c_str() );
  #define str 1
#else
      GB_driver.yyiperror( str(fmt % n % (GB_argc-GB_num_arg_parsed)).c_str() );
#endif
    return token::LEX_ERROR;
//myss1.c_str() );
  }

  // we use GB_argv[n+1] because the first two arguments are the program and the script file
  std::string argument(GB_argv[pos]);
  
  if((yylval->astring = new char[argument.size()+1])==NULL) {
    GB_driver.yyiperror("string allocation error");
    return token::LEX_ERROR;
  }

  strcpy(yylval->astring,argument.c_str());

  return(token::ASTRING);

}

\{          {
//============================ Parse block ====================
//
  if (block_level==0) {
    ami_block = new AmiInstructionBlock();
    ami_block->SetStartingLine(GB_driver.yyiplineno);
    if (GB_debug )std::cerr << "Starting block at " <<  GB_driver.yyiplineno << std::endl;
    if (GB_debug )std::cerr << "Starting block at " << *yylloc << std::endl;
    block_level++;
    BEGIN(block);
    //printf("starting block level 0 at line %d\n",GB_driver.yyiplineno);
  }

}

<block>\"      {
  ami_block->GetBody().append(YYText());
  BEGIN(block_str);
}

<block_str>\" {
  ami_block->GetBody().append(YYText());
  BEGIN(block);
}

<block_str>[\n\r]  {
  GB_driver.yyiperror("string termination error");
}

<block_str>\\n          ami_block->GetBody().append(YYText());
<block_str>\\t          ami_block->GetBody().append(YYText());
<block_str>\\r          ami_block->GetBody().append(YYText());
<block_str>\\b          ami_block->GetBody().append(YYText());
<block_str>\\f          ami_block->GetBody().append(YYText());
<block_str>\\(.|\n\r)   ami_block->GetBody().append(YYText());
<block_str>\#           ami_block->GetBody().append(YYText());
<block_str>[^\\\n\r\"]+ ami_block->GetBody().append(YYText());


<block>\# {
//============================ Parse comment ====================
//
    comment_caller = block;
    BEGIN(comment);
    //printf("begin comment in block at line %d\n",GB_driver.yyiplineno);
}

<block>"//"  {
    comment_caller = block;
    BEGIN(comment);
    //    printf("begin comment in block \n");
}


<block>\r\n|[\r\n] {
  // dealing with windows end-of-lines ...
  yylloc->lines(1); yylloc->step();
  GB_driver.yyiplineno++;
  ami_block->GetBody().append(YYText());
}


<block>\{      {
  //printf("Enter block at line %d\n",GB_driver.yyiplineno);
  block_level++;
  ami_block->GetBody().append(1,'{');
}

<block>\}      {

  block_level--;
  if (block_level>0)
    ami_block->GetBody().append(1,'}');
  else {
    BEGIN(0);
    ami_block->GetBody().append(3,'\0');
//    cpp_block->append(1,YY_END_OF_BUFFER_CHAR);

//     printf("block = *%s*\n",block_buf);

/*
    length=ami_block->GetBody().length();

    if((yyiplval.astring = new char[length+3])==NULL)
      yyiperror(E_MEM);
    strcpy(yyiplval.astring,
            ami_block->GetBody().c_str());
    // why add those 3 characters ...??? lex is looking ahead several characters
    // risky in memory ...
    yyiplval.astring[length  ]=YY_END_OF_BUFFER_CHAR;
    yyiplval.astring[length+1]=YY_END_OF_BUFFER_CHAR;
    yyiplval.astring[length+2]=YY_END_OF_BUFFER_CHAR;
*/
    yylval->ablock = ami_block;
    // cannot use smart pointers in union ...
    // needs to be freed after use ...

    //ami_block = AmiInstructionBlock_ptr();
    return(token::ABLOCK);
  }
}


<block>[^\{\}] {
//  char *yptr = YYText();
//  while (*yptr)
//    *block_buf_ptr++ = *yptr++;
  ami_block->GetBody().append(YYText());
}


\# {
//============================ Parse comment ====================
//
    comment_caller = INITIAL;
    BEGIN(comment);
//  printf("begin comment \n");
}

"//"  {
    comment_caller = INITIAL;
    BEGIN(comment);
//  printf("begin comment \n");
}


<comment>\r\n|[\n\r] {
  //GB_driver.yyiplineno++;
//  printf("end comment from %d \n",comment_caller);
  // use unput to accept the end of the command if any
// std::cout << "<comment>\n [" << YYText() << "]" << std::endl;
// std::cout << "length = " << strlen(YYText()) << std::endl;
  if (strlen(YYText())==1) {
    unput(YYText()[0]);
  }
  if (strlen(YYText())==2) {
    unput(YYText()[1]);
    unput(YYText()[0]);
  }
  BEGIN(comment_caller);
}

<comment>.                 {
  // on ecrit ce qu'on veut dans un commentaire ...
  // sauver les commentaires dans une variable du driver??
}

local::{identifier}   {
//
//============================ Parse variable ====================
//
  int context = Vars.GetCurrentContextNumber();
  string text(YYText());
  string varname = text.substr(7);
  yyip::Parser::token::yytokentype result = checkvar(yylval,varname.c_str(),context);
  return result;
}

global::{identifier}   {
//
//============================ Parse variable ====================
//
  string text(YYText());
  string varname = text.substr(8);
  yyip::Parser::token::yytokentype result = checkvar(yylval,varname.c_str(),0);
  return result;
}

this::{identifier}   {
//
//============================ Parse variable ====================
//
  string text(YYText());
  string varname = text.substr(6);
  yyip::Parser::token::yytokentype 
      result = checkvar(yylval,varname.c_str(),
                        OBJECT_CONTEXT_NUMBER);
  return result;
}


::{identifier}   {
//
//============================ Parse variable ====================
//
  string text(YYText());
  string varname = text.substr(2);
  yyip::Parser::token::yytokentype 
      result = checkvar(yylval,varname.c_str(),
                        OBJECT_CONTEXT_NUMBER);
  return result;
}


::{identifier}->{identifier}   {
// TODO: can all the variable system to return only variable from lex !!!
// this rule is a hack
//
//============================ Parse variable in a given context ====================
//
  //cout << "::XX->XX variable in object ?" << std::endl;
  string text(YYText());
  size_t pos = text.find("->");
  string contextname = text.substr(2,pos-2);


  // check if contextname is really a context
  //cout << "looking for "<< contextname << std::endl;
  BasicVariable::ptr var = IsObject(contextname.c_str(),OBJECT_CONTEXT_NUMBER);
  if (var.get()) 
  {
    FILE_MESSAGE("Object found");
    string varname = text.substr(pos+2);

    Variable<AMIObject>::ptr objvar( boost::dynamic_pointer_cast<Variable<AMIObject> >(var));
    AMIObject::ptr object (objvar->Pointer());

    Variables::ptr previous_ocontext = Vars.GetObjectContext();
    Vars.SetObjectContext(object->GetContext());

    yyip::Parser::token::yytokentype result = checkvar(yylval,varname.c_str(),OBJECT_CONTEXT_NUMBER);

    Vars.SetObjectContext(previous_ocontext);
    return result;
  } else {
    std::string error_string =" lex error \t object not found ";
    GB_driver.yyiperror(error_string.c_str());
  }
}


{identifier}->{identifier}   {
//
//============================ Parse variable in a given context ====================
//
  //cout << "variable in object ?" << std::endl;
  string text(YYText());
  size_t pos = text.find("->");
  string contextname = text.substr(0,pos);


  // check if contextname is really a context
  BasicVariable::ptr var = IsObject(contextname.c_str());
  if (var.get()) 
  {
    FILE_MESSAGE("Object found");
    string varname = text.substr(pos+2);

    Variable<AMIObject>::ptr objvar( boost::dynamic_pointer_cast<Variable<AMIObject> >(var));
    AMIObject::ptr object ( objvar->Pointer());

    Variables::ptr previous_ocontext = Vars.GetObjectContext();
    Vars.SetObjectContext(object->GetContext());

    yyip::Parser::token::yytokentype result = checkvar(yylval,varname.c_str(),OBJECT_CONTEXT_NUMBER);

    Vars.SetObjectContext(previous_ocontext);
    return result;
  } else {
    std::string error_string =" lex error \t object not found ";
    GB_driver.yyiperror(error_string.c_str());
  }
}





{identifier}   {
//
//============================ Parse variable ====================
//
   return checkvar(yylval,YYText());
}


[[:blank:]]       {
                    yylloc->step();
                  }

\\(\r\n|[\n\r])  {
  // allow multiline command
  yylloc->lines(1); 
  //yylloc->step();
  GB_driver.yyiplineno++;
}

\r\n|[\n\r]                {
          //cout << "NEWLINE \n" << std::endl;
//          if (yyleng!=1)std::cout << " ******* yyleng = " << yyleng << "************" << std::endl; 
  yylloc->lines(1); yylloc->step();
  GB_driver.yyiplineno++;
  return(token::END_INSTRUCTION);
} /*{end-of-line,END_INSTRUCTION}*/

.                 {

    std::string error_string =" lex error \t invalid characters ";
    GB_driver.yyiperror(error_string.c_str());

  }




%%



//--------------------------------------------------
//       IsObject()
//--------------------------------------------------
//
BasicVariable::ptr IsObject( const char* varname, int context)
//
{
  BasicVariable::ptr var = Vars.GetVar(varname,context);
  if (var.get())
    if ((var->Type() == type_ami_object))
      return var;
    else 
      return BasicVariable::ptr();
  else
    return BasicVariable::ptr();
}


//--------------------------------------------------
//       checkvar()
//--------------------------------------------------
//
yyip::Parser::token::yytokentype checkvar(
  yyip::Parser::semantic_type* yylval,
  const char* varname,
  int context
)
//
{

  BasicVariable::ptr var = Vars.GetVar(varname,context);
  //std::cout << "Vars ptr = " << &Vars << std::endl;
  //std::cout << "Vars.GetCurrentContextNumber() = " 
  //          << Vars.GetCurrentContextNumber() << std::endl;
  //cout << "res = " << res << std::endl;
  if  ((!GB_driver.procedure_declaration) && var.get())   {

    // add the variable to the stack
    GB_driver.var_stack.AddVar(var);

    //yylval->variable = var.get();
    switch(var->Type()) {
        /*{$variable_image,VAR_IMAGE}*/
      case type_bool:
      case type_float:
      case type_long:
      case type_ulong:
      case type_short:
      case type_ushort:
      case type_double:
      case type_int:
      case type_uchar:
        return token::PROCESSED_VAR; /*{$PROCESSED_VAR,PROCESSED_VAR}*/
//      case type_surfdraw:         return token::VAR_SURFDRAW;
        /*{$variable_surfdraw,VAR_SURFDRAW}*/
//      case type_file:             return token::VAR_FILE;
        /*{$variable_file,VAR_FILE}*/
      case type_c_procedure:      return token::VAR_C_PROCEDURE;
        /*{$variable_c_procedure,VAR_C_PROCEDURE}*/
      case type_class_member:      return token::VAR_CLASS_MEMBER;
        /*{$variable_class_procedure,VAR_CLASS_MEMBER}*/
      case type_c_function: return token::VAR_C_FUNCTION;
        /*{$variable_c_function,VAR_C_FUNCTION}*/

      case type_ami_function:     return token::VAR_AMI_FUNCTION;
        /*{$variable_ami_function,VAR_AMI_FUNCTION}*/
      case type_ami_class:     return token::VAR_AMI_CLASS;
        /*{$variable_ami_class,VAR_AMI_CLASS}*/
      case type_ami_object:     return token::VAR_AMI_OBJECT;
        /*{$variable_ami_object,VAR_AMI_OBJECT}*/

      case type_string:           return token::VAR_STRING;
        /*{$variable_string,VAR_STRING}*/
      case type_array:       {
        Variable<VarArray>::ptr vararray( 
          boost::dynamic_pointer_cast<Variable<VarArray> >(var));
        VarArray::ptr array (vararray->Pointer());
        switch(array->Type()) {
          default:
            GB_driver.err_print("Array type not available \n");
        }
        break;
      }
      default:
        GB_driver.err_print("Variable type still not available \n");
        GB_driver.var_stack.GetLastBasicVar();
    }

  }

  yylval->ident = new IdentifierInfo;
  yylval->ident->SetName( varname);
  yylval->ident->SetCreationContext(context);
  return(token::IDENTIFIER);
}

/*** Additional Code ***/

namespace yyip {

Scanner::Scanner(std::istream* in,
     std::ostream* out)
    : yyipFlexLexer(in, out)
{
}

Scanner::~Scanner()
{
}

void Scanner::set_debug(bool b)
{
    yy_flex_debug = b;
}

}


/* This implementation of ExampleFlexLexer::yylex() is required to fill the
 * vtable of the class ExampleFlexLexer. We define the scanner's main yylex
 * function via YY_DECL to reside in the Scanner class instead. */

#ifdef yylex
#undef yylex
#endif

int yyipFlexLexer::yylex()
{
    std::cerr << "in yyipFlexLexer::yylex() !" << std::endl;
    return 0;
}

/* When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller. */

/*
int yyFlexLexer::yywrap()
{
    return 1;
}
*/







