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
		std::vector<satellite*> m_satellites;

	public:
		simulation();
		~simulation();
		simulation& operator=(const simulation& simulation);
		simulation(const simulation& simulation);
		void setDuration(unsigned int duration);
		void setSatellites(unsigned int satellitesNumber);
		std::vector<satellite*> getSatellites();
		unsigned int getDuration();
		void took_photograph(satellite*, photograph*);
		void addSatellite(satellite *);
};
