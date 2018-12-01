//==================================================================================================
// EXEMPLES C++11                                                                  cpp11_lambda.cpp
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

// Cet exemple illustre les possibilites offertes par les lambdas, et comment
// elles sont implementees. Il est conseille de commencer la lecture par la
// fonction "main" pour comprendre l'exemple.
//
// Plus d'explications ici: http://www.nawouak.net/?doc=course.cpp11+ch=lambdas
//
// ATTENTION: Il s'agit d'un exemple pour illustrer les nouvelles
// fonctionalites de la norme C++11. Le code n'est donc pas forcement complet
// et ne reflete pas toujours de bonnes pratiques de developpement.

// Entetes //---------------------------------------------------------------------------------------
#include <algorithm>
#include <iostream>
#include <vector>
#include <cpp11_function.hpp>
#include <cpp11_typeinfo.hpp>

// Classe  C o m p a r e r I n f e r i e u r //-----------------------------------------------------
struct ComparerInferieur {
 bool operator () (int x,int y) const { return x<y; }
};

// Classe  S t a t i s t i q u e //-----------------------------------------------------------------
class Statistique {
 private:
  int min_;
  int max_;

 public:
  Statistique(int a,int b) : min_(a),max_(b) {}

  void filtrer(std::vector<int> & v) const {
   auto filtre = [this] (int x)
                 { return (x<this->min_ || x>this->max_); };

   replace_if(v.begin(),v.end(),filtre,-4);
  }
};

// Classe  F o n c t e u r C o p i e //-------------------------------------------------------------
class FoncteurCopie { // Exemple d'implementation d'une lambda avec capture par copie
 private:
  int min;
  int max;

 public:
  FoncteurCopie(int a,int b) : min(a),max(b) {}

  bool operator () (int x) const {
   return (x<min || x>max);
  }
};

// Classe  F o n c t e u r R e f //-----------------------------------------------------------------
class FoncteurRef { // Exemple d'implementation d'une lambda avec capture par reference
 private:
  int & min;
  int & max;

 public:
  FoncteurRef(int & a,int & b) : min(a),max(b) {}

  bool operator () (int x) const {
   return (x<min || x>max);
  }
};

// Classe  F o n c t e u r G e n //-----------------------------------------------------------------
class FoncteurGen { // Exemple d'implementation d'une lambda non constante
 private:
  int cpt;

 public:
  FoncteurGen(int c) : cpt(c) {}

  FoncteurGen(const FoncteurGen & g) : cpt(g.cpt) {
   std::cout << "=> FoncteurGen(const FoncteurGen &)" << std::endl;
  }

  int operator () (void) /*const*/ {
   cpt+=2;
   return cpt;
  }
};

// Fonctions //-------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------mysort
template <typename IT,typename COMP>
void mysort(const IT & debut,const IT & fin,const COMP & comparer) {
 for (IT it1 = debut; it1!=fin; ++it1)
  for (IT it2 = it1+1; it2!=fin; ++it2)
   if (comparer(*it2,*it1)) std::swap(*it1,*it2);
}

//---------------------------------------------------------------------------------comparerSuperieur
inline bool comparerSuperieur(int x,int y) { return x>y; }

//--------------------------------------------------------------------------------------Operateur <<
std::ostream & operator << (std::ostream & flux,const std::vector<int> & v) {
 for (int e : v) flux << e << " ";
 return flux;
}

//--------------------------------------------------------------------------------------fonction_gen
int fonction_gen(void) {
 static int cpt = 32;

 cpt+=3;
 return cpt;
}

//-------------------------------------------------------------------------------------mygenerate_v1
template <typename IT,typename GEN>
void mygenerate_v1(const IT & debut,const IT & fin,const GEN & generer) {
 for (IT it = debut; it!=fin; ++it) *it=generer();
}

//-------------------------------------------------------------------------------------mygenerate_v2
template <typename IT,typename GEN>
void mygenerate_v2(const IT & debut,const IT & fin,GEN & generer) {
 for (IT it = debut; it!=fin; ++it) *it=generer();
}

