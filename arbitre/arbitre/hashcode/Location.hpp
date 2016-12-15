#pragma once

#include <cstdlib>

using LocationUnit = long;

/**
 *	Location class
 **/
class Location {

	protected:
		LocationUnit m_latitude  = 0;
		LocationUnit m_longitude = 0;

		inline static LocationUnit
			offsetLatitude(LocationUnit l1, LocationUnit l2) {
			return std::abs(l2 - l1);
		}

		inline static LocationUnit
			offsetLongitude(LocationUnit l1, LocationUnit l2) {
			LocationUnit dist = std::abs(l2 - l1);
			return dist < 648000 ? dist : 1296000 - dist;
		}

	public:
		Location(LocationUnit, LocationUnit);
		~Location();
		Location(const Location&);
		Location& operator=(const Location&);

		LocationUnit getLatitude() const;
		LocationUnit getLongitude() const;

		void setLatitude(LocationUnit);
		void setLongitude(LocationUnit);
};
