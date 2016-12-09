#pragma once

#include <ostream>
#include <array>
#include <map>
#include <string>

#include "Photograph.hpp"
#include "Location.hpp"

using SatelliteLine = std::array<std::string, 5>;

class Satellite : public Location {

	private:
		// earth goes -15" each turn
		const static int earth_velocity = -15;

		unsigned short m_id = 0;

		// orientation of the camera
		LocationUnit m_cam_lat	= 0;
		LocationUnit m_cam_long = 0;

		int m_velocity, // arcs/turn [-500; 500]
			m_orientation_max_change,
			m_orientation_max_value;

		friend std::ostream& operator<<(std::ostream&, const Satellite&);

	public:
		std::map<unsigned int, std::pair<LocationUnit, LocationUnit>> positions;

		Satellite(unsigned short, LocationUnit, LocationUnit, int, int, int);
		Satellite(unsigned short, SatelliteLine);

		~Satellite();
		Satellite(const Satellite&);
		Satellite& operator=(const Satellite&);

		inline short getId() const {
			return this->m_id;
		};

		inline int getOrientationMaxValue() const {
			return this->m_orientation_max_value;
		};

		inline int getOrientationMaxChange() const {
			return this->m_orientation_max_value;
		};

		LocationUnit getLatitudeT(unsigned long int time);
		LocationUnit getLongitudeT(unsigned long int time);

		LocationUnit distanceT(unsigned long int, const Location&);
};
