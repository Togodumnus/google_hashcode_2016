#include "simulation.hpp"
#include <fstream>

simulation::simulation(const char* input_file){
	std::ifstream input;
	input.open(input_file);

	input.close();
}

simulation::~simulation()
{
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

void simulation::took_photograph(satellite* satellite, photograph* photograph){
	m_photographs_taken.push_back(photograph);

}
