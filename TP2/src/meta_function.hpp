#ifndef META_FUNCTION_HPP
#define META_FUNCTION_HPP

template <typename T, T val>
struct Nombre {
  typedef T type;
  static const type valeur = val;
};

template <typename Test, typename Alors, typename Sinon, bool = Test::valeur>
struct Si : Sinon {

};

template <typename N>
struct EstNegatif : Nombre<bool, N::valeur<0 > {

};

template <typename N>
struct ValeurAbsolue : Si <EstNegatif<N>, Nombre<typename N::type, -N::valeur>, Nombre<typename N::type, N::valeur>> {

};

#endif
