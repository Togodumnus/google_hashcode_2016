#include "Location.hpp"

Location::Location(long int latitude, long int longitude) :
	m_latitude(latitude), m_longitude(longitude) { }

Location::~Location() { }

Location::Location(const Location& location) {
	m_latitude = location.m_latitude;
	m_longitude = location.m_longitude;
}

Location& Location::operator=(const Location& location) {
	m_latitude = location.m_latitude;
	m_longitude = location.m_longitude;

	return *this;
}

long int Location::getLatitude() const {
	return this->m_latitude;
}

long int Location::getLongitude() const {
	return this->m_longitude;
}

void Location::setLatitude(long int l){
	this->m_latitude = l;
}

void Location::setLongitude(long int l){
	this->m_longitude = l;
}

