#pragma once

#include "photograph.hpp"
#include "simulation.hpp"
#include "location.hpp"

class simulation;

class satellite{

	private:
		simulation* m_simulation;	
		location m_location;
		float m_velocity, m_orientation_max_change, m_orientation_max_value;
	public:
		satellite(simulation*, double, double, float, float, float);
		~satellite();
		satellite(const satellite& satellite);
		satellite& operator=(const satellite& satelltite);
		bool canTake(photograph*);
		bool take(photograph*);
};
