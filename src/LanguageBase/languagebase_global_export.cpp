
#include "LanguageBaseConfigure.h"

#include "DriverBase.h"
#include "VarContexts.hpp"
#include "TypeConversion.h"

LanguageBase_VAR_EXPORT DriverBase::ptr GB_DriverBase;
LanguageBase_VAR_EXPORT VarContexts Vars;

LanguageBase_EXPORT
void AddClassMap(std::string classname, BasicVariable::wptr classvar) 
{
  Vars.AddClassMap(classname,classvar);
}


LanguageBase_EXPORT 
BasicVariable::wptr GetClassVar(std::string classname)
{ 
  return Vars.GetClassVar(classname);
}

// global variable list all existing types, to deal with type conversion
LanguageBase_EXPORT TypeConversion GB_typeconversions;
