#include "Photograph.hpp"

Photograph::Photograph(PhotographLine photographLine):
	Location(std::stol(photographLine[0]), std::stol(photographLine[1])) { }

Photograph::Photograph(LocationUnit latitude, LocationUnit longitude):
	Location(latitude, longitude) { }

Photograph::~Photograph() { }

Photograph::Photograph(const Photograph& photograph)
	: Location(photograph.m_latitude, photograph.m_longitude)
{
	m_collections = photograph.m_collections; // copy
}

Photograph& Photograph::operator=(const Photograph& photograph)
{
	m_collections = photograph.m_collections; //copy

	return *this;
}

bool Photograph::addToCollection(Collection* col){
	m_collections.push_back(col);
	return true;
}

std::ostream& operator<<(std::ostream& o, const Photograph& p) {
	return o << "Photograph("
		<< &p << " "
		<< "lat[" << p.m_latitude << "] "
		<< "long[" << p.m_longitude << "]"
		<< ")";
}
