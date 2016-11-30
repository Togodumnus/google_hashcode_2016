#pragma once

#include <string>

#include "satellite.hpp"
#include "photograph.hpp"

class satellite;

class simulation{

	private:
		unsigned int m_duration;
		unsigned int m_number_of_satellites;
		unsigned int m_number_of_collections;
		std::vector<photograph*> m_photographs_taken;
		
	public:
		simulation();
		~simulation();
		simulation& operator=(const simulation& simulation);
		simulation(const simulation& simulation);
		void setDuration(unsigned int duration);
		void setSatellites(unsigned int satellitesNumber);
		unsigned int getDuration();
		void took_photograph(satellite*, photograph*);
};
