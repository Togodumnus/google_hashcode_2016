#include "..\include\location.hpp"

location::location(double latitude, double longitude) : m_latitude(latitude), m_longitude(longitude){

}

location::~location()
{
}

location::location(const location & location)
{
	m_latitude = location.m_latitude;
	m_longitude = location.m_longitude;
}

location & location::operator=(const location& location)
{
	m_latitude = location.m_latitude;
	m_longitude = location.m_longitude;
	
	return *this;
}


