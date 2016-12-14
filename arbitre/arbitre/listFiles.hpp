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
	std::vector<const char*> fichiers;
	const char* dossier;
public:
	listFiles(const char*);
	~listFiles();
	std::vector<const char*>& getFiles();
};