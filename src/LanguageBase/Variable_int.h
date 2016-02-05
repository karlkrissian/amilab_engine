
#ifndef _Variable_int_h_
#define _Variable_int_h_

#include "Variable.hpp"
#include "LanguageBaseConfigure.h"

//------------------------------------------------------
//------- Variable<int>
//------------------------------------------------------

template<>  LanguageBase_EXPORT 
  Variable<int>::Variable(const boost::shared_ptr<int>& p);

template<>  LanguageBase_EXPORT 
  Variable<int>::Variable(const std::string& name, 
                                const boost::shared_ptr<int>& p);

template<>  LanguageBase_EXPORT bool 
  Variable<int>::Equal( BasicVariable::ptr v);


/// Copy contents to new variable
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::NewCopy() const;

// Arithmetic operators

/// +a
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator +();

/// prefix ++ operator ++a
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator ++();

/// postfix ++ operator a++
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator ++(int);

/// -a
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator -();

/// prefix -- operator --a
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator --();

/// postfix -- operator a--
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator --(int);


/// a+b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator +(const BasicVariable::ptr& b);

/// a+=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator +=(const BasicVariable::ptr& b);

/// a-b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator -(const BasicVariable::ptr& b);

/// a-=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator -=(const BasicVariable::ptr& b);

/// a*b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator *(const BasicVariable::ptr& b);

/// a*=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator *=(const BasicVariable::ptr& b);

/// a/b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator /(const BasicVariable::ptr& b);

/// a/=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator /=(const BasicVariable::ptr& b);

/// a%b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator %(const BasicVariable::ptr& b);

/// a%=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator %=(const BasicVariable::ptr& b);

//  Comparison Operators

/// a<b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator <(const BasicVariable::ptr& b);

/// a<=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator <=(const BasicVariable::ptr& b);

/// a>b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator >(const BasicVariable::ptr& b);

/// a>=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator >=(const BasicVariable::ptr& b);

/// a!=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator !=(const BasicVariable::ptr& b);

/// a==b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator ==(const BasicVariable::ptr& b);

// Logical operators

template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator !();

template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator &&(const BasicVariable::ptr& b);

template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator ||(const BasicVariable::ptr& b);

template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator ^(const BasicVariable::ptr& b);

template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator |(const BasicVariable::ptr& b);

template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator &(const BasicVariable::ptr& b);

// // Mathematical functions, 
// #define VAR_DECL_FUNC(type,fname) 
// template<> LanguageBase_EXPORT BasicVariable::ptr Variable<type>::m_##fname();

// TODO: don t define trigonometry for int, it should be floating point
// and these functions should not be operators ...
/*
VAR_DECL_FUNC(int,sin)
VAR_DECL_FUNC(int,cos)
VAR_DECL_FUNC(int,tan)
VAR_DECL_FUNC(int,asin)
VAR_DECL_FUNC(int,acos)
VAR_DECL_FUNC(int,atan)
*/
VAR_DECL_FUNC(int,fabs)
/* no rounding or exp
VAR_DECL_FUNC(int,round)
VAR_DECL_FUNC(int,floor)
VAR_DECL_FUNC(int,exp)
VAR_DECL_FUNC(int,log)
VAR_DECL_FUNC(int,ln)
*/
VAR_DECL_FUNC(int,norm)
VAR_DECL_FUNC(int,sqrt)
//VAR_DECL_FUNC(int,pow)


/// Cast to a type based on its name as a string
template<> LanguageBase_EXPORT
BasicVariable::ptr Variable<int>::TryCast(const std::string&) const;

template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::BasicCast(const int& type);

/// (cond?a:b)
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::TernaryCondition(const BasicVariable::ptr& v1, const BasicVariable::ptr&v2);

template<>  LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator[](const BasicVariable::ptr& v);

/// Other operators
/// a=b
/**
 * Basic Assignment operator
 * if b must be a numerical value here
 * @param b 
 * @return 
 */
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<int>::operator =(const BasicVariable::ptr& b);

#endif 
// _Variable_long_h_
