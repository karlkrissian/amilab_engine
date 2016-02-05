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
/* Style.hpp
 * Defines pour rendre la programmation plus lisible
 * Karl KRISSIAN
 * Perpignan        23/09/94
 */

#ifndef STYLE_HPP
#define STYLE_HPP

#if defined(WIN32)
  #define _CRT_SECURE_NO_WARNINGS
  #include <windows.h>
#endif

// VERSION ANGLAISE :
// ==================

//#define TRUE  1
//#define FALSE 0

//#define BeginFunction  {
//#define EndFunction    }

//#define If        if(
//#define Then      ){
//#define Else      }else{
//#define EndIf     }
//#define Otherwise }else

//#define On        if(
//#define DoReturn  ) return

//#define While     while (
//#define Do        ) {
//#define EndWhile  }

// Logical Operators

//#define Or    ||
//#define And   &&
//#define Not   !


// Switch expression In
//   Case ... :
//     ...
//   EndCase
//   ...
// EndSwitch

/*
#define Switch     switch (
#define In         ){
#define Case       case
#define EndCase    break;
#define EndSwitch  }
*/

// InitLoop i = 1 NextWhile i<=fin Step i++ Do
//   ...
// Next

#define InitLoop   for (
#define NextWhile  ;
#define Step       ;
// #define Do         ) {
#define NextLoop   }  


// C++ defines :

//#define PublicMember   ::
//#define PrivateMember  ::


// VERSION FRANCAISE :
// ===================

// Declarations :
// --------------



// Constantes :
// ------------


// Types :
// -------


// Conversions :
// -------------

#define Convertis( type, expr)  (type) (expr)

//#define Alloue                    malloc

// Fonctions :
// -----------


// Tests :
// -------

#define Si              if(
#define Alors           ){
#define Sinon               }else{
#define FinSi               }
#define Autrement           }else
#define AlorsFait               )

#define AlorsRetourne       ) return

// Operateurs :
// ------------

#define Ou              ||
#define Et              &&
#define Non             !


// switch ( expression Vaut
//   Valeur ... :
//     ...
//   FinValeur
//   ...
// FinSelonQue

//#define switch (            switch (
//#define Vaut                ){
//#define Valeur              case
//#define FinValeur           break;
//#define FinSelonQue         }
//#define Defaut                  default

// Boucles :
// ---------


//#define DebutBoucle         for (
//#define ItererTantQue       ;
//#define Pas             ;
// #define Faire        ) {
//#define FinBoucle           } 

// POUR
#define Pour(nombre, min, max)  for(nombre=min; nombre<=max; nombre++) {
#define FinPour                 }

// BOUCLE TANTQUE .. FAIRE .. FINTANTQUE

#define TantQue             while (
#define Faire               ) {
#define FinTantQue          }

// BOUCLE  REPETER .. TANTQUE .. FINREPETER

#define Repeter         do {
#define JusquA          } while (!(
#define FinRepeter      ));



#endif // define STYLE_HPP












