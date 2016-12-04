#pragma once

#include "Photograph.hpp"
#include "Satellite.hpp"

/**
*    Shoot class
**/
class Shoot {

protected:
	long int m_moment = 0;
	Photograph* m_photo;
	Satellite* m_sat;

	friend std::ostream& operator<<(std::ostream&, const Shoot&);

public:
	Shoot(long int, Photograph*, Satellite*);
	~Shoot();
	Shoot(const Shoot &shoot);

};
