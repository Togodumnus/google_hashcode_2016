#pragma once

#include "Location.hpp"
#include <string>
#include <vector>
#include <array>


class Collection; // necessary because of mutual inclusion
using PhotographLine = std::array<std::string, 2>;

/**
 * Photograph
 */
class Photograph : Location {
	private:
		/**
		 * collections the photograph belongs to
		 */
		std::vector<Collection*> m_collections;
		long int m_lat = 0;
		long int m_long = 0;

	public:
		Photograph(PhotographLine);
		Photograph(long int latitude, long int longitude);
		~Photograph();
		Photograph& operator=(const Photograph& photograph);
		Photograph(const Photograph& photograph);

		bool addToCollection(Collection*);
};
