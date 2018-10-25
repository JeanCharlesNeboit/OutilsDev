#ifndef COMPARATEUR_QUANTITE_HPP
#define COMPARATEUR_QUANTITE_HPP

template<class T>
class ComparateurQuantite {
public:
  bool operator()(const T&, const T&) const;
};

#include <comparateurQuantite.hxx>

#endif
