#include "Result.hpp"

unsigned int Result::FigureOutScore(const char* input_file){

	return 0;
}


void parse(std::string input_file){
	std::cout << "[parsing]\t" << "Start" << std::endl;
	std::ifstream input(input_file); // on crée un buffer de stream
	if (input.fail() || input.bad()) {
		throw ReadException(input_file);
	}   
	std::string line; // ligne actuelle
	while (std::getline(input, line)){
		int cpt = 0; // compteur d'élément dans une ligne
		if (std::getline(iss, result, '\n')){

		}
	}
}
