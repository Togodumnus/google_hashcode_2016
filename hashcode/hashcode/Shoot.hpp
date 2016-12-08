#pragma once

#include <iostream>
#include <fstream>

#include "Photograph.hpp"
#include "Satellite.hpp"
#include "utils.hpp"

/**
*    Shoot class
**/
class Shoot {

private:
	long int m_moment = 0;
	Photograph* m_photo;
	Satellite* m_sat;

public:
	Shoot(long int, Photograph*, Satellite*);
	~Shoot();
	Shoot(const Shoot &shoot);

	//Fonction probablement obsolète vu que Guillaume veut faire différemment
	inline void Write() {
		std::ofstream outfile;
		outfile.open("sortie.txt", std::ios_base::app);
  		outfile << m_photo->getLatitude() << " " << m_photo->getLongitude() << " "
				<< m_moment << " " << m_sat->getId(); 
	}

	friend std::ostream& operator<<(std::ostream&, const Shoot&);

	friend std::ofstream& operator<<(std::ofstream&, const Shoot&);


};
