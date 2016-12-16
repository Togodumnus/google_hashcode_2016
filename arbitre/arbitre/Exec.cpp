#define _CRT_SECURE_NO_WARNINGS
#include "Exec.hpp"

Exec::Exec(std::string fichier){
    this->m_executable = fichier; // nom de l'exe
}

/*bool Exec::replace(std::string& str, const std::string& from, const std::string& to) {  // fonction qui prend un string
                                                                                        //et remplace le from par le to
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}*/

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


