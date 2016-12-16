#define _CRT_SECURE_NO_WARNINGS
#include "Exec.hpp"

const int NUMBER_OF_RUN = 2;

Exec::Exec(std::string fichier){
    this->m_executable = fichier; // nom de l'exe
}

int run(std::string input) {

	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	system((input).c_str()); // on fait string -> char* pour que system fonctionne
	end = std::chrono::system_clock::now();

	unsigned int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
		(end-start).count();
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	std::cout << "finished computation at " << std::ctime(&end_time)
		<< "elapsed time: " << elapsed_seconds << "s\n";

	return elapsed_seconds;
}

unsigned int Exec::duration(std::string INPUT){

	unsigned int sum = 0;
	for (int i = 0; i < NUMBER_OF_RUN; i++) {
		sum += run(INPUT);
	}

	return sum / NUMBER_OF_RUN;
}


