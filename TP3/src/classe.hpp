#ifndef CLASSE_HPP
#define CLASSE_HPP

class Classe {
private:
  double inf;
  double sup;
  mutable unsigned quantite;

public:
  Classe(double, double);

  bool operator<(const Classe&) const;
  bool operator>(const Classe&) const;

  double getBorneInf() const { return inf; }
  void setBorneInf(int _inf) { inf = _inf; }
  double getBorneSup() const { return sup; }
  void setBorneSup(int _sup) { sup = _sup; }
  double getQuantite() const { return quantite; }
  void setQuantite(int _quantite) { quantite = _quantite; }
  void ajouter() const { quantite++; }
};

#endif
