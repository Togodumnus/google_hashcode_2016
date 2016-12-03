#pragma once

#include "Collection.hpp"
#include "Location.hpp"
#include <vector>

class Collection; // necessary because of mutual inclusion

/**
 * Photograph
 */
class Photograph : Location {
	private:
		/**
		 * collections the photograph belongs to
		 */
		std::vector<Collection*> m_collections;

	public:
		Photograph(long int latitude, long int longitude);
		~Photograph();
		Photograph& operator=(const Photograph& photograph);
		Photograph(const Photograph& photograph);

		bool addToCollection(Collection*);
};
