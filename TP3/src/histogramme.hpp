#ifndef HISTOGRAMME_HPP
#define HISTOGRAMME_HPP

#include <classe.hpp>
#include <vector>

class Histogramme {
private:
  std::vector<Classe> vecteur;

public:
  using classes_t = std::vector<Classe> ;
  Histogramme(double, double, unsigned);
  std::vector<Classe> getClasses() const { return vecteur; }
};

#endif
