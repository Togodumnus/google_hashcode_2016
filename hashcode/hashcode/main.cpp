#include <iostream>
#include <fstream>
#include <exception>
#include <string>

#include "Simulation.hpp"
#include "Algorithm.hpp"
#include "BasicAlgo.hpp"

using namespace std;

// const char* INPUT = "data/forever_alone.in"; // VS
//const char* INPUT = "hashcode/hashcode/data/forever_alone.in";

int main(int argc, char* argv[]){


	const char* INPUT = argv[1];
	const char* OUTPUT = argv[2];


	std::cout << "Reading file " << INPUT << std::endl;

	try {
		std::unique_ptr<Algorithm> a(new BasicAlgo());
		Simulation s = Simulation(INPUT, a);
		std::cout << s << std::endl;

		s.solve();

		s.write_results(OUTPUT);


	} catch (ReadException& e) {
		std::cerr << "Error : " << e.what() << std::endl;
	}
	
	return 0;
}
