
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "Exec.hpp"
#include "Result.hpp"
#include "listFiles.hpp"
#include "utils.hpp"

class NoOutputFile: std::exception {
	public:
		NoOutputFile() {};
		const char* what() const noexcept {
			return "No output file";
		}
};

void write_result(const char* OUTPUT, std::vector<Result>& results) {

	std::ofstream file(OUTPUT, std::ios::out | std::ios::trunc);
	if (file) {
		file << "Exec;Time;Score;Dataset" << "\n";
		for(Result& r: results) {
			file << r << "\n";
		}
		file.close();
	} else {
		throw NoOutputFile();
	}
}

int main(int argc, const char* argv[]) {

	std::vector<Result> results;

	if (argc > 2) { // on a un argument

#ifdef _WIN32
		listFiles* listFile = new listFiles(argv[1]); // nom du dossier contenant les executables
		listFiles* listInput = new listFiles("..\\..\\..\\arbitre\\arbitre\\dataIN\\"); // nom des fichiers dentrees

		for (std::vector<std::string>::const_iterator it = listFile->getFiles().begin(); it != listFile->getFiles().end(); it++) {

			Exec programme = Exec(*it);

			for (std::vector<std::string>::const_iterator it2 = listInput->getFiles().begin(); it2 != listInput->getFiles().end(); it2++) {

				// it = nom de l'éxécutable
				// it2 = nom du fichier d'entrée

				std::string commande = argv[1];

				commande += "\\" + *it; // nom de l'exe

				std::string input = "..\\..\\..\\arbitre\\arbitre\\dataIN\\";
				input += *it2; // nom du fichier d'entrée
				std::string output = input; // création du nom du fichier de sortie
				replaceString(output, "in", "out"); // on change le .in en .out
				replaceString(output, "IN", "OUT"); // on créer un dossier dataOUT dans le même dossier que dataIN


				commande += " " + input + " " + output /*+ " >> NUL " */;  // la commande totale à éxécuter
																				// redirection du flux de sortie
																				// vers /dev/null pour ne pas être
																				// parasité par la sortie de l'éxécutable

				std::cout << commande << std::endl;
				results.push_back(Result(
					input, output, programme.duration(commande)
				));
			}
		}
#else // UNIX

		listFiles* listFile = new listFiles(argv[1]); // nom du dossier contenant les executables
		listFiles* listInput = new listFiles("arbitre/arbitre/dataIN"); // nom des fichiers dentrees

		for (std::vector<std::string>::const_iterator it = listFile->getFiles().begin(); it != listFile->getFiles().end(); it++) {

			// it = nom de l'éxécutable

			Exec programme = Exec(*it);

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
																			// parasité par la sortie texte de l'éxécutable

				std::cout << commande << std::endl;

				results.push_back(Result(
					input, output, programme.duration(commande)
				));
			}
		}
#endif

		for (Result& r: results) {
			r.FigureOutScore();
		}

		write_result(argv[2], results);

	} else {
		std::cout
			<< "usage: arbitre <binaries folder> <output file>"
			<< std::endl;
	}
}
