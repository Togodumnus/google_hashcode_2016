#pragma once

#include <string>
#include <vector>
#include <array>
#include <ostream>

#include "Location.hpp"

using PhotographLine = std::array<std::string, 2>;

class Collection; // necessary because of mutual inclusion

/**
 * Photograph
 */
class Photograph : public Location {
	private:
		/**
		 * collections the photograph belongs to
		 */
		std::vector<Collection*> m_collections;

		friend std::ostream& operator<<(std::ostream&, const Photograph&);

	public:
		Photograph(PhotographLine);
		Photograph(long int latitude, long int longitude);
		~Photograph();
		Photograph& operator=(const Photograph& photograph);
		Photograph(const Photograph& photograph);

		bool addToCollection(Collection*);
};
