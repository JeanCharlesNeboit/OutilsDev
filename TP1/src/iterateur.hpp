#ifndef ITERATEUR_HPP
#define ITERATEUR_HPP

#include <iostream>

template<class T>
class Iterateur {
private:
  T* p;

public:
  Iterateur(T* = nullptr);
  Iterateur(const Iterateur&);
  Iterateur& operator++();
  Iterateur operator++(int);
  bool operator==(const Iterateur&) const;
  bool operator!=(const Iterateur&) const;
  T& operator*();
};

#include <iterateur.hxx>

#endif
