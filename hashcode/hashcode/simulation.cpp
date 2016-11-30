#include "simulation.hpp"
#include <fstream>

simulation::simulation(){
}

simulation::~simulation()
{
	m_duration = 0;
	m_number_of_satellites = 0;
	m_number_of_collections = 0;
	m_photographs_taken = *(new std::vector<photograph*>);
}

simulation & simulation::operator=(const simulation & simulation)
{
	m_duration = simulation.m_duration;
	m_number_of_collections = simulation.m_number_of_collections;
	m_number_of_satellites = simulation.m_number_of_satellites;
	
	return *this;
}

simulation::simulation(const simulation & simulation)
{
	m_duration = simulation.m_duration;
	m_number_of_collections = simulation.m_number_of_collections;
	m_number_of_satellites = simulation.m_number_of_satellites;
}

void simulation::setDuration(unsigned int duration)
{
	this->m_duration = duration;
}

void simulation::took_photograph(satellite* satellite, photograph* photograph){
	m_photographs_taken.push_back(photograph);

}
