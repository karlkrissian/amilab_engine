
#include "DefineClass.hpp"
#include "Variable.hpp"

#include "ami_function.h"
#include "ami_class.h"
#include "ami_object.h"
#include "wrapfunction_class.h"

#include "VarArray.h"

#include <string>
#include <boost/format.hpp>
#include <iostream>

using namespace std;

#include "CommonConfigure.h"
COMMON_VAR_IMPORT unsigned char GB_debug;


//----------------------------------------------------------------------
//  VarArray
//----------------------------------------------------------------------

void VarArray::Resize( int new_size)
  {
    _vars.resize(new_size);
    _allocated_size = new_size;
    // for the moment, set the size to the allocated size ...
    _size = _allocated_size;
  }


VarArray::VarArray()
{
  _type           = type_void;
  _vars.clear();
  _size           = 0;
  _allocated_size = 0;
}

VarArray::~VarArray()
{
  this->FreeMemory();
}

void VarArray::Init( vartype type, int initsize)
{
  _type           = type;
  _allocated_size = initsize;
  _size = _allocated_size;
  _vars.resize(initsize);
}



BasicVariable::ptr VarArray::GetVar(int i) {
  if ((i>=0)&&(i<_allocated_size)) {
    return _vars[i];
  }    
  else {
    CLASS_ERROR((boost::format("Wrong index %1%") % i).str().c_str());
    return BasicVariable::ptr();
  }
}


//---------------------------------------------------
ostream& operator<<(ostream& o, const VarArray& v)
//       -----------
{
  int i;
  for (i=0;i<v._size;i++) 
    if (v._vars[i].get())
//      if (->Pointer()!=NULL) 
        o  << v._vars[i] << std::endl;
//format("\t\t [%1%]\t %2%") % i  % (*v._vars[i])  << std::endl;
  return o;
} // operator <<


//---------------------------------------------------
void VarArray::display() 
{
 std::cout << *this;
}

void VarArray::FreeMemory()
{
  _vars.clear();
  _size = 0;
}
