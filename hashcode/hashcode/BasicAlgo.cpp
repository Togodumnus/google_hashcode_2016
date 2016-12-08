#include "BasicAlgo.hpp"

#include <vector>
#include <set>
#include <iostream>
#include <algorithm>

#include "Collection.hpp"
#include "utils.hpp"

struct Shoot { // TODO move to own .hpp for result write
	Photograph* photograph;
	Satellite*  satellite;
	unsigned int t;

	Shoot();
	Shoot(
		Photograph* photograph,
		Satellite* satellite,
		unsigned int t
	) : photograph(photograph), satellite(satellite), t(t) {};
};

struct Moment {
	unsigned int t;
	Satellite* satellite;

	Moment();
	Moment(unsigned int t, Satellite* s): t(t), satellite(s) {};

	bool operator==(const Moment& m) const {
		return t == m.t && satellite == m.satellite;
	}

	bool operator<(const Moment& m) const {
		return t < m.t;
	}
};

class Shoots {

	std::vector<Shoot> _shoots;
	std::map<Photograph*, Shoot*> indexPhotograph;
	std::multimap<Moment, Shoot*> indexMoment;

	void _eraseShoot(Shoot* s) {
		auto range = indexMoment.equal_range(Moment(s->t, s->satellite));
		indexMoment.erase(range.first, range.second);

		indexPhotograph.erase(s->photograph);
	}

	public:
		Shoots() {};

		void addPhotograph(Shoot&& sh) {
			_shoots.push_back(sh);

			Shoot& shoot = _shoots.back();

			//if already a shoot for this photo, remove it
			erase(shoot.photograph);

			indexPhotograph[shoot.photograph] = &shoot;
			Moment m(shoot.t, shoot.satellite);
			indexMoment.insert(std::make_pair(m, &shoot));
		};

		std::map<Photograph*, Shoot*>& getPhotographIndex() {
			return indexPhotograph;
		}

		std::multimap<Moment, Shoot*>& getMomentIndex() {
			return indexMoment;
		}

		inline unsigned int countPhotograph(Photograph* p) const {
			return indexPhotograph.count(p);
		}

		// inline Shoot* getShootByPhotograph(Photograph* p) {
			// return indexPhotograph[p];
		// }

		void erase(Photograph* p) {
			auto search = indexPhotograph.find(p);
			if (search == indexPhotograph.end()) {
				return;
			}
			_eraseShoot(search->second);
		}

};

struct PhotosSelector {
	LocationUnit m_dim;
	int m_delta;
	Shoots& m_shoots;

	PhotosSelector(LocationUnit dim, int delta, Shoots& shoots) :
		m_dim(dim), m_delta(delta), m_shoots(shoots) {};

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
			&& !m_shoots.countPhotograph(item.second)
		);
	}
};

void BasicAlgo::solve(Simulation* s) { // TODO

	LogMachine log("basicAlgo");

	std::vector<Collection*>& collections = s->getCollections();
	std::vector<Satellite*>&  satellites  = s->getSatellites();

	Shoots shoots;

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
				latitude, d, shoots
			);
			PhotosSelector longitudeSelector = PhotosSelector(
				longitude, d, shoots
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

			// save these photos (or override their Shoot)
			for (auto p_it: windowsPhotos) {
				shoots.addPhotograph(Shoot(
					&(*p_it),
					*sat,
					t
				));
			}
		}
	}

	log("Photographs to take:");

	for (auto photo_it: shoots.getPhotographIndex()) { // TODO remove log
		Shoot* shoot = photo_it.second;
		std::cout << "time " << shoot->t
			<< "\tsat" << shoot->satellite->getId()
			<< "\t" << *(photo_it.first) << std::endl;
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

		// is a photo not in shoots ?
		bool missingPhoto = std::any_of(
			colPhotographs.begin(),
			colPhotographs.end(),
			[&shoots](Photograph* p) {
				return !shoots.countPhotograph(p); // true if photo not found
			}
		);

		if (missingPhoto) {
			log("Removing all photo of collection", col_it->getId());
			for (auto p_it: colPhotographs) {
				shoots.erase(p_it);
			}
		}
	}

	/**
	 * 4.
	 * Play simulation
	 */

	std::cout << std::endl;

	for (auto m_it : shoots.getMomentIndex()) {
		unsigned int t = m_it.first.t;
		Satellite* s = m_it.first.satellite;

		Photograph* p = m_it.second->photograph;

		log("maybe shoot photo at", t);
		log(p);

		if (s->positions.count(t)) {
			continue; // can't take another photo at turn t
		}

		// find last position and check if we can go from there to photograph p
		unsigned int t_0 = 0;
		std::pair<LocationUnit, LocationUnit> cameraPosition;
		cameraPosition.first  = 0;
		cameraPosition.second = 0;

		if (!s->positions.empty()) {

			// find last position
			auto it = s->positions.lower_bound(t);
			it--;

			t_0 = it->first;
			cameraPosition = it->second;
		}

		double w_lat  = std::abs(p->getLatitude() - cameraPosition.first)
							/ (t - t_0);
		double w_long = std::abs(p->getLongitude() - cameraPosition.second)
							/ (t - t_0);

		if (w_lat < s->getOrientationMaxChange()
				&& w_long < s->getOrientationMaxChange()) {
			std::cout << "sat " << s->getId() << " take photo " << p
				<< " at turn " << t << std::endl;

			s->positions[t].first  = p->getLatitude();
			s->positions[t].second = p->getLongitude();
			//TODO save Shoot somewhere
		} else {
			//TODO or remove Shoot from Shoots._shoot
			//log pb
			if (w_lat >= s->getOrientationMaxChange()) {
				std::cout <<
					"sat " << s->getId() << " turn " << t <<
					" w_lat " << w_lat << " >= " << s->getOrientationMaxChange()
					<< std::endl;
			}
			if (w_long >= s->getOrientationMaxChange()) {
				std::cout <<
					"sat " << s->getId() << " turn " << t <<
					" w_long " << w_long << " >= " << s->getOrientationMaxChange()
					<< std::endl;
			}
		}

	}

}
