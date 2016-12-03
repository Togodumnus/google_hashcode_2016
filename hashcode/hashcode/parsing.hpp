#pragma once

#include <exception>
#include <string>

/**
 * Different states of the reading of input file
 */
enum class ReadState {
	Test,			// TODO remove
	Simulation,
	Collection,
	NumberOfTurns,
	Satellites,
	SatellitesNumber,
	Photograph,
	TimeRange
};

class ReadException: std::exception {
	std::string file;
	public:
		inline ReadException(std::string f) {
			file = f;
		}
		inline const char* what() const _NOEXCEPT {
			std::string m = "Can't read file ";
			m += file;
			return m.c_str();
		};
};

void parseInput(const char* input_file);
