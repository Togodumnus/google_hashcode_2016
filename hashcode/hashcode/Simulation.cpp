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

std::ostream& operator<<(std::ostream& os, const Simulation& simu){
	os << "Nombre de satellites : " << simu.m_number_of_satellites << "\n";
	os << "Nombre de collections : " <<  simu.m_number_of_collections << "\n";
	for (std::vector<Collection*>::const_iterator it = simu.m_collections.begin(); it != simu.m_collections.end(); it++){
		os << "La collection " << (*it)->getID() << " a " << (*it)->getNumberOfPhotographs() << " photos Ã  prendre \n";
	}

	return os;
}

int Simulation::write_results()
{
	std::ofstream file("results.txt", std::ios::out | std::ios::trunc);
	if (file)
	{
		for(auto &it:m_shoots){
			file << *it;
			file << "\n";
		}
		file.close();
	}
	else
		std::cerr << "Erreur à l'ouverture !" << std::endl;

	return 0;

}