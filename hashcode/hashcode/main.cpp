#include <iostream>
#include <exception>

#include "satellite.hpp"
#include "collection.hpp"
#include "parsing.hpp"

int main(){
	std::cout << "Hello World!" << std::endl;

	try {
		parseInput("data/constellation.in");
		// parseInput("hashcode/hashcode/data/forever_alone.in");
	} catch (ReadException& e) {
		std::cerr << "Error : " << e.what() << std::endl;
	}

	return 0;
}
