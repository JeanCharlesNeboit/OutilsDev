#ifndef CARTESIEN_HPP
#define CARTESIEN_HPP

#include <iostream>
#include <sstream>
#include <cmath>
#include <point.hpp>
#include <polaire.hpp>

class Cartesien : public Point {
private:
	double x;
	double y;

public:
	Cartesien();
	Cartesien(double, double);
	Cartesien(const Polaire&);
	~Cartesien();

	void afficher(std::stringstream &) const;
	void convertir(Polaire&) const;
	void convertir(Cartesien&) const;

	double getX() const { return x; }
	void setX(double x) { this->x = x; }
	double getY() const { return y; }
	void setY(double y) {this->y = y; }
};

#endif
