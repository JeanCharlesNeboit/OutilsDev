//==================================================================================================
// EXEMPLES C++11                                                                cpp11_typeinfo.hpp
//                                                                               Par Bruno Bachelet
//==================================================================================================

// Facilite la lecture des informations de type pour g++.

// Gardien //---------------------------------------------------------------------------------------
#ifndef _CPP11_TYPEINFO_HPP_
#define _CPP11_TYPEINFO_HPP_

// Entetes //---------------------------------------------------------------------------------------
#include <string>
#include <typeinfo>

#ifdef __GNUG__
 #include <cstdlib>
 #include <cxxabi.h>
#endif

// Types & Classes //-------------------------------------------------------------------------------
template <typename T> struct typeinfo;

// Fonctions //-------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------demangle
#ifdef __GNUC__
 inline std::string demangle(const char * name) {
  int    status      = -4;
  char * decoded     = abi::__cxa_demangle(name,0,0,&status);
  std::string result = (status==0 ? decoded : name);

  free(decoded);
  return result;
 }
#else
 inline std::string demangle(const char * name) { return name; }
#endif

//--------------------------------------------------------------------------------------get_typeinfo
template <typename T> inline typeinfo<T &&> get_typeinfo(T &&) { return typeinfo<T &&>(); }

// Classe  t y p e i n f o //-----------------------------------------------------------------------

//----------------------------------------------------------------------------------Version primaire
template <typename T> struct typeinfo {
 static std::string name(void) { return demangle(typeid(T).name()); }
};

//---------------------------------------------------------------------------------Version reference
template <typename T> struct typeinfo<T &> {
 static std::string name(void) { return typeinfo<T>::name()+" &"; }
};

//------------------------------------------------------------------------------------Version rvalue
template <typename T> struct typeinfo<T &&> {
 static std::string name(void) { return typeinfo<T>::name()+" &&"; }
};

//---------------------------------------------------------------------------------Version constante
template <typename T> struct typeinfo<const T> {
 static std::string name(void) { return "const "+typeinfo<T>::name(); }
};

// Fin //-------------------------------------------------------------------------------------------
#endif
