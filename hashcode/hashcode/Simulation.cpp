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

	// TODO delete all Shoot
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
		os << "La collection " << (*it)->getId() << " a " << (*it)->getNumberOfPhotographs() << " photos Ã  prendre \n";
	}

	return os;
}

int Simulation::write_results() //TODO refacto
{

	std::sort(
		m_shoots.begin(),
		m_shoots.end(),
		[](const Shoot* s1, const Shoot* s2) {
			return *s1 < *s1;
		}
	);

	std::ofstream file("results.txt", std::ios::out | std::ios::trunc);
	if (file)
	{
		file << m_shoots.size() << "\n"; // write number of taken photos
		for(auto &it:m_shoots){
			std::cout << *it << std::endl;
			file << *it;
			file << "\n";
		}
		file.close(); // TODO pas toujours le même nombre de lignes pour deux
					  // lancer de suite (wc -l results.txt)
	}
	else
		std::cerr << "Erreur à l'ouverture !" << std::endl;

	return 0;
}
