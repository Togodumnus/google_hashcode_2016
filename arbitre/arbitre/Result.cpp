#include <fstream>
#include <sstream>
#include <algorithm>

#include "Result.hpp"
#include "Utils.hpp"


unsigned int Result::FigureOutScore(std::string &input_file){
	/*
	 * TODO
	 * 
	 *		1) verifier que les photos sont atteignables par le satellite
	 *		2) verifier que le satellite peut effectuer la rotation entre 2 photos
	 *		3) stocker les photos bonnes dans les collection
	 *		4) calculer le score final par rapport aux collections completees
	 */

	this->parse(input_file);
	// Test sort
	std::sort(m_results.begin(), m_results.end(), less_than_key());

	

	
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
							res.m_id_satellite = std::stoi(result2);
						else if (i==3)
							res.m_moment = std::stoi(result2);
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
			<< it.m_id_satellite << " " << it.m_moment << " ";
	}
	return o;
}