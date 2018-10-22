#ifndef FACTORIELLE_HPP
#define FACTORIELLE_HPP

template<int N>
class Factorielle {
private:

public:
  //static unsigned long valeur;
  enum { valeur = N * Factorielle<N-1>::valeur };
};

template<>
class Factorielle<0> {
public:
  enum { valeur = 1 };
};

/*template<unsigned long N>
unsigned long Factorielle<N>::valeur = N * Factorielle<N-1>::valeur;

template<>
unsigned long Factorielle<0>::valeur = 1;*/

#endif
