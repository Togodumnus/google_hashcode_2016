#include "photograph.hpp"

photograph::photograph(long int latitude, long int longitude):
	location(latitude, longitude) { }

photograph::~photograph() { }

photograph::photograph(const photograph& photograph)
{
	m_collections = photograph.m_collections; // copy
}

photograph& photograph::operator=(const photograph& photograph)
{
	m_collections = photograph.m_collections; //copy

	return *this;
}

bool photograph::addToCollection(collection* col){
	m_collections.push_back(col);
	return true;
}
