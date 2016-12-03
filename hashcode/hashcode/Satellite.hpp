#pragma once

#include <ostream>
#include <array>
#include <string>
#include "Photograph.hpp"
#include "Simulation.hpp"
#include "Location.hpp"

using SatelliteLine = std::array<std::string, 5>;

class Simulation;

class Satellite : Location {

	private:
		Simulation* m_simulation;

		// orientation of the camera
		long int m_cam_lat  = 0;
		long int m_cam_long = 0;

		int m_velocity, // arcs/turn [-500; 500]
			m_orientation_max_change,
			m_orientation_max_value;

        friend std::ostream& operator<<(std::ostream&, const Satellite&);

	public:
		Satellite(Simulation*, long int, long int, int, int, int);
        Satellite(Simulation*, SatelliteLine);

		~Satellite();
		Satellite(const Satellite&);
		Satellite& operator=(const Satellite&);

		// void getPosition(unsigned long int time); // TODO position au temps t
		// void moveCamera(); // TODO not sure if belongs here
};
