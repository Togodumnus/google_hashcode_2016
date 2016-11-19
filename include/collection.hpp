#pragma once


class collection{

	private:
		unsigned short m_value;
		unsigned short m_number_of_locations;
		unsigned short m_number_of_time_ranges;

	public:

		collection(unsigned short, unsigned short, unsigned short);
		void add_photograph();

};
