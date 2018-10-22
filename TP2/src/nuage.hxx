#include <nuage.hpp>

template<typename T>
Nuage<T>::Nuage() {

}

template<typename T>
Nuage<T>::~Nuage() {

}

template<typename T>
int Nuage<T>::size() const {
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
T barycentre_v1(const Nuage<T>& n) {
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

  return T(Cartesien(x/n.size(), y/n.size()));
}

/*template<>
Polaire barycentre_v1(const Nuage<Polaire>& n) {
  if (n.size() == 0) {
	  return Polaire(0,0);
  }

  double distance = 0;
  double angle = 0;
  for(typename Nuage<Polaire>::const_iterator it = n.begin(); it != n.end(); ++it) {
    distance += (*it).getDistance();
    angle += (*it).getAngle();
  }

  return Polaire(angle/n.size(), distance/n.size());
}*/

template<typename T>
typename T::value_type barycentre_v2(const T& n) {
  typedef typename T::value_type valueType;
  if (n.size() == 0) {
    return valueType(0, 0);
  }

  double x = 0;
  double y = 0;
  Cartesien c;
  for(typename T::const_iterator it = n.begin(); it != n.end(); ++it) {
    (*it).convertir(c);
    x += c.getX();
    y += c.getY();
  }

  return valueType(Cartesien(x/n.size(), y/n.size()));
}
