#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "hashcode/Location.hpp"
#include "hashcode/Satellite.hpp"
#include "hashcode/Photograph.hpp"

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

friend std::ostream& operator<<(std::ostream&, const Result&);

private:
	std::string input;
	std::string output;
	unsigned int time;

	long m_number_of_pictures;
	unsigned int m_score;


	struct execution_result{
		long m_latitude;
		long m_longitude;
		unsigned short m_id_satellite;
		unsigned int m_moment;
	};

	struct less_than_key
	{
	    inline bool operator() (
	    	const execution_result& struct1, 
	    	const execution_result& struct2
	   	) {
	        return (struct1.m_id_satellite < struct2.m_id_satellite);
	    }
	};

	std::vector<execution_result> m_results;
public:
	Result() {};

	// TODO
	unsigned int FigureOutScore(std::string &input_file);

	// TODO verifier le parsing.
	void parse(std::string &);
};


