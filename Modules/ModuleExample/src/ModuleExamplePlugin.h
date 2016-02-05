//
// C++ File: Plugin.h
//
// Description:  A plugin example.
//
//
// Author: xXx <xXx@xXx.com>, (C) YYYY
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef _ModuleExamplePlugin_h_
#define _ModuleExamplePlugin_h_

#include "wxPluginBase.h"

/**
 * @brief Plugin of ExamplePlugin class.
 **/
class WX_AMILAB_EXPORT ModuleExamplePlugin : public wxPluginBase
{
  PLUGIN_DEFINE();

public:
  ModuleExamplePlugin();

  ~ModuleExamplePlugin() 
  {
    this->Destroy();
  }
};

#endif // _ModuleExamplePlugin_h_

