#include <iostream>
#include <Exec.hpp>
#include <Result.hpp>
#include <listFiles.hpp>
#include <string>


int main(int argc, const char* argv[]) {
    if (argc > 1) { // on a un argument
            listFiles* listFile = new listFiles(argv[1]);

            for (std::vector<string>::const_iterator it = listFile->getFiles().begin(); it != listFile->getFiles().end(); it++) {
                //std::cout << " it = " << *it << std::endl;

                Exec* programme = new Exec(*it);
                
                programme->duration();
            }
        }


    else {
        cout << " Fournissez un dossier à traiter " << endl;
    }

}
