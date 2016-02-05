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
//  Fichier param.cpp
//
//  Parametre des programmes
//
//  Karl KRISSIAN           Sophia Antipolis, le 05-06-96
//


#ifdef _MSC_VER
  #define _CRT_SECURE_NO_WARNINGS
#endif 
#include "ficparam.hpp"

// -----------------------------------------------------------
Parametres ::  Parametres()
//                        ------------
{

  pfichier = (FILE*) NULL;

} // Constructor Parametres()


// -----------------------------------------------------------
Parametres :: ~Parametres()
//                        -----------
{

  Si pfichier != (FILE*) NULL Alors
   fclose(pfichier);
   pfichier = (FILE*) NULL;
  FinSi

} // Destructor Parametres()


// -----------------------------------------------------------
void Parametres :: NomFichier( char* fic_param)
//                             ----------
{

#ifdef _MSC_VER
  fopen_s( &pfichier,fic_param, "r");
#else
  pfichier = fopen( fic_param, "r");
#endif
  Si pfichier == NULL Alors
    printf(" Erreur dans l'ouverture du fichier de parametres %s \n"
           , fic_param);
  FinSi

} // NomFichier()


// -----------------------------------------------------------
void Parametres :: LitEntier( int* n)
//                             ---------
{

  fscanf( pfichier, "%d", n);
  printf("%d",*n);

} // LitEntier()


// -----------------------------------------------------------
void Parametres :: LitUCHAR( unsigned char* n)
//                             ---------
{
  int i;
  fscanf( pfichier, "%d", &i);
  *n = (unsigned char) i;
  printf("%d",(int) *n);

} // LitEntier()


// -----------------------------------------------------------
void Parametres :: LitPointeur( void** pt)
//                             -----------
{

  fscanf( pfichier, "%p", pt);
  printf("%p",*pt);

} // LitPointeur()


// -----------------------------------------------------------
void Parametres :: LitReel( float* r)
//                             -------
{

  fscanf( pfichier, "%f", r);
  printf("%f",*r);

} // LitReel()


// -----------------------------------------------------------
void Parametres :: LitChaine( char* ch)
//                             ---------
{

  fscanf( pfichier, "%s", ch);
  printf("%s", ch);

} // LitChaine()


// -----------------------------------------------------------
void Parametres :: LitChaine( std::string& ch)
//                             ---------
{

   char chaine[100];

  fscanf( pfichier, "%s", chaine);
  printf( "%s", chaine);
  ch = std::string(chaine);

} // LitChaine()


// -----------------------------------------------------------
void Parametres :: Parcours( const char* ch)
//                             --------
{

  fscanf( pfichier, ch);
  printf( "%s",ch );

} // LitChaine()

















