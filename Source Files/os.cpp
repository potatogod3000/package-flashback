#include "os.h"

int packagesInstalledCount;
std::vector<std::string> packagesInstalled;

void packages(const char *listPackageCount, const char *listPackages, char **argv) {
    std::string packagesCount, packages;
    std::array<char, 80> buffer;

    // Count of installed packages (argv -i)
    FILE *pkgcnt = popen(listPackageCount, "r"); 
    
    if(!pkgcnt) {
        std::cerr << "Cannot access \"dnf\" package manager. Is this system immutable?" << std::endl;
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

    // listing installed packages (argv -p)
    if (strcmp(argv[1], "-p") == 0) {
        
        //Printing packages in a formatted manner (using <iomanip>)
        const char separator    = ' ';
        const int spaceWidth     = 75;

        std::cout << " The packages installed are:\n\n";
        for(int i = 0; i < packagesInstalled.size(); i += 3) {
            std::cout << std::left << std::setw(spaceWidth) << std::setfill(separator) << packagesInstalled[i];
            std::cout << std::left << std::setw(spaceWidth) << std::setfill(separator) << packagesInstalled[i+1];
            std::cout << std::left << std::setw(spaceWidth) << std::setfill(separator) << packagesInstalled[i+2] << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    if (strcmp(argv[1], "-s") == 0) {
        searchPackages(packagesInstalled, argv);
    }
}

void searchPackages(std::vector<std::string> packagesInstalled, char **argv) {
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