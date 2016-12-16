#pragma once

#ifdef _WIN32
	#include <vector>
	#include <stdio.h>
	#include <cstdlib>
	#include <iostream>
	#include <string.h>
	#include <fstream>
	#include <sys/types.h>
	#include <windows.h>
	#include <tchar.h> 
	#include <strsafe.h>
	#pragma comment(lib, "User32.lib")
#else
	#include <vector>
	#include <stdio.h>
	#include <cstdlib>
	#include <iostream>
	#include <string.h>
	#include <fstream>
	#include <sys/types.h>
	#include <dirent.h>
#endif


class listFiles {

private:
	std::vector<std::string> fichiers;
	std::string dossier;
public:
	listFiles(const char*);
	~listFiles();
	std::vector<std::string>& getFiles();
};