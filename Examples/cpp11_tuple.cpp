//==================================================================================================
// EXEMPLES C++11                                                                   cpp11_tuple.cpp
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

// Cet exemple montre comment utiliser les generiques a parametres variables
// (variadic templates) pour modeliser un tuple. Il est conseille de commencer
// la lecture par la fonction "main" pour comprendre l'exemple.
//
// Plus d'explications ici: http://www.nawouak.net/?doc=course.cpp11+ch=variadic
//
// ATTENTION: Il s'agit d'un exemple pour illustrer les nouvelles
// fonctionalites de la norme C++11. Le code n'est donc pas forcement complet
// et ne reflete pas toujours de bonnes pratiques de developpement.

// Entetes //---------------------------------------------------------------------------------------
#include <iostream>
#include <cpp11_typeinfo.hpp>

// Classe  T u p l e //-----------------------------------------------------------------------------

//---------------------------------------------------------------------------------------Declaration
template <typename... TYPES> class Tuple;

//------------------------------------------------------------------------------------------Cas vide
template <> class Tuple<> {};

//---------------------------------------------------------------------------------------Cas general
template <typename T,typename... RESTE>
class Tuple<T,RESTE...> : public Tuple<RESTE...> {
 public:
  T value;

  Tuple(const T & val,const RESTE &... args)
  : Tuple<RESTE...>(args...),value(val) {}
};

// Classe  T u p l e E l e m e n t //---------------------------------------------------------------

//---------------------------------------------------------------------------------------Declaration
template <unsigned N,typename TUPLE> struct TupleElement;

//-----------------------------------------------------------------------------------------Recursion
template <unsigned N,typename T,typename... RESTE>
struct TupleElement< N, Tuple<T,RESTE...> >
: TupleElement< N-1, Tuple<RESTE...> > {};

//---------------------------------------------------------------------------------Condition d'arret
template <typename T,typename... RESTE>
struct TupleElement< 0, Tuple<T,RESTE...> > {
 typedef T type;

 static T &       get(Tuple<T,RESTE...> & t) { return t.value; }
 static const T & get(const Tuple<T,RESTE...> & t) { return t.value; }
};

// Fonctions //-------------------------------------------------------------------------------------

//------------------------------------------------------------------------------get_value (Variable)
template <unsigned N,typename... TYPES>
typename TupleElement< N, Tuple<TYPES...> >::type &
get_value(Tuple<TYPES...> & t) {
 return TupleElement< N, Tuple<TYPES...> >::get(t);
}

//------------------------------------------------------------------------------get_value (Constant)
template <unsigned N,typename... TYPES>
typename TupleElement< N, Tuple<TYPES...> >::type &
get_value(const Tuple<TYPES...> & t) {
 return TupleElement< N, Tuple<TYPES...> >::get(t);
}

//----------------------------------------------------------------------------------------------main
int main(void) {
 typedef Tuple<int,double> MyTuple;

 MyTuple tuple(13,2.7);

 std::cout << "type 0 = " << typeinfo<TupleElement<0,MyTuple>::type>::name() << std::endl;
 std::cout << "type 1 = " << typeinfo<TupleElement<1,MyTuple>::type>::name() << std::endl;

 // std::cout << "valeur 0 = " << TupleElement<0,decltype(tuple)>::get(tuple) << std::endl;
 // std::cout << "valeur 1 = " << TupleElement<1,decltype(tuple)>::get(tuple) << std::endl;

 std::cout << "valeur 0 = " << get_value<0>(tuple) << std::endl;
 std::cout << "valeur 1 = " << get_value<1>(tuple) << std::endl;
}

// Fin //-------------------------------------------------------------------------------------------
