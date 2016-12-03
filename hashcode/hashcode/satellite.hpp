#pragma once

#include <ostream>
#include "photograph.hpp"
#include "simulation.hpp"

using SatelliteLine = std::array<std::string, 5>;

class simulation;

class satellite : location {

	private:
		simulation* m_simulation;

		// orientation of the camera
		long int m_cam_lat  = 0;
		long int m_cam_long = 0;

		int m_velocity, // arcs/turn [-500; 500]
			m_orientation_max_change,
			m_orientation_max_value;

        friend std::ostream& operator<<(std::ostream&, const satellite&);

	public:
		satellite(simulation*, long int, long int, int, int, int);
        satellite(simulation*, SatelliteLine);

		~satellite();
		satellite(const satellite& satellite);
		satellite& operator=(const satellite& satellite);

		// void getPosition(unsigned long int time); // TODO position au temps t
		// void moveCamera(); // TODO not sure if belongs here
};
