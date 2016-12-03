#include "Collection.hpp"

Collection::Collection(unsigned short value) : m_value(value) { }

Collection::Collection(CollectionLine line)
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
	photograph->addToCollection(this);
};


std::ostream& operator<<(std::ostream& o, const Collection& c) {
	return o << "Collection("
		<< "value[" << c.m_value << "] "
		<< "number of locations [" << c.m_number_of_locations << "] "
		<< "number of time ranges[" << c.m_number_of_time_ranges << "] "
		<< ")";
}
