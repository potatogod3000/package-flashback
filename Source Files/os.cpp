#include "os.h"

int packagesInstalledCount;
std::vector<std::string> packagesInstalled;

void arch(char **argv) {

}

void debian(char **argv) {
    
}

void fedora(char **argv) {
    std::string packagesCount, packages;
    std::array<char, 80> buffer;

    // Count of installed packages (-i)
    FILE *pkgcnt = popen("dnf list installed | wc -l", "r"); 
    
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

    // listing installed packages (-p)
    const char separator    = ' ';
    const int spaceWidth     = 75;

    if (strcmp(argv[1], "-p") == 0) {
        FILE *pkgs = popen("dnf list installed | awk '{print $1}'", "r");

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

        //std::sort(packagesInstalled.begin(), packagesInstalled.end());
    
        std::cout << " The packages installed are:\n\n";
        for(int i = 0; i < packagesInstalled.size(); i += 3) {
            std::cout << std::left << std::setw(spaceWidth) << std::setfill(separator) << packagesInstalled[i];
            std::cout << std::left << std::setw(spaceWidth) << std::setfill(separator) << packagesInstalled[i+1];
            std::cout << std::left << std::setw(spaceWidth) << std::setfill(separator) << packagesInstalled[i+2] << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void ubuntu(char **argv) {

}