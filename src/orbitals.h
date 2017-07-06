#ifndef ORBITALS_H
#define ORBITALS_H

#include <utility>
#include <cmath>

const double G = 6.67428e-11;

struct Body {
	double posX;
	double posY;
	double radius;
	double mass;
	double velX;
	double velY;
};

std::pair<double, double> force(Body self, Body other);

#endif
