#include <vecteur.hpp>

template<class T>
Vecteur<T>::Vecteur(int _size) : size(_size) {
  elements = new int[size];
  std::fill(elements, elements+size, 0);
}

template<class T>
Vecteur<T>::Vecteur(const Vecteur<T>& _vecteur) : Vecteur<T>(_vecteur.size) {
  std::copy(_vecteur.elements, _vecteur.elements+size, elements);
}

template<class T>
Vecteur<T>::~Vecteur() {
  if (elements) {
    delete[] elements;
  }
}

template<class T>
Vecteur<T>& Vecteur<T>::operator=(const Vecteur<T>& _vecteur) {
  if (elements == _vecteur.elements) {
      return *this;
  }
  if (elements) {
    delete[] elements;
  }
  size = _vecteur.size;
  elements = new int[size];
  std::copy(elements, elements+size,_vecteur.elements);
  return *this;
}

template<class T>
Vecteur<T> Vecteur<T>::operator+(const Vecteur<T>& _vecteur) {
  if (size != _vecteur.size) {
    throw std::runtime_error("Vecteurs must have same size");
  }
  Vecteur _v(size);
  for(auto i=0; i<size; ++i) {
    _v.elements[i] += elements[i] + _vecteur.elements[i];
  }
  return _v;
}

template<class T>
T Vecteur<T>::operator*(const Vecteur<T>& _vecteur) {
  if (size != _vecteur.size) {
    throw std::runtime_error("Vecteurs must have same size");
  }
  int scalar = 0;
  for(auto i=0; i<size; ++i) {
    scalar += elements[i] * _vecteur.elements[i];
  }
  return scalar;
}

template<class T>
T& Vecteur<T>::operator[](int _index) {
  if (_index < 0 || _index >= size) {
    throw std::out_of_range("Index out of range.");
  }
  return elements[_index];
}

template<class T>
const T& Vecteur<T>::operator[](int _index) const {
  if (_index < 0 || _index >= size) {
    throw std::out_of_range("Index out of range.");
  }
  return elements[_index];
}

template<class T>
void Vecteur<T>::push(T x) {
  int* tmp = elements;
  elements = new int[++size];
  std::copy(tmp, tmp+size-1, elements);
  elements[size-1] = x;
  if (tmp) {
    delete[] tmp;
  }
}

template<class T>
void Vecteur<T>::pop() {
  if (size > 0) {
    int* tmp = elements;
    elements = new int[--size];
    std::copy(tmp, tmp+size, elements);
    if (tmp) {
      delete[] tmp;
    }
  }
}

template<class T>
typename Vecteur<T>::iterateur Vecteur<T>::begin() {
  return Vecteur::iterateur(elements);
}

template<class T>
typename Vecteur<T>::iterateur Vecteur<T>::end() {
  return Vecteur::iterateur(elements+size);
}

template<class T>
std::ostream& operator<<(std::ostream& _ostream, const Vecteur<T>& _vecteur) {
  for(auto i=0; i<_vecteur.size; ++i) {
    _ostream << _vecteur.elements[i];
    if (i != _vecteur.size-1) std::cout << ",";
  }
  return _ostream;
}
