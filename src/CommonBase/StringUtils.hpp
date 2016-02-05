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

#ifndef _STRINGUTILS_HPP
#define _STRINGUTILS_HPP

//#include "StringUtils.hpp"
#include "CommonBaseConfigure.h"
#include <string>



CommonBase_EXPORT unsigned char CheckEndString( const char* st1, const std::string end);
/*
{
  int l1 = strlen(st1);
  int l2 = strlen(end);
  int i,j;

  if (l2>l1) return false;

//  unsigned char found = true;

  i = l1-l2;
  j = 0;
  while ((st1[i]==end[j])&&(j<l2)) { i++; j++; }
  
  if (j==l2) {
    return true;
  }
  else
    return false;
  
}
*/

CommonBase_EXPORT unsigned char RemoveEndString( char* st1, const char* end);
/*
{
  int l1 = strlen(st1);
  int l2 = strlen(end);
  int i,j;

  if (l2>l1) return false;

  unsigned char found = true;

  i = l1-l2;
  j = 0;
  while ((st1[i]==end[j])&&(j<l2)) { i++; j++; }
  
  if (j==l2) {
    st1[l1-l2]='\0';
    return true;
  }
  else
    return false;
  
}
*/

#endif
