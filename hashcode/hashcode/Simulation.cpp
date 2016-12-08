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
	m_algo->solve(this);
}

std::ostream& operator<<(std::ostream& os, const Simulation& simu){
	os << "Nombre de satellites : " << simu.m_number_of_satellites << "\n";
	os << "Nombre de collections : " <<  simu.m_number_of_collections << "\n";
	for (std::vector<Collection*>::const_iterator it = simu.m_collections.begin(); it != simu.m_collections.end(); it++){
		os << "La collection " << (*it)->getId() << " a " << (*it)->getNumberOfPhotographs() << " photos à prendre \n";
	}

	return os;
}
