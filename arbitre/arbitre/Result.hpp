#pragma once

#include <string>


class Result {

private:
	std::string input;
	std::string output;
	int time;
	unsigned int m_score;
	long m_latitude;
	long m_longitude;
	long m_number_of_pictures;
	unsigned short m_id_satellite;
	unsigned int m_moment;
public:
	Result();
	~Result();

	unsigned int FigureOutScore(const char* input_file);
};
