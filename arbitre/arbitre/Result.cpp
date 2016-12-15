#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <map>
#include <set>

#include "Result.hpp"
#include "utils.hpp"
#include "hashcode/Simulation.hpp"


unsigned int Result::FigureOutScore(std::string &input_file){

	this->parse(input_file);

	// Only for the tests
	std::string a("./arbitre/arbitre/data/forever_alone.in");
	Simulation sim(a);
	
	std::map<int, std::set<ResultShoot>> map_res;

	for(auto &it : m_results) {
		map_res[it.m_id_satellite].insert(ResultShoot(it.m_latitude, it.m_longitude, it.m_moment));
	}

	/*
	 * TODO
	 * 		Check if at time t, id_satellite's got the photo in his windows
	 *		Check if the speed isn't too fast
	 */

	long lat, longi;
	unsigned int time;
	int orientationValue;
	int sum;
	// unsigned to remove warning
	for(unsigned int i=0; i<sim.getNumberSatellites(); i++) {
		int j=0;
		for(auto ind : map_res[i]){

			lat = sim.getSatelliteN(i)->getLatitudeT(ind.m_time);
			longi = sim.getSatelliteN(i)->getLongitudeT(ind.m_time);
			orientationValue = sim.getSatelliteN(i)->getOrientationMaxValue();

			if ( 	ind.getLatitude()  > ( lat + orientationValue   ||
					ind.getLatitude()  < ( lat - orientationValue   ||
					ind.getLongitude() > ( longi + orientationValue ||
					ind.getLongitude() < ( longi - orientationValue ))))){
				j++;
			}

		}
		std::cout << j << std::endl;
		sum+=j;

	}
	std::cout << "Number of pictures impossible : " << sum << "/" << this->m_number_of_pictures << std::endl;

	return 0;
}

enum class ReadState {
	NumberOfPictures,
	TypicalLine,
};

void Result::parse(std::string &input_file){

	std::ifstream input(input_file);
	if (input.fail() || input.bad()) {
		throw ReadException(input_file);
	}   
	std::string line;
	ReadState t = ReadState::NumberOfPictures;

	while (std::getline(input, line)){
		std::istringstream iss(line);

		std::string result;
		std::string result2;
		if (std::getline(iss, result, '\n')){
			std::istringstream iss2(result);
			switch(t) {
				case ReadState::NumberOfPictures:
					m_number_of_pictures=std::stoi(result);
					m_results.reserve(m_number_of_pictures);
					t = ReadState::TypicalLine;
					break;
				case ReadState::TypicalLine:
					int i=0;
					execution_result res;
					while (std::getline(iss2, result2, ' ')) {
						if (i==0)
							res.m_latitude = std::stoi(result2);
						else if (i==1)
							res.m_longitude = std::stoi(result2);
						else if (i==2)
							res.m_moment = std::stoi(result2);
						else if (i==3)
							res.m_id_satellite = std::stoi(result2);
						i++;
					}
					m_results.push_back(res);
					break;
			}
		}
	}
}

std::ostream& operator<<(std::ostream& o, const Result& s) {
	o 	<< "NB of pics : " << s.m_number_of_pictures << "\n";
	for(auto &it : s.m_results) {
		o 	<< it.m_latitude << " " << it.m_longitude    << " "
			<< it.m_moment 	 << " " << it.m_id_satellite << " ";
		o   << "\n";
	}
	return o;
}