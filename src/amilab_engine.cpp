/*
/* 
 * AMILab engine
 * 
 * Karl Krissian
 * 04/2015
 * 
 */


#include "AMILabEngineConfig.h"

#include <iostream>
#include <cstdio>

#include <sys/stat.h>
#ifndef WIN32
#include <unistd.h>
#endif

#include "VarContexts.hpp"
#include <boost/format.hpp>

#ifdef __APPLE__
  #include <ApplicationServices/ApplicationServices.h>
//  #include "amilab_logo_new_32x32_alpha.xpm"
#endif

#include "driver.h"

#include "common_global_import.h"
#include "amilab_global_import.h"

#include "LanguageConfigure.h"
Language_VAR_IMPORT yyip::Driver  GB_driver;

#include "DriverBase.h"
#include "LanguageBaseConfigure.h"
LanguageBase_VAR_IMPORT DriverBase::ptr  GB_DriverBase;

#include "LanguageBaseConfigure.h"
LanguageBase_VAR_IMPORT VarContexts  Vars;

#include "TypeConversion.h"
// global variable list all existing types, to deal with type conversion
LanguageBase_VAR_IMPORT TypeConversion GB_typeconversions;

extern Variable<int>::ptr nullvar;

char program[80];

#include "Wrapping/WrapCommon/Generated/addwrap_common.h"

#include "TTY/tty_curses/tty_func.h"
#include <ctype.h>

#include <ncurses.h>
#include "TTY/ncstream.hpp"

#ifdef USE_STD_REGEX
  #include <regex>
  #define REGEX std
#else
  #include <boost/regex.hpp>
  #define REGEX boost
#endif


class NcursesWindow
{
public:
  NcursesWindow() : 
    _screen_xmin(0), _screen_ymin(0), 
    _screen_xmax(80), _screen_ymax(100),
    _max_lines(1000), _max_cols(100),
    _start_line(0), _start_col(0),
    _cursor_x(0), _cursor_y(0)
  {
    _pad = NULL;
  }
  
  ~NcursesWindow()
  {
    delwin(_pad);
    delwin(_border);
  }
  
  WINDOW* GetWin()
  {
    return _pad;
  }
  
  void SetScreenPosition( int ymin, int xmin, int ymax, int xmax)
  {
    _screen_ymin = ymin;
    _screen_xmin = xmin;
    _screen_xmax = xmax;
    _screen_ymax = ymax;
  }
  
  void ScrollUp( const int& jump = 1)
  {
    _start_line -= jump;
    if (_start_line<0) _start_line =0;
  }
  
  void ScrollDown( const int& jump = 1)
  {
    _start_line += jump;
    if (_start_line>_max_lines) _start_line = _max_lines;
  }
  
  void SetSize( int nlines, int ncols)
  {
    _max_lines = nlines;
    _max_cols  = ncols;
  }
  
  void Create()
  {
    _border = newwin(_screen_ymax-_screen_ymin+1,
                     _screen_xmax-_screen_xmin+1,
                     _screen_ymin,_screen_xmin);
    box(_border,0,0);
            /* 0, 0 gives default characters 
             * for the vertical and horizontal
             * lines      */
    wrefresh(_border);
    _pad = newpad(_max_lines,_max_cols);
  }
  
  void Display()
  {
    
    touchwin(_pad);
    prefresh( _pad,
              _start_line, _start_col,
              _screen_ymin+1, _screen_xmin+1,
              _screen_ymax-1, _screen_xmax-1);
  }
  
  void SetCursorPos(int x, int y)
  {
    _cursor_x = x+1;
    _cursor_y = y+1;
    wmove(_border, _cursor_y,  _cursor_x);
  }
  
  void RefreshCusor()
  {
    move( _screen_ymin+_cursor_y, _screen_xmin +_cursor_x);
    refresh();
  }
  
  int GetCursorX()
  {
    int cx,cy;
    getyx(_border, cy, cx);
    return cx-1;
  }
  
  int GetCursorY()
  {
    int cx,cy;
    getyx(_border, cy, cx);
    return cy-1;
  }
 
  void GetCursorXY( int& cx, int& cy)
  {
    getyx(_border, cy, cx);
    cx--;
    cy--;
  }
  
