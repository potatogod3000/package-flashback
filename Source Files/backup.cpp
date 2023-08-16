#include "system.h"

int packagesInstalledCount;

// Implementation of backup logic
void Actions::backupPackages(const char *listPackageCount, const char *listPackages, char **argv) {
    std::vector<std::string> packagesInstalled;
    std::string packagesCount;
    std::array<char, 80> buffer;

    // Count of installed packages (argv -i)
    FILE *pkgcnt = popen(listPackageCount, "r"); 
    
    if(!pkgcnt) {
        std::cerr << "Cannot access the package manager! Is this system immutable?" << std::endl;
    }

    try {
        while (fgets(buffer.data(), buffer.size(), pkgcnt) != nullptr) {
            packagesCount += buffer.data();
        }
        pclose(pkgcnt);
        packagesCount.erase(std::remove(packagesCount.begin(), packagesCount.end(), '\n'), packagesCount.cend());
        packagesInstalledCount = std::stoi(packagesCount);
        std::cout << "You have " << packagesInstalledCount << " packages installed currently in your system.";
    }
    catch(const std::exception &exception) {
        std::cerr << "\n" << "!!!EXCEPTION!!! \"" << exception.what() << "\"" << '\n';
    }

    // Storing all installed packages in a vector
    packagesInstalled = storePackagesInstalled(listPackages);

    // listing installed packages (argv -p)
    if (strcmp(argv[1], "-p") == 0) {
        
        //Printing packages in a formatted manner (using <iomanip>)
        const char separator    = ' ';
        const int spaceWidth     = 55;

        std::cout << " The packages installed are:\n\n";
        for(int i = 0; i < packagesInstalled.size(); i += 3) {
            std::cout << std::left << std::setw(spaceWidth) << std::setfill(separator) << packagesInstalled[i];
            std::cout << std::left << std::setw(spaceWidth) << std::setfill(separator) << packagesInstalled[i+1];
            std::cout << std::left << std::setw(spaceWidth) << std::setfill(separator) << packagesInstalled[i+2] << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Save packages to a file in $XDG_DATA_HOME/package-flashback
    if(strcmp(argv[1], "-sv") == 0) {
        saveToFile(packagesInstalled);
    }

    // Searching within installed packages (argv -se <"string">)
    if (strcmp(argv[1], "-se") == 0) {
        searchPackages(packagesInstalled, argv);
    }
}

// Storing all installed packages in packagesInstalled vector and return it
std::vector<std::string> Actions::storePackagesInstalled(const char *listPackages) {
    std::string packages;
    std::array<char, 80> buffer;
    std::vector<std::string> packagesInstalled;

    FILE *pkgs = popen(listPackages, "r");

    try {
        while (fgets(buffer.data(), buffer.size(), pkgs) != nullptr) {
            packages = buffer.data();
            packages.erase(std::remove(packages.begin(), packages.end(), '\n'), packages.cend());
            packagesInstalled.push_back(packages);
        }
        pclose(pkgs);
    }
    catch(const std::exception &exception) {
        std::cerr << "\n" << "!!!EXCEPTION!!! \"" << exception.what() << "\"" << '\n';
    }
    return packagesInstalled;
}

// Searching for entered string within the vector elements
void Actions::searchPackages(std::vector<std::string> packagesInstalled, char **argv) {
    std::cout << "Found the package(s): " << std::endl;
    int count = 0;

    for(int i = 0; i < packagesInstalled.size(); i++) {
        std::size_t found = packagesInstalled[i].find(argv[2]);

        if(found != std::string::npos) {
            count++;
            std::cout << count << ". " << packagesInstalled[i] << "\t";
        }
    }

    std::cout << "\nFound " << count << " packages!" << std::endl;
}

// Saving packages and name of OS to a file inside $XDG_DATA_HOME
void Actions::saveToFile(std::vector<std::string> packagesInstalled) {
    FILE *packagesInstalledFile;

    actions.checkDir(actions.packageFlashbackDir);
    
    // Check if packagesInstalled.txt has already been created and make it a backup
    if(packagesInstalledFile = fopen(packageFlashbackFile.c_str(), "r")) {
        std::ifstream packagesInstalledTxt(packageFlashbackFile);
        std::string line;
        bool match;
        for(int i = 0; getline(packagesInstalledTxt, line), i < packagesInstalled.size(); i++) {
            if(strcmp(packagesInstalled[i].c_str(), line.c_str()) == 0) match = true;
            else match = false;
        }

        if(match == true) std::cout << "\nThe packages installed have not changed since the last check. \"packageInstalled.txt\" unchanged." << std::endl;

        else {
            // Renaming the already generated "packagesInstalled.txt" file to store as backup
            std::filesystem::rename(packageFlashbackFile, packageFlashbackDir + "/packagesInstalled_" + currentDateTime() + ".bak");
            fclose(packagesInstalledFile);
            
            std::cout << "\nThere is already a \"packagesInstalled.txt\" file created but the packages installed have changed. A backup of that file has been created.";
        }
    }

    // Writing packagesInstalled vector into "packagesInstalled.txt" file
    std::ofstream packagesTxtFile(packageFlashbackFile);
    for(auto it: packagesInstalled) {
        packagesTxtFile << it << std::endl;
    }
    packagesTxtFile.close();
    std::cout << "Saved in \'" << packageFlashbackDir << "/\'." << std::endl;
}

// Getting current date and time from system
const std::string Actions::currentDateTime() {
    time_t now = time(0);
    struct tm *tstruct = localtime(&now);
    char buf[80];
    strftime(buf, sizeof(buf), "%d-%m-%Y_%H-%M-%S", tstruct);

    return buf;
}