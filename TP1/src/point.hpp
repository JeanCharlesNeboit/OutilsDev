#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <sstream>

class Polaire;
class Cartesien;

class Point {
private:

public:
	Point();
	virtual ~Point();

	virtual void afficher(std::stringstream &) const = 0;
	virtual void convertir(Polaire&) const = 0;
	virtual void convertir(Cartesien&) const = 0;
	friend std::ostream& operator<<(std::ostream&, const Point&);
};

std::ostream& operator<<(std::ostream&, const Point&);

#endif
