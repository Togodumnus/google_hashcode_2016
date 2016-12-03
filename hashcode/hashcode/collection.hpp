#pragma once

#include <vector>
#include "photograph.hpp"
#include "time_range.hpp"

// necessary because of mutual inclusion
class photograph;

class collection{
	private:
		unsigned short m_value;

		// TODO : optimized with an array  by passing number of photograph to
		// constructor
		std::vector<photograph*> m_photographs;

		/**
		 * time ranges during which the collection's photographs can be taken
		 */
		const std::vector<time_range*> m_time_ranges;

	public:
		collection(unsigned short);
		~collection();
		collection(const collection &collection);
		collection& operator=(const collection &collection);

		void add_photograph(photograph*);
};
