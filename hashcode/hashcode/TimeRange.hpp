#pragma once

class TimeRange{
	private:
		unsigned long int m_start_time;
		unsigned long int m_end_time;
	public:
		TimeRange(unsigned long int, unsigned long int);
		~TimeRange();
		TimeRange& operator=(const TimeRange&);
		TimeRange(const TimeRange&);
};
