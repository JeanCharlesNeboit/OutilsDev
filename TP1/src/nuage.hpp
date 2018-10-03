#ifndef NUAGE_HPP
#define NUAGE_HPP

#include <iostream>
#include <vector>
#include <point.hpp>
#include <cartesien.hpp>

class Nuage {
private:
  std::vector<Point*> points;

public:
  Nuage();
  ~Nuage();

  typedef std::vector<Point*>::const_iterator const_iterator;
  const_iterator begin() const;
  const_iterator end() const;

  int size();
  void ajouter(Point&);
};

class BarycentreCartesien {
public:
  Cartesien operator()(Nuage&);
};

class BarycentrePolaire {
public:
  Polaire operator()(Nuage&);
};

Cartesien barycentre(Nuage&);

#endif
