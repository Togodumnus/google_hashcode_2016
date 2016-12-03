#include <iostream>
#include <fstream>
#include <sstream>
#include <array>

#include "Satellite.hpp"
#include "Collection.hpp"
#include "Simulation.hpp"

/**
 * Different states of the reading of input file
 */
enum class ReadState {
	Test,			// TODO remove
	Simulation,
	Collection,
	CollectionsNumber,
	NumberOfTurns,
	Satellites,
	SatellitesNumber,
	Photograph,
	TimeRange
};

void Simulation::parseInput(const char* input_file) {

	Simulation* simulation = this;

	int cptSatellites; // compteur décroissant de satellites
	int cptCollections; // compteur décroissant de collections

	std::ifstream input(input_file); // on crée un buffer de stream

	if (input.fail() || input.bad()) {
		throw ReadException(input_file);
	}

	std::string line; // ligne actuelle
	ReadState t = ReadState::NumberOfTurns; // état de l'automate de lecture

	while (std::getline(input, line))
	{
		int cpt = 0; // compteur d'élément dans une ligne
		std::istringstream iss(line); // buffer de string

		std::string result;
		std::string result2;

		if (std::getline(iss, result, '\n'))
		{

			std::istringstream iss2(result); // deuxième buffer pour parser a l'intérieur des lignes
			//std::cout << "in : " << result << std::endl;

			switch (t) {

				case ReadState::NumberOfTurns:
					std::cout << " nombre de tours : " << result << std::endl;
					simulation->m_duration = std::stoi(result);
					t = ReadState::SatellitesNumber;
					break;

				case ReadState::SatellitesNumber:
					std::cout << " nombre de satellites : " << result << std::endl;
					cptSatellites = std::stoi(result);
					simulation->m_number_of_satellites = cptSatellites;
					t = ReadState::Satellites;
					break;

				case ReadState::Satellites:
				{
					SatelliteLine satelliteLine;
					std::cout << cptSatellites << std::endl;

					// lecture de la ligne à découper selon les espaces
					while (std::getline(iss2, result2, ' ')) {
						// on remplit un tableau intermediaire
						satelliteLine.at(cpt) = result2;
						// on passe a l'arg suivant de la ligne
						cpt++;
					}

					Satellite* s = new Satellite(this, satelliteLine);
					// on ajoute le satellite a la simulation
					this->m_satellites.push_back(s);

					std::cout << *s << std::endl;
					cptSatellites--; // next

					if (cptSatellites == 0) { // une fois qu'on a ajouté tous les satellites
						t = ReadState::Test; // TODO use real state
					}
				}
					break;

				case ReadState::CollectionsNumber:
					std::cout << " Nombre de collections : " << result << std::endl;
					cptCollections = stoi(result);
					this->m_number_of_collections = cptCollections;
					t = ReadState::Collection;
					break;

				case ReadState::Collection:
				{
					CollectionLine collectionLine;
					std::cout << cptCollections << std::endl;

					// lecture de la ligne à découper selon les espaces
					while (std::getline(iss2, result2, ' ')) {
						// on remplit un tableau intermediaire
						collectionLine.at(cpt) = result2;
						// on passe a l'arg suivant de la ligne
						cpt++;
					}

					Collection* s = new Collection(collectionLine);
					// on ajoute le satellite a la simulation
					this->m_collections.push_back(s);

					std::cout << *s << std::endl;
					cptCollections--; // next

					if (cptCollections == 0) { // une fois qu'on a ajouté tous les satellites
						t = ReadState::Test; // TODO use real state
					}
					break;
				}
				case ReadState::Photograph:
					break;

				case ReadState::TimeRange:
					break;

				case ReadState::Test:
					std::cout << "lala" << std::endl;
					return;
					break;
				}
		}
	}

	input.close();
}
