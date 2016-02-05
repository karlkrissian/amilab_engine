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
// fichier ficparam.hpp
//
// Traitement des parametre pour les programmes
//
// Karl KRISSIAN
// Sophia Antipolis,      le 05-06-96
//

#ifndef PARAM_HPP

#define PARAM_HPP


#include "style.hpp"
#include <string>

#include "CommonConfigure.h"

extern "C" {
#include <stdio.h>
}

class COMMON_EXPORT Parametres
//                  ==========
{

  std::string NomFicSortie;
  std::string NomFicParam;
  FILE*  pfichier;

public:
  
     Parametres();
  //------------

    ~Parametres();
  //-----------

  void NomFichier( char*);
  //   ----------

  unsigned char FichierOK()
  //      ---------
  {
    return (pfichier!=NULL);
  }

  unsigned char EndFile()
  //      -------
  {
    return (feof(pfichier));
  }

  void LitReel( float*);
  //   -------

  void LitEntier( int*);
  //   ---------

  void LitUCHAR( unsigned char*);
  //   ---------

  void LitPointeur( void**);
  //   -----------

  void LitChaine( char*);
  //   ---------

  void LitChaine( std::string&);
  //   ---------
  
  void Parcours( const char*);
  //   --------


}; // Parametres



#endif // PARAM_HPP
