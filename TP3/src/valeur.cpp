#include <valeur.hpp>

Valeur::Valeur() : real(0.0), nom("inconnu") {

}

Valeur::Valeur(double x, std::string n) : real(x), nom(n) {

}

bool Valeur::operator<(const Valeur & v) const {
  return real < v.getNombre();
}
