#include <iostream>
#include <exception>

#include "Satellite.hpp"
#include "Collection.hpp"

const char* INPUT = "data/forever_alone.in"; // VS
// const char* INPUT = "hashcode/hashcode/data/toy.in";

int main(){
	std::cout << "Reading file " << INPUT << std::endl;

	try {
		Simulation s = Simulation(INPUT);
		std::cout << " parsing terminé " << std::endl;
		int i = 0;
		std::cin >> i;
	} catch (ReadException& e) {
		std::cerr << "Error : " << e.what() << std::endl;
	}

	return 0;
}