  bool IsInside(int x, int y)
  {
    return  (x>_screen_xmin)&&(x<_screen_xmax)&&
            (y>_screen_ymin)&&(y<_screen_ymax);
  }
  
private:
  WINDOW* _border;
  WINDOW* _pad;
  int _screen_xmin;
  int _screen_xmax;
  int _screen_ymin;
  int _screen_ymax;
  
  int _max_lines;
  int _max_cols;
  
  int _start_line;
  int _start_col;
  
  int _cursor_x;
  int _cursor_y;
};


WINDOW *create_newwin(int height, int width, int starty, int startx, bool use_box = true)
{ WINDOW *local_win;

  local_win = newwin(height, width, starty, startx);
  if (use_box)
    box(local_win, 0 , 0);    /* 0, 0 gives default characters 
            * for the vertical and horizontal
            * lines      */
  wrefresh(local_win);    /* Show that box    */

  return local_win;
}

void destroy_win(WINDOW *local_win)
{ 
  /* box(local_win, ' ', ' '); : This won't produce the desired
   * result of erasing the window. It will leave it's four corners 
   * and so an ugly remnant of window. 
   */
  wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
  /* The parameters taken are 
   * 1. win: the window on which to operate
   * 2. ls: character to be used for the left side of the window 
   * 3. rs: character to be used for the right side of the window 
   * 4. ts: character to be used for the top side of the window 
   * 5. bs: character to be used for the bottom side of the window 
   * 6. tl: character to be used for the top left corner of the window 
   * 7. tr: character to be used for the top right corner of the window 
   * 8. bl: character to be used for the bottom left corner of the window 
   * 9. br: character to be used for the bottom right corner of the window
   */
  wrefresh(local_win);
  delwin(local_win);
}
/*
//-----------------------------------------
bool CheckEnvDir(const wxString& envname, wxString& res, const wxString& lookforfile = wxEmptyString)
{

  // Looking for the environment variable
  bool foundenv = wxGetEnv(envname,&res);
  if (!foundenv) {
    std::cerr << "Environment variable " << envname << " not defined. " << std::endl;
  } else
  if (!wxDir::Exists(res)) {
    std::cerr << "Error accessing directory " << res.mb_str();
  } else
    return true;

  // First check relative to the executable path
  wxFileName execpath(wxStandardPaths::Get().GetExecutablePath());
  // if last directory is bin, remove it
  wxString LastDir = execpath.GetDirs().Last();
  if (LastDir.MakeUpper()==wxT("BIN")) {
      execpath.RemoveLastDir();
      execpath.AppendDir(_T("share"));
      execpath.AppendDir(GetwxStr("amilab-")+GetwxStr(AMILAB_VERSION));
  }
  res = execpath.GetPath(wxPATH_GET_VOLUME | wxPATH_GET_SEPARATOR);
 std::cout  << "looking for the file " << lookforfile.mb_str() << " in " << res.mb_str() << std::endl;
  wxDir directory(res);
  if (lookforfile != wxEmptyString) {
    wxString path = directory.FindFirst(res,lookforfile);
    if (path!=wxEmptyString) {
        res = wxFileName(path).GetPath(wxPATH_GET_VOLUME | wxPATH_GET_SEPARATOR);
        return true;
    }
  }


  std::cerr << "file not found, set the path manually from the interface." << std::endl;

  res=::wxGetCwd();
  std::cerr << " , set to " << res << std::endl
        << "check the environment variable " << envname.mb_str() << std::endl;
  return false;

}
*/


