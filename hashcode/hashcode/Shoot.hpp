#pragma once

#include "Photograph.hpp"
#include "Satellite.hpp"

/**
 *    Shoot class
 **/
class Shoot {

    protected:
        long int moment  = 0;
        Photograph * photo;
        Satellite * sat;



    public:
		Shoot(long int, Photograph, Satellite);
		~Shoot();
		Shoot(const Shoot &shoot);
		Shoot& operator=(const Shoot &shoot);
        
};
