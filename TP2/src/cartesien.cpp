#include <cartesien.hpp>

Cartesien::Cartesien() : x(0), y(0) {

}

Cartesien::Cartesien(double x, double y) : x(x), y(y) {

}

Cartesien::Cartesien(const Polaire& p) {
	p.convertir(*this);
}

Cartesien::~Cartesien() {

}

void Cartesien::afficher(std::stringstream &s) const {
	s << "(x=" << x << ";y=" << y << ")";
}

void Cartesien::convertir(Polaire& p) const {
	double deg = 360/(2*M_PI);
	p.setDistance(sqrt(pow(x,2)+pow(y,2)));
	p.setAngle(atan(y/x)*deg);
}

void Cartesien::convertir(Cartesien& c) const {
	c.setX(x);
	c.setY(y);
}
