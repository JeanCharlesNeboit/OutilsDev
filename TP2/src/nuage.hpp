#ifndef NUAGE_HPP
#define NUAGE_HPP

#include <iostream>
#include <vector>
#include <point.hpp>
#include <cartesien.hpp>

template<typename T>
class Nuage {
private:
  std::vector<T> points;

public:
  Nuage();
  ~Nuage();

  typedef typename std::vector<T>::const_iterator const_iterator;
  using container = std::vector
  const_iterator begin() const;
  const_iterator end() const;

  int size();
  void ajouter(const T);
};

template<typename T>
class BarycentreCartesien {
public:
  Cartesien operator()(Nuage<T>&);
};

template<typename T>
class BarycentrePolaire {
public:
  Polaire operator()(Nuage<T>&);
};

template<typename T>
T barycentre_v1(Nuage<T>&);

#include <nuage.hxx>

#endif
