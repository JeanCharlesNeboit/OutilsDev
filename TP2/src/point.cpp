#include <point.hpp>

Point::Point() {

}

Point::~Point() {

}

std::ostream& operator<<(std::ostream& os, const Point& p) {
  std::stringstream ss;
  p.afficher(ss);
  os << ss.str();
  return os;
}
