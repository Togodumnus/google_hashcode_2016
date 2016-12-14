#include <iostream>
#include <Exec.hpp>
#include <Result.hpp>
#include <listFiles.hpp>
#include <string>


int main(int argc, const char* argv[]) {
    if (argc > 1) { // on a un argument
            listFiles* listFile = new listFiles(argv[1]);

            for (std::vector<const char*>::const_iterator it = listFile->getFiles().begin(); it != listFile->getFiles().end(); it++) {
                

                std::cout << *it << std::endl;

                //Exec* programme = new Exec(*it);
                //std::string str(*it);
                //std::cout << *it << std::endl;
                //programme->duration();
            }
        }


    else {
        cout << " Fournissez un dossier à traiter " << endl;
    }

}
