#pragma once
#ifndef _AMI_BASICVARIABLE_H
#define _AMI_BASICVARIABLE_H

//#include "ParamBox.hpp"
//#include "DessinImage.hpp"
//#include "Viewer3D.hpp"
//#include "paramlist.h"
#include <string>
#include <string.h>
//#include <iostream>
#include "ami_format.h"

#include "DefineClass.hpp"

#include "amilab_messages.h"
#include "vartype.h"
//#include "paramlist.h"

// forward definition of Variables
class Variables;
//class VarArray;


/*
template<class T>  
std::ostream& operator<<(std::ostream& o, const Variable<T>& v);

template<class T> 
std::ostream& PrintType(std::ostream& o, const Variable<T>& v);
*/


/// Getting variable type 
template<class T> vartype GetVarType();


/**
  Basic Variable class without template
**/
#include "LanguageBaseConfigure.h"
class LanguageBase_EXPORT BasicVariable {

  DEFINE_CLASS(BasicVariable);

protected:
  vartype       _type;
  std::string   _name;
  std::string   _comments;
  boost::shared_ptr<Variables>   _context; // points to the context
    // that the variable belong to, if any

  /// Own list of variables
  boost::shared_ptr<Variables>  _vars;

public:

  // static empty variable to use for returning references or simply empty variable result.
  static BasicVariable::ptr empty_variable;


  BasicVariable();
/*
: _type(type_void), _name(""), _comments("") 
  {
    _vars     = boost::shared_ptr<Variables>(new Variables);
  }
*/
  virtual ~BasicVariable();

  /**
    * Virtual Method that creates a new smart pointer to a basic variable with the same type
    */
  virtual BasicVariable::ptr NewCopy() const = 0;

  /**
    * Virtual Method that creates a new smart pointer to a basic variable with the same type
    */
  virtual BasicVariable::ptr NewReference() const = 0;

  /**
   * Return the number of references (value of use_count()) of the smart pointer to the variable value
  **/
  virtual int GetPtrCounter() const = 0;

  /**
   * Return the availability of the pointer (value of get()) of the smart pointer to the variable value
  **/
  virtual bool HasPointer() const = 0;

//  virtual void operator = (const BasicVariable& v) = 0;

//  void operator = (const BasicVariable::ptr& v) {
//     (*this) = (*v);
//  }

  virtual bool Equal( BasicVariable::ptr v)  = 0;

  virtual bool operator == (BasicVariable* v)  = 0;

  virtual bool SameContents(BasicVariable* v)  = 0;

  /**
   * Gets the list of variables 
   * @return object context (contains its variables)
   */
  boost::shared_ptr<Variables>& GetOwnContext() { return _vars;}


  void SetContext(const boost::shared_ptr<Variables>& val) 
  {
    _context = val;
  }

  /**
   * Returns the context that contains the variable.
   * @return variable's context
   */
  boost::shared_ptr<Variables> GetContext() const
  {
    return _context;
  }


  vartype Type() const { return _type; }


  /**
   * Try to cast the variable to the type given as a string in parameter.
   * @param type_string : type as a string
   * @return smart pointer to a variable of the new type if success, empty smart pointer otherwise
   */
  virtual BasicVariable::ptr TryCast (const std::string& type_string) const = 0;

  /**
   * Rename variable.
   * @param newname 
   */
  void Rename(const char* newname);

  std::string Name() const { return _name;}

  virtual std::string TreeCtrlInfo() const = 0;

  void SetComments(const std::string& comments) { _comments = comments;}
  std::string GetComments() const { return _comments; }

  virtual bool FreeMemory() = 0;

  virtual void Delete() = 0;


  int HasName(const char* name)
  {
    if (_type==type_void) return 0;
    return (strcmp(_name.c_str(), name)==0);
  }

  virtual const std::string GetTypeName() const { return std::string(); };

  //
  virtual void display(std::ostream& o) const = 0;

  virtual bool IsNumeric() const;

  virtual double GetValueAsDouble() const = 0;

//  virtual std::string GetTypeAsString() const = 0;

  /**
   * Virtual method to return the value of a variable.
   * @return a string containing the value of the variable.
   */
  virtual std::string GetValueAsString() const  =0;
  //{ return std::string(); }

  // allow access to private members of Variable class
//  friend class VarArray;



//     ami::format f(" %1%::operator %2% not defined."); \
//     PrintWarning( (f % get_name() % __func__).GetString() ); \

#define DECLARE_BASICVAR_UNARYOP(op) \
  virtual BasicVariable::ptr operator op(); 

#define DECLARE_BASICVAR_OP_VAR(op) \
  virtual BasicVariable::ptr operator op(const BasicVariable::ptr& b);


#define DECLARE_BASICVAR_COMP_OP_VAR(op) \
  virtual BasicVariable::ptr operator op(const BasicVariable::ptr& b);

#define BASICVAR_LOGIC_OP(op) \
  virtual BasicVariable::ptr operator op() \
  {\
    return this->NewReference();  \
  }

#define BASICVAR_LOGIC_OP_VAR(op) \
  virtual BasicVariable::ptr operator op(const BasicVariable::ptr& b) \
  {\
    return this->NewReference(); \
  }

