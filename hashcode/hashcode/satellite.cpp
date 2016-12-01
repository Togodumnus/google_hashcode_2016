#include "satellite.hpp"


satellite::satellite()
{
}

satellite::satellite(simulation* simulation, double latitude, double longitude, float velocity, float orientation_max_change, float orientation_max_value) : m_simulation(simulation), m_latitude(latitude), m_longitude(longitude), m_velocity(velocity), m_orientation_max_change(orientation_max_change), m_orientation_max_value(orientation_max_value){

}

satellite::~satellite(){

}

satellite::satellite(const satellite& satellite) {
	m_latitude = satellite.m_latitude;
	m_longitude = satellite.m_longitude;
	m_simulation = satellite.m_simulation;
	m_velocity = satellite.m_velocity;
	m_orientation_max_change = satellite.m_orientation_max_change;
	m_orientation_max_value = satellite.m_orientation_max_value;
}


satellite & satellite::operator=(const satellite & satellite)
{
	m_simulation = satellite.m_simulation;
	m_latitude = satellite.m_latitude;
	m_longitude = satellite.m_longitude;
	m_velocity = satellite.m_velocity;
	m_orientation_max_change = satellite.m_orientation_max_change;
	m_orientation_max_value = satellite.m_orientation_max_value;

	return *this;
}

float satellite::getVelocity()
{
	return m_velocity;
}


// TODO
/*bool satellite::canTake(photograph* photograph) {
}*/

bool satellite::take(photograph* photograph){
	return false;
}

void satellite::moveCamera()
{
}
