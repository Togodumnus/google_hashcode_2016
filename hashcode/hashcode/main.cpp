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


	string INPUT_string = "hashcode/hashcode/data/"; // on transforme en string pour pouvoir utiliser le +
	INPUT_string += argv[1];

	string OUTPUT_string = "hashcode/hashcode/data/";
	OUTPUT_string += argv[2];

	const char *INPUT = INPUT_string.c_str(); // on remet en char* pour l'utiliser dans les fonctions
	const char *OUTPUT = OUTPUT_string.c_str();


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
