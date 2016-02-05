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
/* Math1.hpp 
 * Analyse d'une expression math�matique sous forme de chaine de caract�res
 * reprise du programme en pascal
 * Karl KRISSIAN
 * Perpignan		22/09/94
 */

#ifndef _MATH1_HPP
#define _MATH1_HPP

#include <math.h>
#include "chaine.hpp"
#include "CommonConfigure.h"

#ifndef PI
const double PI = 3.141592741;
#endif

/*
#if ( defined(_solaris_) ) 
#define cosd(x)     cos((x)*PI/180.0)
#define sind(x)     sin((x)*PI/180.0)
#define atand2(y,x) (atan2(y,x)*180.0/PI)
#define fabsf(x)    fabs(x)
#define log2f(x)    (float) (log(x)/log(2))
#define atan2f(y,x) (atan2(y,x))
#endif

#if defined(_sgi_) || defined(_linux_) 
#define cosd(x)     cos((x)*PI/180.0)
#define sind(x)     sin((x)*PI/180.0)
#define atand2(y,x) (atan2(y,x)*180.0/PI)
#define log2f(x)    (logf(x)/logf(2))
//#define logf(x)    (log(x))
//#define fabsf(x)    fabs(x)
#endif
*/

#define cosd(x)     cos((x)*PI/180.0)
#define sind(x)     sin((x)*PI/180.0)
#define atand2(y,x) (atan2(y,x)*180.0/PI)
#if (!defined(log2f)) 
 #define log2f(x)    (logf(x)/logf(2))
#endif

#ifndef macro_min
  #define macro_min(n1,n2) ((n1)<(n2)?(n1):(n2))
#endif

#ifndef macro_max
  #define macro_max(n1,n2) ((n1)>(n2)?(n1):(n2))
#endif 

#define macro_abs(n)     ((n)>0?(n):-(n))

typedef char st46[46];
typedef char st68[68];

enum Token {

  //
  Tok_addition,
  Tok_soustraction,

  //
  Tok_multiplication,
  Tok_division,

  // Conditions
  Tok_superieur,
  Tok_inferieur,
  Tok_egal,
  Tok_et,
  Tok_ou,

  // valeurs r�elles
  Tok_nombre,

  // fonctions � 1 parametre
  Tok_parametre,

  Tok_sinus,
  Tok_cosinus,
  Tok_valeur_absolue,
  Tok_tangente,
  Tok_arc_tangente,
  Tok_arc_sinus,
  Tok_arc_cosinus,
  Tok_exponentielle,
  Tok_logarithme_neperien,
  Tok_logarithme10,
  Tok_round,
  Tok_cosinus_hyperbolique,
  Tok_sinus_hyperbolique,
  Tok_valeur_entiere,

  // 
  Tok_puissance,
  Tok_factorielle,
  Tok_degre,

  // int�grale : cas particulier
  Tok_integrale

};

int   comb           ( int p, int n);
float abs            ( float);
float puis           ( float a, float b);
float nombre         ( st46 a);

/* ===========================================================================
 * Expression compil�e
 */

class COMMON_EXPORT CompileExpr
//                  ===========
{


  // Tableau des instructions
  Token* Instruction;
  int Taille_Instr;
  int Instr_Pos;

  // Tableau des nombres
  float*  TabNombre;
  int Taille_Nombre;
  int Nombre_Pos;

  // Pile de calcul
  float*  Pile;
  int Taille_Pile;
  int Pile_Pos;

protected:

  float ParamValue[10];
  int    Erreur; // 0: pas d'erreur,
		 // 1: erreur de syntaxe,
		 // 2: erreur dans le calcul
                 // 3: erreur syntaxe + calcul

  // Construction des instructions
  void AjouteNombre( float);
  void AjouteInstruction( Token);

public:

   CompileExpr();
  ~ CompileExpr();
  float         Resultat();

}; // CompileExpr


/* ===========================================================================
 * Expression math�matique :
 */

//#ifndef NO_ERROR
//#define NO_ERROR     0
//#endif

#define SYNTAX_ERROR 1
#define CALCUL_ERROR 2

class COMMON_EXPORT ExprMath : public CompileExpr
//                  ========
{

  Chaine chaine;
  char   Parameter[10];
  int NumberOfParameters;

  int    pos;
  int    LastPos;
  int a_compiler; // bool�en

   private:
// ============= 

  //float integrale( int, int, float, float, int);
  //    ---------

  int   CanBeDigit( char);
  //    ----------

  void  recherche( char, char, int&, int&);
  //    ---------

  void  SauteBlancs();
  //    -----------

  void  HigherLevel();
  //    -----------

  void  PuisTerm();
  //    --------

  void  MultTerm();
  //    ---------

  void  AddTerm();
  //    -------

  void  Compile( int, int);
  //    -------

   public:
// ================

    ExprMath( Chaine&, char param1 = 'X' , char param2 = 'V');
  //--------

  float Value( float val1, float val2 = 0); // 2 param�tres
  //    -----

  int AddParameter( char);
  //     ------------

  int SetParamValue( char, float);
  //     -------------

  int Erreurs();
  //     -------

}; // ExprMath

#endif
// END.
