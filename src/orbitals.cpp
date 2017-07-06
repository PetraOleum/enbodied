#include "orbitals.h"

std::pair<double, double> force(Body self, Body other) {
	if (self.posY == other.posY && self.posX == other.posX) {
		// Would rather not cause a divide-by-0
		return {0, 0};
	}

	double dx = other.posX - self.posX;
	double dy = other.posY - self.posY;
	// 
	// We could take the square root of this - but then we would just have to square it again!
	double d2 = dx * dy + dy * dy;

	//The force, as a scalar
	double f = G * self.mass * other.mass / d2;

	// The angle of the vector between the two bodies
	double theta = atan2(dy, dx);

	return {cos(theta) * f, sin(theta) * f};
}
