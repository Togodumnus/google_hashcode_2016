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
	type t = type::simulation;

	simulation simulation;

	while (std::getline(input, line))
	{
		std::cout << "oui " << std::endl;
		std::istringstream iss(line); // buffer de string

		std::string result;
		if (std::getline(iss, result, '\n'))
		{
			switch (t) {
				case type::simulation:
					std::cout << result << std::endl;
					simulation.setDuration(std::stoi(result));
					t = type::test;
					std::cout << simulation.getDuration() << std::endl; // ok ça marche 
					break;
				case type::collection:
					std::cout << result << std::endl;
					cpt = std::stoi(result); // on sait qu'il y a 25 satellites
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