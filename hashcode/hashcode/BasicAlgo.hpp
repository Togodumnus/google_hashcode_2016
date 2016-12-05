#pragma once

#include <map>

#include "Algorithm.hpp"
#include "Location.hpp"
#include "Simulation.hpp"

class Photograph;

class BasicAlgo : public Algorithm
{

	private:
		std::map<LocationUnit, Photograph*> latitudeIndex;
		std::map<LocationUnit, Photograph*> longitudeIndex;

	public:
		void solve(Simulation*);
};
