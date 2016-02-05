//
// C++ Interface: VariableStack
//
// Description: 
//
//
// Author: Karl Krissian <>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef _VariableStack_h_
#define _VariableStack_h_

#include <stack>
#include "Variable.hpp"
#include "ami_class.h"
#include "amilab_messages.h"


/**
  * Variable Stack: Allows operations on variables
 **/
class VariableStack{
//    ----------

  DEFINE_CLASS(VariableStack);

  std::stack<BasicVariable::ptr> _variables;

 public:

  VariableStack() {}

  ~VariableStack()    { }



  /**
   * Adds a variable to the stack
   * @param var 
   */
  void AddVar( const BasicVariable::ptr& var)
  {
    _variables.push(var);
  }

  BasicVariable::ptr GetLastBasicVar()
  {
    if (_variables.empty()) {
      CLASS_ERROR("Returning null variable !!!");
      return BasicVariable::ptr();
    }
    BasicVariable::ptr tmp = _variables.top();
    _variables.pop();
    return tmp;
  }

  template <class T>
  boost::shared_ptr<Variable<T> > GetLastVar();

}; // VariableStack


template <class T>
boost::shared_ptr<Variable<T> > VariableStack::GetLastVar()
{
  if (_variables.empty()) return boost::shared_ptr<Variable<T> >();
  boost::shared_ptr<Variable<T> > tmp( boost::dynamic_pointer_cast<Variable<T> >(_variables.top()));
  _variables.pop();
  return tmp;
}

#endif // _VariableStack_h_
