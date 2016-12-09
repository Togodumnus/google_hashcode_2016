#include "BasicAlgo.hpp"

#include <vector>
#include <set>
#include <iostream>
#include <algorithm>

#include "Satellite.hpp"
#include "Photograph.hpp"
#include "Shoot.hpp"
#include "Collection.hpp"

const double LOG_INTERVAL = .01; // 1%

using SatelliteIndex = std::map<unsigned int, Photograph*>;

struct SetAllocator {
	// we use this for the order to be consistent accross runs
	bool operator()(const Photograph* p1, const Photograph* p2) const {
		return p1->getId() < p2->getId();
	}
};

void BasicAlgo::solve(Simulation* s) {

	std::vector<Collection*>& collections = s->getCollections();
	std::vector<Satellite*>&  satellites  = s->getSatellites();

	std::set<Photograph*, SetAllocator> photosToTake;

	// one index for each satellite
	std::map<Satellite*, SatelliteIndex> photosToTakeIndex;

	std::cout << "Start building photographs index" << std::endl;

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

	std::cout << "End building photographs index" << std::endl;

	/**
	 * 2.
	 * For each turn, for each satellite, select photo we can reach
	 */

	std::cout << "Start looking for photo we can shoot" << std::endl;

	// for each turn, for each satellite, find photographs it can reach
	for (unsigned int t = 0; t < s->getDuration(); t++) {

		// log progression
		if (t % int(s->getDuration() * LOG_INTERVAL) == 0) {
			std::cout << t * 100 / s->getDuration() << "%" << std::endl;
		}

		for (auto sat = satellites.begin(); sat != satellites.end(); sat++) {

			Satellite& satellite = *(*sat);

			int d = (*sat)->getOrientationMaxValue();
			LocationUnit lat       = (*sat)->getLatitudeT(t);
			LocationUnit longitude = (*sat)->getLongitudeT(t);

			std::pair<LocationUnit, LocationUnit>
				lat_bounds(lat - d + 1, lat + d);
			std::pair<LocationUnit, LocationUnit>
				long_bounds(longitude - d + 1, longitude + d);

			// FIXME on peut sortir du domaine de définition des latitude
			// et longitude

			// photographs we can reach in latitude
			std::set<Photograph*> latitudePhotos;
			auto lat_lower = latitudeIndex.lower_bound(lat_bounds.first);
			auto lat_upper = latitudeIndex.upper_bound(lat_bounds.second);
			std::transform(
				lat_lower,
				lat_upper,
				std::inserter(latitudePhotos, latitudePhotos.begin()),
				[](std::pair<LocationUnit, Photograph*> p) {
					return p.second;
				}
			);

			// photographs we can reach in longitude
			std::set<Photograph*> longitudePhotos;
			auto long_lower = longitudeIndex.lower_bound(long_bounds.first);
			auto long_upper = longitudeIndex.upper_bound(long_bounds.second);
			std::transform(
				long_lower,
				long_upper,
				std::inserter(longitudePhotos, longitudePhotos.begin()),
				[](std::pair<LocationUnit, Photograph*> p) {
					return p.second;
				}
			);

			// photographs we can reach in both latitude and longitude
			std::set<Photograph*> windowsPhotos;
			std::set_intersection(
				latitudePhotos.begin(), latitudePhotos.end(),
				longitudePhotos.begin(), longitudePhotos.end(),
				std::inserter(windowsPhotos, windowsPhotos.begin())
			);

			// save these photograh (or override their Shoot) if needed
			for (Photograph* p: windowsPhotos) {
				Shoot* old_shoot = p->getShoot();

				if (
					//never shoot this photograph
					old_shoot == nullptr
					// already shoot this one but this position is better
					|| old_shoot->distance() > satellite.distanceT(t, *(p))
				) {
					Shoot* new_shot = new Shoot(p, &satellite, t);
					p->setShoot(new_shot);
					photosToTake.insert(p);
				}
			}
		}
	}

	std::cout << "Photographs to take" << photosToTake.size() << std::endl;

	// construct time index by satellite
	for (auto photo_it: photosToTake) {
		Shoot* shoot = photo_it->getShoot();
		photosToTakeIndex[shoot->m_satellite].insert(
			std::make_pair(shoot->m_t, photo_it)
		);
	};

	// TODO on voit que deux photos peuvent être attribuées au même satellite
	// au même tour
	// faire un index sur le tour pour savoir si le satellite est occupé ?
	// TODO c'est toujours vrai ?

	std::cout << "End looking for photo we can shoot" << std::endl;

	/**
	 * 3.
	 * Infer collections we can't complete
	 */

	std::cout << "Remove collections we can't complete" << std::endl;

	for (auto col_it: s->getCollections()) {
		std::vector<Photograph*>& colPhotographs = col_it->getPhotographs();

		// is a photo not in shoots ?
		bool missingPhoto = std::any_of(
			colPhotographs.begin(),
			colPhotographs.end(),
			[&photosToTake](Photograph* p) {
				return !photosToTake.count(p); // true if photo not found
			}
		);

		if (missingPhoto) {
			std::cout << "Removing all photo of collection"
				<< col_it->getId() << std::endl;
			for (auto p_it: colPhotographs) {
				photosToTake.erase(p_it);
			}
		}
	}

	std::cout << "Photographs to take :" << photosToTake.size() << std::endl;

	/**
	 * 4.
	 * Play simulation
	 */

	std::cout << std::endl;

	// for each satellite, check photograph in chronological order
	for (std::pair<Satellite*, SatelliteIndex> it: photosToTakeIndex) {

		Satellite* sat = it.first;
		SatelliteIndex& satelliteIndex = it.second;

		std::pair<LocationUnit, LocationUnit> camera(0, 0);
		unsigned int t_0 = 0;

		for (std::pair<unsigned int, Photograph*> moment: satelliteIndex) {

			unsigned int t = moment.first;
			Photograph* p  = moment.second;

			double w_lat = std::abs(p->getLatitude() - camera.first)
								/ (t - t_0);
			double w_long = std::abs(p->getLongitude() - camera.second)
								/ (t - t_0);

			// we can reach this photograph at t with the camera position t_0
			if (w_lat < sat->getOrientationMaxChange()
					&& w_long < sat->getOrientationMaxChange()) {

				// std::cout << "sat" << sat->getId()
					// << " take photo " << *p
					// << "\t at turn " << t << std::endl;

				camera.first  = p->getLatitude();
				camera.second = p->getLongitude();

				t_0 = t;

				s->addShoot(p->getShoot());

				// int d = sat->getOrientationMaxValue();
				// LocationUnit las = sat->getLatitudeT(p->getShoot()->m_t);
				// LocationUnit lgs = sat->getLongitudeT(p->getShoot()->m_t);

				// //TODO remove
				// if (std::abs(las - p->getLatitude()) >= d
				//         || std::abs(lgs - p->getLongitude()) >= d) {
				//     std::cout << "error ----------------" << std::endl;
				// }

				// std::cout
				//     << "t"
				//     << p->getShoot()->m_t
				//     << " sat(" << sat->getLatitudeT(p->getShoot()->m_t)
				//     << "," << sat->getLongitudeT(p->getShoot()->m_t) << ") "
				//     << std::endl;

			} else { //log pb
				std::cout << "pb -----------" << std::endl;
				if (w_lat >= sat->getOrientationMaxChange()) {
					std::cout <<
						"sat " << sat->getId() << " turn " << t <<
						" w_lat " << w_lat << " >= " << sat->getOrientationMaxChange()
						<< std::endl;
				}
				if (w_long >= sat->getOrientationMaxChange()) {
					std::cout <<
						"sat " << sat->getId() << " turn " << t <<
						" w_long " << w_long << " >= " << sat->getOrientationMaxChange()
						<< std::endl;
				}
			}
		}
	}

	std::cout << "Photographs taken :" << s->countShoots() << std::endl;
}
