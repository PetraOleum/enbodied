#include "orbitals.h"
#include <cstdio>

std::pair<double, double> force(Body self, Body other) {
	if (self.posY == other.posY && self.posX == other.posX) {
		// Would rather not cause a divide-by-0
		return {0, 0};
	}

	double dx = other.posX - self.posX;
	double dy = other.posY - self.posY;
	// 
	// We could take the square root of this - but then we would just have to square it again!
	double d2 = dx * dx + dy * dy;

	//The force, as a scalar
	double f = G * self.mass * other.mass / d2;

	// The angle of the vector between the two bodies
	double theta = atan2(dy, dx);

//	printf("dx: %f, dy: %f   d2: %f, G: %f, f: %f", dx, dy, d2, G, f);

	return {cos(theta) * f, sin(theta) * f};
}

std::pair<double, double> KeplerParameters::calculate(double time) {
	// n = average rate of sweep; M_PI is pi
	double n = 2 * M_PI / this->period;

	// M = mean anomaly
	double M = M0 + n * (time - Epoch);

	// E is the eccentric anomaly
	// These are useful values for calculating E
	double e2 = ecce * ecce;
	double e3 = ecce * e2;
	double cM = cos(M);

	// A third-order approximation of E
	double E = M + (-1/2 * e3 + ecce + (e2 + 3/2 * cM * e3) * cM) * sin(M);

	// The true anomaly
	double theta = 2 * atan2(sqrt(1 - ecce) * cos(E/2), sqrt(1 + ecce) * sin(E / 2));

	// The "heliocentric distance"
	double r = a * (1 - ecce * cos(E));

	// From theta and r (the hypotenuse of a triangle) can calculate distance from a focus
	return { r * cos(theta), r * sin(theta) };
}

