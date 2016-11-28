#include "..\include\photograph.hpp"

photograph::photograph(const location& location, const time_range& time_range): m_location(location), m_time_range(time_range){

}

bool photograph::belongs_to_collection(collection* col){
	m_collections.push_back(col);
	return true;
}
