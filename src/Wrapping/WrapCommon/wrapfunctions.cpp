//
// C++ Interface: wrapAMIFluid
//
// Description:
//
//
// Author: Karl Krissian,,, <karl@UBUNTU-KARL>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <iomanip>
#include <cassert>
#include "boost/format.hpp"

#include "paramlist.h"
#include "wrapfunctions.hpp"
#include "DefineClass.hpp"
#include "amilab_messages.h"
//#include "DessinImage.hpp"
#include "ami_function.h"

#include <string>
using namespace std;

/**
 * Function returns the number of parameters of the parameters list
 * if the pointer is NULL, returns -1 to allow display the documentation
 */
size_t get_num_param(ParamList* p)
{
  if (!p) return -1;
  return p->GetNumParam();
}


bool get_next_param( BasicVariable::ptr& var, 
                    ParamList*p, int& num, bool required, bool quiet)
{
  if (!p) return false;
  // if the parameter number is too high, skip it (use default value)
  if (num>=p->GetNumParam()) return (!required);
  var =  p->GetParam(num++);
  if (!var.get()) {
    if (!quiet)
      FILE_ERROR((boost::format("Parameter %d is an empty variable") % num).str().c_str());
    // there a parameter so, even if it is not required, return false here
    return false;
  }
  return true;
}


/**
 * Function used to parse a variable of generic type in a list of parameters, and to give back a smart pointer to the variable.
 */
bool get_generic_var_param( BasicVariable::ptr& var, ParamList*p, int& num, bool force_ref )
{
  if (!p) return false;
  // Getting the Variable and checking its type
  var = p->GetParam(num++); // = is like a swap of smart pointers ...
  if (var.get()) {
    // this part is in testing mode
    if (force_ref) {
      // check that the variable is not just local
      int var_count = var->GetPtrCounter();
      if (var_count==1) {
        FILE_ERROR((boost::format("Parameter %1% is not passed as a reference ... (%2%)")%num%var->Name()).str().c_str());
        return false;
      }
    }
    return true;
  }
  else
  {
    FILE_ERROR((boost::format("Parameter %d not found ") % num).str().c_str());
    return false;
  }
}


/**
 * Function used to parse an integer in a list of parameters
 */
bool get_int_param(int& arg, ParamList*p, int& num, bool required)
{
  // Get an integer param from a float value ...
  // copy to start with default value
  float val = arg;
  if (get_val_param<float>(val,p,num)) {
    arg = (val>=0?(int(val+0.5)):(int(val-0.5)));
    return true;
  }
  else 
  {
    if (required) {
      FILE_ERROR("Could not get an integer parameter from a floating point value");
    }
    return false;
  }
}



// /**
//  * Function used to parse a vectorial image in a list of parameters
//  */
// bool get_vectimage_param(InrImage*& arg, ParamList*p, int& num)
// {
//   if (get_val_ptr_param<InrImage>(arg,p,num))
//   {
//     if (!arg->VectorialFormat()) {
//       FILE_ERROR((boost::format("Param %d must be a vectorial image.") %num).str().c_str());
//       return false;
//     }
//     else return true;
//   } 
//   else return false;
// }


