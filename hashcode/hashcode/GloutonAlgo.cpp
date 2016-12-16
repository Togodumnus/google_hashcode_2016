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

void GloutonAlgo::initCameraOffsets() {
	for (Satellite* s: this->simulation->getSatellites()) {
		cameraOffsets.insert(std::make_pair(s, Offset(0, 0, 0)));
	}
}

bool GloutonAlgo::canReach(Satellite* sat, Photograph* p, unsigned int t) {

	std::pair<Satellite*, Offset> sat_cam_pos = *(this->cameraOffsets.find(sat));
	Offset& camera = sat_cam_pos.second;

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

void GloutonAlgo::findWindowOfSatellite(
		Satellite* satellite,
		unsigned long int t,
		std::set<Photograph*, WindowPhotographAllocator>& photographs
	) {

	SatellitePosition position = std::make_pair(
		satellite->getLatitudeT(t),
		satellite->getLongitudeT(t)
	);

	int d = satellite->getOrientationMaxValue();

	//TODO handle max latitude
	std::pair<LocationUnit, LocationUnit>
		lat_bounds(position.first - d, position.first + d);

	//TODO handle border cases
	std::pair<LocationUnit, LocationUnit>
		long_bounds(position.second - d, position.second + d);

	PhotosByLat& latitudeIndex = this->photosIndex.get<PhotoLat>();

	// photo we can reach in latitude
	PhotosByLat::iterator
		lat_lower = latitudeIndex.lower_bound(lat_bounds.first),
		lat_upper = latitudeIndex.upper_bound(lat_bounds.second);

	if (lat_lower == lat_upper) {
		return;
	}

	for (auto it = lat_lower; it != lat_upper; it++) {
		Photograph* p = *it;

		// if not in window
		if (long_bounds.first >= p->getLongitude()
				|| long_bounds.second <= p->getLongitude()) {
			continue;
		}

		//if not reachable by camera
		if (!this->canReach(satellite, p, t)) {
			continue;
		}

		//already taken
		if (this->photosTaken.find(p) != this->photosTaken.end()) {
			continue;
		}

		photographs.insert(p);
	}
}

void GloutonAlgo::findPhotosOfSatellite(Satellite* satellite) {

	for (unsigned long int t = 0; t < this->simulation->getDuration(); t++) {

		// Photos we can take
		std::set<Photograph*, WindowPhotographAllocator> window;
		this->findWindowOfSatellite(
			satellite,
			t,
			window
		);

		auto it = window.begin();
		if (it == window.end()) { // no photograph in window
			continue;
		}

		//save photo
		Photograph* p = *it;
		this->photosTaken.insert(std::make_pair(p, Shoot(p, satellite, t)));

		//save camera pos
		std::pair<LocationUnit, LocationUnit> new_camera(
			p->getLatitude()  - satellite->getLatitudeT(t),
			p->getLongitude() - satellite->getLongitudeT(t)
		);
		this->cameraOffsets[satellite] = Offset(
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

	std::cout << "Init cameras offsets" << std::endl;
	this->initCameraOffsets();
	std::cout << "End" << std::endl;

	std::cout << "Find photo each satellite can take" << std::endl;

	for (Satellite* sat : this->simulation->getSatellites()) {
		this->findPhotosOfSatellite(sat);
	}

	std::cout << "End photos" << std::endl;

	for (auto& taken: this->photosTaken) {
		this->simulation->addShoot(&taken.second);
	}

}
