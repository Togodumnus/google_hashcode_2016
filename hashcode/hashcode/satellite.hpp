#pragma once

#include "photograph.hpp"
#include "simulation.hpp"

class simulation;

class satellite{

	private:
		simulation* m_simulation;
		double m_latitude;
		double m_longitude;
		double m_cam_lat;
		double m_cam_long;
		float m_velocity, m_orientation_max_change, m_orientation_max_value;
	public:
		satellite();
		satellite(simulation*, double, double, float, float, float);
		~satellite();
		satellite(const satellite& satellite);
		satellite& operator=(const satellite& satellite);
		float getVelocity();
		bool canTake(photograph*);
		bool take(photograph*);
		void moveCamera();
};
