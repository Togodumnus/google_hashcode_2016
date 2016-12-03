#pragma once

#include <string>

#include "satellite.hpp"
#include "photograph.hpp"

class satellite;

class simulation{

	private:
		unsigned long int m_duration;
		unsigned int	  m_number_of_satellites;
		unsigned int	  m_number_of_collections;

		// TODO missing info (class "shoot" instead ? or attributes on class
		// photograph ?)
		std::vector<photograph*> m_photographs_taken;

		std::vector<satellite*>  m_satellites;
		std::vector<collection*> m_collections;

	public:
		simulation();
		~simulation();
		simulation& operator=(const simulation& simulation);
		simulation(const simulation& simulation);

		inline void setDuration(unsigned int duration) {
			m_duration = duration;
		}

		inline void setSatellitesNumber(unsigned int satellitesNumber) {
			m_number_of_satellites = satellitesNumber;
		}

		inline unsigned int getDuration() {
			return this->m_duration;
		}

		inline void addSatellite(satellite* satellite) {
			m_satellites.push_back(satellite);
		}
};
