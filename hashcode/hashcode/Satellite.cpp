#include <ostream>
#include <iostream>
#include <array>
#include "Satellite.hpp"

Satellite::Satellite(
		unsigned short id,
		long int latitude,
		long int longitude,
		int velocity,
		int orientation_max_change,
		int orientation_max_value) :
		Location(latitude, longitude),
		m_id(id),
		m_velocity(velocity),
		m_orientation_max_change(orientation_max_change),
		m_orientation_max_value(orientation_max_value) { }

Satellite::Satellite(
		unsigned short id,
		SatelliteLine line) :
		Location(std::stol(line[0]), std::stol(line[1])),
		m_id(id) {
	m_velocity               = std::stoi(line[2]);
	m_orientation_max_change = std::stoi(line[3]);
	m_orientation_max_value  = std::stoi(line[4]);
}

Satellite::~Satellite() { }

Satellite::Satellite(const Satellite& satellite) :
	Location(satellite.m_latitude, satellite.m_longitude) {
	m_velocity	 = satellite.m_velocity;
	m_orientation_max_change = satellite.m_orientation_max_change;
	m_orientation_max_value = satellite.m_orientation_max_value;
}

Satellite& Satellite::operator=(const Satellite & satellite)
{
	m_latitude	 = satellite.m_latitude;
	m_longitude  = satellite.m_longitude;
	m_velocity	 = satellite.m_velocity;
	m_orientation_max_change = satellite.m_orientation_max_change;
	m_orientation_max_value = satellite.m_orientation_max_value;

	return *this;
}

std::ostream& operator<<(std::ostream& o, const Satellite& s) {
	return o << "Satellite("
		<< "id[" << s.m_id << "] "
		<< "lat[" << s.m_latitude << "] "
		<< "long[" << s.m_longitude << "] "
		<< "cam_lat[" << s.m_cam_lat << "] "
		<< "cam_long[" << s.m_cam_long << "] "
		<< "velocity[" << s.m_velocity << "] "
		<< "orientationMaxChange[" << s.m_orientation_max_change << "] "
		<< "orientationMaxValue[" << s.m_orientation_max_value << "]"
		<< ")";
}

long int Satellite::getLatitudeT(unsigned long int time) {
	return this->getLatitude();
}

long int Satellite::getLongitudeT(unsigned long int time) {
	return this->getLongitude();
}