  /** @name ArithmeticOperators
   *  Variable Arithmetic Operators.
   */
  //@{
  // -------- Operators ---

  /// *T
  DECLARE_BASICVAR_UNARYOP(*)

  /// +T
  DECLARE_BASICVAR_UNARYOP(+)

  /// prefix ++ operator ++T 
  DECLARE_BASICVAR_UNARYOP(++)

  /// prefix ++ operator T++ 
  virtual BasicVariable::ptr operator ++(int)
  { return this->NewReference(); }



  /// a+b
  // can I keep the const here, no because we return a reference ... ???
  // question, should we create a new variable ????
  // in this case yes, and the rule should take care of choosing a+b or a+=b to avoid 
  // a new allocation
  DECLARE_BASICVAR_OP_VAR(+);
  DECLARE_BASICVAR_OP_VAR(+=);

  /// -T
  DECLARE_BASICVAR_UNARYOP(-)

  /// a-b
  DECLARE_BASICVAR_OP_VAR(-);

  /// prefix -- operator --T 
  DECLARE_BASICVAR_UNARYOP(--)

  /// prefix -- operator T-- 
  virtual BasicVariable::ptr operator --(int)
  { return this->NewReference(); }

  DECLARE_BASICVAR_OP_VAR(-=);
  DECLARE_BASICVAR_OP_VAR(*);
  DECLARE_BASICVAR_OP_VAR(*=);
  DECLARE_BASICVAR_OP_VAR(/);
  DECLARE_BASICVAR_OP_VAR(/=);
  DECLARE_BASICVAR_OP_VAR(%);
  DECLARE_BASICVAR_OP_VAR(%=);

  //@}

  /** @name ComparisonOperators
   *  Variable Comparison operators/Relational operators.
   */
  //@{
    DECLARE_BASICVAR_COMP_OP_VAR(<);
    DECLARE_BASICVAR_COMP_OP_VAR(<=);
    DECLARE_BASICVAR_COMP_OP_VAR(>);
    DECLARE_BASICVAR_COMP_OP_VAR(>=);
    DECLARE_BASICVAR_COMP_OP_VAR(!=);
    DECLARE_BASICVAR_COMP_OP_VAR(==);
  //@}

  /** @name LogicalOperators
   *  Variable Logical operators.
   */
  //@{
    BASICVAR_LOGIC_OP(!);
    BASICVAR_LOGIC_OP_VAR(&&);
    BASICVAR_LOGIC_OP_VAR(||);
  //@}

  /** @name BitwiseOperators
   *  Variable Bitwise operators.
   */
  //@{
    BASICVAR_LOGIC_OP_VAR(^);
    BASICVAR_LOGIC_OP_VAR(|);
    BASICVAR_LOGIC_OP_VAR(&);
  //@}

  /** @name OtherOperators
   *  Variable Other operators.
   */
  //@{
    /// basic assignment operator
    DECLARE_BASICVAR_OP_VAR(=);
    DECLARE_BASICVAR_OP_VAR(<<);
    DECLARE_BASICVAR_OP_VAR(>>);

    /**
     * Forces the copy, even if a new object needs to be created.
     * @param b 
     * @return 
     */
    virtual BasicVariable::ptr left_assign(const BasicVariable::ptr& b) = 0;

    /// Transpose operator
    virtual BasicVariable::ptr Transpose()
    { return this->NewReference(); }

    /// PointWise multiplication, included for matrices
    virtual BasicVariable::ptr PointWiseMult(const BasicVariable::ptr& b) 
    {
      ami::format f(" %1%::operator %2% not defined."); \
      PrintWarning( (f % get_name() % __func__).GetString() ); \
      return this->NewReference(); 
    }
  //@}


#define BASICVAR_FUNC(func) \
  virtual BasicVariable::ptr m_##func() = 0;

// { \
//     ami::format f(" %1%, %2% not defined."); \
//     PrintWarning( (f % get_name() % __func__).GetString() ); \
//     return this->NewReference(); \
//   }

  /** @name Mathematical functions
   *  Mathematical functions.
   */
  //@{
    BASICVAR_FUNC(sin)
    BASICVAR_FUNC(cos)
    BASICVAR_FUNC(tan)
    BASICVAR_FUNC(asin)
    BASICVAR_FUNC(acos)
    BASICVAR_FUNC(atan)
    BASICVAR_FUNC(fabs)
    BASICVAR_FUNC(round)
    BASICVAR_FUNC(floor)
    BASICVAR_FUNC(exp)
    BASICVAR_FUNC(log)
    BASICVAR_FUNC(ln)
    BASICVAR_FUNC(sqrt)
    BASICVAR_FUNC(norm)
  //@}

  /**
   * Cast to standard predefined types
   * @param type of type WORDTYPE initially defined for image pixel types
   * @return the new variable after the cast
   */
  virtual BasicVariable::ptr BasicCast(const int& type) = 0;

  virtual BasicVariable::ptr operator[](const BasicVariable::ptr& v) = 0;

  virtual BasicVariable::ptr TernaryCondition(const BasicVariable::ptr& v1, const BasicVariable::ptr&v2) = 0;

}; // class BasicVariable



#endif
