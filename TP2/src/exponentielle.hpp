#ifndef EXPONENTIELLE_HPP
#define EXPONENTIELLE_HPP

#include <factorielle.hpp>
#include <puissance.hpp>

template<int N>
class Exponentielle {
public:
  static double valeur(double);
};

template<int N>
double Exponentielle<N>::valeur(double x) {
  return Exponentielle<N-1>::valeur(x) + Puissance<N>::valeur(x)/Factorielle<N>::valeur;
}

template<>
double Exponentielle<0>::valeur(double x) {
  return 1;
}

#endif
