#pragma once

#include <string>

#include "Satellite.hpp"
#include "Photograph.hpp"

class Satellite;

class Simulation {

	private:
		unsigned long int m_duration;
		unsigned int	  m_number_of_satellites;
		unsigned int	  m_number_of_collections;

		// TODO missing info (class "shoot" instead ? or attributes on class
		// photograph ?)
		std::vector<Photograph*> m_photographs_taken;

		std::vector<Satellite*>  m_satellites;
		std::vector<Collection*> m_collections;

	public:
		Simulation();
		~Simulation();
		Simulation& operator=(const Simulation&);
		Simulation(const Simulation&);

		inline void setDuration(unsigned int duration) {
			m_duration = duration;
		}

		inline void setSatellitesNumber(unsigned int satellitesNumber) {
			m_number_of_satellites = satellitesNumber;
		}

		inline unsigned int getDuration() {
			return this->m_duration;
		}

		inline void addSatellite(Satellite* satellite) {
			m_satellites.push_back(satellite);
		}
};
