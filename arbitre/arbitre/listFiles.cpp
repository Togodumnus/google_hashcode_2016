#include <listFiles.hpp>
#include <utils.hpp>

listFiles::listFiles(const char* INPUT){
		
        DIR *pDIR;

        if(pDIR=opendir(INPUT)){

				//std::string str(INPUT); // on transforme en string afin de le concaténer avec le fichier

                while(auto entry = readdir(pDIR)){
                        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ){
                            const char* fichier = concat(INPUT, entry->d_name);
                            std::cout << fichier << std::endl;
                	        fichiers.push_back(fichier);
                    }
                }
                closedir(pDIR);
        }
}

listFiles::~listFiles(){

};

std::vector<const char*>& listFiles::getFiles(){
	return this->fichiers;
}

