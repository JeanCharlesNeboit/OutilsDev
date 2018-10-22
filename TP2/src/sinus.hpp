#ifndef SINUS_HPP
#define SINUS_HPP

#include <factorielle.hpp>
#include <puissance.hpp>
#include <cmath>

template<int N>
class Sinus {
public:
  static double valeur(double);
};

template<int N>
double Sinus<N>::valeur(double x) {
  return Sinus<N-1>::valeur(x) + Puissance<N>::valeur(-1)*Puissance<2*N+1>::valeur(x)/Factorielle<2*N+1>::valeur;
}

template<>
double Sinus<0>::valeur(double x) {
  return Puissance<0>::valeur(0)*Puissance<1>::valeur(x)/Factorielle<1>::valeur;
}

#endif
