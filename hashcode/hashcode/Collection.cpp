#include "Collection.hpp"

#include <algorithm>

Collection::Collection(unsigned short id, CollectionLine line): m_id(id)
{
	m_value = std::stoi(line[0]);
	m_number_of_locations = std::stoi(line[1]);
	m_number_of_time_ranges = std::stoi(line[2]);
}

Collection::~Collection() { }

Collection::Collection(const Collection &collection)
{
	m_value = collection.m_value;
	m_photographs = collection.m_photographs; // copy
}

Collection& Collection::operator=(const Collection & collection)
{
	m_value = collection.m_value;
	m_photographs = collection.m_photographs; // copy
	return *this;
}

void Collection::add_photograph(Photograph* photograph){
	m_photographs.push_back(photograph);
};

void Collection::add_timeRange(TimeRange t){
	m_time_ranges.push_back(t);
};

bool Collection::isInTimeRanges(unsigned long int t) {
	return std::any_of(
		m_time_ranges.begin(),
		m_time_ranges.end(),
		[t](std::pair<unsigned long int, unsigned long int> range) {
			return t >= range.first && t <= range.second;
		}
	);
}

std::ostream& operator<<(std::ostream& o, const Collection& c) {
	return o << "Collection("
		<< "id[" << c.m_id << "] "
		<< "value[" << c.m_value << "] "
		<< "numberLocations [" << c.m_number_of_locations << "] "
		<< "numberTimeRanges[" << c.m_number_of_time_ranges << "]"
		<< ")";
}
