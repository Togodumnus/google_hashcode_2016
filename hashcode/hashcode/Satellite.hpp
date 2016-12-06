#pragma once

#include <ostream>
#include <array>
#include <string>

#include "Photograph.hpp"
#include "Location.hpp"

using SatelliteLine = std::array<std::string, 5>;

class Satellite : Location {

	private:
		unsigned short m_id = 0;

		// orientation of the camera
		long int m_cam_lat  = 0;
		long int m_cam_long = 0;

		int m_velocity, // arcs/turn [-500; 500]
			m_orientation_max_change,
			m_orientation_max_value;

		// earth goes -15" each turn
		const static int earth_velocity = -15;

        friend std::ostream& operator<<(std::ostream&, const Satellite&);

	public:
		Satellite(unsigned short, long int, long int, int, int, int);
        Satellite(unsigned short, SatelliteLine);

		~Satellite();
		Satellite(const Satellite&);
		Satellite& operator=(const Satellite&);

		inline int getId() const {
			return this->m_id;
		};

		inline int getOrientationMaxValue() {
			return this->m_orientation_max_value;
		};

		long int getLatitudeT(unsigned long int time);
		long int getLongitudeT(unsigned long int time);
		// void moveCamera(); // TODO not sure if belongs here
};
