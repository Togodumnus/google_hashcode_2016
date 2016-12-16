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
		os << "La collection " << (*it)->getId() << " a " << (*it)->getNumberOfPhotographs() << " photos à prendre \n";
	}

	return os;
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

