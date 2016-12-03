#include "collection.hpp"

collection::collection(unsigned short value) : m_value(value) { }

collection::~collection() { }

collection::collection(const collection &collection)
{
	m_value = collection.m_value;
	m_photographs = collection.m_photographs; // copy
}

collection & collection::operator=(const collection & collection)
{
	m_value = collection.m_value;
	m_photographs = collection.m_photographs; // copy
	return *this;
}

void collection::add_photograph(photograph* photograph){
	m_photographs.push_back(photograph);
	photograph->addToCollection(this);
};
