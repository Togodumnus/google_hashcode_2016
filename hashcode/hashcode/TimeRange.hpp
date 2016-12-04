#pragma once

#include <array>
#include <string>
#include <ostream>

using TimeRangeLine = std::array<std::string, 2>;


class TimeRange{
	private:
		unsigned long int m_start_time;
		unsigned long int m_end_time;

		friend std::ostream& operator<<(std::ostream&, const TimeRange&);

	public:
		TimeRange(TimeRangeLine);
		TimeRange(unsigned long int, unsigned long int);
		~TimeRange();
		TimeRange& operator=(const TimeRange&);
		TimeRange(const TimeRange&);
};
