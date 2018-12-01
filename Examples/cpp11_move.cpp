//==================================================================================================
// EXEMPLES C++11                                                                    cpp11_move.cpp
//                                                                               Par Bruno Bachelet
//==================================================================================================
// Copyright (c) 2014-2016
// Bruno Bachelet - bruno@nawouak.net - http://www.nawouak.net
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the license, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
// more details (http://www.gnu.org).

// Cet exemple illustre les possibilites offertes par les references "rvalue"
// et les operateurs de mouvement. Il est conseille de commencer la lecture
// par la fonction "main" pour comprendre l'exemple.
//
// Plus d'explications ici: http://www.nawouak.net/?doc=course.cpp11+ch=move
//
// ATTENTION: Il s'agit d'un exemple pour illustrer les nouvelles
// fonctionalites de la norme C++11. Le code n'est donc pas forcement complet
// et ne reflete pas toujours de bonnes pratiques de developpement.

// Entetes //---------------------------------------------------------------------------------------
#include <iostream>
#include <cpp11_typeinfo.hpp>

// Classe  V e c t e u r //-------------------------------------------------------------------------
class Vecteur {
 //----------------------------------------------------------------------------------------Attributs
 private:
  int *    tab_;
  unsigned taille_;

 //---------------------------------------------------------------------------------------Accesseurs
 public:
  int      operator [] (unsigned i) const { return tab_[i]; }
  int &    operator [] (unsigned i) { return tab_[i]; }
  unsigned getTaille(void) const { return taille_; }

 public:

 //-------------------------------------------------------------------------------------Constructeur
 explicit Vecteur(unsigned taille) : tab_(new int[taille]),taille_(taille) {
  std::cout << "=> Vecteur(unsigned)" << std::endl;
  for (unsigned i = 0; i<taille_; ++i) tab_[i]=0;
 }

 //-----------------------------------------------------------------------------Constructeur (Copie)
 Vecteur(const Vecteur & v) : tab_(new int[v.taille_]),taille_(v.taille_) {
  std::cout << "=> Vecteur(const Vecteur &)" << std::endl;
  for (unsigned i = 0; i<taille_; ++i) tab_[i]=v.tab_[i];
 }

 //------------------------------------------------------------------------------------depouiller_v1
 void depouiller_v1(Vecteur && victime) {
  if (tab_) delete [] tab_;
  tab_=victime.tab_;
  taille_=victime.taille_;
  victime.tab_=0;
  victime.taille_=0;
 }

 //------------------------------------------------------------------------------------depouiller_v2
 void depouiller_v2(Vecteur && victime) {
  std::swap(tab_,victime.tab_);
  std::swap(taille_,victime.taille_);
 }

 //--------------------------------------------------------------------------------------Destructeur
 ~Vecteur(void) {
  if (tab_) delete [] tab_;
 }

 //------------------------------------------------------------------------------Operateur = (Copie)
 Vecteur & operator = (const Vecteur & v) {
  std::cout << "=> operator = (const Vecteur &)" << std::endl;

  if (this!=&v) {
   if (tab_) delete [] tab_;
   tab_=new int[v.taille_];
   taille_=v.taille_;
   for (unsigned i = 0; i<taille_; ++i) tab_[i]=v.tab_[i];
  }

  return *this;
 }

 //-------------------------------------------------------------------------Constructeur (Mouvement)
 Vecteur(Vecteur && v) : tab_(v.tab_),taille_(v.taille_) {
  std::cout << "=> Vecteur(Vecteur &&)" << std::endl;
  v.tab_=0;
  v.taille_=0;
 }

 //--------------------------------------------------------------------------Operateur = (Mouvement)
 Vecteur & operator = (Vecteur && v) {
  std::cout << "=> operator = (Vecteur &&)" << std::endl;
  std::swap(tab_,v.tab_);
  std::swap(taille_,v.taille_);
  return *this;
 }
};

// Fonctions //-------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------Operateur <<
std::ostream & operator << (std::ostream & flux,const Vecteur & vecteur) {
 for (unsigned i = 0; i<vecteur.getTaille(); ++i) flux << vecteur[i] << " ";
 return flux;
}

//---------------------------------------------------------------------------------------Operateur +
Vecteur operator + (const Vecteur & v1,const Vecteur & v2) {
 Vecteur v3(v1.getTaille());

 for (unsigned i = 0; i<v1.getTaille(); ++i) v3[i]=v1[i]+v2[i];
 return v3;
}

//--------------------------------------------------------------------------------------creerVecteur
Vecteur creerVecteur(void) {
 Vecteur v(10);

 for (unsigned i = 0; i<v.getTaille(); ++i) v[i]=i*10;
 return v;
}

//----------------------------------------------------------------------------------------remove_ref
template <typename T> // Alias pour simplifier l'utilisation de "std::remove_reference"
using remove_ref = typename std::remove_reference<T>::type;

//--------------------------------------------------------------------------------------------mymove
template <typename T> // Exemple d'implementation de "std::move"
inline remove_ref<T> && mymove(T && x) {
 return static_cast<remove_ref<T> &&>(x);
}

