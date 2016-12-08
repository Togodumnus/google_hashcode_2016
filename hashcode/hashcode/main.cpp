#include <iostream>
#include <exception>

#include "Satellite.hpp"
#include "Collection.hpp"
#include "Simulation.hpp"
#include "Algorithm.hpp"
#include "BasicAlgo.hpp"

using namespace std;
// const char* INPUT = "data/forever_alone.in"; // VS
const char* INPUT = "hashcode/hashcode/data/forever_alone.in";

int main(){
	std::cout << "Reading file " << INPUT << std::endl;

	try {
		std::unique_ptr<Algorithm> a(new BasicAlgo());
		Simulation s = Simulation(INPUT, a);
		s.solve();
	} catch (ReadException& e) {
		std::cerr << "Error : " << e.what() << std::endl;
	}

	return 0;
}
