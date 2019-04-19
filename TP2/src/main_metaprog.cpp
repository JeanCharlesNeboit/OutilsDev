#include <cstdlib>
#include <meta_function.hpp>
#include <iostream>

int main() {
 std::cout << ValeurAbsolue<Nombre<int, -1>>::valeur << std::endl;
 return EXIT_SUCCESS;
}
