#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <cmath>

#include "Result.hpp"
#include "utils.hpp"
#include "hashcode/Simulation.hpp"

/**
 * @return score
 */
unsigned int Result::FigureOutScore(std::string &input_file){

	std::cout << "AVANT PARSE" << std::endl;
	this->parse(input_file);
	std::cout << "APRES PARSE" << std::endl;

	// Only for the tests
	std::string a("./arbitre/arbitre/data/constellation.in");
	Simulation sim(a);

	// stocke les Shoot par satellite
	std::map<int, std::set<ResultShoot>> map_res;

	for(auto &it : m_results) {
		map_res[it.m_id_satellite]
			.insert(ResultShoot(it.m_latitude, it.m_longitude, it.m_moment));
	}

	unsigned int timeB4 = 0; // t-1
	long lat, longi, latCam, longiCam,
		 latCamB4 = 0, longiCamB4 = 0; // camera t-1
	int orientationValue, orientationSpeed, camSpeed=0;

	// for each satellite
	for (unsigned int i=0; i < sim.getNumberSatellites(); i++) {

		orientationSpeed = sim.getSatelliteN(i)->getOrientationMaxVelocity();
		orientationValue = sim.getSatelliteN(i)->getOrientationMaxValue();

		// for each ResultShoot
		for(auto ind : map_res[i]){

			lat = sim.getSatelliteN(i)->getLatitudeT(ind.m_time);
			longi = sim.getSatelliteN(i)->getLongitudeT(ind.m_time);

			// CHECK on the satellite's shot window
			if ( 	ind.getLatitude()  > ( lat + orientationValue   )||
					ind.getLatitude()  < ( lat - orientationValue   )||
					ind.getLongitude() > ( longi + orientationValue )||
					ind.getLongitude() < ( longi - orientationValue )){
				return 0;
			}

			// Get lat cam at current t
			latCam = std::abs(ind.getLatitude() - lat);
			longiCam = std::abs(ind.getLongitude() - longi);

			// CHECK if lat cam speed isn't too high
			camSpeed = std::abs(latCam - latCamB4) / (ind.m_time - timeB4);
			if (camSpeed >= orientationSpeed) {
				return 0;
			}

			// CHECK if longi cam speed isn't too high
			camSpeed = std::abs(longiCam - longiCamB4) / (ind.m_time - timeB4);
			if (camSpeed >= orientationSpeed) {
				return 0;
			}

			latCamB4 = latCam;
			longiCamB4 = longiCam;
			timeB4 = ind.m_time;

		}

	}

	std::cout << "APRES VERIF" << std::endl;

	// BUILD map<Collection*, int>
	std::map<Collection *, int> map_collections;
	for(auto &ite : sim.getCollections()) {
		map_collections[ite]=0;
	}

	std::cout << "AVANT FILL COLLECTIONS" << std::endl;
	// FILL map<Collection*,int> when there is a photo
	for(unsigned int i=0; i<sim.getNumberSatellites(); i++) {
		for(auto ind : map_res[i]){
			Photograph* p = sim.getPhotograph(
				ind.getLatitude(),
				ind.getLongitude()
			);
			for(auto iterator: p->getCollections()){
				map_collections[iterator]++;
			}
		}
	}
	std::cout << "AVANT PARCOURS COLLECTIONS" << std::endl;
	unsigned int score = 0;
	for(auto &ite : sim.getCollections()) {
		std::cout << *ite << std::endl;
		if (map_collections[ite] == ite->getPhotographs().size()) {
			score+=ite->getValue();
		}
	}

	std::cout << "SCORE : " << score << std::endl;

	return score;
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
