#ifndef VALEUR_HPP
#define VALEUR_HPP

#include <vector>
#include <string>

class Valeur {
private:
  double real;
  std::string nom;

public:
  Valeur();
  Valeur(double, std::string = "");

  bool operator<(const Valeur&) const;

  double getNombre() const { return real; }
  void setNombre(int x) { real = x; }
  double getNote() const { return real; }
  void setNote(int x) { real = x; }
  std::string getEtudiant() const { return nom; }
  void setEtudiant(std::string s) { nom = s; }
};

#endif
