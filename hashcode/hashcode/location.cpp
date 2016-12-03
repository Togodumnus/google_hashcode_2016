#include "location.hpp"

location::location() { }

location::location(long int latitude, long int longitude) :
	m_latitude(latitude), m_longitude(longitude) { }

location::~location() { }

location::location(const location & location) {
	m_latitude = location.m_latitude;
	m_longitude = location.m_longitude;
}

location & location::operator=(const location& location) {
	m_latitude = location.m_latitude;
	m_longitude = location.m_longitude;

	return *this;
}

long int location::getLatitude() const {
	return this->m_latitude;
}

long int location::getLongitude() const {
	return this->m_longitude;
}

