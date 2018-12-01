//==================================================================================================
// EXEMPLES C++11                                                           cpp11_variadic_call.cpp
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

// Cet exemple presente differentes manieres de parcourir un pack d'arguments
// (cf. variadic templates). Il est conseille de commencer la lecture par la
// fonction "main" pour comprendre l'exemple.
//
// Plus d'explications ici: http://www.nawouak.net/?doc=course.cpp11+ch=variadic
//
// ATTENTION: Il s'agit d'un exemple pour illustrer les nouvelles
// fonctionalites de la norme C++11. Le code n'est donc pas forcement complet
// et ne reflete pas toujours de bonnes pratiques de developpement.

// Entetes //---------------------------------------------------------------------------------------
#include <initializer_list>
#include <iostream>

// Fonctions //-------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------display_v1
template <typename T>
void display_v1(const T & valeur) {
 std::cout << valeur << std::endl;
}

template <typename T,typename... RESTE>
void display_v1(const T & v1,const RESTE &... reste) {
 std::cout << v1 << " ; ";
 display_v1(reste...);
}

//----------------------------------------------------------------------------------variadic_call_v1
template <typename... TYPES>
inline void variadic_call_v1(const TYPES &...) {}

//----------------------------------------------------------------------------------variadic_call_v2
struct variadic_call_v2 {
 template <typename... TYPES> variadic_call_v2(const TYPES &...) {}
};

//----------------------------------------------------------------------------------variadic_call_v3
struct variadic_call_v3 {
 variadic_call_v3(const std::initializer_list<int>) {}
};

//----------------------------------------------------------------------------------------display_v2
template <typename T> void display_v2(const T & valeur) {
 std::cout << valeur << " ; ";
}

template <typename... TYPES>
void display_v2(const TYPES &... valeurs) {
 // display_v2(valeurs)...;                       // 1ere tentative, expansion interdite ici
 // variadic_call_v1(display_v2(valeurs)...);     // 2eme tentative, "display" retourne "void"
 // variadic_call_v1((display_v2(valeurs),0)...); // 3eme tentative, OK mais ordre non garanti
 // variadic_call_v2{(display_v2(valeurs),0)...}; // Ordre garanti mais dans le mauvais sens
 variadic_call_v3{(display_v2(valeurs),0)...};    // Ordre garanti dans le bon sens
 std::cout << std::endl;
}

//----------------------------------------------------------------------------------------------main
int main(void) {
 display_v1(13,2.7,"Hello World !");
 display_v2(13,2.7,"Hello World !");
}

// Fin //-------------------------------------------------------------------------------------------