//-------------------------------------------------------------------------------------mygenerate_v3
template <typename IT,typename GEN>
void mygenerate_v3(const IT & debut,const IT & fin,GEN && generer) {
 for (IT it = debut; it!=fin; ++it) *it=generer();
}

//-------------------------------------------------------------------------------------mygenerate_v4
template <typename IT,typename RET>
void mygenerate_v4(const IT & debut,const IT & fin,
                   const std::function<RET(void)> & generer) {
 for (IT it = debut; it!=fin; ++it) *it=generer();
}

//-------------------------------------------------------------------------------------mygenerate_v5
template <typename IT,typename RET>
void mygenerate_v5(const IT & debut,const IT & fin,
                   const myfunction<RET(void)> & generer) {
 for (IT it = debut; it!=fin; ++it) *it=generer();
}

//----------------------------------------------------------------------------------------------main
int main(void) {
 std::cout << "TEST LAMBDA SANS CAPTURE" << std::endl;

 std::vector<int> v;

 for (unsigned i = 0; i<10; ++i) v.push_back(i);
 std::cout << "v = " << v << std::endl;

 std::cout << "tri decroissant avec lambda..." << std::endl;
 mysort(v.begin(),v.end(),[] (int x, int y) { return x>y; });
 std::cout << "v = " << v << std::endl;

 std::cout << "tri croissant avec foncteur..." << std::endl;
 mysort(v.begin(),v.end(),ComparerInferieur());
 std::cout << "v = " << v << std::endl;

 std::cout << "tri decroissant avec fonction..." << std::endl;
 mysort(v.begin(),v.end(),comparerSuperieur);
 std::cout << "v = " << v << std::endl;

 auto f = [] (int x,int y) { return x>y; };
 typedef decltype(f) lambda_t;

 std::cout << "type lambda = " << typeinfo<lambda_t>::name() << std::endl;

 std::cout << std::endl;
 std::cout << "TEST LAMBDA AVEC CAPTURE" << std::endl;

 int min = 5;
 int max = 7;

 auto lambda_copie = [min,max] (int x) { return (x<min || x>max); };
 auto lambda_ref   = [&min,&max] (int x) { return (x<min || x>max); };
 auto lambda_auto  = [=] (int x) { return (x<min || x>max); };

 FoncteurCopie foncteur_copie(min,max);
 FoncteurRef   foncteur_ref(min,max);

 min=3;
 max=10;

 std::vector<int> v1 = v;
 std::vector<int> v2 = v;
 std::vector<int> v3 = v;
 std::vector<int> v4 = v;
 std::vector<int> v5 = v;
 std::vector<int> v6 = v;

 replace_if(v1.begin(),v1.end(),lambda_copie,-1);
 replace_if(v2.begin(),v2.end(),lambda_ref,-2);
 replace_if(v3.begin(),v3.end(),lambda_auto,-3);
 Statistique(5,7).filtrer(v4);
 replace_if(v5.begin(),v5.end(),foncteur_copie,-5);
 replace_if(v6.begin(),v6.end(),foncteur_ref,-6);

 std::cout << "v1 = " << v1 << " (lambda avec capture par copie)" << std::endl;
 std::cout << "v2 = " << v2 << " (lambda avec capture par reference)" << std::endl;
 std::cout << "v3 = " << v3 << " (lambda avec capture automatique par copie)" << std::endl;
 std::cout << "v4 = " << v4 << " (lambda avec capture de 'this')" << std::endl;
 std::cout << "v5 = " << v5 << " (foncteur avec capture par copie)" << std::endl;
 std::cout << "v6 = " << v6 << " (foncteur avec capture par reference)" << std::endl;

 std::cout << std::endl;
 std::cout << "TEST LAMBDA NON CONSTANTE" << std::endl;

 int cpt = 32;

 auto lambda_gen = [cpt] (void) mutable {
  cpt+=1;
  return cpt;
 };

 FoncteurGen foncteur_gen(cpt);

 std::generate(v1.begin(),v1.end(),lambda_gen);
 std::generate(v2.begin(),v2.end(),foncteur_gen);

 std::cout << "v1 = " << v1 << " (lambda non constante, inc = +1)" << std::endl;
 std::cout << "v2 = " << v2 << " (foncteur non constant, inc = +2)" << std::endl;

 std::cout << std::endl;
 std::cout << "TEST ABSTRACTION DE FONCTION" << std::endl;

 std::cout << std::endl;
 std::cout << "tentative avec 'const T &'" << std::endl;

 // mygenerate_v1(v3.begin(),v3.end(),lambda_gen);   // Probleme operateur "()" non constant
 // mygenerate_v1(v4.begin(),v4.end(),foncteur_gen); // Probleme operateur "()" non constant

 mygenerate_v1(v5.begin(),v5.end(),&fonction_gen);

 // mygenerate_v1(v6.begin(),v6.end(),[cpt] (void) mutable
 //                                   { cpt+=5; return cpt; }); // Probleme operateur "()" non constant

 std::cout << "v5 = " << v5 << " (fonction, inc = +3)" << std::endl;

 std::cout << std::endl;
 std::cout << "tentative avec 'T &'" << std::endl;

 mygenerate_v2(v3.begin(),v3.end(),lambda_gen);
 mygenerate_v2(v4.begin(),v4.end(),foncteur_gen);

 // mygenerate_v2(v5.begin(),v5.end(),&fonction_gen); // Probleme pointeur constant

 // mygenerate_v2(v6.begin(),v6.end(),[cpt] (void) mutable
 //                                   { cpt+=5; return cpt; }); // Probleme rvalue

 std::cout << "v3 = " << v3 << " (lambda non constante, inc = +1)" << std::endl;
 std::cout << "v4 = " << v4 << " (foncteur non constant, inc = +2)" << std::endl;

 std::cout << std::endl;
 std::cout << "tentative avec 'T &&'" << std::endl;

 mygenerate_v3(v3.begin(),v3.end(),lambda_gen);
 mygenerate_v3(v4.begin(),v4.end(),foncteur_gen);
 mygenerate_v3(v5.begin(),v5.end(),&fonction_gen);
 mygenerate_v3(v6.begin(),v6.end(),[cpt] (void) mutable { cpt+=5; return cpt; });

 std::cout << "v3 = " << v3 << std::endl;
 std::cout << "v4 = " << v4 << std::endl;
 std::cout << "v5 = " << v5 << std::endl;
 std::cout << "v6 = " << v6 << std::endl;

 std::cout << std::endl;
 std::cout << "tentative avec 'std::function'" << std::endl;

 mygenerate_v4(v3.begin(),v3.end(),std::function<int(void)>(lambda_gen));
 mygenerate_v4(v4.begin(),v4.end(),std::function<int(void)>(foncteur_gen));
 mygenerate_v4(v5.begin(),v5.end(),std::function<int(void)>(&fonction_gen));

 mygenerate_v4(v6.begin(),v6.end(),std::function<int(void)>([cpt] (void) mutable
                                                            { cpt+=5; return cpt; }));

 std::cout << "v3 = " << v3 << std::endl;
 std::cout << "v4 = " << v4 << std::endl;
 std::cout << "v5 = " << v5 << std::endl;
 std::cout << "v6 = " << v6 << std::endl;

 std::cout << std::endl;
 std::cout << "tentative avec 'myfunction'" << std::endl;

 mygenerate_v5(v3.begin(),v3.end(),myfunction<int(void)>(lambda_gen));
 mygenerate_v5(v4.begin(),v4.end(),myfunction<int(void)>(foncteur_gen));
 mygenerate_v5(v5.begin(),v5.end(),myfunction<int(void)>(&fonction_gen));

 mygenerate_v5(v6.begin(),v6.end(),myfunction<int(void)>([cpt] (void) mutable
                                                         { cpt+=5; return cpt; }));

 std::cout << "v3 = " << v3 << std::endl;
 std::cout << "v4 = " << v4 << std::endl;
 std::cout << "v5 = " << v5 << std::endl;
 std::cout << "v6 = " << v6 << std::endl;
}

// Fin //-------------------------------------------------------------------------------------------
