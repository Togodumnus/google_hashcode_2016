#pragma once

#include <string>
#include <memory>
#include <exception>
#include <stdexcept>

#include "Collection.hpp"
#include "Satellite.hpp"
#include "Photograph.hpp"
#include "Algorithm.hpp"


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

		std::unique_ptr<Algorithm>& m_algo;

		void parseInput(const char* input_file, bool logging = false);

	public:
		Simulation(const char* input_file, std::unique_ptr<Algorithm>&);
		~Simulation();
		Simulation& operator=(const Simulation&);
		Simulation(const Simulation&);

		inline unsigned int getDuration() {
			return this->m_duration;
		}

		inline unsigned int getNumberSatellites() {
			return this->m_number_of_satellites;
		}

		inline unsigned int getNumberCollections() {
			return this->m_number_of_collections;
		}

		inline Satellite* getSatelliteN(const unsigned int n) {
			
			if(this->getNumberSatellites() <= n){
				throw std::out_of_range("N > nb satellites.");
			}
			else {
				return this->m_satellites[n];
			}		
		}

		void solve();
};
