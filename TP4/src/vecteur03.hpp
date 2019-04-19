// Gardien //---------------------------------------------------------------------------------------
#ifndef _VECTEUR03_HPP_
#define _VECTEUR03_HPP_

// Entetes //---------------------------------------------------------------------------------------
#include <complexe.hpp>
#include <stdexcept>
#include <iterator>

// Classe  V e c t e u r //-------------------------------------------------------------------------
class Vecteur {
 //----------------------------------------------------------------------------------------Attributs
 private:
  unsigned     taille_;
  complexe_t * tableau_;

 //---------------------------------------------------------------------------------------Accesseurs
 public:
  unsigned getTaille(void) const { return taille_; }

  complexe_t & operator[](unsigned i) {
   if (i<taille_) return tableau_[i];
   throw std::out_of_range("");
  }

  const complexe_t & operator[](unsigned i) const {
   if (i<taille_) return tableau_[i];
   throw std::out_of_range("");
  }

  //---------------------------------------------------------------------------------------Iterators
  private:
    class Iterator : public std::iterator<std::input_iterator_tag, int>
    {
      complexe_t* p;
      public:
        Iterator(complexe_t* x) :p(x) {}
        Iterator(const Iterator& mit) : p(mit.p) {}
        Iterator& operator++() {++p;return *this;}
        Iterator operator++(int) {Iterator tmp(*this); operator++(); return tmp;}
        bool operator==(const Iterator& rhs) const {return p==rhs.p;}
        bool operator!=(const Iterator& rhs) const {return p!=rhs.p;}
        complexe_t & operator*() {return *p;}
    };

  public:
    using iterator = Iterator;
    iterator begin() { return iterator(tableau_); }
    iterator end() { return iterator(tableau_ + taille_); }

  public:
  //-----------------------------------------------------------------------------Constructeur defaut
  explicit Vecteur(unsigned t = 10) : taille_(t),tableau_(new complexe_t[taille_]) {}

  //------------------------------------------------------------------------------Constructeur copie
  Vecteur(const Vecteur & v) : taille_(v.taille_),tableau_(new complexe_t[taille_]) {
   for (unsigned i = 0; i<taille_; ++i) tableau_[i]=v[i];
  }

  //-------------------------------------------------------------------------------------Destructeur
  ~Vecteur(void) { if (tableau_) delete [] tableau_; }

  //-------------------------------------------------------------------------------Affectation copie
  Vecteur & operator=(const Vecteur & v) {
   if (this!=&v) {
    if (taille_!=v.taille_) throw std::length_error("");
    for (unsigned i = 0; i<v.taille_; ++i) tableau_[i]=v[i];
   }

   return *this;
  }
};

// Surcharge operateurs //--------------------------------------------------------------------------

//----------------------------------------------------------------------------------------operator<<
inline std::ostream & operator<<(std::ostream & flux,const Vecteur & v) {
 for (unsigned i = 0; i<v.getTaille(); ++i) flux << v[i] << " ";
 return flux;
}

//-----------------------------------------------------------------------------------------operator+
inline Vecteur operator+(const Vecteur & v1,const Vecteur & v2) {
 Vecteur v;

 for (unsigned i = 0; i<v1.getTaille(); ++i) v[i]=v1[i]+v2[i];

 return v;
}

//-----------------------------------------------------------------------------------------operator*
inline Vecteur operator*(const Vecteur & v1,const Vecteur & v2) {
 Vecteur v;

 for (unsigned i = 0; i<v1.getTaille(); ++i) v[i]=v1[i]*v2[i];

 return v;
}

// Fin //-------------------------------------------------------------------------------------------
#endif
