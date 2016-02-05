//
// C++ Interface: PluginBase
//
// Description: Sets the basis for the definition of a Plugin.
//
//
// Author: Karl Krissian 
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef PluginBase_H
#define PluginBase_H

#include "AMILabEngineConfig.h"


//--------------------------------------------------
// Definition of macros to determine the mode of use
// of the Plugin.
//--------------------------------------------------
#define PLUGIN_IN_CONSOLE_MODE  0
#define PLUGIN_IN_GRAPHIC_MODE  1

#include <string>
#include "PluginInterface.h"

//--------------------------------------------------
// Specified how export functions from DLL or 
// shared library.
//--------------------------------------------------

#ifdef WIN32
  #if defined (_MSC_VER) || defined (__BORLANDC__)
    #define PLUGIN_AMILAB_DLLEXPORT __declspec( dllexport )
  //#else
    //#      error "don't know how export functions from DLL with this compiler"
  #endif
#else
  #define PLUGIN_AMILAB_DLLEXPORT
#endif

/**
 * @brief Class that sets the basis for the definition of a Plugin.
 **/
class 
  //WXEXPORT 
  PluginBase: public PluginInterface
{
    
  public:
    
   virtual ~PluginBase() { }

    /**
     * @brief Get the plugin name.
     *
     * @return return a std::string with the plugin name
     **/
    virtual std::string GetName(void) const
    {
      return m_Name;
    }

    /**
     * @brief Get the plugin description.
     *
     * @return return a std::string with the plugin description
     **/
    virtual std::string GetDescription(void) const
    {
      return m_Description;
    }

    /**
     * @brief Get the plugin version.
     *
     * @return return a std::string with the plugin version
     **/
    virtual std::string GetVersion(void) const
    {
      return m_Version;
    }

    /**
     * @brief Get the plugin author.
     *
     * @return return a std::string with the plugin author
     **/
    virtual std::string GetAuthor(void) const
    {
      return m_Author;
    }

    /**
     * @brief Set the plugin name.
     *
     * @param Name A std::string with the plugin name
     **/
    virtual void SetName(const std::string &Name)
    {
      m_Name = Name;
    }

    /**
     * @brief Set the plugin description.
     *
     * @param Description A std::string with the plugin description
     **/
    virtual void SetDescription(const std::string &Description)
    {
      m_Description = Description;
    }

    /**
     * @brief Set the plugin version.
     *
     * @param Version A std::string with the plugin version
     **/
    virtual void SetVersion(const std::string &Version)
    {
      m_Version = Version;
    }

    /**
     * @brief Set the plugin author.
     *
     * @param Author A std::string with the plugin author
     **/
    virtual void SetAuthor(const std::string &Author)
    {
      m_Author = Author;
    }
    

    /**
     * @brief Set that the plugin executes in mode console.
     *
     * The plugin does not require the graphical environment(wxWindow) to work.
     **/     
    virtual void SetConsoleMode(void)
    {
      m_plugin_mode = PLUGIN_IN_CONSOLE_MODE;
    }

    /**
     * @brief Set that the plugin executes in mode graphic.
     *
     * The plugin requires the graphical environment(wxWindow) to work.
     **/  
    virtual void SetGraphicMode(void)
    {
      m_plugin_mode = PLUGIN_IN_GRAPHIC_MODE;
    }

    /**
     * @brief Checks if this in console mode.
     *
     * @return Returns true if this in console mode.
     **/
    virtual bool IsConsoleMode(void) const
    {
      return (m_plugin_mode == PLUGIN_IN_CONSOLE_MODE);
    }

    /**
     * @brief Checks if this in graphic mode.
     *
     * @return Returns true if this in graphic mode.
     **/
    virtual bool IsGraphicMode(void) const
    {
      return (m_plugin_mode == PLUGIN_IN_GRAPHIC_MODE);
    }

    /**
     * @brief Execute the plugin.
     *
     * @return return true if the plugin executes correctly
     **/
    virtual bool Execute (void)
    {
      //TODO
      return true;
    }      
  
    virtual void Destroy ()
    {
       //std::cout << "Destroy() {}" << std::endl;
    }      

private:
    unsigned char m_plugin_mode;  // Determines the mode in which the plugin is executed.
    std::string      m_Name,         // The plugin name
                  m_Description,  // The plugin description 
                  m_Version,      // The plugin version
                  m_Author;       // The plugin Author
//    wxWindow*     m_win;          // The plugin wxWindow.

}; // PluginBase


/** @name This is the API that each AMILAB shared lib must implement. */
//@{
extern "C"
{
   /**
    Each module DLL must implement a function CreatePlugin of this
    type which will be called to initialise it. That function must
    return the new object representing this module.
   */
  typedef PluginBase* ( *CreatePlugin_function)();

}
//@}

// ----------------------------------------------------------------------------
// macros for module declaration/implementation.
//
// This macros must be used inside the class declaration for any module class.
// ----------------------------------------------------------------------------

#define PLUGIN_DEFINE() \
public: \
    virtual bool Execute (void); \
    virtual void Destroy();

#define PLUGIN_ENTRY_FUNCTION(name) \
extern "C" PLUGIN_AMILAB_DLLEXPORT PluginBase* CreatePlugin() \
{ \
  return new name(); \
};

#endif // PluginBase_H
