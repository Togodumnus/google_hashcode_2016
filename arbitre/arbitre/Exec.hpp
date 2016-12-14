#pragma once

#include <ctime>
#include <chrono>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <fstream>
#include <dirent.h>
#include <vector>


class Exec {

private:
	const char* executable;

public:
	Exec();
	~Exec();
	
	/*
	 * Faut aussi que tu stockes les résultats qq part pour qu'on les envoie apres
	 * à la classe Result qui va calculer le score et vérifier le tout
	 */
	void duration(const char* INPUT);
	friend std::ofstream& operator<<(std::ofstream&, const Exec&);

};
