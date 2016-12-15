#pragma once

#include <ctime>
#include <chrono>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <dirent.h>
#include <vector>
#include "listFiles.hpp"


class Exec {

private:

	// name of the executable file
	std::string m_executable;

	// input files 
	std::vector<std::string> m_input;
	std::vector<std::string> m_output;
	// seconds ?	
	unsigned int m_duration;

	// appeler result pour déterminer le score
	unsigned int m_score;

	// nom du fichier de jeu 
	const char* m_jeu;

public:
	Exec(std::string fichier);
	~Exec();
	
	/*
	 * Faut aussi que tu stockes les résultats qq part pour qu'on les envoie apres
	 * à la classe Result qui va calculer le score et vérifier le tout
	 */
	void duration(std::string);
	friend std::ofstream& operator<<(std::ofstream&, const Exec&);

	//bool replace(std::string& str, const std::string& from, const std::string& to);

	inline std::vector<std::string> getInput(){
		return m_input;
	}

};
