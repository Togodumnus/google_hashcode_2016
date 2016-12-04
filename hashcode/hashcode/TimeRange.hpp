#pragma once
#include <array>
#include <string>
	
using TimeRangeLine = std::array<std::string, 2>;


class TimeRange{
	private:
		unsigned long int m_start_time;
		unsigned long int m_end_time;
	public:
		TimeRange(TimeRangeLine);
		TimeRange(unsigned long int, unsigned long int);
		~TimeRange();
		TimeRange& operator=(const TimeRange&);
		TimeRange(const TimeRange&);
};
