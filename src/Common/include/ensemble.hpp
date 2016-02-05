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
/**
   classe ensemble d'elements quelconques 
*/


#ifndef _ENSEMBLE_HPP
#define _ENSEMBLE_HPP


#define Bool short int
#define true 1
#define false 0

/**
  classe liste de base 
*/
template < class T >
class liste_base
{
private:

  ///
  T info;

  ///
  liste_base<T> * suivant;
public:

  /// 1er constructeur
  liste_base()  	{ suivant = 0; }

  /// 2e  constructeur
  liste_base(T t) { info = t; suivant=0; }  

  ///
  T Valeur() 	{ return info; }

  ///
  liste_base<T> * Succ()	{ return suivant; }

  ///
  void MetSucc(liste_base<T> * lbt) { suivant = lbt; }
};

/**
  classe ensemble 
*/
template < class T >
class Ensemble
{
  ///
  liste_base<T> * ensemble,* position;

  /// position et indice permettent de parcourir plus rapidement l'ensemble
  int taille,indice;

public:

  Ensemble() { ensemble = position = 0;
			   taille   = indice   = 0;}
  Bool Vide() { return ensemble==0; }
  int Nbelts() { return taille;}

  /** prendre le i-eme element de l'ensemble 
     cette fonction permet le parcours de l'ensemble dans une boucle
     sans reparcourir tous les elements precedents
  */
  T * EltNumero(int);

  /** test d'appartenance 
      le test d'egalite == doit s'appliquer a T 
   */
  Bool contient(T); 

  /** ajout d'un element a l'ensemble */
  Ensemble<T> operator+=(T);

  /** union de 2 ensembles */
  Ensemble<T> operator+=(Ensemble);

  /** idem */
  friend Ensemble<T> operator +(Ensemble<T>,Ensemble<T>);

  /** intersection */
  friend Ensemble<T> operator *(Ensemble<T>,Ensemble<T>); 

  /** enlever un element */
  Ensemble<T> operator-=(T);

};

template<class T>
T * Ensemble<T>::EltNumero(int n)
// prendre le n-eme element de l'ensemble
// cette fonction permet le parcours de l'ensemble dans une boucle
// sans reparcourir tous les elements precedents
{
	T valeur;
	if ((n>taille)||(n<1)) return 0;
	if ((n<indice)||(indice==0))
	{
		position=ensemble;
		indice=1;
	};
	while(indice<n)
	{
		position = position->Succ();
		indice++;
	}
	valeur = position->Valeur();
	return &(valeur);
}

template<class T>
Bool Ensemble<T>::contient(T t)
/* test d'egalite == doit s'appliquer a T */
{
	liste_base<T> * reste;
	reste = ensemble;
	while (reste != 0)
	{
		if (reste->Valeur()==t) return true;
		reste = reste ->Succ();
	}
	return false;
}

template<class T>
Ensemble<T> Ensemble<T>::operator+=(T t) /* ajout d'un element a l'ensemble */
{
	liste_base<T> * liste;
	if (!contient(t))
	{
		liste = new liste_base<T>(t);
		liste->MetSucc(ensemble);
		ensemble = liste;
		taille++;
	}
	return *this;
}

template<class T>
Ensemble<T> Ensemble<T>::operator+=(Ensemble<T> e) /* union de 2 ensembles */
{
	liste_base<T> * liste,* l;
	T element;

	l = liste = 0;
	for(int i=1; i<=e.Nbelts(); i++)
	{
		element = *(e.EltNumero(i));
		if (!contient(element)) // on ne parcours que l'ensemble initial
		{
			l = new liste_base<T>(element);
			if (liste==0) l->MetSucc(ensemble);
			// si c'est le 1er element ajoute son successeur est 'ensemble'
			else l->MetSucc(liste);
			taille++;
			liste = l;
		}
	}
	if (liste!=0)  ensemble = liste;
	return *this;
}

template<class T>
Ensemble<T> operator+(Ensemble<T> e1, Ensemble<T> e2)
{
	Ensemble<T> e3;
	e3+=e1;
	e3+=e2;
	return e3;
}

template<class T>
Ensemble<T> operator*(Ensemble<T> e1, Ensemble<T> e2)
{
	Ensemble<T> e3;
	T element;
	liste_base<T> * liste;
	for(int i=1; i<=e2.Nbelts(); i++)
	{
		element = *(e2.EltNumero(i));
		if (e1.contient(element))
		{
			liste = new liste_base<T>(element);
			liste->MetSucc(e3.ensemble);
			e3.ensemble = liste;
			e3.taille++;
		}
	}
	return e3;
}

template<class T>
Ensemble<T> Ensemble<T>::operator-=(T t) /* enlever un element */
{
	liste_base<T> *liste;

	if (ensemble==0) return *this;
	if (ensemble->Valeur()==t)
	{
		ensemble = ensemble->Succ();
		taille--;
		return *this;
	}
	liste = ensemble;
	while (liste->Succ() !=0 )
	{
		if (liste->Succ()->Valeur() == t)
		{
			liste->MetSucc(liste->Succ()->Succ());
			taille--;
			break;
		}
		liste = liste->Succ();
	}
	return *this;
}


#endif // _ENSEMBLE_HPP
