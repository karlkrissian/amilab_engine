
#ifndef _Variable_AMIObject_h_
#define _Variable_AMIObject_h_

#include "Variable.hpp"

class AMIObject;
#include "LanguageBaseConfigure.h"

template<>  LanguageBase_EXPORT 
  Variable<AMIObject>::Variable(const boost::shared_ptr<AMIObject>& p);

template<>  LanguageBase_EXPORT 
  Variable<AMIObject>::Variable(const std::string& name, 
                                const boost::shared_ptr<AMIObject>& p);

template<>  LanguageBase_EXPORT bool 
  Variable<AMIObject>::Equal( BasicVariable::ptr v);

//------------------------------------------------------
//------- Variable<AMIObject>
//------------------------------------------------------


/// Cast to a type based on its name as a string
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::TryCast(const std::string& type_string) const; ///New Added:12-07-2010

// Copy contents to new variable
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::NewCopy() const;

template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::NewReference() const;

// Arithmetic operators

/// +a
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator +();

/// -a
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator -();


/// prefix ++ operator *a
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator *();

/// prefix ++ operator ++a
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator ++();

/// postfix ++ operator a++
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator ++(int);

/// prefix -- operator --a
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator --();

/// postfix -- operator a--
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator --(int);

/// a+b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator +(const BasicVariable::ptr& b);
/// a+=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator +=(const BasicVariable::ptr& b);

/// a-b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator -(const BasicVariable::ptr& b);

/// a-=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator -=(const BasicVariable::ptr& b);

/// a*b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator *(const BasicVariable::ptr& b);

/// a*=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator *=(const BasicVariable::ptr& b);

/// a/b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator /(const BasicVariable::ptr& b);

/// a/=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator /=(const BasicVariable::ptr& b);

/// a%b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator %(const BasicVariable::ptr& b);

/// a%=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator %=(const BasicVariable::ptr& b);


//  Comparison Operators

/// a<b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator <(const BasicVariable::ptr& b);

/// a<=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator <=(const BasicVariable::ptr& b);

/// a>b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator >(const BasicVariable::ptr& b);

/// a>=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator >=(const BasicVariable::ptr& b);

/// a!=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator !=(const BasicVariable::ptr& b);

/// a==b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator ==(const BasicVariable::ptr& b);

/// Logical operators
/// !a
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator !();

/// a&&b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator &&(const BasicVariable::ptr& b);

/// a||b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator ||(const BasicVariable::ptr& b);

// Bitwise operators
/// a^b.
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator ^(const BasicVariable::ptr& b);

/// a&b.
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator &(const BasicVariable::ptr& b);

/// a|b.
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator |(const BasicVariable::ptr& b);

template<> LanguageBase_EXPORT 
  BasicVariable::ptr Variable<AMIObject>::BasicCast(const int& type);

template<> LanguageBase_EXPORT 
  BasicVariable::ptr Variable<AMIObject>::PointWiseMult(
    const BasicVariable::ptr& b);

template<> LanguageBase_EXPORT 
  BasicVariable::ptr Variable<AMIObject>::Transpose();


// Mathematical functions

VAR_DECL_FUNC(AMIObject,sin)
VAR_DECL_FUNC(AMIObject,cos)
VAR_DECL_FUNC(AMIObject,tan)
VAR_DECL_FUNC(AMIObject,asin)
VAR_DECL_FUNC(AMIObject,acos)
VAR_DECL_FUNC(AMIObject,atan)
VAR_DECL_FUNC(AMIObject,fabs)
VAR_DECL_FUNC(AMIObject,round)
VAR_DECL_FUNC(AMIObject,floor)
VAR_DECL_FUNC(AMIObject,exp)
VAR_DECL_FUNC(AMIObject,log)
VAR_DECL_FUNC(AMIObject,ln)
VAR_DECL_FUNC(AMIObject,norm)
VAR_DECL_FUNC(AMIObject,sqrt)


/**
 * Array subscript operator,
 * @return redirects to the object member named at() if it exists
 */
template<> LanguageBase_EXPORT  BasicVariable::ptr Variable<AMIObject>::operator[](const BasicVariable::ptr& v);


/// (cond?a:b)
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::TernaryCondition(const BasicVariable::ptr& v1, const BasicVariable::ptr&v2);

/// Other operators
/// a=b

/**
 * Assignment operator
 * @return 
 **/
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator =(const BasicVariable::ptr& b);

/**
 * << operator
 * @return 
 **/
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator <<(const BasicVariable::ptr& b);

/**
 * >> operator
 * @return 
 **/
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::operator >>(const BasicVariable::ptr& b);

/**
 * Defines operator <<= for each object type, normally, it tries to force the assignation.
 * @param b 
 * @return 
 */
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<AMIObject>::left_assign(const BasicVariable::ptr& b);

#endif
// _Variable_AMIObject_h_
