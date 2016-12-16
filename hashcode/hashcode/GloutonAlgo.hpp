#pragma once

#include <map>
#include <set>
#include <mutex>
#include <future>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>

#include "Algorithm.hpp"
#include "Location.hpp"
#include "Simulation.hpp"
#include "Photograph.hpp"
#include "Simulation.hpp"
#include "Satellite.hpp"
#include "Shoot.hpp"

using namespace ::boost;
using namespace ::boost::multi_index;

struct PhotoId {};
struct PhotoLat {};
struct PhotoLng {};
struct CollectionIndex {};

using GeoPhotographIndex = multi_index_container<
	Photograph*,
	indexed_by<
		ordered_non_unique<
			tag<PhotoLat>,
			const_mem_fun<Photograph, LocationUnit, &Photograph::getLatitude>
		>,
		ordered_non_unique<
			tag<PhotoLng>,
			const_mem_fun<Photograph, LocationUnit, &Photograph::getLongitude>
		>
	>
>;

struct Offset {
	int o_lat;
	int o_lng;
	unsigned int t;

	Offset(): o_lat(0), o_lng(0), t(0) {};
	Offset(int lat, int lng, unsigned int t): o_lat(lat), o_lng(lng), t(t) {}
	Offset(const Offset& o): o_lat(o.o_lat), o_lng(o.o_lng), t(o.t) {}
};

struct WindowPhotographAllocator {
	bool operator()(const Photograph* p1, const Photograph* p2) const {
		return p1->getValue() > p2->getValue();
	}
};

class GloutonAlgo : public Algorithm {

	public:
		Simulation* simulation;
		GeoPhotographIndex photosIndex;

		std::map<Photograph*, Shoot> photosTaken;

		void buildPhotographIndex();

		void initCameraOffsets();

		bool canReach(Satellite*, Photograph*, unsigned int, Offset& camera);

		std::mutex mutexShoots;
		std::mutex mutexPhotosIndex;

		void insertShoot(
			Photograph*,
			Satellite*,
			unsigned int t
		);

		void updateCamera(
			Satellite*,
			Offset&&
		);

		bool isPhotoTaken(Photograph*);

		void solve(Simulation*);

};

class Worker {
	private:
		GloutonAlgo& algo;
		Satellite& satellite;

		Offset offset;

		void findWindowOfSatellite(
			unsigned long int,
			std::set<Photograph*, WindowPhotographAllocator>&
		);

	public:
		Worker(GloutonAlgo&, Satellite&, unsigned long int);
};
