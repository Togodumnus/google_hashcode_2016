#pragma once


class time_range{
	private:
		unsigned long int m_start_time;
		unsigned long int m_end_time;
	public:
		time_range(unsigned long int, unsigned long int);
		~time_range();
		time_range& operator=(const time_range& time_range);
		time_range(const time_range& time_range);
};
