#pragma once

#include <iostream>
#include <string>

inline std::string concat(const char* c1, const char* c2){
	
	std::string s1(c1);
	std::string s2(c2);

	std::string s3(s1 + "/" + s2);

	//char* c3 = s3.c_str();

	return s3;
}

inline bool replaceString(std::string& str, const std::string& from, const std::string& to) {  // fonction qui prend un std::string 
                                                                                        //et remplace le from par le to
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
};


class ReadException : std::exception {
std::string file;
public:
	inline ReadException(std::string f) {
		file = f;
	}
	inline const char* what() const noexcept {
		std::string m = "Can't read file ";
		m += file;
		return m.c_str();
	};
};

