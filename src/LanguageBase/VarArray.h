
#ifndef _VarArray_h_
#define _VarArray_h_

//#include "ParamBox.hpp"
//#include "DessinImage.hpp"
//#include "Viewer3D.hpp"
//#include "paramlist.h"
#include <string>
#include <iosfwd>

#include "DefineClass.hpp"

#include "amilab_messages.h"
#include "vartype.h"
#include "paramlist.h"
#include "Variable.hpp"


/// Array of variable
/// This class should soon become deprecated with the new wrapping to std::vector<BasicVariable>

#include "LanguageBaseConfigure.h"
class LanguageBase_EXPORT VarArray {

  DEFINE_CLASS(VarArray);

private:
  int           _size;
  int           _allocated_size;
  vartype       _type;
  std::vector<BasicVariable::ptr>     _vars;
  void Resize( int new_size);

 public:

  VarArray();
  virtual ~VarArray();
  int Size() {return _size;}
  void Init( vartype type, int initsize=10);

  template <class T>
  /**
   * Initialize a value within the array of variables
   * @param i : array position
   * @param p : smart pointer to the value
   * @param name : name of the new created variable
   */
  void InitElement( int i, 
                    const boost::shared_ptr<T>& p,
                    const char* name)
  {
    if (i>=_allocated_size) this->Resize(i+1);
    if ((i>=0)&&(i<_allocated_size)) {
      _vars[i] = BasicVariable::ptr(new Variable<T>(name,p));
    }
  }

  BasicVariable::ptr GetVar(int i); 
  vartype Type() { return _type; }
  void FreeMemory();

  //
  void display();

  //
  friend std::ostream& operator<<(std::ostream& o, const VarArray& v);

}; // VarArray


#endif
// _VarArray_h_