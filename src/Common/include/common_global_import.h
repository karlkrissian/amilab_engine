
#ifndef _common_global_import_h_
#define _common_global_import_h_

#include "Erreurs.hpp"
#include "AmiMessage.h"
#include "CommonConfigure.h"
#include <stack>
#include <vector>

COMMON_VAR_IMPORT unsigned char GB_AfficheWarning;
COMMON_VAR_IMPORT unsigned char GB_AfficheErreur;
COMMON_VAR_IMPORT unsigned char GB_debug;
COMMON_VAR_IMPORT unsigned char GB_verbose;
COMMON_VAR_IMPORT unsigned char GB_nofile;
COMMON_VAR_IMPORT std::stack<NomMethode*> GB_pile_nom_methode;
COMMON_VAR_IMPORT AmiMessage   GB_AmiMessage;

#endif // define _common_global_import_h_
