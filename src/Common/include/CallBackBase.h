//
// C++ Interface: CallbackBase
//
// Description: 
//
//
// Author:  <>, (C) 2010
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef _CallBackBase_h_
#define _CallBackBase_h_

#include "DefineClass.hpp"

/**
  Base Class for dealing with callbacks in a clean way
**/
class CallBackBase
{
  DEFINE_CLASS(CallBackBase);
  public:
    /**
     * Call the callback function
     * @return True is success, false otherwise
     */
    virtual bool operator()() = 0;
};


#endif //  _CallBackBase_h_
