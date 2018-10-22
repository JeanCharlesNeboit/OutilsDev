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

  //typedef typename std::vector<T>::const_iterator const_iterator;
  using const_iterator = typename std::vector<T>::const_iterator;
  using value_type = T;

  const_iterator begin() const;
  const_iterator end() const;

  int size() const;
  void ajouter(const T);
};

template<typename T>
T barycentre_v1(const Nuage<T>&);

template<typename T>
typename T::value_type barycentre_v2(const T&);

#include <nuage.hxx>

#endif
