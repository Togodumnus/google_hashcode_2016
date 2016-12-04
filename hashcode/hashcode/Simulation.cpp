#include <fstream>
#include "Simulation.hpp"

Simulation::Simulation(const char* input_file, std::unique_ptr<Algorithm>& algo)
	: m_algo(algo)
{
	parseInput(input_file, true);
}

Simulation::~Simulation()
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

Simulation& Simulation::operator=(const Simulation& simulation)
{
	m_algo = std::move(simulation.m_algo);
	m_duration = simulation.m_duration;
	m_number_of_collections = simulation.m_number_of_collections; // copy
	m_number_of_satellites	= simulation.m_number_of_satellites;  // copy

	return *this;
}

Simulation::Simulation(const Simulation& simulation)
	: m_algo(simulation.m_algo)
{
	m_duration = simulation.m_duration;
	m_number_of_collections = simulation.m_number_of_collections; // copy
	m_number_of_satellites	= simulation.m_number_of_satellites;  // copy
}

void Simulation::solve() {
	m_algo->solve();
}
