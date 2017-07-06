#include "orbitals.h"

std::pair<double, double> force(Body self, Body other) {
	if (self.posY == other.posY && self.posX == other.posX) {
		// Would rather not cause a divide-by-0
		return {0, 0};
	}
	double dx = other.posX - self.posX;
	double dy = other.posY - self.posY;
	double d2 = dx * dy + dy * dy;

	double f = self.mass * other.mass / d2;

	double theta = atan2(dy, dx);

	return {cos(theta) * f, sin(theta) * f};
}
