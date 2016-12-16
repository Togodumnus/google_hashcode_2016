#include "Shoot.hpp"

Shoot::Shoot(
	Photograph* photograph,
	Satellite*  satellite,
	unsigned long int t
) :
	m_collection(nullptr),
	m_photograph(photograph),
	m_satellite(satellite),
	m_t(t) {};

Shoot::Shoot(
	Collection* collection,
	Photograph* photograph,
	Satellite*  satellite,
	unsigned long int t
) :
	m_collection(collection),
	m_photograph(photograph),
	m_satellite(satellite),
	m_t(t) {};

Shoot::Shoot(const Shoot & shoot)
{
	m_collection = shoot.m_collection;
	m_photograph = shoot.m_photograph;
	m_satellite  = shoot.m_satellite;
	m_t = shoot.m_t;
}

std::ostream& operator<<(std::ostream& o, const Shoot& s) {
	o << "Shoot[time=" << s.m_t
		<< " satellite=" << *s.m_satellite
		<< " photo=" << *(s.m_photograph)
		<< " collection=" << *(s.m_collection)
		<< "]";
	return o;
}

std::ofstream& operator<<(std::ofstream& of, const Shoot& s)
{
	of	<< s.m_photograph->getLatitude()
		<< " " << s.m_photograph->getLongitude()
		<< " " << s.m_t << " " << s.m_satellite->getId();
	return of;
}
