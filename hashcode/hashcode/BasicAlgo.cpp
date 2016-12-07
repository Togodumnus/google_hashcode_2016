#include "BasicAlgo.hpp"

#include <vector>
#include <set>
#include <iostream>
#include <algorithm>

#include "Collection.hpp"
#include "utils.hpp"

struct Moment { // TODO move to own .hpp for result write
	Satellite* s;
	unsigned int t;
	LocationUnit latitude;
	LocationUnit longitude;

	Moment(): s(nullptr), t(0), latitude(0), longitude(0) {};
	Moment(
		Satellite* s,
		unsigned int t,
		LocationUnit latitude,
		LocationUnit longitude
	) : s(s), t(t), latitude(latitude), longitude(longitude) {};
};

using PhotographToMoment = std::map<Photograph*, Moment>;

struct PhotosSelector {
	LocationUnit m_dim;
	int m_delta;
	PhotographToMoment& m_p;

	PhotosSelector(LocationUnit dim, int delta, PhotographToMoment& p) :
		m_dim(dim), m_delta(delta), m_p(p) {};

	/**
	 * select Photograph
	 */
	bool operator()(const std::pair<LocationUnit, Photograph*>& item) {
		return(
			// test if photo can be reach by camera
			item.first >= m_dim - m_delta
			&& item.first <= m_dim + m_delta

			// test if photo is not already taken
			// TODO Optimiser suivant la distance
			// (si un satellite peut la prendre avec une plus petite distance)
			&& !m_p.count(item.second)
		);
	}
};

void BasicAlgo::solve(Simulation* s) { // TODO

	LogMachine log("basicAlgo");

	std::vector<Collection*>& collections = s->getCollections();
	std::vector<Satellite*>&  satellites  = s->getSatellites();

	PhotographToMoment photoWeCanShoot;

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

	/**
	 * 2.
	 * For each turn, for each satellite, select photo we can reach
	 */

	log("Start looking for photo we can shoot");

	// for each turn, for each satellite, find photographs it can reach
	for (unsigned int t = 0; t < s->getDuration(); t++) {
		for (auto sat = satellites.begin(); sat != satellites.end(); sat++) {


			long int longitude = (*sat)->getLongitudeT(t);
			long int latitude  = (*sat)->getLatitudeT(t);
			int d = (*sat)->getOrientationMaxValue();

			PhotosSelector latitudeSelector = PhotosSelector(
				latitude, d, photoWeCanShoot
			);
			PhotosSelector longitudeSelector = PhotosSelector(
				longitude, d, photoWeCanShoot
			);

			// photos we can reach in latitude and satifies the selector
			std::set<Photograph*> latitudePhotos;
			auto latitude_it = std::find_if(
				latitudeIndex.begin(),
				latitudeIndex.end(),
				latitudeSelector
			);
			for (; latitude_it != latitudeIndex.end(); latitude_it++) {
				latitudePhotos.insert(latitude_it->second);
			}

			// photos we can reach in longitude and satifies the selector
			std::set<Photograph*> longitudePhotos;
			auto longitude_it = std::find_if(
				longitudeIndex.begin(),
				longitudeIndex.end(),
				longitudeSelector
			);
			for (; longitude_it != longitudeIndex.end(); longitude_it++) {
				longitudePhotos.insert(longitude_it->second);
			}

			// photos we can reach in both latitude and longitude
			std::vector<Photograph*> windowsPhotos;
			std::set_intersection(
				latitudePhotos.begin(), latitudePhotos.end(),
				longitudePhotos.begin(), longitudePhotos.end(),
				std::back_inserter(windowsPhotos)
			);

			// save these photos (or override their Moment)
			for (auto p_it: windowsPhotos) {
				photoWeCanShoot[&(*p_it)] = Moment(
					*sat,
					t,
					p_it->getLatitude(),
					p_it->getLongitude()
				);
			}
		}
	}

	log("Photographs to take:");

	for (auto photo_it: photoWeCanShoot) { // TODO remove log
		Moment& m = photo_it.second;
		std::cout << "time " << m.t
			<< " sat" << m.s->getId()
			<< " -- " << *(photo_it.first) << std::endl;
	};

	// TODO on voit que deux photos peuvent être attribuées au même satellite
	// au même tour
	// faire un index sur le tour pour savoir si le satellite est occupé ?

	log("End looking for photo we can shoot");

	/**
	 * 3.
	 * Infer collections we can't complete
	 */

	for (auto col_it: s->getCollections()) {
		std::vector<Photograph*>& colPhotographs = col_it->getPhotographs();

		// is a photo not in photoWeCanShoot ?
		bool missingPhoto = std::any_of(
			colPhotographs.begin(),
			colPhotographs.end(),
			[&photoWeCanShoot](Photograph* p) {
				return !photoWeCanShoot.count(p); // true if photo not found
			}
		);

		if (missingPhoto) {
			log("Removing all photo of collection", col_it->getId());
			for (auto p_it: colPhotographs) {
				photoWeCanShoot.erase(p_it);
			}
		}
	}
}
