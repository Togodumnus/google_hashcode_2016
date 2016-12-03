#include <ostream>
#include <array>
#include "satellite.hpp"

satellite::satellite(
		simulation* simulation,
		long int latitude,
		long int longitude,
		int velocity,
		int orientation_max_change,
		int orientation_max_value) :
		location(latitude, longitude),
		m_simulation(simulation),
		m_velocity(velocity),
		m_orientation_max_change(orientation_max_change),
		m_orientation_max_value(orientation_max_value) { }

satellite::satellite(
		simulation* simulation,
		SatelliteLine line) :
		m_simulation(simulation) {
	location(std::stol(line[0]), std::stol(line[1]));
	m_velocity               = std::stoi(line[2]);
	m_orientation_max_change = std::stoi(line[3]);
	m_orientation_max_value  = std::stoi(line[4]);
}

satellite::~satellite() { }

satellite::satellite(const satellite& satellite) {
	m_latitude	 = satellite.m_latitude;
	m_longitude  = satellite.m_longitude;
	m_simulation = satellite.m_simulation;
	m_velocity	 = satellite.m_velocity;
	m_orientation_max_change = satellite.m_orientation_max_change;
	m_orientation_max_value = satellite.m_orientation_max_value;
}

satellite & satellite::operator=(const satellite & satellite)
{
	m_latitude	 = satellite.m_latitude;
	m_longitude  = satellite.m_longitude;
	m_simulation = satellite.m_simulation;
	m_velocity	 = satellite.m_velocity;
	m_orientation_max_change = satellite.m_orientation_max_change;
	m_orientation_max_value = satellite.m_orientation_max_value;

	return *this;
}

std::ostream& operator<<(std::ostream& o, const satellite& s) {
	return o << "Satellite("
		<< "lat[" << s.m_latitude << "] "
		<< "long[" << s.m_longitude << "] "
		<< "cam_lat[" << s.m_cam_lat << "] "
		<< "cam_long[" << s.m_cam_long << "] "
		<< "velocity[" << s.m_velocity << "] "
		<< "orientationMaxChange[" << s.m_orientation_max_change << "] "
		<< "orientationMaxValue[" << s.m_orientation_max_value << "]"
		<< ")";
}
