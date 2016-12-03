#include "TimeRange.hpp"

TimeRange::TimeRange(unsigned long int start_time, unsigned long int end_time) :
	m_start_time(start_time), m_end_time(end_time) { }

TimeRange::~TimeRange() { }

TimeRange& TimeRange::operator=(const TimeRange& timeRange)
{
	m_start_time = timeRange.m_start_time;
	m_end_time = timeRange.m_end_time;
	return *this;
}

TimeRange::TimeRange(const TimeRange& timeRange)
{
	m_start_time = timeRange.m_start_time;
	m_end_time = timeRange.m_end_time;
}
