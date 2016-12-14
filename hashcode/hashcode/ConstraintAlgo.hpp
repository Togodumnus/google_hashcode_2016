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

using namespace ::boost;
using namespace ::boost::multi_index;

using GeoPhotographIndex = multi_index_container<
	Photograph*,
	indexed_by<
		ordered_non_unique<
			const_mem_fun<Photograph, LocationUnit, &Photograph::getLatitude>
		>,
		ordered_non_unique<
			const_mem_fun<Photograph, LocationUnit, &Photograph::getLongitude>
		>
	>
>;

class ConstraintAlgo: public Algorithm {

	Simulation* simulation;

	GeoPhotographIndex photosIndex;

	/**
	 * 1.
	 * Build latitude / longitude index on Photographs
	 */
	void buildPhotographIndex();

	public:
		void solve(Simulation*);

};
