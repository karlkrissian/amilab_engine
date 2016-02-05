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

#ifndef PluginManager_H
#define PluginManager_H

#include "CommonConfigure.h"
#include "PluginBase.h"
#include "DynamicLibrary.h"
#include "DefineClass.hpp"

/**
 * @brief Class that manages the life-cycle of the plugins.
 **/
class COMMON_EXPORT PluginManager
{
  DEFINE_CLASS(PluginManager);
public:

  /// Destructor
  ~PluginManager();
  
  /**
   * @brief Load the library with the given name (full or not), return true if ok.
   *
   * @param LibName the library name
   * @return return true if load library with the given name
   **/
  bool Load (const char * LibName);

  /**
   * @brief Unloads the library from memory.
   *
   * Works when previously the Detach method has been invoked.
   **/  
  bool Unload (void);

  /**
   * @brief Gets the plugin handler.
   *
   * @return return the plugin handler
   **/
  boost::shared_ptr<PluginBase> Getplugin() { return m_plugin;}
  
  DynamicLibrary& GetLib() { return m_lib; }
  

private:
  DynamicLibrary                    m_lib;    // Library manager.
  boost::shared_ptr<PluginBase>     m_plugin; // Plugin handle.

}; // PluginManager

#endif // PluginManager_H