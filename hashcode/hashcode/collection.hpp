#pragma once

#include "photograph.hpp"
#include <vector>

// necessary because of mutual inclusion
class photograph;

class collection{

	private:
		unsigned short m_value;
		unsigned short m_number_of_locations;
		unsigned short m_number_of_time_ranges;

		std::vector<photograph*> m_photographs;

	public:

		collection(unsigned short, unsigned short, unsigned short);
		~collection();
		collection(const collection &collection);
		collection& operator=(const collection &collection);
		void add_photograph(photograph*);

};
