//
// C++ Interface: CallBackAMIFunction
//
// Description: 
//
//
// Author:  <>, (C) 2010
//
// Copyright: See COPYING file that comes with this distribution
//
//
#pragma once
#ifndef _CallBackAMIFunction_h_
#define _CallBackAMIFunction_h_

#include "DefineClass.hpp"
#include "CallBackBase.h"
#include "ami_function.h"

/**
  Creates a callback based on a function from the scripting language.
**/
#include "LanguageBaseConfigure.h"
class LanguageBase_EXPORT CallBackAMIFunction : public CallBackBase
{
  DEFINE_CLASS(CallBackAMIFunction);

  AMIFunction::wptr wfunc;
  public:
    CallBackAMIFunction( const AMIFunction::ptr& fp) {
      wfunc = AMIFunction::wptr(fp);
    }

    void SetAMIFunction( const AMIFunction::ptr& fp)
    {
      wfunc = AMIFunction::wptr(fp);
    }

    bool operator()();
};


#endif // _CallBackAMIFunction_h_
