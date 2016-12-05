#include "BasicAlgo.hpp"

#include <vector>
#include <iostream>

#include "Collection.hpp"
#include "utils.hpp"

struct Moment {
	Satellite* s;
	unsigned long int t;
	long int latitude;
	long int longitude;
};

void BasicAlgo::solve(Simulation* s) { // TODO

	LogMachine log("basicAlgo");

	std::vector<Collection*>& collections = s->getCollections();
	std::vector<Satellite*>&  satellites  = s->getSatellites();

	std::map<Photograph*, Moment> PhotoWeCanShoot;

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

	log("Start looking for photo we can shoot");

	for (unsigned int t = 0; t < s->getDuration(); t++) {
		for (auto sat = satellites.begin(); sat != satellites.end(); sat++) {
			long int longitude = sat.getLongitudeT(t);
			long int latitude  = sat.getLatitudeT(t);
			int d = sat.getOrientationMaxValue();

			// TODO utiliser map::find_if
		}
	}

	log("End looking for photo we can shoot");

}
