#include "Shoot.hpp"

Shoot::Shoot(long int moment, Photograph * photo, Satellite * sat) :
	m_moment(moment), m_photo(photo), m_sat(sat) { }


Shoot::~Shoot()
{
}

Shoot::Shoot(const Shoot & shoot)
{
	m_moment = shoot.m_moment;
	m_photo = shoot.m_photo;
	m_sat = shoot.m_sat;
}

std::ostream & operator<<(std::ostream & o, const Shoot & s)
{
	return o << "Shoot("
		<< "moment[" << s.m_moment << "] "
		<< "photo[" << s.m_photo << "] "
		<< "sat[" << s.m_sat << "] "
		<< ")";
}
