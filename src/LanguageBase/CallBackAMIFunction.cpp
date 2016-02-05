//
// C++ Implementation: CallBackAMIFunction
//
// Description: 
//
//
// Author:  <>, (C) 2010
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "CallBackAMIFunction.h"

/*#include "driver.h"
#if defined(WIN32)
  #define VAR_IMPORT __declspec( dllimport ) 
#else
  #define VAR_IMPORT extern
#endif
VAR_IMPORT yyip::Driver GB_driver;
*/

#include "DriverBase.h"
#include "LanguageBaseConfigure.h"
LanguageBase_VAR_IMPORT DriverBase::ptr  GB_DriverBase;

bool CallBackAMIFunction::operator()()
{
  if (AMIFunction::ptr f = wfunc.lock()) {
    GB_DriverBase->yyip_call_function(f.get());
    return true;
  }
  else {
    GB_DriverBase->err_print("Trying to call a non-existing AMIFunction !");
    return false;
  }
}
