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
