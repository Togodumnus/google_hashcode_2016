#include <iostream>
#include <fstream>
#include <sstream>
#include <array>

#include "satellite.hpp"
#include "collection.hpp"
#include "simulation.hpp"
#include "parsing.hpp"

void parseInput(const char* input_file) {

	int cptSatellites; // compteur décroissant de satellites

	std::ifstream input(input_file); // on crée un buffer de stream
	std::string line; // ligne actuelle
	type t = type::numberOfTurns; // état de l'automate de lecture

	simulation simulation;

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

				case type::numberOfTurns:
					std::cout << " nombre de tours : " << result << std::endl;
					simulation.setDuration(std::stoi(result));
					t = type::satellitesNumber;
					break;

				case type::satellitesNumber:
					std::cout << " nombre de satellites : " << result << std::endl;
					cptSatellites = std::stoi(result);
					simulation.setSatellitesNumber(cptSatellites);
					t = type::satellites;
					break;

				case type::satellites:
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

					satellite* s = new satellite(&simulation, satelliteLine);
					// on ajoute le satellite a la simulation
					simulation.addSatellite(s);

					std::cout << *s << std::endl;
					cptSatellites--; // next

					if (cptSatellites == 0) { // une fois qu'on a ajouté tous les satellites
						t = type::test; // TODO use real state
					}
				}
					break;

				case type::collection:
					std::cout << result << std::endl;
					cpt = std::stoi(result);
					break;

				case type::photograph:
					break;

				case type::time_range:
					break;

				case type::test:
					std::cout << "lala" << std::endl;
					return;
					break;
				}
		}
	}
	input.close();
}
