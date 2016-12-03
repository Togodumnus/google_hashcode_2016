#pragma once

#include <string>

#include "Satellite.hpp"
#include "Photograph.hpp"


class Satellite;

class ReadException : std::exception {
	std::string file;
	public:
		inline ReadException(std::string f) {
			file = f;
		}
		inline const char* what() const noexcept {
			std::string m = "Can't read file ";
			m += file;
			return m.c_str();
		};
};

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

		void parseInput(const char* input_file);

	public:
		Simulation(const char* input_file);
		~Simulation();
		Simulation& operator=(const Simulation&);
		Simulation(const Simulation&);

		inline unsigned int getDuration() {
			return this->m_duration;
		}

};
