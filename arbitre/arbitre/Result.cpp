#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

#include "Result.hpp"
#include "utils.hpp"
#include "hashcode/Simulation.hpp"


unsigned int Result::FigureOutScore(std::string &input_file){
	std::cout << "[SCORE] Function starts" << std::endl;
	/*
	 * TODO
	 * 
	 * array < set < ResultShoot, 
	 *
	 *
	 *
	 *
	 *
	 *
	 */

	this->parse(input_file);
	std::cout << "\t[PARSING] done" << std::endl;
	// Test sort
	std::sort(m_results.begin(), m_results.end(), less_than_key());
	std::cout << "\t[SORTING] done" << std::endl;
	//std::cout << *this << std::endl;
	std::string a("./arbitre/arbitre/data/constellation.in");
	Simulation sim(a);
	
	//std::cout << sim.getNumberSatellites() << std::endl;
	std::vector<std::set<ResultShoot>> michael;
	michael.reserve(sim.getNumberSatellites());
	for(auto &it : m_results) {
		michael[it.m_id_satellite].insert(ResultShoot(it.m_latitude, it.m_longitude, it.m_moment));
	}


	
	return 0;
}

enum class ReadState {
	NumberOfPictures,
	TypicalLine,
};

void Result::parse(std::string &input_file){

	std::ifstream input(input_file); // on crée un buffer de stream
	if (input.fail() || input.bad()) {
		throw ReadException(input_file);
	}   
	std::string line; // ligne actuelle
	ReadState t = ReadState::NumberOfPictures;

	while (std::getline(input, line)){
		std::istringstream iss(line);

		std::string result;
		std::string result2;
		if (std::getline(iss, result, '\n')){
			// deuxième buffer pour parser a l'intérieur des lignes
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
		o 	<< it.m_latitude << " " << it.m_longitude << " "
			<< it.m_moment << " " << it.m_id_satellite << " ";
		o << "\n";
	}
	return o;
}