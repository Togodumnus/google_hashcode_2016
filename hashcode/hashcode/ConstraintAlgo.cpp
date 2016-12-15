#include "ConstraintAlgo.hpp"

#include <vector>
#include <unordered_set>

typedef GeoPhotographIndex::index<PhotoLat>::type    Photos_by_lat;
typedef ShootMutliIndex::index<ColIndex>::type       Shoots_by_col;
typedef ShootMutliIndex::index<PhotoIndex>::type     Shoots_by_photo;

typedef ShootDoneMutliIndex::index<SatelliteTimeIndex>::type
	Shoots_by_satellite_time;

const double LOG_INTERVAL = .01; // 1%
const double MAX_FREQ = 2000; //TODO optimize

void ConstraintAlgo::buildPhotographIndex() {

	std::vector<Collection*>& collections = this->simulation->getCollections();

	for(auto c = collections.begin(); c != collections.end(); c++) {
		std::vector<Photograph*>& photographs = (*c)->getPhotographs();

		for (auto p = photographs.begin(); p != photographs.end(); p++) {
			this->photosIndex.insert(*p);
		}
	}
}

void ConstraintAlgo::generateShoots() { // TODO paralléliser ça

	Simulation* s = this->simulation;
	std::vector<Satellite*>& satellites = this->simulation->getSatellites();

	// for each turn, for each satellite, find photographs it can reach
	for (unsigned int t = 0; t < s->getDuration(); t++) {

		// log progression
		if (t % int(s->getDuration() * LOG_INTERVAL) == 0) {
			std::cout << t * 100 / s->getDuration() << "%" << std::endl;
		}

		for (auto sat = satellites.begin(); sat != satellites.end(); sat++) {

			Satellite* satellite = *sat;

			int d = satellite->getOrientationMaxValue();
			LocationUnit lat       = satellite->getLatitudeT(t);
			LocationUnit longitude = satellite->getLongitudeT(t);

			//TODO handle max latitude
			std::pair<LocationUnit, LocationUnit>
				lat_bounds(lat - d + 1, lat + d);
			//TODO handle border cases
			std::pair<LocationUnit, LocationUnit>
				long_bounds(longitude - d , longitude + d);

			Photos_by_lat& latitudeIndex = this->photosIndex.get<PhotoLat>();

			// photo we can reach in latitude
			Photos_by_lat::iterator
				lat_lower = latitudeIndex.lower_bound(lat_bounds.first),
				lat_upper = latitudeIndex.upper_bound(lat_bounds.second);

			for (auto it = lat_lower; it != lat_upper; it++) {
				Photograph* p = *it;
				if (long_bounds.first < p->getLongitude()
						&& long_bounds.second > p->getLongitude()) {
					for (Collection* col: p->getCollections()) {
						this->shoots.insert(Shoot(col, p, satellite, t));
					}
				}
			}
		}
	}
}

void ConstraintAlgo::cleanCollections() {

	std::vector<Collection*>& collections = this->simulation->getCollections();

	Shoots_by_col& shootsIndex = this->shoots.get<ColIndex>();

	for (Collection* col: collections) {

		std::pair<Shoots_by_col::iterator, Shoots_by_col::iterator> p =
			shootsIndex.equal_range(col);

		std::unordered_set<Photograph*> photos_in_col;
		for (auto it = p.first; it != p.second; it++) {
			photos_in_col.insert(it->m_photograph);
		}

		// missing photographs
		if (col->getNumberOfPhotographs() > photos_in_col.size()) {
			std::cout << "Remove " << *col << std::endl;
			shootsIndex.erase(p.first, p.second);
		}

	}

}

void ConstraintAlgo::initConstraints() {

	Shoots_by_photo& shootsIndex = this->shoots.get<PhotoIndex>();

	std::map<Photograph*, unsigned int> freq;

	for (const Shoot& s : shootsIndex) {
		freq[s.m_photograph]++;
	}

	for (const std::pair<Photograph*, unsigned int>& p : freq) {
		this->constraints.insert(Constraint(
			p.first->getValue() + MAX_FREQ - p.second, p.first
		));
	}

}

