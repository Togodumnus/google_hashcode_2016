#pragma once

#include <set>
#include <list>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/composite_key.hpp>
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
struct SatelliteTimeIndex {};

using ShootMutliIndex = multi_index_container<
	Shoot,
	indexed_by<
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
		>
	>
>;

struct Constraint {

	unsigned int m_value;
	Photograph* m_photograph;

	Constraint(unsigned int v, Photograph* p): m_value(v), m_photograph(p) {}
	Constraint(const Constraint& c):
		m_value(c.m_value), m_photograph(c.m_photograph) {}
	Constraint(Constraint&& c):
		m_value(c.m_value), m_photograph(c.m_photograph) {}

	bool operator<(const Constraint& c) const {
		return m_value < c.m_value;
	};
};

using ConstraintIndex = multi_index_container<
	Constraint,
	indexed_by<
		ordered_non_unique<identity<Constraint>>,
		ordered_unique<
			tag<PhotoIndex>,
			member<Constraint, Photograph*, &Constraint::m_photograph>
		>
	>
>;

struct ShootNode {
	explicit ShootNode(const Shoot* s): shoot(s) {};
	const Shoot*           shoot;		// current shoot
	std::set<const Shoot*> shootTested;	// children already tested
};


using ShootDoneMutliIndex = multi_index_container<
	Shoot,
	indexed_by<
		ordered_non_unique<identity<Shoot>>,
		ordered_non_unique<
			tag<PhotoIndex>,
			member<Shoot, Photograph*, &Shoot::m_photograph>
		>,
		ordered_non_unique<
			tag<SatelliteTimeIndex>,
			composite_key<
				Shoot,
				member<Shoot, Satellite*, &Shoot::m_satellite>,
				member<Shoot, unsigned long, &Shoot::m_t>
			>
		>
	>
>;

class NoSolutionException: std::exception {
	public:
		NoSolutionException() {};
		const char* what() const noexcept {
			return "No solution";
		}
};

class ConstraintAlgo: public Algorithm {

	Simulation* simulation;

	GeoPhotographIndex photosIndex;
	ShootMutliIndex    shoots;

	ConstraintIndex constraints;

	ShootDoneMutliIndex shootsDone;

	std::list<ShootNode> branch;

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

	/**
	 * 5.
	 * Look for a good solution
	 */
	void findGoodBranch();

	void findShoot(Photograph* photo);

	bool isShootReachable(const Shoot& s);

	bool canGoFromShootToShoot(const Shoot&, const Shoot&);

	void removeNode();
	void addNode(const Shoot*);

	public:
		void solve(Simulation*);

};
