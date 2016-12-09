#pragma once

#include <ostream>
#include "Satellite.hpp"

class Photograph;

/**
 * Represent the time when the satellite take the photograph
 */
struct Shoot {
	Photograph* photograph;
	Satellite*  satellite;
	unsigned long int t;

	friend std::ostream& operator<<(std::ostream& o, const Shoot& s) {
		o << "Shoot[time=" << s.t
			<< " satellite" << s.satellite->getId()
			<< " photo " << s.photograph << "]";
		return o;
	}

	Shoot(
		Photograph* photograph,
		Satellite*  satellite,
		unsigned long int t
	) : photograph(photograph), satellite(satellite), t(t) {};

	LocationUnit distance() {
		return satellite->distanceT(t, *photograph);
	}
};
