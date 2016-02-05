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

#ifndef _BoostFileSystemPlugin_h_
#define _BoostFileSystemPlugin_h_

#include "PluginBase.h"

/**
 * @brief Plugin of ExamplePlugin class.
 **/
class 
  //WX_AMILAB_EXPORT 
  BoostFileSystemPlugin : public PluginBase
{
  PLUGIN_DEFINE();

public:
  BoostFileSystemPlugin();

  ~BoostFileSystemPlugin() 
  {
    //this->Destroy();
  }
};

#endif // _BoostFileSystemPlugin_h_

