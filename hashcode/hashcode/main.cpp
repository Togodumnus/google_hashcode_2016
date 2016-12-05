#include <iostream>
#include <exception>

#include "Satellite.hpp"
#include "Collection.hpp"
#include "Simulation.hpp"
#include "Algorithm.hpp"
#include "BasicAlgo.hpp"

using namespace std;
// const char* INPUT = "data/forever_alone.in"; // VS
const char* INPUT = "hashcode/hashcode/data/toy.in";

int main(){
	std::cout << "Reading file " << INPUT << std::endl;

	try {
		std::unique_ptr<Algorithm> a(new BasicAlgo());
		Simulation s = Simulation(INPUT, a);
		s.solve();
		Satellite sat = *s.getSatelliteN(0);
		std::cout << sat<< std::endl;
		for(int i=0;i<10;i++){
			cout <<"Latitude a t : " << i << " ; " << sat.getLatitudeT(i) << endl;
			cout << "Longitude a t : " << i << " ; " << sat.getLongitudeT(i) << endl;
		}
	} catch (ReadException& e) {
		std::cerr << "Error : " << e.what() << std::endl;
	}



	return 0;
}
