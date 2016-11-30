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
		std::istringstream iss(line); // buffer de string

		std::string result;
		if (std::getline(iss, result, '\n'))
		{
			std::string token;
			switch (t) {
			case type::simulation:
				while (std::getline(iss, token, '\n'))
				{
					std::cout << token << std::endl;
					simulation.setDuration(std::stoi(token));
					t = type::test;
				}
				break;
			case type::collection:
				while (std::getline(iss, token, '\n'))
				{
					std::cout << token << std::endl;
					cpt = std::stoi(token); // on sait qu'il y a 25 satellites
				}
				break;
			case type::photograph:
				break;
			case type::time_range:
				break;
			case type::test:
				int i = 0;
				std::cin >> i;
				break;
			}
		}
		input.close();
	}
}