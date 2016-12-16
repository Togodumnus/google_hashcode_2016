#include "GloutonAlgo.hpp"

#include <cmath>

typedef std::pair<LocationUnit, LocationUnit> SatellitePosition;
typedef GeoPhotographIndex::index<PhotoLat>::type PhotosByLat;

void GloutonAlgo::buildPhotographIndex() {

	std::vector<Collection*>& collections = this->simulation->getCollections();

	for(auto c = collections.begin(); c != collections.end(); c++) {

		std::vector<Photograph*>& photographs = (*c)->getPhotographs();

		for (auto p = photographs.begin(); p != photographs.end(); p++) {
			this->photosIndex.insert(*p);
		}
	}
}

bool GloutonAlgo::canReach(
	Satellite* sat,
	Photograph* p,
	unsigned int t,
	Offset& camera
) {

	std::pair<LocationUnit, LocationUnit> new_camera(
		p->getLatitude()  - sat->getLatitudeT(t),
		p->getLongitude() - sat->getLongitudeT(t)
	);

	double w_lat = std::abs(
		(new_camera.first - camera.o_lat)
		/ (double(t) - double(camera.t))
	);
	double w_long = std::abs(
		(new_camera.second - camera.o_lng)
		/ (double(t) - double(camera.t))
	);

	return w_lat < sat->getOrientationMaxVelocity()
		&& w_long < sat->getOrientationMaxVelocity();
}

void GloutonAlgo::insertShoot(
	Photograph* p,
	Satellite* satellite,
	unsigned int t
) {

	std::unique_lock<std::mutex> lock(mutexShoots);
	this->photosTaken.insert(std::make_pair(p, Shoot(p, satellite, t)));
}

bool GloutonAlgo::isPhotoTaken(Photograph* p) {
	std::unique_lock<std::mutex> lock(this->mutexShoots);
	return this->photosTaken.find(p) != this->photosTaken.end();
}

void Worker::findWindowOfSatellite(
		unsigned long int t,
		std::set<Photograph*, WindowPhotographAllocator>& photographs
	) {

	SatellitePosition position = std::make_pair(
		this->satellite.getLatitudeT(t),
		this->satellite.getLongitudeT(t)
	);

	int d = this->satellite.getOrientationMaxValue();

	//TODO handle max latitude
	std::pair<LocationUnit, LocationUnit>
		lat_bounds(position.first - d, position.first + d);

	//TODO handle border cases
	std::pair<LocationUnit, LocationUnit>
		long_bounds(position.second - d, position.second + d);

	std::unique_lock<std::mutex> lock(algo.mutexPhotosIndex);
	PhotosByLat& latitudeIndex = algo.photosIndex.get<PhotoLat>();

	// photo we can reach in latitude
	PhotosByLat::iterator
		lat_lower = latitudeIndex.lower_bound(lat_bounds.first),
		lat_upper = latitudeIndex.upper_bound(lat_bounds.second);

	if (lat_lower == lat_upper) {
		return;
	}

	for (auto it = lat_lower; it != lat_upper; it++) {
		Photograph* p = *it;

		// if can't be taken now
		if (!p->isInTimeRanges(t)) {
			continue;
		}

		// if not in window
		if (long_bounds.first >= p->getLongitude()
				|| long_bounds.second <= p->getLongitude()) {
			continue;
		}

		//if not reachable by camera
		if (!algo.canReach(&satellite, p, t, this->offset)) {
			continue;
		}

		//already taken
		if (algo.isPhotoTaken(p)) {
			continue;
		}

		photographs.insert(p);
	}
}

Worker::Worker(
		GloutonAlgo& g,
		Satellite& s,
		unsigned long int maxDuration
	): algo(g), satellite(s) {

	for (unsigned long int t = 0; t < maxDuration; t++) {

		// Photos we can take
		std::set<Photograph*, WindowPhotographAllocator> window;
		this->findWindowOfSatellite(
			t,
			window
		);

		auto it = window.begin();
		if (it == window.end()) { // no photograph in window
			continue;
		}

		//save photo
		Photograph* p = *it;
		algo.insertShoot(p, &satellite, t);

		//save camera pos
		std::pair<LocationUnit, LocationUnit> new_camera(
			p->getLatitude()  - this->satellite.getLatitudeT(t),
			p->getLongitude() - this->satellite.getLongitudeT(t)
		);
		this->offset = Offset(
			new_camera.first,
			new_camera.second,
			t
		);

	}

}

void GloutonAlgo::solve(Simulation* s) {

	this->simulation = s;

	std::cout << "Start building photographs index" << std::endl;
	this->buildPhotographIndex();
	std::cout << "End building photographs index" << std::endl;

	std::cout << "Find photo each satellite can take" << std::endl;

	GloutonAlgo& algo = *this;
	std::vector<std::future<void>> workers;

	unsigned long int maxDuration = this->simulation->getDuration();
	for (Satellite* sat : this->simulation->getSatellites()) {
		// this->findPhotosOfSatellite(sat);
		workers.push_back(std::async([maxDuration, &algo](Satellite* s) {
			Worker(algo, *s, maxDuration);
		}, sat));
	}

	for(auto &w : workers) {
		w.get();
	}

	std::cout << "End photos" << std::endl;

	for (auto& taken: this->photosTaken) {
		this->simulation->addShoot(&taken.second);
	}

}
