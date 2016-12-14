#include "Result.hpp"

unsigned int Result::FigureOutScore(const char* input_file){
	/*
	 * TODO
	 * 
	 *		1) verifier que les photos sont atteignables par le satellite
	 *		2) verifier que le satellite peut effectuer la rotation entre 2 photos
	 *		3) stocker les photos bonnes dans les collection
	 *		4) calculer le score final par rapport aux collections completees
	 */
	return 0;
}

enum class ReadState {
	NumberOfPictures,
	TypicalLine,
};

void Result::parse(std::string input_file){

	std::ifstream input(input_file); // on crée un buffer de stream
	if (input.fail() || input.bad()) {
		throw ReadException(input_file);
	}   
	std::string line; // ligne actuelle
	ReadState t = ReadState::NumberOfPictures;

	while (std::getline(input, line)){
		int cpt = 0; // compteur d'élément dans une ligne
		std::istringstream iss(line);

		std::string result;
		std::string result2;
		if (std::getline(iss, result, '\n')){
			// deuxième buffer pour parser a l'intérieur des lignes
			std::istringstream iss2(result);

			switch(t) {

				case ReadState::NumberOfPictures:
					m_number_of_pictures=std::stoi(result);
					t = ReadState::TypicalLine;
					break;
				case ReadState::TypicalLine:
					int i=0;
					while (std::getline(iss2, result2, ' ')) {
						if (i==0)
							m_number_of_pictures = result2;
						else if (i==1)
							m_latitude = result2;
						else if (i==2)
							m_longitude = result2;
						else if (i==3)
							m_id_satellite = result2;
						else if (i==4)
							m_moment = result2;
					}
					break;
			}
		}
	}
}
