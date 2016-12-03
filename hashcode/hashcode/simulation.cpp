#include "simulation.hpp"
#include <fstream>

simulation::simulation() {}

simulation::~simulation()
{
    for (auto it = m_satellites.begin(); it != m_satellites.end(); it++) {
        delete (*it);
    }
    m_satellites.clear();

    for (auto it = m_collections.begin(); it != m_collections.end(); it++) {
        delete (*it);
    }
    m_collections.clear();

    // TODO delete all photgraphs taken
}

simulation & simulation::operator=(const simulation & simulation)
{
	m_duration = simulation.m_duration;
	m_number_of_collections = simulation.m_number_of_collections; // copy
	m_number_of_satellites  = simulation.m_number_of_satellites;  // copy

	return *this;
}

simulation::simulation(const simulation & simulation)
{
	m_duration = simulation.m_duration;
	m_number_of_collections = simulation.m_number_of_collections; // copy
	m_number_of_satellites  = simulation.m_number_of_satellites;  // copy
}
