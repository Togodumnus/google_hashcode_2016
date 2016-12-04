#include <fstream>
#include "Simulation.hpp"

Simulation::Simulation(const char* input_file) {
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
	m_duration = simulation.m_duration;
	m_number_of_collections = simulation.m_number_of_collections; // copy
	m_number_of_satellites	= simulation.m_number_of_satellites;  // copy

	return *this;
}

Simulation::Simulation(const Simulation& simulation)
{
	m_duration = simulation.m_duration;
	m_number_of_collections = simulation.m_number_of_collections; // copy
	m_number_of_satellites	= simulation.m_number_of_satellites;  // copy
}

int Simulation::write_results()
{
	std::ofstream file("results.txt", std::ios::out | std::ios::trunc);
	if (file)
	{
		file << "test";
		file.close();
	}
	else
		std::cerr << "Erreur à l'ouverture !" << std::endl;

	return 0;
}