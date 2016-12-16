#pragma once

#include <iostream>
#include <string>

#ifdef _WIN32
	#include <windows.h>



inline std::string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);
}

#endif

inline std::string concat(const char* c1, const char* c2){

	std::string s1(c1);
	std::string s2(c2);

	std::string s3(s1 + "/" + s2);

	return s3;
}

inline std::string concatWindows(const char* c1, const char* c2) {

	std::string s1(c1);
	std::string s2(c2);

	std::string s3(s1 + "\\" + s2);

	return s3;
}

// fonction qui prend un std::string
// et remplace le from par le to
inline bool replaceString(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if(start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
};

