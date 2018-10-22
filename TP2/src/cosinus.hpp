#ifndef COSINUS_HPP
#define COSINUS_HPP

#include <factorielle.hpp>
#include <puissance.hpp>
#include <cmath>

template<int N>
class Cosinus {
public:
  static double valeur(double);
};

template<int N>
double Cosinus<N>::valeur(double x) {
  return Cosinus<N-1>::valeur(x) + Puissance<N>::valeur(-1)*Puissance<2*N>::valeur(x)/Factorielle<2*N>::valeur;
}

template<>
double Cosinus<0>::valeur(double x) {
  return 1;
}

#endif
