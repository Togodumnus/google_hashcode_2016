#include "satellite.hpp"
#include "collection.hpp"
#include "simulation.hpp"
#include "parsing.h"
#include <iostream>
#include <fstream>
#include <sstream>



void parse(const char* input_file) {

	int cpt = 0; // Compteur de ligne 
	std::ifstream input(input_file); // on créer un buffer de stream 
	std::string line; // ligne actuelle
	type t = type::numberOfTurns;

	simulation simulation;

	while (std::getline(input, line))
	{
		std::istringstream iss(line); // buffer de string
		std::string result;
		std::string result2;
		if (std::getline(iss, result, '\n'))
		{
			switch (t) {
				case type::numberOfTurns:
					std::cout << result << std::endl;
					simulation.setDuration(std::stoi(result));
					t = type::satellites;
					//std::cout << simulation.getDuration() << std::endl; // ok ça marche 
					break;
				case type::satellitesNumber:
					std::cout << result << std::endl;
					simulation.setSatellites(std::stoi(result));
					t = type::satellites; 
					break;
				case type::satellites:
					if (std::getline(iss, result2, ' ')){ // condition jamais validée, pq ? 
						std::cout << " oui " << std::endl;
						std::cout << result2 << std::endl;
					}
					t = type::test;
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