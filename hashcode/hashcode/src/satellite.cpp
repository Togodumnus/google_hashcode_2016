#include "..\include\satellite.hpp"


satellite::satellite(simulation* simulation, double latitude, double longitude, float velocity, float orientation_max_change, float orientation_max_value) : m_simulation(simulation), m_location(latitude, longitude), m_velocity(velocity), m_orientation_max_change(orientation_max_change), m_orientation_max_value(orientation_max_value){
	
}

satellite::~satellite(){

}

satellite::satellite(const satellite & satellite)
{
	m_simulation = satellite.m_simulation;
	m_location = satellite.m_location;
	m_velocity = satellite.m_velocity;
	m_orientation_max_change = satellite.m_orientation_max_change;
	m_orientation_max_value = satellite.m_orientation_max_value;
}

satellite & satellite::operator=(const satellite & satellite)
{
	m_simulation = satellite.m_simulation;
	m_location = satellite.m_location;
	m_velocity = satellite.m_velocity;
	m_orientation_max_change = satellite.m_orientation_max_change;
	m_orientation_max_value = satellite.m_orientation_max_value;

	return *this;
}

bool satellite::take(photograph* photograph){
	return false;	
}
