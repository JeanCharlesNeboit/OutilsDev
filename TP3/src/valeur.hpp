#ifndef VALEUR_HPP
#define VALEUR_HPP

#include <vector>

class Valeur {
private:
  double real;

public:
  Valeur();
  Valeur(int);

  bool operator<(const Valeur&) const;

  double getNombre() const { return real; }
  void setNombre(int x) { real = x; }
};

#endif
