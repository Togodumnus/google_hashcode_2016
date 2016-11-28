#include "..\include\time_range.hpp"

time_range::time_range(unsigned int start_time, unsigned int end_time) : m_start_time(start_time), m_end_time(end_time){


}

time_range::~time_range()
{
}

time_range & time_range::operator=(const time_range & time_range)
{
	m_start_time = time_range.m_start_time;
	m_end_time = time_range.m_end_time;
	return *this;
}

time_range::time_range(const time_range & time_range)
{
	m_start_time = time_range.m_start_time;
	m_end_time = time_range.m_end_time;
}
