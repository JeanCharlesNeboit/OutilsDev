#include <classe.hpp>
#include <iostream>

Classe::Classe(double _inf, double _sup) : inf(_inf), sup(_sup), quantite(0) {

}

bool Classe::operator<(const Classe & c) const {
  return inf < c.inf;
}

bool Classe::operator>(const Classe & c) const {
  return inf > c.inf;
}
