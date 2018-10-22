#include <valeur.hpp>

Valeur::Valeur() : real(0.0) {

}

Valeur::Valeur(int x) : real(x) {

}

bool Valeur::operator<(const Valeur & v) const {
  return real < v.getNombre();
}
