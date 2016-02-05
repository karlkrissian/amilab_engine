
#ifndef _Variable_bool_h_
#define _Variable_bool_h_

#include "Variable.hpp"


//------------------------------------------------------
//------- Variable<bool>
//------------------------------------------------------

/// Copy contents to new variable
template<> BasicVariable::ptr Variable<bool>::NewCopy() const;


// Logical operators

/// !a
template<> BasicVariable::ptr Variable<bool>::operator !();

/// a&&b
template<> BasicVariable::ptr Variable<bool>::operator &&(const BasicVariable::ptr& b);

/// a||b
template<> BasicVariable::ptr Variable<bool>::operator ||(const BasicVariable::ptr& b);

//  Comparison Operators

/// a!=b
template<> BasicVariable::ptr Variable<bool>::operator !=(const BasicVariable::ptr& b);

/// a==b
template<> BasicVariable::ptr Variable<bool>::operator ==(const BasicVariable::ptr& b);

/// Cast to a type based on its name as a string
template<>
BasicVariable::ptr Variable<bool>::TryCast(const std::string&) const;

template<> BasicVariable::ptr Variable<bool>::BasicCast(const int& type);

/// (cond?a:b)
template<> BasicVariable::ptr Variable<bool>::TernaryCondition(const BasicVariable::ptr& v1, const BasicVariable::ptr&v2);

/// Other operators
/// a=b
/**
 * Basic Assignment operator
 * if b must be a boolean value here
 * @param b 
 * @return 
 */
template<> BasicVariable::ptr Variable<bool>::operator =(const BasicVariable::ptr& b);

#endif 
// _Variable_bool_h_