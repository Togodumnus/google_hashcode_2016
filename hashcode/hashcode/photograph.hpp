#pragma once

#include "collection.hpp"
#include "location.hpp"
#include <vector>

class collection; // necessary because of mutual inclusion

/**
 * Photograph
 */
class photograph : location {
	private:
		/**
		 * collections the photograph belongs to
		 */
		std::vector<collection*> m_collections;

	public:
		photograph(long int latitude, long int longitude);
		~photograph();
		photograph& operator=(const photograph& photograph);
		photograph(const photograph& photograph);

		bool addToCollection(collection*);
};
