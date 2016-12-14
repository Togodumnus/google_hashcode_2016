#include "ConstraintAlgo.hpp"

void ConstraintAlgo::buildPhotographIndex() {

	std::vector<Collection*>& collections = this->simulation->getCollections();

	for(auto c = collections.begin(); c != collections.end(); c++) {
		std::vector<Photograph*>& photographs = (*c)->getPhotographs();

		for (auto p = photographs.begin(); p != photographs.end(); p++) {
			this->photosIndex.insert(*p);
		}
	}
}


void ConstraintAlgo::solve(Simulation* s) {

	this->simulation = s;

	std::cout << "hello world" << std::endl;

	buildPhotographIndex();

	std::cout << "end" << std::endl;

}
