#pragma once

/**
 *	Location class
 **/
class location {

	protected:
		long int m_latitude  = 0;
		long int m_longitude = 0;

	public:
		location();
		location(long int, long int);
		~location();
		location(const location& location);
		location& operator=(const location& location);

		long int getLatitude() const;
		long int getLongitude() const;
};
