#include <polaire.hpp>

Polaire::Polaire() : angle(0), distance(0) {

}

Polaire::Polaire(double a, double d) : angle(a), distance(d) {

}

Polaire::Polaire(const Cartesien& c) {
	c.convertir(*this);
}

Polaire::~Polaire() {

}

void Polaire::afficher(std::stringstream &s) const {
	s << "(a=" << angle << ";d=" << distance << ")";
}

void Polaire::convertir(Cartesien& c) const {
	double rad = (2*M_PI)/360;
	c.setX(distance*cos(angle*rad));
	c.setY(distance*sin(angle*rad));
}

void Polaire::convertir(Polaire& p) const {
	p.setAngle(angle);
	p.setDistance(distance);
}
