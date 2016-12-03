#pragma once

/**
 *	Location class
 **/
class Location {

	protected:
		long int m_latitude  = 0;
		long int m_longitude = 0;

	public:
		Location(long int, long int);
		~Location();
		Location(const Location&);
		Location& operator=(const Location&);

		long int getLatitude() const;
		long int getLongitude() const;
};
