
#include "DriverBase.h"
#include "boost/format.hpp"

#include "VarContexts.hpp"
LanguageBase_VAR_IMPORT VarContexts Vars;

//-----------------------------------------
void CB_delete_variable( void* var)
{
  BasicVariable* vartodelete = (BasicVariable*) var;

  FILE_MESSAGE((boost::format("deleting %1%") % vartodelete->Name()).str().c_str());
  if (!Vars.deleteVar(vartodelete))
  FILE_ERROR("Could not delete variable "); 

}

//-----------------------------------------
void CB_delete_varlist( void* var)
{
  if (!var) return;

  std::list<BasicVariable::wptr>* varlist = (std::list<BasicVariable::wptr>*) var;

  if (varlist) {
    // iterate over the list
    std::list<BasicVariable::wptr>::iterator it;
    for(it=varlist->begin(); it!=varlist->end(); it++) {
      BasicVariable::wptr vartodelete = *it;
      if (BasicVariable::ptr lockedvar = vartodelete.lock()) 
      {
        bool deleted=false;
        FILE_MESSAGE((boost::format("Pointer counter = %1%") % lockedvar->GetPtrCounter()).str().c_str());
        std::string name = lockedvar->Name();
        FILE_MESSAGE((boost::format("deleting %1%") % name).str().c_str());
        Variables::ptr context = lockedvar->GetContext();

        // free lock first
        lockedvar.reset();
        if (context.get()) {
          deleted = context->deleteVar(name.c_str());
        }
        if (!deleted)
          FILE_ERROR((boost::format("Could not delete variable %1%") % name).str().c_str()); 
      }
    }

    // should be safe to delete varlist if the window is now closed!!!
    delete varlist;
  }
}


DriverBase::DriverBase(void)
{
}

DriverBase::~DriverBase(void)
{
}
