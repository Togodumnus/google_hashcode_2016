#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <cmath>

#include "Result.hpp"
#include "utils.hpp"
#include "hashcode/Simulation.hpp"

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
	ReadState state = ReadState::NumberOfPictures;

	while (std::getline(input, line)){
		std::istringstream iss(line);

		std::string result;
		std::string result2;
		if (std::getline(iss, result, '\n')){
			std::istringstream iss2(result);
			switch(state) {

				case ReadState::NumberOfPictures:
					m_number_of_pictures=std::stoi(result);
					state = ReadState::TypicalLine;
					break;

				case ReadState::TypicalLine:
					int i = 0;

					LocationUnit lat, lng;
					unsigned int t, sat_id;
					while (std::getline(iss2, result2, ' ')) {
						switch(i) {
							case 0:
								lat = std::stoi(result2);
								break;
							case 1:
								lng = std::stoi(result2);
								break;
							case 2:
								t = std::stoi(result2);
								break;
							case 3:
								sat_id = std::stoi(result2);
							default:
								break;
						}
						i++;
					}

					map_res[sat_id]
						.insert(ResultShoot(lat, lng, t));

					break;
			}
		}
	}
}

void Result::FigureOutScore(){

	// parse result file
	this->parse(this->output);

	Simulation sim(this->input);

	int orientationValue, orientationSpeed, camSpeed=0;
	unsigned int timeB4 = 0; // t-1
	long lat, longi, latCam, longiCam,
		 latCamB4 = 0, longiCamB4 = 0; // camera t-1

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
				this->m_score = 0;
				return;
			}

			// Get lat cam at current t
			latCam = std::abs(ind.getLatitude() - lat);
			longiCam = std::abs(ind.getLongitude() - longi);

			// CHECK if lat cam speed isn't too high
			camSpeed = std::abs(latCam - latCamB4) / (ind.m_time - timeB4);
			if (camSpeed >= orientationSpeed) {
				this->m_score = 0;
				return;
			}

			// CHECK if longi cam speed isn't too high
			camSpeed = std::abs(longiCam - longiCamB4) / (ind.m_time - timeB4);
			if (camSpeed >= orientationSpeed) {
				this->m_score = 0;
				return;
			}

			latCamB4 = latCam;
			longiCamB4 = longiCam;
			timeB4 = ind.m_time;

		}

	}

	// BUILD map<Collection*, int>
	std::map<Collection *, int> map_collections;
	for(auto &ite : sim.getCollections()) {
		map_collections[ite]=0;
	}

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

	unsigned int score = 0;
	for(auto &ite : sim.getCollections()) {
		if (map_collections[ite] == ite->getPhotographs().size()) {
			score+=ite->getValue();
		}
	}

	this->m_score = score;
}

std::ostream& operator<<(std::ostream& of, const Result& result) {
	of << result.output << "," //TODO change for exec name
		<< result.time << ","
		<< result.m_score << ","
		<< result.input;
	return of;
}