//--------------------------------------------
void AddWrapBasicTypes(AMIObject::ptr& obj)
{

//  WrapClass_VarVector::AddVar_VarVector( obj->GetContext());
  wrap_common_classes(obj->GetContext());
  wrap_common_functions(obj->GetContext());
  

  BasicVariable::ptr std_cout_var = 
    AMILabType<std::ostream>::CreateVar(&std::cout,true);
  obj->GetContext()->AddVar("cout", std_cout_var, obj->GetContext());

  BasicVariable::ptr std_cerr_var = 
    AMILabType<std::ostream>::CreateVar(&std::cerr,true);
  obj->GetContext()->AddVar("cerr", std_cerr_var, obj->GetContext());
  
  BasicVariable::ptr std_clog_var = 
    AMILabType<std::ostream>::CreateVar(&std::clog,true);
  obj->GetContext()->AddVar("clog", std_clog_var, obj->GetContext());

//  WrapClass_File::AddVar_File( obj->GetContext());

  BasicVariable::ptr vartrue  = AMILabType<bool>::CreateVar(true);
  BasicVariable::ptr varfalse = AMILabType<bool>::CreateVar(false);

  obj->GetContext()->AddVar( "true",vartrue,obj->GetContext());
  obj->GetContext()->AddVar( "false",varfalse,obj->GetContext());

  // NULL variable
  obj->GetContext()->AddVar( "NULL",nullvar,obj->GetContext());
  
}


//
void  RegisterBuiltinTypes()
{
    
    // register basic types
    GB_typeconversions.RegisterType<bool>           ();
    GB_typeconversions.RegisterType<unsigned char>  ();
    GB_typeconversions.RegisterType<float>          ();
    GB_typeconversions.RegisterType<double>         ();
    GB_typeconversions.RegisterType<long>           ();
    GB_typeconversions.RegisterType<int>            ();
    GB_typeconversions.RegisterType<short>          ();
    GB_typeconversions.RegisterType<unsigned long>  ();
    GB_typeconversions.RegisterType<unsigned short> ();
    GB_typeconversions.RegisterType<AMIFunction>    ();
    GB_typeconversions.RegisterType<AMIClass>       ();

    
}


/**
 * Default wrapping
 */
void AddWrapImports()
{

  // Language
  {
    // Create new instance of the class
    AMIObject::ptr amiobject(new AMIObject);
    amiobject->SetName("Language");

    // Add context to builtin as 'default' context
    Vars.GetBuiltinContext()->AddVar<AMIObject>( amiobject->GetName().c_str(), 
                                                 amiobject,
                                                 Vars.GetBuiltinContext());
    Vars.GetBuiltinContext()->AddDefault(amiobject->GetContext());
  }

  
  // Structures
  {
    // Create new instance of the class
    AMIObject::ptr amiobject(new AMIObject);
    amiobject->SetName("DataStructures");

    // Add Wrapped classes and functions
    AddWrapBasicTypes(      amiobject);

    // Add context to builtin as 'default' context
    Vars.GetBuiltinContext()->AddVar<AMIObject>( amiobject->GetName().c_str(), 
                                                 amiobject,
                                                 Vars.GetBuiltinContext());
    Vars.GetBuiltinContext()->AddDefault(amiobject->GetContext());
  }

  // Libraries
  {
    // Create new instance of the class
    AMIObject::ptr amiobject(new AMIObject);
    amiobject->SetName("Libraries");



    // Add context to builtin as 'default' context
    Vars.GetBuiltinContext()->AddVar<AMIObject>( amiobject->GetName().c_str(), 
                                                 amiobject,
                                                 Vars.GetBuiltinContext());
    Vars.GetBuiltinContext()->AddDefault(amiobject->GetContext());
  }

  // Others
  {
    // Create new instance of the class
    AMIObject::ptr amiobject(new AMIObject);
    amiobject->SetName("Others");

    // Add context to builtin as 'default' context
    Vars.GetBuiltinContext()->AddVar<AMIObject>( amiobject->GetName().c_str(), 
                                                 amiobject,
                                                 Vars.GetBuiltinContext());
    Vars.GetBuiltinContext()->AddDefault(amiobject->GetContext());
  }

}


// temporary use of global variables to convert the code from AMILab
bool in_completion = false;
int  completion_count = 0;
std::string completion_lastcommand;
int cursor_x_last_command;
boost::shared_ptr<std::vector<std::string> > completions( new std::vector<std::string>());


//------------------------------------------------------------------------------
void DisplayCompletion(std::string& last_command, int& cursor_x)
{
   last_command =  completion_lastcommand+(*completions)[completion_count];
   cursor_x = cursor_x_last_command + (*completions)[completion_count].size();
}