bool ConstraintAlgo::canGoFromShootToShoot(const Shoot& s1, const Shoot& s2) {

	std::pair<LocationUnit, LocationUnit> Loc1(
		s1.m_photograph->getLatitude(),
		s1.m_photograph->getLongitude()
	);

	std::pair<LocationUnit, LocationUnit> Loc2(
		s2.m_photograph->getLatitude(),
		s2.m_photograph->getLongitude()
	);

	double w_lat = std::abs(Loc1.first - Loc2.first)
		/ double(s2.m_t - s1.m_t);

	double w_long = std::abs(Loc1.second - Loc2.second)
		/ double(s2.m_t - s1.m_t);

	return w_lat < s2.m_satellite->getOrientationMaxVelocity()
			&& w_long < s2.m_satellite->getOrientationMaxVelocity();
}

bool ConstraintAlgo::isShootReachable(const Shoot& s) {

	Shoots_by_satellite_time& shootsIndex =
		this->shootsDone.get<SatelliteTimeIndex>();

	auto li = shootsIndex.lower_bound(boost::make_tuple(s.m_satellite, s.m_t-1));
	auto ui = shootsIndex.upper_bound(boost::make_tuple(s.m_satellite, s.m_t));

	// shoot of the same satellite, before s
	const Shoot& s_past = *li;

	// shoot of the same satellite, after s
	const Shoot& s_futur = *ui;

	return this->canGoFromShootToShoot(s_past, s)
		&& this->canGoFromShootToShoot(s_futur, s);
}


struct ShootAllocator {
	bool operator()(const Shoot* s1, const Shoot* s2) const {
		//TODO choose distance between last shoot instead ?
		return s1->distance() > s2->distance();
	}
};

void ConstraintAlgo::findShoot(
	Photograph* photo,
	std::function<void(const Shoot*)> success,
	std::function<void()>       error
) {
	Shoots_by_photo& shootsIndex = this->shoots.get<PhotoIndex>();
	Shoots_by_photo::iterator s_it = shootsIndex.find(photo);

	std::set<const Shoot*, ShootAllocator> photo_shoots;

	for (auto it = s_it; it != shootsIndex.end(); it++) {
		if (!this->isShootReachable(*it)) {
			continue;
		}
		const Shoot* s = &(*it);

		// if shoot has already been tried
		ShootNode& parent = *(this->branch.rbegin());
		if (parent.shootTested.find(s) != parent.shootTested.end()) {
			continue;
		}

		photo_shoots.insert(s);
	}

	if (photo_shoots.size()) {
		success(*photo_shoots.begin());
	} else {
		error();
	}

}

void ConstraintAlgo::removeNode() {
	ShootNode n =*(this->branch.rbegin());
	this->branch.pop_back();
	this->shootsDone.erase(*(n.shoot));
	//TODO baisser contrainte

	ShootNode& parent = *(this->branch.rbegin());
	parent.shootTested.insert(n.shoot);
}

void ConstraintAlgo::addNode(const Shoot* s) {
	this->branch.push_back(ShootNode(s));
	this->shootsDone.insert(*s);

	//TODO augmenter contrainte
}

void ConstraintAlgo::findGoodBranch() {

	do { // TODO change

		const Constraint& max = *(this->constraints.rbegin());
		Photograph* maxPhoto = max.m_photograph;

		this->findShoot(
			maxPhoto,
			[](const Shoot* s) {}, //TODO
			[]() {}
		);

	} while(this->branch.begin() == this->branch.end());

	throw NoSolutionException(); //TODO find better way to stop
}

void ConstraintAlgo::solve(Simulation* s) {

	this->simulation = s;

	std::cout << "hello world" << std::endl;

	std::cout << "Start building photographs index" << std::endl;
	this->buildPhotographIndex();
	std::cout << "End building photographs index" << std::endl;

	std::cout << "Start looking for photo we can shoot" << std::endl;
	this->generateShoots();
	std::cout << "End looking for photo we can shoot" << std::endl;

	std::cout << "Remove collections we can not complete" << std::endl;
	this->cleanCollections();
	std::cout << "End collections removal" << std::endl;

	std::cout << "Init constraints" << std::endl;
	this->initConstraints();
	std::cout << "End constraints init" << std::endl;

	ConstraintIndex::nth_index<0>::type& constraints =
		this->constraints.get<0>();
	for (auto it = constraints.rbegin(); it != constraints.rend(); it++) {
		std::cout << (*it).m_value << " " << *((*it).m_photograph) << std::endl;
	}

	std::cout << "end" << std::endl;

}
