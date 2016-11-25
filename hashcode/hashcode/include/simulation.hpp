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
		
	public:
		simulation(const char*);
		void took_photograph(satellite*, photograph*);
};
