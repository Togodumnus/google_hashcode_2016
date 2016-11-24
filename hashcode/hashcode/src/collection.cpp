#include "collection.hpp"


collection::collection(unsigned short value, unsigned short number_of_locations, unsigned short number_of_time_ranges) : m_value(value), m_number_of_locations(number_of_locations), m_number_of_time_ranges(number_of_time_ranges), m_photographs(number_of_locations){
}

void collection::add_photograph(photograph* photograph){
	// optimized if array capacity is enough. Should be initialized correctly in the constructor
	// otherwise, will result in poor performances
	m_photographs.push_back(photograph);
	photograph->belongs_to_collection(*this);
};
