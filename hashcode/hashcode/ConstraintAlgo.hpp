#pragma once

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>

#include "Algorithm.hpp"
#include "Location.hpp"
#include "Photograph.hpp"
#include "Simulation.hpp"
#include "Satellite.hpp"

using namespace ::boost;
using namespace ::boost::multi_index;

struct PhotoLat {};
struct PhotoLng {};

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

struct ColIndex {};
struct PhotoIndex {};
struct SatelliteIndex {};
struct TimeIndex {};

using ShootMutliIndex = multi_index_container<
	Shoot,
	indexed_by<
		// ordered_unique<identity<Shoot*>>,
		ordered_non_unique<
			tag<ColIndex>,
			member<Shoot, Collection*, &Shoot::m_collection>
		>,
		ordered_non_unique<
			tag<PhotoIndex>,
			member<Shoot, Photograph*, &Shoot::m_photograph>
		>,
		ordered_non_unique<
			tag<SatelliteIndex>,
			member<Shoot, Satellite*, &Shoot::m_satellite>
		>,
		ordered_non_unique<
			tag<TimeIndex>,
			member<Shoot, unsigned long int, &Shoot::m_t
		>>
	>
>;

class ConstraintAlgo: public Algorithm {

	Simulation* simulation;

	GeoPhotographIndex photosIndex;
	ShootMutliIndex    shoots;

	std::map<Photograph*, unsigned int> constraints;

	/**
	 * 1.
	 * Build latitude / longitude index on Photographs
	 */
	void buildPhotographIndex();

	/**
	 * 2.
	 * For each turn, for each satellite, select photo we can reach
	 */
	void generateShoots();

	/**
	 * 3.
	 * Remove collections we can not complete
	 * */
	void cleanCollections();

	/**
	 * 4.
	 * Init constraints
	 * */
	void initConstraints();

	public:
		void solve(Simulation*);

};
