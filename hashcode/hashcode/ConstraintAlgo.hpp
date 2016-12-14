#pragma once

#include "Algorithm.hpp"
#include "Location.hpp"
#include "Photograph.hpp"
#include "Simulation.hpp"

class ConstraintAlgo: public Algorithm {

	Simulation* simulation;

	public:
		void solve(Simulation*);

};
