#pragma once

#include <string>
#include <exception>
#include <vector>
#include <memory>
#include <algorithm>

#include "Collection.hpp"
#include "Algorithm.hpp"
#include "Shoot.hpp"

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

	friend std::ostream& operator<<(std::ostream&, const Simulation&);

	private:
		unsigned long int m_duration;
		unsigned int	  m_number_of_satellites;
		unsigned int	  m_number_of_collections;

		std::vector<Satellite*>  m_satellites;
		std::vector<Collection*> m_collections;
		std::vector<Shoot*>      m_shoots;

		std::unique_ptr<Algorithm>& m_algo;

		void parseInput(const char* input_file);

	public:
		Simulation(const char* input_file, std::unique_ptr<Algorithm>&);
		~Simulation();
		Simulation& operator=(const Simulation&);
		Simulation(const Simulation&);

		inline unsigned int getDuration() const {
			return this->m_duration;
		}

		inline unsigned int getNumberSatellites() const {
			return this->m_number_of_satellites;
		}

		inline unsigned int getNumberCollections() const {
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

		inline std::vector<Collection*>& getCollections() {
			return this->m_collections;
		}

		inline std::vector<Satellite*>& getSatellites() {
			return this->m_satellites;
		}

		inline void addShoot(Shoot* s) {
			this->m_shoots.push_back(s);
		}

		inline int countShoots() const {
			return this->m_shoots.size();
		}

		void solve();

		int write_results(const char* OUTPUT);
};