//--------------------------------------------------------------------------------------------myswap
template <typename T> // Exemple d'implementation de "std::swap"
inline void myswap(T & a,T & b) {
 T tmp = mymove(a);
 a=mymove(b);
 b=mymove(tmp);
}

//-----------------------------------------------------------------------------------------myforward
template <typename T> // Exemple d'implementation de "std::forward"
inline T && myforward(remove_ref<T> & x) {
 return static_cast<T &&>(x);
}

//-------------------------------------------------------------------------------------------------g
template <typename T> void g(T &&) {
 std::string param = typeinfo<T>::name();
 std::string arg   = typeinfo<T &&>::name();

 std::cout << " => g<" << param << ">(" << arg << ")";
}

//----------------------------------------------------------------------------------------------f_v1
template <typename T> void f_v1(T && x) {
 std::string param = typeinfo<T>::name();
 std::string arg   = typeinfo<T &&>::name();

 std::cout << " => f1<" << param << ">(" << arg << ")";
 g(x);
 std::cout << std::endl;
}

//----------------------------------------------------------------------------------------------f_v2
template <typename T> void f_v2(T && x) {
 std::string param = typeinfo<T>::name();
 std::string arg   = typeinfo<T &&>::name();

 std::cout << " => f2<" << param << ">(" << arg << ")";
 g(myforward<T>(x));
 std::cout << std::endl;
}

//----------------------------------------------------------------------------------------------main
int main(void) {
 std::cout << "TEST DEPOUILLEMENT" << std::endl;

 Vecteur v1(7);
 Vecteur v2(7);

 for (unsigned i = 0; i<v1.getTaille(); ++i) {
  v1[i]=i;
  v2[i]=2*i;
 }

 std::cout << "v1 = " << v1 << std::endl;
 std::cout << "v2 = " << v2 << std::endl;

 std::cout << "v1.depouiller(creerVecteur())..." << std::endl;
 v1.depouiller_v1(creerVecteur());
 std::cout << "v2.depouiller(creerVecteur())..." << std::endl;
 v2.depouiller_v2(creerVecteur());

 std::cout << "v1 = " << v1 << std::endl;
 std::cout << "v2 = " << v2 << std::endl;

 std::cout << std::endl;
 std::cout << "TEST AFFECTATION PAR COPIE" << std::endl;

 Vecteur v3(5);
 Vecteur v4(5);

 for (unsigned i=0; i<v3.getTaille(); ++i) v3[i]=i;

 std::cout << "v3 = " << v3 << std::endl;
 std::cout << "v4 = " << v4 << std::endl;

 std::cout << "v4=v3..." << std::endl;
 v4=v3;

 std::cout << "v3 = " << v3 << std::endl;
 std::cout << "v4 = " << v4 << std::endl;

 std::cout << std::endl;
 std::cout << "TEST AFFECTATION PAR MOUVEMENT" << std::endl;

 Vecteur v5(5);

 for (unsigned i=0; i<v4.getTaille(); ++i) v4[i]=i*10;

 std::cout << "v3 = " << v3 << std::endl;
 std::cout << "v4 = " << v4 << std::endl;
 std::cout << "v5 = " << v5 << std::endl;

 std::cout << "v5=v3+v4..." << std::endl;
 v5=v3+v4;

 std::cout << "v3 = " << v3 << std::endl;
 std::cout << "v4 = " << v4 << std::endl;
 std::cout << "v5 = " << v5 << std::endl;

 std::cout << std::endl;
 std::cout << "TEST CONSTRUCTION PAR COPIE" << std::endl;
 std::cout << "v3 = " << v3 << std::endl;

 std::cout << "v6(v3)..." << std::endl;
 Vecteur v6(v3);

 std::cout << "v3 = " << v3 << std::endl;
 std::cout << "v6 = " << v6 << std::endl;

 std::cout << std::endl;
 std::cout << "TEST CONSTRUCTION PAR MOUVEMENT" << std::endl;
 std::cout << "v3 = " << v3 << std::endl;
 std::cout << "v4 = " << v4 << std::endl;

 std::cout << "swap(v3,v4)..." << std::endl;
 myswap(v3,v4);

 std::cout << "v3 = " << v3 << std::endl;
 std::cout << "v4 = " << v4 << std::endl;

 std::cout << std::endl;
 std::cout << "TEST REFERENCE UNIVERSELLE" << std::endl;

 int       x = 13;
 const int y = 27;

 std::cout << "f_v1(5)"; f_v1(5);
 std::cout << "f_v1(x)"; f_v1(x);
 std::cout << "f_v1(y)"; f_v1(y);

 std::cout << std::endl;
 std::cout << "TEST 'PERFECT FORWARDING'" << std::endl;

 std::cout << "f_v2(5)"; f_v2(5);
 std::cout << "f_v2(x)"; f_v2(x);
 std::cout << "f_v2(y)"; f_v2(y);
}

// Fin //-------------------------------------------------------------------------------------------
