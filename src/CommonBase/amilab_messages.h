//
// C++ Interface: amilab_messages
//
// Description: 
//
//
// Author: Karl Krissian <krissian@dis.ulpgc.es>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#pragma once
#ifndef _amilab_messages_h_
#define _amilab_messages_h_

#include "AMILabEngineConfig.h"
#include "ami_format.h"

#include "CommonBaseConfigure.h"


CommonBase_EXPORT void PrintWarning(const char* mess);
CommonBase_EXPORT void PrintWarning(const ami::format& f);

CommonBase_EXPORT void PrintError(const char* mess);
CommonBase_EXPORT void PrintError(const ami::format& f);

// Error message should always be displayed
#define FILE_ERROR( m) { \
  ami::format f("Error \t file: %1% \n     \t %2% \n     \t %3%");\
  PrintError( f % __FILE__ % __func__ % m ); }

#define FILE_MESSAGE( m)  \
  if ((GB_verbose) || (GB_debug)) { \
    ami::format f("Error \t file: %1% \n     \t %2% \n     \t %3%");\
    PrintError( f % __FILE__ % __func__ % m ); \
  }

// Error message should always be displayed
#define CLASS_ERROR( m) \
  {\
    ami::format f("Error \t %1%::%2%(), line %3% \t %4%");\
    PrintError( f % this->get_name() % __func__ % __LINE__ % m );\
  }

#define CLASS_MESSAGE(m) \
  if ((GB_verbose) || (GB_debug)) { \
    ami::format f("Info \t %1%::%2%(), line %3% \t %4%");\
    PrintWarning( f % this->get_name() % __func__ % __LINE__ % m );\
  }

#define VTK_CLASS_MESSAGE(m) \
  if ((GB_verbose) || (GB_debug)) { \
    ami::format f("Info \t %1%::%2%(), line %3% \t %4%");\
    PrintWarning( f % this->GetClassName() % __func__ % __LINE__ % m );\
  }

#define CLASS_MESSAGE_STATIC(_this,m) \
  if ((GB_verbose) || (GB_debug)) { \
    ami::format f("Info \t %1%::%2%(), line %3% \t %4%");\
    PrintWarning( f % _this->get_name() % __func__ % __LINE__ % m );\
  }

CommonBase_VAR_IMPORT unsigned char GB_debug;
CommonBase_VAR_IMPORT unsigned char GB_verbose;


#endif //  _amilab_messages_h_
