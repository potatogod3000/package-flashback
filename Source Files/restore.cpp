#include "restore.h"

std::vector<std::string> fileCheck(char **argv) {
    std::vector<std::string> packagesToRestore;
    std::ifstream importFile(argv[2]);
    
    if(!importFile) {
        std::cerr << "The restore file doesn't exist!" << std::endl;
    }

    else if(importFile.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "The restore file is empty!" << std::endl;
        importFile.close();
    }

    else {
        std::string line;
        for(int i=0; getline(importFile, line); i++) {
            packagesToRestore.push_back(line);
        }

        std::cout << "You will be installing the following packages: \n";
        
        //Printing packages in a formatted manner (using <iomanip>)
        const char separator    = ' ';
        const int spaceWidth     = 55;

        for(int i = 0; i < packagesToRestore.size(); i += 3) {
            std::cout << std::left << std::setw(spaceWidth) << std::setfill(separator) << packagesToRestore[i];
            std::cout << std::left << std::setw(spaceWidth) << std::setfill(separator) << packagesToRestore[i+1];
            std::cout << std::left << std::setw(spaceWidth) << std::setfill(separator) << packagesToRestore[i+2] << std::endl;
        }
    }
    return packagesToRestore;
}

void restorePackages(const char* installPackagesCommand, std::vector<std::string> packagesInstalled, std::vector<std::string> packagesToRestore) {
    for(int i, j; i < packagesInstalled.size(), j < packagesToRestore.size(); i++, j++) {
        if(packagesInstalled[i] == packagesInstalled[j]) {
            
        }
    }
}