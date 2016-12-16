
#include "listFiles.hpp"
#include "utils.hpp"	

listFiles::listFiles(const char* INPUT){
		

       #ifdef _WIN32
        //define something for Windows

			std::cout << " System windows " << std::endl;
            HANDLE hFind;
			WIN32_FIND_DATA data;

			std::string dossier;
			dossier = concatWindows(INPUT, "*.*");
			//system("dir");
			//std::cout << 
			std::cout << " dossier = " << (dossier).c_str() << std::endl;
			hFind = FindFirstFile((dossier).c_str(), &data);
			if (hFind != INVALID_HANDLE_VALUE) {
			  do {
				  if (strcmp(data.cFileName, ".") != 0 && strcmp(data.cFileName, "..") != 0) {
					  printf("%s\n", data.cFileName);
					  fichiers.push_back(data.cFileName);
				  }
			  } while (FindNextFile(hFind, &data));
			  FindClose(hFind);
			}

 
        #else
          //define it for a Unix machine
		std::cout << " System unix " << std::endl;

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
        #endif

}

listFiles::~listFiles(){

};

std::vector<std::string>& listFiles::getFiles(){
	return this->fichiers;
}

