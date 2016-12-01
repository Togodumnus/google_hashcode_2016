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
					// std::cout << result << std::endl;
					simulation.setDuration(std::stoi(result));
					t = type::satellitesNumber;
					//std::cout << simulation.getDuration() << std::endl; // ok ça marche
					break;
				case type::satellitesNumber:
					std::cout << result << std::endl;
					simulation.setSatellites(std::stoi(result));
					t = type::satellites;
					break;
				case type::satellites:
				{
					while (std::getline(iss2, result2, ' ')) {
						std::cout << result2 << std::endl;
						tab.at(cpt) = result2;
						cpt++;
					}
					satellite* s = new satellite(&simulation, std::stod(tab[0]), std::stod(tab[1]), std::stof(tab[2]), std::stof(tab[3]), std::stof(tab[4]));
					simulation.addSatellite(s);
					t = type::test;
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
