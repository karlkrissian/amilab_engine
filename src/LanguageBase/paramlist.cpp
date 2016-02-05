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

#include <iomanip>
#include <cassert>
#include "boost/format.hpp"

#include "paramlist.h"
//class DessinImage;
//class Viewer3D;




//-------  implementation class ParamList

/**
  * Constructor
  */
ParamList::ParamList()
  {
  }

//  ~ParamList();


/**
  * 
  * @return the number of parameters
  */
int ParamList::GetNumParam() { return (int)params.size(); }

/**
  * 
  * @param i 
  * @return the type of the parameter i
  */
vartype ParamList::GetType( int i) { 
  if (i<0) {
    fprintf(stderr,"ParamList:: GetType() negative param number \n");
    i=0; 
  }
  if (i>=(int)GetNumParam()) {
    fprintf(stderr,"ParamList:: GetType()  param number too high \n");
    i = (int)GetNumParam()-1; 
  }

  return params[i]->Type();
}

bool ParamList::AddParam( const BasicVariable::ptr& var) {
  params.push_back(var);
  return true;
}

BasicVariable::ptr ParamList::GetParam(int i)    
{
  int nbp = GetNumParam();
  if ((i<0)||(i>=nbp)) {
      CLASS_ERROR((boost::format("Wrong parameter number %1% not in [0, %2%]") % i % (nbp-1)).str().c_str());
      return BasicVariable::ptr();
  } else
    return params[i];
}

//-------  end implementation class ParamList


//-------  implementation class ParamListDecl

ParamListDecl::ParamListDecl()
{
    num_param = 0;
}

ParamListDecl::~ParamListDecl()
{
}

int ParamListDecl::GetNumParam() 
{ 
  return num_param; 
}

vartype ParamListDecl::GetType( int i) 
{
    if (i<0) {
      fprintf(stderr,"ParamList:: GetType() negative param number \n");
      return type[0]; 
    }
    if (i>=num_param) {
      fprintf(stderr,"ParamList:: GetType()  param number too high \n");
      return type[num_param-1]; 
    }
    return type[i];
}

char* ParamListDecl::GetName( int i) 
{
    if (i<0) {
      fprintf(stderr,"ParamList:: GetName() negative param number \n");
      return (char*) name[0].c_str(); 
    }
    if (i>=num_param) {
      fprintf(stderr,"ParamList:: GetName()  param number too high \n");
      return (char*) name[num_param-1].c_str(); 
    }
    return (char*) name[i].c_str();
}

unsigned char ParamListDecl::AddParam( const std::string& st, vartype t)
{
    if ( num_param<MAX_PARAM-2 )
    {
      name[num_param] = st;
      type[num_param] = t;
      num_param++;
      return 1;
    }
    else
    {
      fprintf ( stderr,"ParamListDecl::AddParam() \t too many parameters \n" );
      return 0;
    }
}

unsigned char ParamListDecl::GetParam( int num, std::string& st, vartype& t, bool needed)
{
    if ((num>=0)&&(num<num_param)) {
      st = name[num];
      t  = type[num];
      return 1;
    }
    else {
      if (needed)
        fprintf(stderr,"ParamListDecl::GetParam()\t bad parameter number\n");
      return 0;
    }
}

bool ParamListDecl::CheckParam( ParamList* pl) 
{
    int       i;
    //void*     p;
    //vartype t;
    if ( pl->GetNumParam() != GetNumParam() )
    {
      fprintf ( stderr,"Bad number of parameters \n" );
      return false;
    }

    // Can't be that strict since there can be automatic conversion ...
    for ( i=0;i<(int)GetNumParam();i++ )
    {
      //  pl->GetParam( i, p, t);
      //  printf("%d: %d %d \n",i,t,type[i]);
      // treat numeric (float) type separately ...
      if (GetType(i)!=type_any)
      {
        if (GetType(i) == type_float)
        {
          // only check that the parameter is of numeric type
          if (!pl->GetParam(i)->IsNumeric()) return false;
        } else {
          if ( pl->GetType ( i ) !=GetType ( i ) )
          {
            fprintf ( stderr,"Parameter %d has incorrect type \n",i );
            return false;
          }
        }
      }
    }

  
    return true;
}


// end implementation class ParamListDecl


