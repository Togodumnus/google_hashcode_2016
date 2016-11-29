#pragma once

#include "collection.hpp"
#include "location.hpp"
#include "time_range.hpp"
#include <vector>
// necessary because of mutual inclusion
class collection;

class photograph{

	private:
	std::vector<collection*> m_collections;
	const location* m_location;
	const time_range* m_time_range;
	public:
		photograph(const location*, const time_range*);
		~photograph();
		photograph& operator=(const photograph& photograph);
		photograph(const photograph& photograph);
		bool belongs_to_collection(collection*);

};
