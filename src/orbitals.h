#ifndef ORBITALS_H
#define ORBITALS_H

#include <utility>
#include <cmath>
#include <vector>
#include "taylor.h"

/// @brief The gravitational constant
const double G = 6.67428e-11;

/**
 * @brief Struct for holding a classical, Keplarian orbit
 */
struct KeplerParameters {
	double Epoch = 0;
	double ARGP;
	double ecce;
	double N0;
	double M0;
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
	Taylor tayX;
	Taylor tayY;
};



/// @brief Calculate the amount of force acting on object self by object other
///
/// @param self A not-on-rails Body
/// @param other An on rails body
///
/// @return The 2d force vector of other on self (or vice versa)
std::pair<double, double> force(Body self, Body other);

#endif
