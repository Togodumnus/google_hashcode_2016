#pragma once

/**
 * Different states of the reading of input file
 */
enum class type {
	test,			// TODO remove
	simulation,
	collection,
	numberOfTurns,
	satellites,
	satellitesNumber,
	photograph,
	time_range
};

void parseInput(const char* input_file);
