#include <listFiles.hpp>
#include <utils.hpp>

listFiles::listFiles(const char* INPUT){
		
        this->dossier = string(INPUT);
        DIR *pDIR;

        if(pDIR=opendir(INPUT)){

				//std::string str(INPUT); // on transforme en string afin de le concaténer avec le fichier

                while(auto entry = readdir(pDIR)){
                        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ){
                            string fichier = concat(INPUT, entry->d_name);
                            //std::cout << fichier << std::endl;
                	        fichiers.push_back(fichier);
                    }
                }
                closedir(pDIR);
        }
}

listFiles::~listFiles(){

};

std::vector<string>& listFiles::getFiles(){
	return this->fichiers;
}

