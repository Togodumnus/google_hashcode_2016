#include <string>
#include <iostream>

#include "Exec.hpp"
#include "Result.hpp"
#include "listFiles.hpp"
#include "utils.hpp"

using namespace std;
//#include <listFiles.hpp>

// J'laisse ça là pour au cas ou j'ai cassé des trucs
/*
void listFile(const char* INPUT){
		* D'après Nico c'est de la merde
		 * Théoriquement c'est valide partout, mais
		 * Sur Windows ça bug
		 *
		 * Le problème c'est que tu prends en compte aussi les Directory
		 *
        DIR *pDIR;
        struct dirent *entry;
        if( pDIR=opendir(INPUT) ){
                while(entry = readdir(pDIR)){
                        if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 )
                        cout << entry->d_name << "\n";
                }
                closedir(pDIR);
        }
}

//using namespace std;

*/
int main(int argc, const char* argv[]) {

	/*
    if (argc > 1) { // on a un argument


            listFiles* listFile = new listFiles(argv[1]); // nom du dossier contenant les executables
            listFiles* listInput = new listFiles("arbitre/arbitre/dataIN"); // nom des fichiers d'entrées


            for (std::vector<std::string>::const_iterator it = listFile->getFiles().begin(); it != listFile->getFiles().end(); it++) {
                std::cout << " itijrig = " << *it << std::endl;

                Exec* programme = new Exec(*it);

                for (std::vector<std::string>::const_iterator it2 = listInput->getFiles().begin(); it2 != listInput->getFiles().end(); it2++) {
                   //std::cout << " it = " << *it << std::endl;

                   //(programme->getInput()).push_back(*it);
                    std::string commande = *it; // nom de l'exe                
                    std::string input = *it2; // nom du fichier d'entrée
                    std::string output = input; // création du nom du fichier de sortie
                    replaceString(output,"in","out"); // on change le .in en .out
                    replaceString(output,"IN","OUT"); // on créer un dossier dataOUT dans le même dossier que dataIN

                    commande += " " + input + " " + output;  // la commande totale a éxécuté 

                    //std::cout << commande << std::endl;

                    programme->duration(commande);


            }

                //Exec* programme = new Exec(*it);

                for (std::vector<string>::const_iterator it = listFile->getFiles().begin(); it != listFile->getFiles().end(); it++) {
                std::cout << " it = " << *it << std::endl;

                (programme->m_input).push_back()
                
                //programme->duration();
            }
        }


    else {
        std::cout << " Fournissez un dossier à traiter " << std::endl;
    }
	*/
    //listFiles* listFile = new listFiles(argv[1]);
	Result res;
	std::string a("./arbitre/arbitre/sortie/results_constellation.out");
	res.FigureOutScore(a);
	
}
