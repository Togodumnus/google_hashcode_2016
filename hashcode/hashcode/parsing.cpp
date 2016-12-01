#include "satellite.hpp"
#include "collection.hpp"
#include "simulation.hpp"
#include "parsing.h"
#include <array>

#include <iostream>
#include <fstream>
#include <sstream>

void parse(const char* input_file) {

	int cpt = 0; // Compteur de ligne
	int cptSatellites = 0; // compteur de satellites 

	std::ifstream input(input_file); // on créer un buffer de stream
	std::string line; // ligne actuelle
	type t = type::numberOfTurns;

	std::array<std::string, 5> tab;

	simulation simulation;

	while (std::getline(input, line))
	{
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
					//std::cout << simulation.getDuration() << std::endl; // ok ça marche
					break;
				case type::satellitesNumber:
					std::cout << " nombre de satellites : " << result << std::endl;
					simulation.setSatellites(std::stoi(result));
					cptSatellites = stoi(result);
					t = type::satellites;
					break;
				case type::satellites:
				{
					std::cout << cptSatellites << std::endl;
					if (cptSatellites != 0) {
						while (std::getline(iss2, result2, ' ')) {
							//std::cout << "infos satellites : \n " << result2 << std::endl;
							tab.at(cpt) = result2; // on remplit un tableau intermediaire	
							cpt++; // on passe a l'arg suivant de la ligne
						}
						cpt = 0; // on a fini de prendre les infos de ce satellites
						cptSatellites--;
						std::cout << " lat = " << tab[0] << " long = "   << tab[1] << "velocity = "  << tab[2] << " moc = " <<  tab[3] << " mov = " << tab [4] << std::endl;
						satellite* s = new satellite(&simulation, std::stod(tab[0]), std::stod(tab[1]), std::stof(tab[2]), std::stof(tab[3]), std::stof(tab[4])); // on créer un nouveau satellite
						simulation.addSatellite(s); // on ajoute le satellite a la simu
						simulation.getSatellites // TODO  error use '&' to create a pointer to member
						//std::cout << " velocité du satellite 1 = " << simulation.getSatellites.at(1).getVelocity() << std::endl;

					}
					else { // une fois qu'on a ajouté tous les satellites
						t = type::test;
					}
					break;
				}
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
