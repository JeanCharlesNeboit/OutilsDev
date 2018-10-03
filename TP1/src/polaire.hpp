#ifndef POLAIRE_HPP
#define POLAIRE_HPP

#include <iostream>
#include <sstream>
#include <point.hpp>
#include <cartesien.hpp>

class Polaire : public Point {
private:
	double angle;
	double distance;

public:
	Polaire();
	Polaire(double, double);
	Polaire(const Cartesien&);
	~Polaire();

	void afficher(std::stringstream &) const;
	void convertir(Cartesien&) const;
	void convertir(Polaire&) const;

	double getAngle() const { return angle; }
	void setAngle(double a) { angle = a; }
	double getDistance() const { return distance; }
	void setDistance(double d) { distance = d; }
};

#endif
