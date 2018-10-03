#ifndef VECTEUR_HPP
#define VECTEUR_HPP

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <iterateur.hpp>

template<class T>
class Vecteur {
private:
  int size;
  T* elements;

public:
  Vecteur(int = 0);
  Vecteur(const Vecteur<T>&);
  ~Vecteur();

  Vecteur<T>& operator=(const Vecteur<T>&);
  Vecteur<T> operator+(const Vecteur<T>&);
  T& operator[](int);
  const T& operator[](int) const;
  T operator*(const Vecteur<T>&);
  void push(T);
  void pop();
  friend std::ostream& operator<<(std::ostream&, const Vecteur<T>&);

  typedef Iterateur<T> iterateur;
  iterateur begin();
  iterateur end();
};

template<class T>
std::ostream& operator<<(std::ostream&, const Vecteur<T>&);

#include <vecteur.hxx>

#endif
