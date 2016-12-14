#pragma once

#include <iostream>
#include <string>

using namespace std;

inline const char* concat(const char* c1, const char* c2){
	
	string s1(c1);
	string s2(c2);

	string s3(s1 + "/" + s2);

	const char* fichier = s3.c_str();

	return fichier;
}