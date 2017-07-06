#ifndef ORBITALS_H
#define ORBITALS_H

#include <utility>
#include <cmath>
#include <vector>

/// @brief The gravitational constant
const double G = 6.67428e-11;

/**
 * @brief Struct for holding a classical, Keplarian orbit
 */
struct KeplerParameters {

};

/**
 * @brief Holds some basic information about a "body"
 */
struct Body {
	double posX;
	double posY;
	double radius;
	double mass;
	double velX;
	double velY;
	bool onRails;
};

/**
 * @brief Class that contains a prediction for the future locations of a Body
 */
class OrbitalPrediction {

};

/// @brief Calculate the amount of force acting on object self by object other
///
/// @param self A not-on-rails Body
/// @param other An on rails body
///
/// @return The 2d force vector of other on self (or vice versa)
std::pair<double, double> force(Body self, Body other);

#endif
