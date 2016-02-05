
#ifndef _Variable_WrapClassMember_h_
#define _Variable_WrapClassMember_h_

#include "Variable.hpp"

class WrapClassMember;
#include "LanguageBaseConfigure.h"

//------------------------------------------------------
//------- Variable<WrapClassMember>
//------------------------------------------------------

template<>  LanguageBase_EXPORT 
  Variable<WrapClassMember>::Variable(const boost::shared_ptr<WrapClassMember>& p);

template<>  LanguageBase_EXPORT 
  Variable<WrapClassMember>::Variable( WrapClassMember* p);

template<>  LanguageBase_EXPORT 
  Variable<WrapClassMember>::Variable(const std::string& name, 
                                const boost::shared_ptr<WrapClassMember>& p);

template<>  LanguageBase_EXPORT bool 
  Variable<WrapClassMember>::Equal( BasicVariable::ptr v);


/// Cast to a type based on its name as a string
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::TryCast(const std::string& type_string) const; ///New Added:12-07-2010


// Arithmetic operators

/// +a
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator +();

/// -a
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator -();


/// prefix ++ operator *a
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator *();

/// prefix ++ operator ++a
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator ++();

/// postfix ++ operator a++
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator ++(int);

/// prefix -- operator --a
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator --();

/// postfix -- operator a--
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator --(int);

/// a+b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator +(const BasicVariable::ptr& b);
/// a+=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator +=(const BasicVariable::ptr& b);

/// a-b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator -(const BasicVariable::ptr& b);

/// a-=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator -=(const BasicVariable::ptr& b);

/// a*b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator *(const BasicVariable::ptr& b);

/// a*=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator *=(const BasicVariable::ptr& b);

/// a/b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator /(const BasicVariable::ptr& b);

/// a/=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator /=(const BasicVariable::ptr& b);

/// a%b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator %(const BasicVariable::ptr& b);

/// a%=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator %=(const BasicVariable::ptr& b);


//  Comparison Operators

/// a<b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator <(const BasicVariable::ptr& b);

/// a<=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator <=(const BasicVariable::ptr& b);

/// a>b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator >(const BasicVariable::ptr& b);

/// a>=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator >=(const BasicVariable::ptr& b);

/// a!=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator !=(const BasicVariable::ptr& b);

/// a==b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator ==(const BasicVariable::ptr& b);

/// Logical operators
/// !a
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator !();

/// a&&b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator &&(const BasicVariable::ptr& b);

/// a||b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator ||(const BasicVariable::ptr& b);

// Bitwise operators
/// a^b.
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator ^(const BasicVariable::ptr& b);

/// a&b.
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator &(const BasicVariable::ptr& b);

/// a|b.
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator |(const BasicVariable::ptr& b);

template<> LanguageBase_EXPORT 
  BasicVariable::ptr Variable<WrapClassMember>::BasicCast(const int& type);

template<> LanguageBase_EXPORT 
  BasicVariable::ptr Variable<WrapClassMember>::PointWiseMult(
    const BasicVariable::ptr& b);

template<> LanguageBase_EXPORT 
  BasicVariable::ptr Variable<WrapClassMember>::Transpose();


// Mathematical functions

VAR_DECL_FUNC(WrapClassMember,sin)
VAR_DECL_FUNC(WrapClassMember,cos)
VAR_DECL_FUNC(WrapClassMember,tan)
VAR_DECL_FUNC(WrapClassMember,asin)
VAR_DECL_FUNC(WrapClassMember,acos)
VAR_DECL_FUNC(WrapClassMember,atan)
VAR_DECL_FUNC(WrapClassMember,fabs)
VAR_DECL_FUNC(WrapClassMember,round)
VAR_DECL_FUNC(WrapClassMember,floor)
VAR_DECL_FUNC(WrapClassMember,exp)
VAR_DECL_FUNC(WrapClassMember,log)
VAR_DECL_FUNC(WrapClassMember,ln)
VAR_DECL_FUNC(WrapClassMember,norm)
VAR_DECL_FUNC(WrapClassMember,sqrt)


/**
 * Array subscript operator,
 * @return redirects to the object member named at() if it exists
 */
template<> LanguageBase_EXPORT  BasicVariable::ptr Variable<WrapClassMember>::operator[](const BasicVariable::ptr& v);


/// (cond?a:b)
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::TernaryCondition(const BasicVariable::ptr& v1, const BasicVariable::ptr&v2);

/// Other operators
/// a=b

/**
 * Assignment operator
 * @return 
 **/
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::operator =(const BasicVariable::ptr& b);

/**
 * Defines operator <<= for each object type, normally, it tries to force the assignation.
 * @param b 
 * @return 
 */
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<WrapClassMember>::left_assign(const BasicVariable::ptr& b);

#endif
// _Variable_WrapClassMember_h_