//------------------------------------------------------------------------------
void ProcessTab(std::string& last_command, int& cursor_x)
{
  if (in_completion) {
    completion_count = (completion_count+1)%(completions->size());
    //printf("in_completion %d / %d \n",completion_count, completions->GetCount());
    DisplayCompletion(last_command, cursor_x);
    return;
  }

  // get the last word
  std::string   alltext;
  alltext = last_command;
  
  if (alltext.empty()) {
    std::cerr << "empty string for completion" << std::endl;
    return;
  }
  
  std::string last_variable;
  REGEX::smatch sm;    // same as std::match_results<string::const_iterator> sm;
  
  try {
//     std::regex expr(".*[^[:alnum:]_\\.\\:]((global\\:\\:)?([_[:alpha:]][_[:alnum:]]*\\.)*([_[:alpha:]][_[:alnum:]]*)?)$");
//     REGEX::regex expr(".*[^[:alnum:]_\\.\\:]((global\\:\\:)?([_[:alpha:]][_[:alnum:]]*\\.)*([_[:alpha:]][_[:alnum:]]*)?)$", boost::regex::extended);
    // on est déjà sur la derniere commande, donc inutile de virer le texte antérieur
    REGEX::regex expr("(.*[^[:alnum:]_\\.\\:]|^)((global\\:\\:)?([_[:alpha:]][_[:alnum:]]*\\.)*([_[:alpha:]][_[:alnum:]]*)?)$", boost::regex::extended);

    
   // (.*[^[:alnum:]_\.\:]|^)((global\:\:)?([_[:alpha:]][_[:alnum:]]*\.)*([_[:alpha:]][_[:alnum:]]*)?)$
  //   if (!last_variable_regex.IsValid()) {
  //    std::cout << "Expression not valid !!!" << std::endl;
  //   }
  
  
    REGEX::regex_match(last_command,sm,expr);
  }
  catch (REGEX::regex_error& e)
  {
    std::cerr << "regex error : " << e.what() << std::endl;
  }
  
  if (!sm.empty())
  {
    last_variable = sm[2];
    std::cout << "alltext: '" << alltext << "'" << std::endl;
    std::cout << "last pending variable name: '"
              << last_variable << "'" << std::endl;
  } else 
  {
   std::cout << "no match !!!" << std::endl;
   return;
  }

  // find the corresponding context if any
  // allow global or builtin ...
  bool inglobal=true;
  int seppos = last_variable.find(".");
  Variables::ptr context = Vars.GetCurrentContext();
  while (seppos != std::string::npos) 
  {
    std::string varname = last_variable.substr(0,seppos);
    BasicVariable::ptr var;
    auto find_global = varname.find("global::");
    if ( find_global != std::string::npos) {
      varname = varname.substr(find_global+strlen("global::"),std::string::npos); // get rid of global::
      var = context->GetVar(varname.c_str());
    }
    else
    {
      if (inglobal)
        var = Vars.GetVar(varname.c_str());
      else
        var = context->GetVar(varname.c_str());
      }
    if (!var.get()) {
      std::cout << "Completion failed, check variable ..." << std::endl;
      return;
    }
    DYNAMIC_CAST_VARIABLE(AMIObject,var,var1);
    if (!var1.get()) {
      std::cout << "variable " << var->get_name() 
                << " is not of type AMIObject" << std::endl;
      return;
    }
    context = var1->Pointer()->GetContext();
    inglobal = false;
    last_variable = last_variable.substr(seppos+1,std::string::npos);
    seppos = last_variable.find(".");
  }

  if (inglobal)
  {
    
    auto find_global = last_variable.find("global::");
    if ( find_global != std::string::npos) {
      last_variable = last_variable.substr(find_global+strlen("global::"),std::string::npos); // get rid of global::
      context->SearchCompletions(last_variable, completions);
    }
    else
    {
      completions = Vars.SearchCompletions(last_variable);

//       // add keywords
//       int i = 0;
//       while (token_list[i]!=0) {
//         wxString token=wxString::FromAscii(token_list[i]);
//         if (token.First(last_variable) == 0)
//             completions->Add(token);
//         i++;
//       }
    }
  }
  else
  {
    completions->clear();
    context->SearchCompletions(last_variable, completions);
  }


  if (GB_debug)
   std::cout << "going for it " << completions->size() << std::endl;
  if (!completions->empty()) {
     completion_lastcommand = last_command.substr(0,last_command.size()-last_variable.size());
     cursor_x_last_command = cursor_x - last_variable.size();
     in_completion = true;
     completion_count = 0;
     DisplayCompletion(last_command, cursor_x);
//     printf("Found %d completions \n",(int)completions->GetCount());
    for(int i=0;i<(int)completions->size();i++) {
     std::cout << (*completions)[i] << std::endl;
    }
  }
  
} // ProcessTab()


