#include <echantillon.hpp>

Echantillon::Echantillon() {

}

void Echantillon::ajouter(Valeur v) {
  vecteur.push_back(v);
}

Valeur Echantillon::getMinimum() const {
  if (vecteur.empty()) {
    throw std::domain_error("");
  }
  return *(std::min_element(vecteur.begin(), vecteur.end()));
}

Valeur Echantillon::getMaximum() const {
  if (vecteur.empty()) {
    throw std::domain_error("");
  }
  return *(std::max_element(vecteur.begin(), vecteur.end()));
}

Valeur Echantillon::getValeur(int index) const {
  /*if (index < 0 || index >= vecteur.size()) {
    throw std::out_of_range("");
  }
  return vecteur[index];*/
  return vecteur.at(index);
}
