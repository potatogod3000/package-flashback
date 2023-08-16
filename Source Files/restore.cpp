#include "system.h"

// Checking the input file and returning packagesToRestore vector
std::vector<std::string> Actions::fileCheck(char **argv) {
    std::vector<std::string> packagesToRestore;
    std::ifstream importFile(argv[2]);
    
    // Checking whether the input file location is valid and checking if its empty
    if(!importFile) {
        std::cerr << "The restore file doesn't exist!" << std::endl;
    }

    else if(importFile.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "The restore file is empty!" << std::endl;
        importFile.close();
    }

    // Adding each line as an element to packagesToRestore vector
    else {
        std::string line;
        for(int i=0; getline(importFile, line); i++) {
            packagesToRestore.push_back(line);
        }
    }

    return packagesToRestore;
}

// Implementation of restore logic
void Actions::restorePackages(std::string installPackagesCommand, std::vector<std::string> packagesInstalled, std::vector<std::string> packagesToRestore, char **argv) {
    
    // Iterating in packagesInstalled vector and removing already installed packages from packagesToRestore vector
    std::vector<std::string>::iterator installedIt = packagesInstalled.begin();
    for(installedIt; installedIt != packagesInstalled.end(); installedIt++) {
        packagesToRestore.erase(std::find(packagesToRestore.begin(), packagesToRestore.end(), *installedIt));
    }

    // Restore process
    if(packagesToRestore.empty()) {
        std::cerr << "No packages to install!" << std::endl;
    }

    else {
        installPackages(packagesToRestore, installPackagesCommand);
    }
}

// Packages installation logic
void Actions::installPackages(std::vector<std::string> packagesToRestore, std::string installPackagesCommand) {
    std::cout << "You will be installing these " << packagesToRestore.size() << " packages: \n";
        
    //Printing packages
    for(auto it: packagesToRestore) {
        std::cout << it << std::endl;
        installPackagesCommand += " " + it;
    }

    char decision;
    std::cout << "\nDo you wish to install the packages now? [Type 'Y' for yes or 'N' for no]: ";
    while(std::cin >> decision) {
        if(decision == 'Y' || decision == 'y' || decision == 'N' || decision == 'n') {
            break;
        }

        else {
            std::cin.ignore();
            std::cout << "Please enter either 'Y' for yes or 'N' for no: ";
        }
    }

    if(decision == 'Y' || decision == 'y') {
        std::cout << installPackagesCommand << "\n";
        std::array<char, 128> buffer;
        std::string result;
        FILE *installation = popen(installPackagesCommand.c_str(), "r");
        try {
            while (fgets(buffer.data(), buffer.size(), installation) != nullptr) {
                result = buffer.data();
                std::cout << result;
            }
            result.erase();
            pclose(installation);
        }
        catch(const std::exception &exception) {
            std::cerr << "\n" << "!!!EXCEPTION!!! \"" << exception.what() << "\"" << '\n';
        }
    }
}