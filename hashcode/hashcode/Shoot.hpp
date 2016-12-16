#pragma once

#include <ostream>
#include <fstream>
#include "Satellite.hpp"

class Photograph;

/**
 * Represent the time when the satellite take the photograph
 */
struct Shoot {
	Collection* m_collection;
	Photograph* m_photograph;
	Satellite*  m_satellite;
	unsigned long int m_t;

	Shoot(
		Photograph* photograph,
		Satellite*  satellite,
		unsigned long int t
	);

	Shoot(
		Collection* collection,
		Photograph* photograph,
		Satellite*  satellite,
		unsigned long int t
	);

	Shoot(const Shoot& shoot);

	~Shoot() {};

	bool operator<(const Shoot& s) const {
        return (m_t < s.m_t);
    }

	inline LocationUnit distance() const {
		return m_satellite->distanceT(m_t, *m_photograph);
	}

	friend std::ostream& operator<<(std::ostream&, const Shoot&);
	friend std::ofstream& operator<<(std::ofstream&, const Shoot&);
};
