#ifndef ECHANTILLON_HPP
#define ECHANTILLON_HPP

#include <valeur.hpp>
#include <algorithm>

#include <stdexcept>

class Echantillon {
private:
  std::vector<Valeur> vecteur;

public:
  Echantillon();

  int getTaille() const { return vecteur.size(); }
  void ajouter(Valeur);
  Valeur getMinimum() const;
  Valeur getMaximum() const;
  Valeur getValeur(int) const;
};

#endif
