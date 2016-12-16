#include "Exec.hpp"

Exec::Exec(std::string fichier){
    this->m_executable = fichier; // nom de l'exe

    /* listFiles* listInput = new listFiles("arbitre/arbitre/data"); // nom des fichiers d'entrées


    for (std::vector<string>::const_iterator it = listInput->getFiles().begin(); it != listInput->getFiles().end(); it++) {
                std::cout << " it = " << *it << std::endl;
            }
    */

    /*this->m_input = fichier;
    this->m_output = m_input;
    replace(this->m_output,"in","out"); //on créer un fichier de sortie au même endroit mais en changeant le .in en .out
    this->m_executable += m_input + " " + m_output; // représente la commande complète */
}

Exec::~Exec(){

}

/*bool Exec::replace(std::string& str, const std::string& from, const std::string& to) {  // fonction qui prend un string
                                                                                        //et remplace le from par le to
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}*/

void Exec::duration(std::string INPUT){

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    //system("../bin/hashcode ../hashcode/hashcode/data/forever_alone.in ../hashcode/hashcode/data/forever_alone.out");
    system((INPUT).c_str()); // on fait string -> char* pour que system fonctionne
    end = std::chrono::system_clock::now();

    int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
                             (end-start).count();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds << "s\n";

}


