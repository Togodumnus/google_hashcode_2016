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
	Collection,
	CollectionsNumber,
	NumberOfTurns,
	Satellites,
	SatellitesNumber,
	Photograph,
	TimeRange,
};

void Simulation::parseInput(const char* input_file) {


	Simulation* simulation = this;

	int cptSatellites;	// compteur décroissant de satellites
	int cptCollections; // compteur décroissant de collections
	int cptPhotos;		// compteur décroissant de photos
	int cptTimeRanges;	// compteur décroissant des fenêtres de temps

	int cptPhotosAll = 0;

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
			// deuxième buffer pour parser a l'intérieur des lignes
			std::istringstream iss2(result);

			switch (t) {

				case ReadState::NumberOfTurns:
					simulation->m_duration = std::stoi(result);
					t = ReadState::SatellitesNumber;
					break;

				case ReadState::SatellitesNumber:
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
					Satellite* s = new Satellite(
						simulation->getNumberSatellites() - cptSatellites,
						satelliteLine
					);
					// on ajoute le satellite a la simulation
					this->m_satellites.push_back(s);

					cptSatellites--; // next

					if (cptSatellites == 0) {
						// une fois qu'on a ajouté tous les satellites
						t = ReadState::CollectionsNumber;
					}
				}
					break;

				case ReadState::CollectionsNumber:

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
						// on passe a l'arg suivant de la ligne
						cpt++;
					}
					cpt = 0;

					Collection* c = new Collection(
						simulation->getNumberCollections() - cptCollections,
						collectionLine
					);
					// on ajoute la collection a la simulation
					this->m_collections.push_back(c);

					// compteur du nb de photos dans la collection
					cptPhotos	  = c->getNumberOfPhotographs();
					cptTimeRanges = c->getNumberOfTimeRanges();;
					cptCollections--; // next

					// on passe aux photos de la collection
					t = ReadState::Photograph;

					break;
				}

				// FIXME : problème ici si on croise plusieurs fois la même
				// photo appartement à plusieurs collections, on créer plusieurs
				// objets
				case ReadState::Photograph:
				{
					PhotographLine PhotographLine;

					// lecture de la ligne à découper selon les espaces
					while (std::getline(iss2, result2, ' ')) {
						// on remplit un tableau intermediaire
						PhotographLine.at(cpt) = result2;
						cpt++; // on passe a l'arg suivant de la ligne
					}
					cpt = 0;

					Photograph* p = new Photograph(
						cptPhotosAll++,
						PhotographLine
					);

					unsigned short collectionIndex =
						this->m_number_of_collections - cptCollections - 1;

					// on ajoute la photo a la collection correspondante
					Collection* c = this->m_collections.at(collectionIndex);
					p->addToCollection(c);
					c->add_photograph(p);

					cptPhotos--;

					if (cptPhotos == 0) {
						// une fois qu'on a ajouté toutes les photos
						t = ReadState::TimeRange;
					}
				}
					break;

				case ReadState::TimeRange:
				{
					std::array<std::string, 2> timeRangeLine;

					// lecture de la ligne à découper selon les espaces
					while (std::getline(iss2, result2, ' ')) {
						// on remplit un tableau intermediaire
						timeRangeLine.at(cpt) = result2;
						cpt++;
					}
					cpt = 0;

					unsigned long int start_time = std::stoi(timeRangeLine[0]);
					unsigned long int end_time   = std::stoi(timeRangeLine[1]);

					TimeRange time = std::make_pair(start_time, end_time);

					unsigned short collectionIndex =
						this->m_number_of_collections - cptCollections - 1;

					// on ajoute la timerange a la collection correspondante
					this->m_collections.at(collectionIndex)
						->add_timeRange(time);

					cptTimeRanges--;

					if (cptTimeRanges == 0 && cptCollections == 0) {
						return;
					} else if (cptTimeRanges == 0) {
						// une fois qu'on a ajouté tous les Time Range,
						// prochaine collection
						t = ReadState::Collection;
					}
				}
					break;
			}
		}
	}

	input.close();
}
