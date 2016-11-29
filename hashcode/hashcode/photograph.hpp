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
		const location* getLocation(); //important de le mettre en const cf http://stackoverflow.com/questions/28855894/return-value-type-does-not-match-function-type-when-returning-pointer-to-constan
};
