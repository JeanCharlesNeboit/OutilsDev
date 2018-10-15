#include <nuage.hpp>

template<typename T>
Nuage<T>::Nuage() {

}

template<typename T>
Nuage<T>::~Nuage() {

}

template<typename T>
int Nuage<T>::size() {
  return points.size();
}

template<typename T>
void Nuage<T>::ajouter(const T p) {
  points.push_back(p);
}

template<typename T>
typename Nuage<T>::const_iterator Nuage<T>::begin() const {
  return points.begin();
}

template<typename T>
typename Nuage<T>::const_iterator Nuage<T>::end() const {
  return points.end();
}

template<typename T>
T barycentre_v1(Nuage<T>& n) {
  if (n.size() == 0) {
	  return T(0,0);
  }
  
  double x = 0;
  double y = 0;
  Cartesien c;
  for(typename Nuage<T>::const_iterator it = n.begin(); it != n.end(); ++it) {
    (*it).convertir(c);
    x += c.getX();
    y += c.getY();
  }
  return Cartesien(x/n.size(), y/n.size());
}

template<typename T>
Cartesien BarycentreCartesien<T>::operator()(Nuage<T> &n) {
  return barycentre(n);
}

template<typename T>
Polaire BarycentrePolaire<T>::operator()(Nuage<T> &n) {
  Polaire p;
  barycentre(n).convertir(p);
  return p;
}
