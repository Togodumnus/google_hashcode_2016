#include "Location.hpp"

Location::Location(LocationUnit latitude, LocationUnit longitude) :
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

LocationUnit Location::getLatitude() const {
	return this->m_latitude;
}

LocationUnit Location::getLongitude() const {
	return this->m_longitude;
}

void Location::setLatitude(LocationUnit l){
	this->m_latitude = l;
}

void Location::setLongitude(LocationUnit l){
	this->m_longitude = l;
}

