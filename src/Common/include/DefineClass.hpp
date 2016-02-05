/*
    ==================================================
    Software : AMILab
    Authors  : Karl Krissian
    Email    : karl@bwh.harvard.edu

    AMILab is a language for image processing
    ==================================================
    Copyright (C) 1996-2005  Karl Krissian

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    ==================================================
   The full GNU Lesser General Public License file is in Devel/Sources/Prog/LesserGPL_license.txt
*/
//
//  Author: Karl Krissian
//
//

#ifndef _DefineClass_hpp_
#define _DefineClass_hpp_

#include "AMILabEngineConfig.h"

//--- string formatting using boost
//#include <iostream>
//#include <string>
// need these includes to prevent conflicts with boost iostream ...
// #include <iomanip>
// #include <cassert>
// #include "boost/format/format_fwd.hpp"

#include <boost/shared_ptr.hpp>
//#include <boost/shared_array.hpp>
#include <boost/weak_ptr.hpp>
/*#include <list>
#include <vector>*/
//#include <stdio.h>
 
// TODO: deal with templates here ...

#define DEFINE_CLASS(class) \
public:\
  virtual char const* get_name() const { return #class; } \
  typedef boost::shared_ptr<class>    ptr;              \
  typedef boost::weak_ptr<class>      wptr;             \

#define DEFINE_TEMPLATE_CLASS1(_class,_t) \
public:\
  virtual char const* get_name() const { return (std::string(#_class)+"<T>").c_str(); }  \
  typedef _class<_t> ClassType; \
  typedef typename boost::shared_ptr<ClassType >    ptr; \
  typedef typename boost::weak_ptr<ClassType >      wptr; \


template<class T>
class wxwindow_deleter
  {
  public:
    void operator()(T * p)
    {
      if (p!=NULL) p->Destroy();
    }
  };

template<class T>
class wxwindow_nodeleter
  {
  public:
    void operator()(T * p)  {  }
  };


#define new_wxWindow_ptr(_class,_parent) \
  _class::ptr(new _class(_parent),wxwindow_nodeleter<_class>())

#define new_wxWindow_ptr_deleter(_class,_parent) \
  _class::ptr(new _class(_parent),wxwindow_deleter<_class>())

// no special type added
#define DEFINE_SIMPLE_CLASS(class) \
public:\
  virtual char const* get_name() const { return #class; }

#include "amilab_boost.h"


#ifdef  _MSC_VER
  #define AMI_DLLEXPORT __declspec( dllexport )
#else 
  #define AMI_DLLEXPORT
#endif

#endif // _DefineClass_hpp_
