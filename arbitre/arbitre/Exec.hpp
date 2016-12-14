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


class Exec {

private:

	// name of the executable file
	const char* m_executable;

	// seconds ?	
	unsigned int m_duration;

	// appeler result pour déterminer le score
	unsigned int m_score;

	// nom du fichier de jeu 
	const char* m_jeu;

public:
	Exec(const char* fichier);
	~Exec();
	
	/*
	 * Faut aussi que tu stockes les résultats qq part pour qu'on les envoie apres
	 * à la classe Result qui va calculer le score et vérifier le tout
	 */
	void duration();
	friend std::ofstream& operator<<(std::ofstream&, const Exec&);

};
