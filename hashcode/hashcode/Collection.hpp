#pragma once

#include <vector>
#include "Photograph.hpp"
#include "TimeRange.hpp"

// necessary because of mutual inclusion
class Photograph;

class Collection{
	private:
		unsigned short m_value;

		// TODO : optimized with an array  by passing number of photograph to
		// constructor
		std::vector<Photograph*> m_photographs;

		/**
		 * time ranges during which the collection's photographs can be taken
		 */
		const std::vector<TimeRange*> m_time_ranges;

	public:
		Collection(unsigned short);
		~Collection();
		Collection(const Collection &collection);
		Collection& operator=(const Collection &collection);

		void add_photograph(Photograph*);
};
