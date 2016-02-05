//
// C++ Interface: wrapfunction_class
//
// Description: Prototype for wrapping functions
// based on http://www.parashift.com/c++-faq-lite/pointers-to-members.html#faq-33.1
//
// Author: Karl Krissian <>, (C) 2010
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <iomanip>
#include <cassert>
#include "boost/format.hpp"

#include "paramlist.h"
#include "wrapfunction_class.h"

#include <sstream>

/// global Null variable
Variable<int>::ptr nullvar(new Variable<int>(boost::shared_ptr<int>(new int(0))));

/**
 * Function to check if the next parameter to parse is the pre-defined NULL variable
 **/
bool CheckNullVar(ParamList* _p, int _n)
{
  if (_n>=_p->GetNumParam())  return false;
  boost::shared_ptr<Variable<int> > var = boost::dynamic_pointer_cast<Variable<int> >(_p->GetParam(_n));
  if (!var.get()) return false;
  return var->Pointer().get() == nullvar->Pointer().get();
}


std::string GetPointerAsString(void* p)
{
  std::string res;
  std::stringstream ss(res);
  ss << p;
  return res;
}


void WrapClassMemberWithDoc::ShowHelp() 
{
  std::string mess; 
  std::string paramlist_str;
  int nb_param = parameters_comments.size();
  
  // We consider that, when the help is displayed, the argument failure flag is set to true
  Set_arg_failure(true);

  for(int n=0;n<nb_param;n++) {
    //if ()
    paramlist_str += (boost::format("%1% p%2%") % paramtypes[n] %n).str(); 
    
    if (n<nb_param-1) paramlist_str += ", ";
  }

  mess += "\n";
  if (return_comments!="") 
    mess += "Variable ";
  mess += (boost::format("%1%(%2%)\n")% GetFunctionName() % paramlist_str).str();
  mess += "\n"; 
  if (nb_param>0) {
    //mess +=  "\n  Parameters:\n"; 
    for(int n=0;n<nb_param;n++) {
      mess +=  (boost::format("    - p%1%: %2% \n") % n % parameters_comments[n]).str(); 
    }
  }
  mess += "\n"; 
  mess +=  (boost::format("    %s\n") % GetDescription()).str(); 

  if (return_comments!="") {
    mess += "\n";
    mess += "  Returns: ";
    mess += return_comments;
    mess += "\n";
  }

  // TODO: display help message
//   wxMessageDialog* msg = new wxMessageDialog(NULL,wxString(mess.c_str(),wxConvUTF8),
//       wxString::FromAscii("Info"),wxOK | wxICON_INFORMATION  );
//   msg->ShowModal();
//   msg->Destroy();
}

