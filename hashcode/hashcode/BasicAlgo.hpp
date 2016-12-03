#pragma once

#include <array>
#include "Algorithm.hpp"
#include "Location.hpp"

using namespace std;

class BasicAlgo : public Algorithm
{
	public:
		BasicAlgo();

		vector<Location*> Solve(Simulation);

	private:
		vector<Location*>  list_locations;
}