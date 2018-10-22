#ifndef PUISSANCE_HPP
#define PUISSANCE_HPP

template<int N>
class Puissance {
public:
  static double valeur(double);
};

template<int N>
double Puissance<N>::valeur(double x) {
  return Puissance<N-1>::valeur(x) * x;
}

template<>
double Puissance<0>::valeur(double x) {
  return 1;
}

#endif
