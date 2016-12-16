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

	// I/O files
	std::vector<std::string> m_input;
	std::vector<std::string> m_output;

	// duration of the solution
	unsigned int m_duration;

	// score of the solution
	unsigned int m_score;

	// nom du fichier de jeu
	std::string m_jeu;

public:
	Exec(std::string fichier);
	~Exec();

	void duration(std::string);

	inline std::vector<std::string> getInput(){
		return m_input;
	}

};
