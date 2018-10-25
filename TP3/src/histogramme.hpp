#ifndef HISTOGRAMME_HPP
#define HISTOGRAMME_HPP

#include <classe.hpp>
#include <vector>
#include <set>
#include <map>
#include <echantillon.hpp>

template<typename T = std::less<Classe>>
class Histogramme {
private:
  using ContainerType = std::set<Classe, T>;
  ContainerType container;
  using ValeurType = std::multimap<Classe, Valeur, T>;
  ValeurType valeurs;
  void ajouter_valeur(Classe, Valeur);

public:
  using classes_t = ContainerType;
  using valeurs_t = ValeurType;
  using it_valeurs_t = typename ValeurType::const_iterator;
  Histogramme(double, double, unsigned);
  template<typename U>
  Histogramme(const Histogramme<U>&);
  const ContainerType& getClasses() const { return container; }
  const ValeurType& getValeurs() const { return valeurs; }
  std::pair<it_valeurs_t, it_valeurs_t> getValeurs(const Classe&) const;
  void ajouter(Echantillon&);
  void ajouter(double&);
  void reordering();
};

template<typename T>
using ContainerType = typename Histogramme<T>::ContainerType;

#include <histogramme.hxx>

#endif
