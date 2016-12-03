#include "Collection.hpp"

Collection::Collection(unsigned short value) : m_value(value) { }

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
