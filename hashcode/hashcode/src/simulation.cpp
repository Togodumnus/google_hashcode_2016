#include "..\include\simulation.hpp"
#include <fstream>

simulation::simulation(const char* input_file){
	std::ifstream input;
	input.open(input_file);

	input.close();
}

void simulation::took_photograph(satellite* satellite, photograph* photograph){
	
}
