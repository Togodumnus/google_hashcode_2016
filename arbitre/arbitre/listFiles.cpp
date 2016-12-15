#include <listFiles.hpp>
#include <utils.hpp>

listFiles::listFiles(const char* INPUT){
		
        this->dossier = std::string(INPUT);
        DIR *pDIR;

        if(pDIR=opendir(INPUT)){


                while(auto entry = readdir(pDIR)){
                        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ){
                            std::string fichier = concat(INPUT, entry->d_name);
                	        fichiers.push_back(fichier);
                    }
                }
                closedir(pDIR);
        }
}

listFiles::~listFiles(){

};

std::vector<std::string>& listFiles::getFiles(){
	return this->fichiers;
}

