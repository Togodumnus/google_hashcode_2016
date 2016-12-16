#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <set>

#include "hashcode/Location.hpp"
#include "hashcode/Satellite.hpp"
#include "hashcode/Photograph.hpp"
#include "hashcode/Simulation.hpp"

struct ResultShoot : public Location {
	unsigned int m_time;

	bool operator<(const ResultShoot& RS) const {
		return m_time < RS.m_time;
	}
	ResultShoot(const ResultShoot& rs) :
		Location(rs), m_time(rs.m_time){}
	ResultShoot(long latitude, long longitude, unsigned int t):
		Location(latitude, longitude), m_time(t){}
};

class Result {

private:
	std::string m_input;
	std::string m_output;
	unsigned int m_time;

	long m_number_of_pictures;
	unsigned int m_score;

	std::map<int, std::set<ResultShoot>> map_res;

	friend std::ostream& operator<<(std::ostream&, const Result&);

public:
	Result(std::string input, std::string output, unsigned int t):
		m_input(input), m_output(output), m_time(t) {};

	void parse(std::string &);
	void FigureOutScore();
};


