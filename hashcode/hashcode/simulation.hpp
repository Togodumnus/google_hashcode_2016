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
		simulation(const char*);
		~simulation();
		simulation& operator=(const simulation& simulatin);
		simulation(const simulation& simulation);
		void took_photograph(satellite*, photograph*);
};
