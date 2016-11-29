#include "..\include\photograph.hpp"

photograph::photograph(const location* location, const time_range* time_range): m_location(location), m_time_range(time_range){

}

photograph::~photograph()
{
	while (!m_collections.empty()){
		delete m_collections.back();
		m_collections.pop_back;
	}
}

photograph::photograph(const photograph& photograph)
{
	m_location = photograph.m_location; 
	m_time_range = photograph.m_time_range;

	m_collections = photograph.m_collections;
}

photograph& photograph::operator=(const photograph& photograph)
{
	m_location = photograph.m_location; 
	m_time_range = photograph.m_time_range; 
	m_collections = photograph.m_collections;
	
	return *this;
}

bool photograph::belongs_to_collection(collection* col){
	m_collections.push_back(col);
	return true;
}
