#pragma once

#include <iostream>
#include <string>

using namespace std;

inline string concat(const char* c1, const char* c2){
	
	string s1(c1);
	string s2(c2);

	string s3(s1 + "/" + s2);

	//char* c3 = s3.c_str();

	return s3;
}

