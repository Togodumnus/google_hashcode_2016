#include "BasicAlgo.hpp"

#include <vector>
#include <iostream>

#include "Collection.hpp"
#include "utils.hpp"

void BasicAlgo::solve(Simulation* s) { // TODO

	LogMachine log("basicAlgo");

	std::vector<Collection*>& collections = s->getCollections();

	log("Start building photographs index");

	/**
	 * 1.
	 * Build latitude / longitude index on Photographs
	 */

	for(auto c = collections.begin(); c != collections.end(); c++) {
		std::vector<Photograph*>& photographs = (*c)->getPhotographs();

		for (auto p = photographs.begin(); p != photographs.end(); p++) {
			this->latitudeIndex[(*p)->getLatitude()] = *p;
			this->longitudeIndex[(*p)->getLongitude()] = *p;
		}
	}

	log("End building photographs index");

}
