#include "Photograph.hpp"

#include <algorithm>

Photograph::Photograph(int id, PhotographLine photographLine):
	Location(std::stol(photographLine[0]), std::stol(photographLine[1])),
	m_id(id) {}

Photograph::Photograph(const Photograph& p):
	Location(p.m_latitude, p.m_longitude),
	m_id(p.m_id) {
	m_collections = p.m_collections; // copy
}

Photograph::~Photograph() { }


Photograph& Photograph::operator=(const Photograph& photograph)
{
	m_collections = photograph.m_collections; //copy

	return *this;
}

bool Photograph::addToCollection(Collection* col){
	m_collections.push_back(col);
	return true;
}

bool Photograph::isInTimeRanges(unsigned long int t) {
	return std::any_of(
		m_collections.begin(),
		m_collections.end(),
		[t](Collection* collection) {
			return collection->isInTimeRanges(t);
		}
	);
}

std::ostream& operator<<(std::ostream& o, const Photograph& p) {
	return o << "Photograph("
		<< "id=" << p.m_id << " "
		<< "lat=" << p.m_latitude << " "
		<< "long=" << p.m_longitude << ""
		<< ")";
}

LocationUnit Photograph::getLatitude() const {
	return this->m_latitude;
}

LocationUnit Photograph::getLongitude() const {
	return this->m_longitude;
}
