#include <iostream>
#include <fstream>
#include <sstream>
#include <array>

#include "Satellite.hpp"
#include "Collection.hpp"
#include "Simulation.hpp"
#include "TimeRange.hpp"

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
	int cptPhotos; // compteur décroissant de photos
	int cptTimeRanges; // compteur décroissant des fenêtres de temps

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
					// lecture de la ligne à découper selon les espaces
					while (std::getline(iss2, result2, ' ')) {
						// on remplit un tableau intermediaire
						satelliteLine.at(cpt) = result2;
						// on passe a l'arg suivant de la ligne
						cpt++;
					}
					cpt = 0;
					Satellite* s = new Satellite(this, satelliteLine);
					// on ajoute le satellite a la simulation
					this->m_satellites.push_back(s);

					//std::cout << *s << std::endl;
					cptSatellites--; // next

					if (cptSatellites == 0) { // une fois qu'on a ajouté tous les satellites
						t = ReadState::CollectionsNumber; // TODO use real state
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
					// lecture de la ligne à découper selon les espaces
					while (std::getline(iss2, result2, ' ')) {
						// on remplit un tableau intermediaire
						collectionLine.at(cpt) = result2;
						//std::cout << result2 << std::endl;
						// on passe a l'arg suivant de la ligne
						cpt++;
					}
					cpt = 0;
					Collection* s = new Collection(collectionLine);
					// on ajoute le satellite a la simulation
					this->m_collections.push_back(s);

					//std::cout << *s << std::endl;
					cptPhotos = std::stoi(collectionLine[1]); // compteur du nb de photos dans la collection
					cptTimeRanges = std::stoi(collectionLine[2]);
					cptCollections--; // next

					t = ReadState::Photograph; // on passe aux photos de la collection

					break;
				}
				case ReadState::Photograph:
				{
					PhotographLine PhotographLine;
					// lecture de la ligne à découper selon les espaces
					while (std::getline(iss2, result2, ' ')) {
						//std::cout << " Coordonnées photo = :  "<< result2 << std::endl;
						PhotographLine.at(cpt) = result2;// on remplit un tableau intermediaire
						cpt++; // on passe a l'arg suivant de la ligne
					}
					cpt = 0;
					Photograph* p = new Photograph(PhotographLine);

					int z = this->m_number_of_collections - cptCollections;
					//std::cout << " z = " << z << std::endl;
					//this->m_collections.at(z)->add_photograph(p); // on ajoute la photo a la collection correspondante(ne marche pas) TODO
						
					cptPhotos--;


					if (cptPhotos == 0) { // une fois qu'on a ajouté tous les satellites
						t = ReadState::TimeRange; // TODO use real state
					}
					break;
				}
					break;

				case ReadState::TimeRange:
				{
					TimeRangeLine timeRangeLine;
					// lecture de la ligne à découper selon les espaces
					while (std::getline(iss2, result2, ' ')) {
						//std::cout << " Time ranges = :  " << result2 << std::endl;
						timeRangeLine.at(cpt) = result2; // on remplit un tableau intermediaire
						cpt++;
					}
					cpt = 0;

					//TODO
					//this->m_collections.at() // on ajoute la timerange a la collection correspondante(ne marche pas) 

					cptTimeRanges--;

					if (cptTimeRanges == 0 && cptCollections == 0) {
						t = ReadState::Test;
					}
					if (cptTimeRanges == 0) { // une fois qu'on a ajouté tous les satellites
						t = ReadState::Collection; // TODO use real state
					}
					break;
				}
				case ReadState::Test:
					std::cout << "lala" << std::endl;
					return;
					break;
				}
		}
	}

	input.close();
}
