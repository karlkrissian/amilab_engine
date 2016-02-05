
#ifndef _Variable_ushort_h_
#define _Variable_ushort_h_

#include "Variable.hpp"
#include "LanguageBaseConfigure.h"


//------------------------------------------------------
//------- Variable<unsigned short>
//------------------------------------------------------


/// Copy contents to new variable
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::NewCopy() const;

// Arithmetic operators

/// +a
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator +();

/// prefix ++ operator ++a
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator ++();

/// postfix ++ operator a++
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator ++(int);

/// -a
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator -();

/// prefix -- operator --a
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator --();

/// postfix -- operator a--
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator --(int);


/// a+b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator +(const BasicVariable::ptr& b);

/// a+=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator +=(const BasicVariable::ptr& b);

/// a-b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator -(const BasicVariable::ptr& b);

/// a-=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator -=(const BasicVariable::ptr& b);

/// a*b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator *(const BasicVariable::ptr& b);

/// a*=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator *=(const BasicVariable::ptr& b);

/// a/b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator /(const BasicVariable::ptr& b);

/// a/=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator /=(const BasicVariable::ptr& b);

/// a%b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator %(const BasicVariable::ptr& b);

/// a%=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator %=(const BasicVariable::ptr& b);

//  Comparison Operators

/// a<b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator <(const BasicVariable::ptr& b);

/// a<=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator <=(const BasicVariable::ptr& b);

/// a>b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator >(const BasicVariable::ptr& b);

/// a>=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator >=(const BasicVariable::ptr& b);

/// a!=b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator !=(const BasicVariable::ptr& b);

/// a==b
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator ==(const BasicVariable::ptr& b);

// Logical operators

template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator !();

template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator &&(const BasicVariable::ptr& b);

template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator ||(const BasicVariable::ptr& b);

// // Mathematical functions
// #define VAR_DECL_FUNC(type,fname) 
// template<> LanguageBase_EXPORT BasicVariable::ptr Variable<type>::m_##fname();

// VAR_DECL_FUNC(long,sin)
// VAR_DECL_FUNC(long,cos)
// VAR_DECL_FUNC(long,tan)
// VAR_DECL_FUNC(long,asin)
// VAR_DECL_FUNC(long,acos)
// VAR_DECL_FUNC(long,atan)
// VAR_DECL_FUNC(long,fabs)
// VAR_DECL_FUNC(long,round)
// VAR_DECL_FUNC(long,floor)
// VAR_DECL_FUNC(long,exp)
// VAR_DECL_FUNC(long,log)
// VAR_DECL_FUNC(long,ln)
// VAR_DECL_FUNC(long,norm)
// VAR_DECL_FUNC(long,sqrt)

/// Cast to a type based on its name as a string
template<>
BasicVariable::ptr Variable<unsigned short>::TryCast(const std::string&) const;


template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::BasicCast(const int& type);

/// (cond?a:b)
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::TernaryCondition(const BasicVariable::ptr& v1, const BasicVariable::ptr&v2);

template<>  LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator[](const BasicVariable::ptr& v);

/// Other operators
/// a=b
/**
 * Basic Assignment operator
 * if b must be a numerical value here
 * @param b 
 * @return 
 */
template<> LanguageBase_EXPORT BasicVariable::ptr Variable<unsigned short>::operator =(const BasicVariable::ptr& b);

#endif 
// _Variable_ushort_h_
