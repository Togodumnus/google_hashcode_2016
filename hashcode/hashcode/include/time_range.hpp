#pragma once


class time_range{

	private:
		unsigned int m_start_time;
		unsigned int m_end_time;
	public:
		time_range(unsigned int, unsigned int);
		~time_range();
		time_range& operator=(const time_range& time_range);
		time_range(const time_range& time_range);
};
