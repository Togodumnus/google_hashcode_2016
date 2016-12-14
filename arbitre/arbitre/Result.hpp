#pragma once

#include <string>

class Result {

private:
	unsigned int score;
public:
	Result();
	~Result();

	unsigned int FigureOutScore(const char* input_file);
};