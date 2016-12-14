#pragma once

#include <string>

class Result {

private:

	struct execution_result{
		unsigned int m_score;
		long m_latitude;
		long m_longitude;
		long m_number_of_pictures;
		unsigned short m_id_satellite;
		unsigned int m_moment;
	}
	std::vector<execution_result> m_results;

	parse(std::string);
public:
	Result();
	~Result();

	unsigned int FigureOutScore(const char* input_file);
};
