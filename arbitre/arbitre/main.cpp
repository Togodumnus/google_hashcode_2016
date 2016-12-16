
#include <string>
#include <iostream>


#include "Exec.hpp"
#include "Result.hpp"
#include "listFiles.hpp"
#include "utils.hpp"


int main(int argc, const char* argv[]) {

	if (argc > 1) { // on a un argument


#ifdef _WIN32
	//listFiles* listFile = new listFiles("../../testDirWindows/*.*"); // nom du dossier contenant les executables
		listFiles* listFile = new listFiles(argv[1]); // nom du dossier contenant les executables
		//std::string path = ExePath();
		//path += 
		//listFiles* listFile = new listFiles("C:\\Cours\\Projets\\google_hashcode_2016\\testDirWindows"); // nom du dossier contenant les executables
		//listFiles* listFile = new listFiles("C:\\Cours\\Projets\\google_hashcode_2016\\testDirWindows"); // nom du dossier contenant les executables



		//system("dir");
		//listFiles* listInput = new listFiles("C:\\Cours\\Projets\\google_hashcode_2016\\arbitre\\arbitre\\dataTEST"); // nom des fichiers dentrees
		listFiles* listInput = new listFiles("..\\dataTEST"); // nom des fichiers dentrees

		//int i = 0;
		//std::cin >> i;

		for (std::vector<std::string>::const_iterator it = listFile->getFiles().begin(); it != listFile->getFiles().end(); it++) {

			// it = nom de l'éxécutable

			Exec* programme = new Exec(*it);

			for (std::vector<std::string>::const_iterator it2 = listInput->getFiles().begin(); it2 != listInput->getFiles().end(); it2++) {

				// it2 = nom du fichier d'entrée

				//std::string path = ExePath();

				//std::cout << " EXEPATH : " << ExePath() << std::endl;
				//std::string commande = "C:\\Cours\\Projets\\google_hashcode_2016\\testDirWindows\\";
				std::string commande = argv[1];
				//std::string commande = *it;

				commande += "\\" + *it; // nom de l'exe
				//std::string input = "C:\\Cours\\Projets\\google_hashcode_2016\\arbitre\\arbitre\\dataTEST\\";
				std::string input = "..\\dataTEST\\";
				input += *it2; // nom du fichier d'entrée
				std::string output = input; // création du nom du fichier de sortie
				replaceString(output, "in", "out"); // on change le .in en .out
				replaceString(output, "IN", "OUT"); // on créer un dossier dataOUT dans le même dossier que dataIN


				commande += " " + input + " " + output + " >> NUL " ;  // la commande totale à éxécuter
																				// redirection du flux de sortie 
																				// vers /dev/null pour ne pas être
																				// parasité par la sortie de l'éxécutable

				std::cout << commande << std::endl;
				Result* result = new Result(input, output, programme->duration(commande));

				std::cout << *result << std::endl;
            }
        }

#else // UNIX

		listFiles* listFile = new listFiles(argv[1]); // nom du dossier contenant les executables
		listFiles* listInput = new listFiles("arbitre/arbitre/dataTEST"); // nom des fichiers dentrees

		for (std::vector<std::string>::const_iterator it = listFile->getFiles().begin(); it != listFile->getFiles().end(); it++) {

			// it = nom de l'éxécutable

			Exec* programme = new Exec(*it);

			for (std::vector<std::string>::const_iterator it2 = listInput->getFiles().begin(); it2 != listInput->getFiles().end(); it2++) {

				// it2 = nom du fichier d'entrée

				std::string commande = *it; // nom de l'exe                
				std::string input = *it2; // nom du fichier d'entrée
				std::string output = input; // création du nom du fichier de sortie
				replaceString(output, "in", "out"); // on change le .in en .out
				replaceString(output, "IN", "OUT"); // on créer un dossier dataOUT dans le même dossier que dataIN

				commande += " " + input + " " + output + " >> /dev/null" ;  // la commande totale à éxécuter
																			// redirection du flux de sortie 
																			// vers /dev/null pour ne pas être
																			// parasité par la sortie de l'éxécutable

				std::cout << commande << std::endl;
				Result* result = new Result(input, output, programme->duration(commande));

				std::cout << *result << std::endl;

			}
		}
#endif	
			}
	else {
	std::cout << " Fournissez un dossier à traiter " << std::endl;
		}
    }

	

