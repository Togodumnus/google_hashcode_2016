#include "Simulation.hpp"

#include <stdexcept>

Simulation::Simulation(std::string& input_file)
{
	parseInput(input_file);
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

	// TODO delete all Shoot
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

/*void Simulation::solve() {
	m_algo->solve(this);
}*/

std::ostream& operator<<(std::ostream& os, const Simulation& simu){
	os << "Nombre de satellites : " << simu.m_number_of_satellites << "\n";
	os << "Nombre de collections : " <<  simu.m_number_of_collections << "\n";
	for (std::vector<Collection*>::const_iterator it = simu.m_collections.begin(); it != simu.m_collections.end(); it++){
		os << "La collection " << (*it)->getId() << " a " << (*it)->getNumberOfPhotographs() << " photos Ã  prendre \n";
	}

	return os;
}

int Simulation::write_results(const char* OUTPUT)
{

	std::sort(
		m_shoots.begin(),
		m_shoots.end(),
		[](const Shoot* s1, const Shoot* s2) {
			return *s1 < *s1;
		}
	);

	std::ofstream file(OUTPUT, std::ios::out | std::ios::trunc);
	if (file)
	{
		file << m_shoots.size() << "\n"; // write number of taken photos
		for(auto &it:m_shoots){
			std::cout << *it << std::endl;
			file << *it;
			file << "\n";
		}
		file.close();
	}
	else
		std::cerr << "Erreur à l'ouverture !" << std::endl;

	return 0;
}

Photograph* Simulation::getPhotograph(LocationUnit lat, LocationUnit lng) {
	auto lat_its = this->photographsByLat.equal_range(lat);

	for (auto it = lat_its.first; it != lat_its.second; it++) {
		if (it->second->getLongitude() == lng) {
			return it->second;
		}
	}

	throw std::range_error("Bad latitude or longitude");
}

