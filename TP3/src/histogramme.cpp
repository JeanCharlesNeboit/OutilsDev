#include <histogramme.hpp>

Histogramme::Histogramme(double _inf, double _sup, unsigned n) {
  auto pas = _inf/_sup;
  for(auto i=_inf; i<=_sup; i+=pas) {
    vecteur.push_back(Classe(i, i+pas));
  }
}
