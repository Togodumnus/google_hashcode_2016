#include "Exec.hpp"

Exec::Exec(std::string fichier){
    this->m_executable = fichier; // nom de l'exe
}

Exec::~Exec(){

}


unsigned int Exec::duration(std::string INPUT){

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    system((INPUT).c_str()); // on fait string -> char* pour que system fonctionne
    end = std::chrono::system_clock::now();
 
    int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
                             (end-start).count();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds << "s\n";

    return elapsed_seconds;
              
}

std::ofstream& operator<<(std::ofstream& of, const Exec& exec){
	of << exec.m_executable << "," << exec.m_duration << "," << exec.m_score << "," << exec.m_jeu;
	return of;
}

