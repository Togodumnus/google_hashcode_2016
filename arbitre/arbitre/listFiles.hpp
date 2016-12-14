#pragma once

#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>

using namespace std;


class listFiles {

private:
	std::vector<string> fichiers;
	std::string dossier;
public:
	listFiles(const char*);
	~listFiles();
	std::vector<string>& getFiles();
};