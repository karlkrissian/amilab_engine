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
// Fichier Erreurs.hpp
//
// Gestion des erreurs
//
// Karl Krissian        Sophia Antipolis le 15-08-98
//

#pragma once
#ifndef _ERREURS_HPP
#define _ERREURS_HPP


#include <iosfwd>

#include <string>
#include <iostream>

#include "CommonConfigure.h"

class ExceptionErreur;
class NomMethode;
 
/* Variables Globales */
/*
  liste des exceptions
 */

/*
  pile des methodes utilisees
 */


#include "CommonConfigure.h"

#include "common_global_import.h"
//COMMON_EXPORT Pile<NomMethode*> GB_pile_nom_methode;
//COMMON_EXPORT unsigned char GB_AfficheWarning;
//COMMON_EXPORT unsigned char GB_AfficheErreur;

///
void AffichePileNomMethode();

//NomMethode* Pile<NomMethode*>::_defaut = NULL;

///
static  std::string GB_mess_warning[1] = {
  "Warning              "
};


///
static  std::string GB_mess_erreur[4] = {
  "Erreur de Calcul     ",
  "Erreur d'allocation  ",
  "Erreur de parametres ",
  "Erreur divers        "
};


typedef 
/**
@name type_warning
 */
enum { 
  ///
   WARNING_DIVERS 
} type_warning;

typedef 
/**
@name type_erreur
 */
enum { 
  ///
  ERREUR_CALCUL     = 0,
  ///
  ERREUR_ALLOCATION = 1,
  ///
  ERREUR_PARAMETRES,
  ///
  ERREUR_DIVERS 
}   type_erreur;



/**
 */
class NomClasse
//     ---------
{

public:
  ///
  std::string _nom_classe;

  ///
   NomClasse( const std::string& nom):_nom_classe(nom) {}

};


/**
 */
class NomMethode : public NomClasse
//     ---------- 
{

public:

  ///
  std::string _nom_fichier;
  ///
  std::string _nom_methode;

  ///
   NomMethode( const std::string& classe="?", 
			   const std::string& fichier="?",
			   const std::string& methode="?"):
    NomClasse(classe),
    _nom_fichier(fichier),
    _nom_methode(methode)
  {}

  /// Message
  friend COMMON_EXPORT std::ostream& operator<<(std::ostream&, const NomMethode&);

};



/**
class Exception
 */

// class COMMON_EXPORT Exception 
// //                  ---------
// {
// 
// protected:
// 
//   ///
//   NomMethode    _nom_methode;
//   ///
//   std::string        _message;
// 
// public:
// 
//   /// constructeur
//    Exception( const std::string& mess): _message(mess) 
//   {
//     NomMethode* top;
//     top = GB_pile_nom_methode.top();
//     if (top!=NULL) 
//       _nom_methode = *top;
//   }
// 
// 
// }; // ExceptionErreur


// /**
// class ExceptionErreur
//  */
// class COMMON_EXPORT ExceptionErreur : public Exception
// //                  ---------------
// {
// 
// protected:
// 
//   ///
//   type_erreur  _type;
// 
// public:
// 
//   /// constructeur
//    ExceptionErreur( const std::string& mess) : Exception( mess) 
//   {
//   }
// 
//   /// Message
//   friend COMMON_EXPORT std::ostream& operator<<(std::ostream&, const ExceptionErreur&);
// 
// }; // ExceptionErreur
// 
// 
// /**
// class ExceptionWarning
//  */
// class COMMON_EXPORT ExceptionWarning : public Exception
// //     ---------------
// {
// 
// protected:
// 
//   ///
//   type_warning  _type;
// 
// public:
// 
//   /// constructeur
//    ExceptionWarning( const std::string& mess) : Exception( mess) 
//   {
//   }
// 
//   /// Message
//   friend COMMON_EXPORT std::ostream& operator<<(std::ostream&, const ExceptionWarning&);
// 
// }; // ExceptionWarning
// 
// 
// /**
//  */
// class COMMON_EXPORT WarningDivers: public ExceptionWarning
// //     -------------
// {
// 
// public:
// 
//   ///
//    WarningDivers( const std::string& mess);
// 
// }; // WarningDivers
// 

// /**
//  */
// class COMMON_EXPORT ErreurDivers: public ExceptionErreur
// //     ------------
// {
// 
// public:
// 
//   ///
//    ErreurDivers( const std::string& mess);
// //   {
// //     _type = ERREUR_DIVERS; 
// //     Si GB_AfficheErreur AlorsFait std::cerr << *this;
// //   }
// 
// }; // ErreurDivers


// /**
//  */
// class COMMON_EXPORT ErreurParametres: public ExceptionErreur
// //     ----------------
// {
// 
// public:
// 
//   ///
//   ErreurParametres( const std::string& mess);
// 
// }; // ErreurParametres


// /**
//  */
// class COMMON_EXPORT ErreurAllocation: public ExceptionErreur
// //     ----------------
// {
// 
// public:
// 
//   ///
//    ErreurAllocation( const std::string& mess) : 
//     ExceptionErreur(mess)
//   {
//     _type = ERREUR_ALLOCATION;
//     if (GB_AfficheErreur) 
//       std::cerr << *this;
//   }
// 
// }; // ErreurParametres


// /**
//  */
// class COMMON_EXPORT ErreurCalcul: public ExceptionErreur
// //     ------------
// {
// 
// public:
// 
//   ///
//    ErreurCalcul( std::string& mess);
// //   {
// //      _type = ERREUR_CALCUL;
// //     Si GB_AfficheErreur AlorsFait std::cerr << *this;
// //   }
// 
// }; // ErreurParametres
// 



//---------------------------------------------------------------------
/** class de Gestion des Erreurs
 */
class COMMON_EXPORT GestionErreurs
//                  --------------
{

  ///
  std::string _nom_fichier;
  ///
  std::string _nom_classe;
  ///
  std::string _nom_methode_courante;

  ///
  unsigned char _debug;

public:

  ///
   GestionErreurs( const std::string nomclasse)
  //           --------------
{
  _nom_classe = nomclasse;
  InitMessages();

  _debug = false;
}


  ///
  ~ GestionErreurs();
  //

  ///
  void SetDebug( unsigned char debug) { _debug = debug; }
  //   --------

  ///
  void SetNomClasse( std::string nomclasse) { _nom_classe = nomclasse; }
  //   ------------

  ///
  void InitMessages()
  //
  {

  /*
    GB_mess_warning[WARNING_DIVERS] = "Warning";

    GB_mess_erreur[ERREUR_CALCUL]     = "Erreur de Calcul";
    GB_mess_erreur[ERREUR_ALLOCATION] = "Erreur d'allocation";
    GB_mess_erreur[ERREUR_PARAMETRES] = "Erreur de parametres";
    GB_mess_erreur[ERREUR_DIVERS]     = "Erreur";
  */

  }

  ///
  void MethodeCourante(  const std::string& nom, const std::string& fichier="?");
  //   ---------------

  ///
  void FinMethode( );
  //   ----------

  ///
  void AfficheWarning( type_warning type, const std::string& mess);
  //   --------------

  ///
  void AfficheErreur( type_erreur type, const std::string& mess);
  //   -------------


}; // GestionErreurs






#endif // _ERREURS_HPP
