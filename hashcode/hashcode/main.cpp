#include <iostream>
#include <fstream>
#include <exception>
#include <string>

#include "Simulation.hpp"
#include "Algorithm.hpp"
#include "GloutonAlgo.hpp"

using namespace std;

int main(int argc, char* argv[]){

	if (argc < 3) {
		cout << "usage: hashcode input_file output_file" << endl;
		return 0;
	}

	const char* INPUT = argv[1];
	const char* OUTPUT = argv[2];

	std::cout << "Reading file " << INPUT << std::endl;

	try {
		std::unique_ptr<Algorithm> a(new GloutonAlgo());
		Simulation s = Simulation(INPUT, a);
		std::cout << s << std::endl;

		s.solve();

		s.write_results(OUTPUT);

	} catch (ReadException& e) {
		std::cerr << "Error : " << e.what() << std::endl;
	}

	return 0;
}
