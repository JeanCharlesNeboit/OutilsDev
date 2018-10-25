#include <comparateurQuantite.hpp>

template<class T>
bool ComparateurQuantite<T>::operator()(const T& first, const T& second) const {
  return first < second;
}

template<>
bool ComparateurQuantite<Classe>::operator()(const Classe& first, const Classe& second) const {
  if (first.getQuantite() == second.getQuantite()) return first < second;
  return first.getQuantite() > second.getQuantite();
}
