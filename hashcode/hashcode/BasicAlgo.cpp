#include "BasicAlgo.hpp"

#include <vector>
#include <iostream>
#include <algorithm>

#include "Collection.hpp"
#include "utils.hpp"

struct Moment {
	Satellite* s;
	unsigned long int t;
	LocationUnit latitude;
	LocationUnit longitude;

	Member(Satellite* s,  unsigned long int t, LocationUnit latitude, LocationUnit longitude) :
		s(s), t(t), latitude(latitude), longitude(longitude) {}
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
			long int longitude = (*sat)->getLongitudeT(t);
			long int latitude  = (*sat)->getLatitudeT(t);
			int d = (*sat)->getOrientationMaxValue();

			auto latitude_it = std::find_if(latitudeIndex.begin(), latitudeIndex.end(), 
			   [&latitude, &d, &PhotoWeCanShoot](const std::pair<LocationUnit, Photograph*>& item) -> bool { 
			     	return item.first >= latitude - d && item.first <= latitude + d
			     		// TODO Optimiser suivant la distance (si un satellite peut la prendre avec une plus petite distance)
			      		&& !PhotoWeCanShoot.count(item.second);
			    	;
			   }
			);


			for (; latitude_it != latitudeIndex; latitude_it++) {
				// TODO for sur l'itérateur, on stocke toutes les phtoos dans la set, on fait la meme sur longitude. Puis une fonction intersect prend les deux
				PhotoWeCanShoot[(*latitude_it)] = Member((*sat), t, )
			}
		}
	}

	log("End looking for photo we can shoot");

}
