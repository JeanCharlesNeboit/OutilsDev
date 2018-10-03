#include <iterateur.hpp>

template<class T>
Iterateur<T>::Iterateur(T* x) : p(x) {

}

template<class T>
Iterateur<T>::Iterateur(const Iterateur<T>& it) : p(it.p) {

}

template<class T>
Iterateur<T>& Iterateur<T>::operator++() {
  ++p;
  return *this;
}

template<class T>
Iterateur<T> Iterateur<T>::operator++(int) {
  Iterateur tmp(*this);
  operator++();
  return *tmp;
}

template<class T>
bool Iterateur<T>::operator==(const Iterateur<T>& it) const {
  return p == it.p;
}

template<class T>
bool Iterateur<T>::operator!=(const Iterateur<T>& it) const {
  return p != it.p;
}

template<class T>
T& Iterateur<T>::operator*() {
  return *p;
}
