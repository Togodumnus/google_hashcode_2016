#pragma once

#include <string>
#include <vector>
class Result {

private:
	long m_number_of_pictures;
	struct execution_result{
		unsigned int m_score;
		long m_latitude;
		long m_longitude;
		unsigned short m_id_satellite;
		unsigned int m_moment;
	};
	std::vector<execution_result> m_results;

public:
	Result();
	~Result();

	// TODO
	unsigned int FigureOutScore(const char* input_file);

	// TODO verifier le parsing.
	void parse(std::string input_file)
};
