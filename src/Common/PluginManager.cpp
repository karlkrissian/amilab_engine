//
// C++ Interface: PluginManager
//
// Description: It manages the life-cycle of the plugins.
//
//
// Author: Karl Krissian 
//
// Copyright: See COPYING file that comes with this distribution
//

#include "PluginManager.h"
#include <iostream>

//=======================================================
PluginManager::~PluginManager()
{
  //std::cout << "~PluginManager::PluginManager()" << std::endl;
  //m_plugin->Destroy();
  m_plugin.reset();
  Unload();
}

  
//=======================================================
bool PluginManager::Load (const char* LibName)
{
  m_lib.Load(LibName);
  std::cout << "calling m_lib.Load(" << LibName << ")" << std::endl;
  if(m_lib.GetHandle())
  {
    //Create a valid function pointer using the function pointer type in PluginBase.h
    CreatePlugin_function pfnCreatePlugin = m_lib.GetFunc<CreatePlugin_function>("CreatePlugin");
    //check if the function is found
    if(pfnCreatePlugin)
    {
      //Create the plugin
      m_plugin = boost::shared_ptr<PluginBase>(pfnCreatePlugin());
      return true;
    }
  }
  return false;
} //LoadPlugins definition.

//=======================================================
bool PluginManager::Unload (void)
{
  if(m_lib.GetHandle()) {
    m_lib.Free();
    std::cout << "calling m_lib.Free()" << std::endl;
    return true;
  }
  return false;
} //Unload definition.

