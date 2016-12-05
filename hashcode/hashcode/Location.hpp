#pragma once

using LocationUnit = long int;

/**
 *	Location class
 **/
class Location {

	protected:
		LocationUnit m_latitude  = 0;
		LocationUnit m_longitude = 0;

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