int main( int argc, const char* argv[] )
{
  
  std::string s1("s1");  
  std::string s2("s2");  
  std::string s3 = s1+s2;  
  
  GB_DriverBase = DriverBase::ptr(&GB_driver,smartpointer_nodeleter<DriverBase>());
  
  GB_debug = false;
  GB_nofile = false;

  GB_num_arg_parsed = 1;
  
  GB_argc  = argc;
  
  GB_argv  = new std::string[argc];
  for(int i=0; i<argc; ++i)
    GB_argv[i] = argv[i];
  GB_cmdline = "";

  // Get environment variables
//  CheckEnvDir( _T("AMI_HELP"),    GB_help_dir,    _T("tokens.html"));
//  CheckEnvDir( _T("AMI_SCRIPTS"), GB_scripts_dir, _T("scripts.amil"));
  
  GB_help_dir    = ".";
  GB_scripts_dir = ".";
  
  RegisterBuiltinTypes();
  
  AddWrapImports();

  GB_typeconversions.DisplayTypes();
  
   if(tty_break() != 0)
     return 1;
   
  std::string command_input;
  
  std::list<std::string> commands;

  
  start_color();      /* Start color      */
  init_pair(1, COLOR_RED, COLOR_BLACK);
  attron(COLOR_PAIR(1));

  // Get all the mouse events
  mousemask(ALL_MOUSE_EVENTS, NULL);

  refresh();
  
  NcursesWindow cmd_win;
  cmd_win.SetScreenPosition(1,1, 6, 85);
  cmd_win.Create();
  keypad(cmd_win.GetWin(), true); 
  scrollok(cmd_win.GetWin(),TRUE);

  NcursesWindow cout_win;
  cout_win.SetScreenPosition(7,1, 30, 85);
  cout_win.Create();
  keypad(cout_win.GetWin(), true); 
  scrollok(cout_win.GetWin(),TRUE);
  
  NcursesWindow cerr_win;
  cerr_win.SetScreenPosition(32,1, 50, 85);
  cerr_win.Create();
  keypad(cerr_win.GetWin(), true); 
  scrollok(cerr_win.GetWin(),TRUE);
  
  nc::nc_window_streambuf cout_buf( cout_win.GetWin(), std::cout );
  nc::nc_window_streambuf cerr_buf( cerr_win.GetWin(), std::cerr );
  std::cerr << "__Error test" << std::endl;
// 
  std::string current_command = "";
  commands.push_front(current_command);
  std::list<std::string>::iterator commands_it = commands.begin();
  
  int c;
  int cursor_x,cursor_y;
  cmd_win.SetCursorPos(0,0);
  NcursesWindow* current_win = &cmd_win;
  
  std::cout << "start" << std::endl;
  
  while (command_input!="quit")
  {
    
    
    attron(COLOR_PAIR(1));
    cerr_win.Display();
    cout_win.Display();
    bool redraw=true;
    cmd_win.GetCursorXY(cursor_x,cursor_y);
    cmd_win.RefreshCusor();
    c = getch();
    
    int cy = cerr_win.GetCursorY();
//    std::cout << "cerr y pos = " << cy << std::endl;
    
    bool key_mouse = false;
    switch(c)
    {
        case KEY_MOUSE:
          // do nothing for the moment
          key_mouse = true;
          MEVENT event;
          if (getmouse(&event)==OK)
          {
            std::cerr << "mouse state " << event.bstate << std::endl;
            // check on which window is the mouse
            if (cmd_win.IsInside(event.x,event.y)) current_win = &cmd_win;
            else 
            if (cout_win.IsInside(event.x,event.y)) current_win = &cout_win;
            else 
                            current_win = &cerr_win;
            current_win->Display();
          }
          break;
          
        default:
          // automatically set the command window if a character is pressed
          if ((c>=32)&&(c<=126))
            if (current_win!=&cmd_win)
              current_win = &cmd_win;
          
    }
    if (current_win==&cmd_win)
    {
//      std::cout << "current_win is cmd win" << std::endl;

      // don't maintain completion if tab is not pressed
      if (c!=9) 
      {
        in_completion = false;
      }
      
      switch(c)
      {
        
          // tab for completion
          case 9:
            ProcessTab(current_command,cursor_x);
            break;
            
          case KEY_UP:
            // save front command
            if (commands_it == commands.begin())
              commands.front() = command_input;
            ++commands_it;
            if (commands_it == commands.end()) --commands_it;
            current_command = *commands_it;
            break;
          case KEY_DOWN:
            if (commands_it!=commands.begin())
              --commands_it;
            current_command = *commands_it;
            break;
          case KEY_LEFT:
            cursor_x--;
            break;
          case KEY_RIGHT:
            cursor_x++;
            break;
          case KEY_BACKSPACE:
            // locate the character to remove
            // if one line command
            // if multiline command?
            if (cursor_x-1<current_command.size())
            {
              current_command.erase(cursor_x-1,1);
              mvwprintw(cmd_win.GetWin(),0,0,"%s ",current_command.c_str());
            }
            redraw = false;
            cursor_x--;
            break;
  //        case KEY_DC:
  //          break;
        case 10:
        {
  //         current_command+="[enter]";
          command_input = current_command;
          std::cout << current_command << std::endl;
          try{
          GB_driver.parse_string(command_input+"\n");
          }
          catch (std::exception& e)
          {
             std::cerr << e.what() << '\n';
          }
          commands.front() = command_input;
          current_command = "";
          commands.push_front(current_command);
          commands_it = commands.begin();
          cursor_x = 0;
          cursor_y = 0;
          
//           // Get contents
//           char cerr_contents[1000];
//           winnstr(cerr_win.GetWin(),cerr_contents,1000);
//           std::cout <<  "error window contents  = [" << cerr_contents << "]" << std::endl;
        }
          
        break;
          
        default:
          if ((c>=32)&&(c<=126))
          {
            int pos = std::min((int)current_command.size(),cursor_x);
//             std::cout << "pos = " << pos << std::endl;
            if (pos<0) pos = 0;
            current_command.insert(current_command.begin()+pos, char(c));
            cursor_x++;
          }
          else
            std::cerr << (boost::format("[%1%]") % c).str() << std::endl;
      }

      if (redraw)
      {
        wclear(cmd_win.GetWin());
        mvwprintw(cmd_win.GetWin(),0,0,"%s",current_command.c_str());
        //wprintw(cmd_win.GetWin(),"%s",current_command.c_str());
      }
      cmd_win.SetCursorPos(cursor_x,cursor_y);
      cmd_win.Display();
      
      //std::cout << cout_buf.GetLineCount() << std::endl;
    } 
    else
    {
      switch(c)
      {
          case KEY_UP:
          {
            current_win->ScrollUp();
            current_win->Display();
            //std::cerr << "KEY_UP:"<< err << std::endl;
            break;
          }
          case KEY_DOWN:
          {
            current_win->ScrollDown();
            current_win->Display();
            //std::cerr << "KEY_DOWN:" << err << std::endl;
            break;
          }
          case KEY_PPAGE:
          {
            current_win->ScrollUp(10);
            current_win->Display();
            //std::cerr << "KEY_DOWN:" << err << std::endl;
            break;
          }
          case KEY_NPAGE:
          {
            current_win->ScrollDown(10);
            current_win->Display();
            //std::cerr << "KEY_DOWN:" << err << std::endl;
            break;
          }
      }
    }
    
                            /* print the message at the center of the screen */
    
//     putchar(c);
    
//    std::getline(std::cin,command_input);
    //std::cout << " command is '" << command_input << "'" << std::endl;
//    GB_driver.parse_string(command_input+"\n");
  }
  
  tty_fix();
  
  return 0;
}


