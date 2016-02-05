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
// Gestion des erreurs,
// variables globales
// et recuperation des exceptions
//


#ifndef _ERREURS_MAIN_HPP_
#define _ERREURS_MAIN_HPP_

#include "style.hpp"
#include "Erreurs.hpp"
#include <iosfwd>


//-------------------------------------------------------------------
// VARIABLES GLOBALES
//-------------------------------------------------------------------

#include "amilab_global_import.h"
//Pile<NomMethode*> GB_pile_nom_methode((NomMethode*)NULL);
//unsigned char GB_AfficheWarning = false;
//unsigned char GB_AfficheErreur  = false;



//-------------------------------------------------------------------
// UNEXPECTED EXCEPTION
//-------------------------------------------------------------------
/*

class unexpected
{
};

///
typedef void(*PFV)();

///
PFV set_unexpected(PFV); //throw (unexpected);

///
class SRC_unexpected{ // store and reset class
  PFV old;
public:
  SRC_unexpected(PFV f) { old = set_unexpected(f); }
  ~SRC_unexpected() {set_unexpected(old); }
};

///
void new_unexpected()
{
  std::cerr << "new_unexpected()" << std::endl;
  //  throw unexpected();
}

//-------------------------------------------------------------------
// UNCAUGHT EXCEPTION
//-------------------------------------------------------------------




class uncaught
{
};

///
PFV set_terminate(PFV); //throw (uncaught);


class SRC_terminate{
  PFV old;
public:
  SRC_terminate(PFV f) { old = set_terminate(f); }
  ~SRC_terminate() {set_terminate(old); }
};

///
void new_terminate()
{
 std::cout << "new_terminate()" << std::endl;
  //  throw uncaught();
}


//----------------------------------------------------
SRC_unexpected src_u(new_unexpected);
SRC_terminate  src_t(new_terminate);


*/


#endif // _ERREURS_MAIN_HPP_
