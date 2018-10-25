#include <histogramme.hpp>
#include <iostream>

template<typename T>
Histogramme<T>::Histogramme(double _inf, double _sup, unsigned n) {
  auto pas = (_sup-_inf)/n;
  for(auto i=_inf; i<_sup; i+=pas) {
    //container.push_back(Classe(i, i+pas));
    container.insert(Classe(i, i+pas));
  }
}

template<typename T>
template<typename U>
Histogramme<T>::Histogramme(const Histogramme<U>& h) {
  for(typename Histogramme<U>::classes_t::iterator it=h.getClasses().begin(); it!=h.getClasses().end(); ++it) {
    container.insert(*it);
  }
}

template<typename T>
void Histogramme<T>::ajouter(Echantillon & e) {
  for(auto i=0; i<e.getTaille(); ++i) {
    typename ContainerType::iterator it = find_if(container.begin(), container.end(), [&](const Classe& c) {
      return c.getBorneInf() <= e.getValeur(i).getNombre() && e.getValeur(i).getNombre() < c.getBorneSup();
    });
    if (it != container.end()) {
      it->ajouter();
      ajouter_valeur(*it, e.getValeur(i).getNombre());
    }
  }
}

template<typename T>
void Histogramme<T>::ajouter(double & v) {
  typename ContainerType::iterator it = find_if(container.begin(), container.end(), [&](const Classe& c) {
    return c.getBorneInf() <= v && v < c.getBorneSup();
  });
  if (it != container.end()) {
    it->ajouter();
    ajouter_valeur(*it, v);
    reordering();
  }
}

template<typename T>
void Histogramme<T>::ajouter_valeur(Classe c, Valeur v) {
  valeurs.insert(std::make_pair(c, v));
}

template<typename T>
void Histogramme<T>::reordering() {
  ContainerType c(container);
  container.swap(c);
}

template<typename T>
std::pair<typename Histogramme<T>::it_valeurs_t, typename Histogramme<T>::it_valeurs_t> Histogramme<T>::getValeurs(const Classe & c) const {
  Histogramme<T>::it_valeurs_t first;
  Histogramme<T>::it_valeurs_t last;
  typename ValeurType::const_iterator ret = find_if(valeurs.begin(), valeurs.end(), [&c](const typename ValeurType::value_type& v) {
    return v.first.getBorneInf() == c.getBorneInf() && v.first.getBorneSup() == c.getBorneSup();
  });
  if (ret != valeurs.end()) {
    first = ret;
    last = ret;
    for(typename ValeurType::const_iterator it=++ret; it!=valeurs.end(); ++it) {
        if (it->first.getBorneInf() == c.getBorneInf() && it->first.getBorneSup() == c.getBorneSup()) {
          last = it;
        }
    }
  }
  std::pair<typename Histogramme<T>::it_valeurs_t, typename Histogramme<T>::it_valeurs_t> pair(first, last);
  return pair;
}
