#include "Photograph.hpp"


Photograph::Photograph(long int latitude, long int longitude):
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
