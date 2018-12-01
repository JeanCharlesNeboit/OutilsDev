//==================================================================================================
// EXEMPLES C++11                                                                cpp11_function.hpp
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

// Cet exemple presente l'ebauche d'une implementation possible de la classe
// "std::function". Il est conseille de commencer la lecture par le fichier
// "c++11_lambda.cpp" qui utilise cette implementation.
//
// Plus d'explications ici: http://www.nawouak.net/?doc=course.cpp11+ch=lambdas
//
// ATTENTION: Il s'agit d'un exemple pour illustrer les nouvelles
// fonctionalites de la norme C++11. Le code n'est donc pas forcement complet
// et ne reflete pas toujours de bonnes pratiques de developpement.

// Gardien //---------------------------------------------------------------------------------------
#ifndef _CPP11_FUNCTION_HPP_
#define _CPP11_FUNCTION_HPP_

// Entetes //---------------------------------------------------------------------------------------
#include <iostream>
#include <memory> // Pour "std::unique_ptr"

// Classe  c a l l a b l e //-----------------------------------------------------------------------
template <typename> class callable;

template <typename RET,typename... ARGS> class callable<RET(ARGS...)> {
 public:
  virtual RET operator () (ARGS... args) const = 0;
  virtual ~callable(void) {}
};

// Classe  c a l l a b l e _ f o n c t e u r //-----------------------------------------------------
template <typename,typename> class callable_foncteur;

template <typename FONC,typename RET,typename... ARGS>
class callable_foncteur<FONC,RET(ARGS...)> : public callable<RET(ARGS...)> {
 private:
  FONC & foncteur_;

 public:
  callable_foncteur(FONC & f) : foncteur_(f) {}

  RET operator () (ARGS... args) const { return foncteur_(args...); }
};

// Classe  c a l l a b l e _ f o n c t i o n //-----------------------------------------------------
template <typename> class callable_fonction;

template <typename RET,typename... ARGS>
class callable_fonction<RET(ARGS...)> : public callable<RET(ARGS...)> {
 private:
  RET (*fonction_)(ARGS...);

 public:
  callable_fonction(RET (*f)(ARGS...)) : fonction_(f) {}

  RET operator () (ARGS... args) const { return (*fonction_)(args...); }
};

// Classe  m y f u n c t i o n //-------------------------------------------------------------------
template <typename> class myfunction;

template <typename T> // Alias pour simplifier l'utilisation de "std::remove_reference"
using remove_ref = typename std::remove_reference<T>::type;

template <typename RET,typename... ARGS> class myfunction<RET(ARGS...)> {
 //----------------------------------------------------------------------------------------Attributs
 private:
  // callable<RET(ARGS...)> * callable_;
  std::unique_ptr< callable<RET(ARGS...)> > callable_;

 public:

 //--------------------------------------------------------------------------Constructeur (Foncteur)
 template <typename FONC> myfunction(FONC && foncteur)
 : callable_(new callable_foncteur< remove_ref<FONC>, RET(ARGS...) >(foncteur)) {}

 //-----------------------------------------------------------------Constructeur (Pointeur fonction)
 myfunction(RET (*fonction)(ARGS...))
 : callable_(new callable_fonction<RET(ARGS...)>(fonction)) {}

 //-------------------------------------------------------------------------------------Operateur ()
 RET operator () (ARGS... args) const { return (*callable_)(args...); }
};

// Fin //-------------------------------------------------------------------------------------------
#endif
