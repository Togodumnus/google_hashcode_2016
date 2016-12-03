#include <iostream>
#include <exception>

#include "Satellite.hpp"
#include "Collection.hpp"

int main(){
	std::cout << "Hello World!" << std::endl;

	try {
		// Simulation s = Simulation("data/constellation.in");
		Simulation s = Simulation("hashcode/hashcode/data/forever_alone.in");
	} catch (ReadException& e) {
		std::cerr << "Error : " << e.what() << std::endl;
	}

	return 0;
}
