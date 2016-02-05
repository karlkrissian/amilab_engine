
/*
  taken from http://idlebox.net/2007/flex-bison-cpp-example/
  Thanks to the authors:
    Timo Bingmann
  and http://ioctl.org/jan/bison/
*/
// $Id: driver.h 17 2007-08-19 18:51:39Z tb $
/** \file driver.h Declaration of the yyip::Driver class. */

#pragma once
#ifndef EXAMPLE_DRIVER_H
#define EXAMPLE_DRIVER_H

#include <fstream>
#include <string>
#include <vector>
#include <set>

#include "ami_function.h"
#include "Timing.hpp"

#include "VariableStack.h"
#include "ami_class.h"
#include "ami_object.h"
#include "DriverBase.h"

struct yy_buffer_state;

#include "LanguageConfigure.h"



/** The example namespace is used to encapsulate the three parser classes
 * example::Parser, example::Scanner and example::Driver */
namespace yyip {

/** The Driver class brings together all components. It creates an instance of
 * the Parser and Scanner classes and connects them. Then the input stream is
 * fed into the scanner object and the parser gets it's token
 * sequence. Furthermore the driver object is available in the grammar rules as
 * a parameter. Therefore the driver class contains a reference to the
 * structure into which the parsed data is saved. */
class Language_EXPORT Driver: public DriverBase
{
  DEFINE_CLASS(Driver);

protected:

    /**
     * Disable MessageDialogs
     **/
    bool nomessagedialog;

    /// Set of error messages to skip
    std::set<std::string> error_messages_to_skip;

public:

    //ImageStack        im_stack;
    VariableStack     var_stack;
    Timing             IP_time;

    // Dealing with output files
    std::ofstream language_debug_stream;

    std::ostream* err_output; // errors
    std::ostream* res_output; // result

    FILE_ptr       cmdhistory;
    std::string cmdhistory_filename;

    void SetNoMessageDialog(bool b) { nomessagedialog = b; }
    bool GetNoMessageDialog() { return nomessagedialog; }

    void init_debug_stream();
    void close_debug_stream();

    void AddSkipMessage(std::string mess) {
      error_messages_to_skip.insert(mess);
    }
    
    bool SkipMessage(std::string mess)  {
      return 
        (error_messages_to_skip.find(mess) != error_messages_to_skip.end());
    }
    
    void ClearSkipMessages() {
      error_messages_to_skip.clear();
    }
    
    void init_err_output();
    int  err_print(const char* st, const class location& l);
    int  err_print(const char* st);
    int  err_print(const std::string& st) 
    { 
      return this->err_print(st.c_str()); 
    }
    void close_err_output(void);

    void info_print(const char* st);
    void info_print(const std::string& st)
    {
      this->info_print(st.c_str()); 
    }


    void init_res_output();
    void res_print(const char* st);
    void res_print(const std::string& st) 
    { 
      this->res_print(st.c_str()); 
    }
    void close_res_output();

    void init_cmdhistory();
    void ws_print(const char* st);
    void ws_print(const std::string& st) 
    { 
      this->ws_print(st.c_str()); 
    }
    void close_cmdhistory();

    /// kept for transition from C flex-bison code
    /// should be removed later
    int yyiplineno;
    int yyiplineno_lastparser;
    std::string current_file;

    /// Access to last comments parsed
    std::string last_comments;

    /// flag for accepting variable names as identifiers
    /// when declaring the parameters of a function
    /// not thread-safe for the language ...
    bool  procedure_declaration;
    

public:

    /// construct a new parser driver context
    Driver();

    /// Destructor
    ~Driver();

    /// enable debug output in the flex scanner
    bool trace_scanning;

    /// enable debug output in the bison parser
    bool trace_parsing;

    void SetTraceScanning(bool val) { trace_scanning = val; }
    void SetTraceParsing(bool val) { trace_parsing = val; }

    /**
     * Check if we are running from the command line.
     * @return if we are running from the command line.
     */
    bool InConsole() { return in_console; }

    /// stream name (file or input stream) used for error messages.
    std::string streamname;

    /** Invoke the scanner and parser for a stream.
     * @param in	input stream
     * @param sname	stream name for error messages
     * @return		true if successfully parsed
     */
    bool parse_stream(std::istream& in,
		      const std::string& sname = "stream input",
          bool inconsole = false);

    /** Invoke the scanner and parser on an input string.
     * @param input	input string
     * @param sname	stream name for error messages
     * @return		true if successfully parsed
     */
    bool parse_string(const std::string& input,
		      const std::string& sname = "string stream");

    /** Invoke the scanner and parser on an input command line string
     * @param input input string
     * @param sname stream name for error messages
     * @return    true if successfully parsed
     */
    bool parse_commandline(const std::string& input,
          const std::string& sname = "string stream");

    /** Invoke the scanner and parser on a file. Use parse_stream with a
     * std::ifstream if detection of file reading errors is required.
     * @param filename	input file name
     * @return		true if successfully parsed
     */
    bool parse_file(const std::string& filename);

    /** Switch the parser to an instruction block
    * @param b instruction block
    */
    bool parse_block( const AmiInstructionBlock::ptr& b );

    /** call to a language function
    * @param v pointer to the AMIFunction object, unfortunately, we could not use smart pointers here (a little bit complicate to understand ... but related to button callback)
    * @param param list of parameters
    */
    BasicVariable::ptr yyip_call_function( AMIFunction* v, 
              const ParamList::ptr& param = ParamList::ptr() );

    BasicVariable::ptr yyip_call_function( AMIFunction::ptr& v, 
              const ParamList::ptr& param = ParamList::ptr() )
    {
      return yyip_call_function( v.get(), param);
    }

    /**
     * Recursively calls itself with its parent class if any, anf then executes the body block of the class within the current environment. TODO: take care about potential loops here 
     * @param oclass 
     */
    void ParseClassBody(const AMIClass::ptr& oclass);

    /** instanciate an object of a given class
    * @param f smart pointer to the function
    */
    void yyip_instanciate_object(  AMIClass::ptr& oclass,
      AMIObject::ptr& object);

    /** switching to a script file
    * @param filename
    */
    bool parse_script(  const char* filename);

    void print_buf_info(yy_buffer_state* b);

    void yyiperror(const char *s);

   // To demonstrate pure handling of parse errors, instead of
    // simply dumping them on the standard error output, we will pass
    // them to the driver using the following two member functions.

    /** Error handling with associated line number. This can be modified to
     * output the error e.g. to a dialog box. */
    int error(const class location& l, const std::string& m);

    /** General error handling. This can be modified to output the error
     * e.g. to a dialog box. */
    int error(const std::string& m);

    /** Return the current filename */
    std::string GetCurrentFilename() 
    { 
      return current_file; 
    }

    /** Pointer to the current lexer instance, this is used to connect the
     * parser to the scanner. It is used in the yylex macro. */
    class Scanner* lexer;

    void SetCurrentFile( const char* cf )
    {
      //std::cout << "Setting current file to " << cf << std::endl;
      this->current_file = cf;
    }

    /** Reference to the calculator context filled during parsing of the
     * expressions. */
    //class CalcContext& calc;
};

} // namespace yyip

#endif // EXAMPLE_DRIVER_H
