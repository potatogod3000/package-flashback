#include "os.h"

int packagesInstalledCount;
std::vector<std::string> packagesInstalled;

void arch() {

}

void debian() {
    
}

void fedora() {
    std::string packagesCount, packages;
    std::array<char, 80> buffer;
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
        std::cout << "You have " << packagesInstalledCount << " packages installed currently in your system." << std::endl;
    }
    catch(const std::exception& exception) {
        std::cerr << "\n" << "!!!EXCEPTION!!! \"" << exception.what() << "\"" << '\n';
    }

    FILE *pkgs = popen("dnf list installed | awk '{print $1}'", "r");

    try {
        while (fgets(buffer.data(), buffer.size(), pkgs) != nullptr) {
            packages = buffer.data();
            packages.erase(std::remove(packages.begin(), packages.end(), '\n'), packages.cend());
            packagesInstalled.push_back(packages);
        }
        pclose(pkgs);
    }
    catch(const std::exception& exception) {
        std::cerr << "\n" << "!!!EXCEPTION!!! \"" << exception.what() << "\"" << '\n';
    }

    std::cout << "The packages installed are:\n";
    for(int i = 0; i < packagesInstalled.size(); i++) {
        std::cout << packagesInstalled[i] << "  ";
    }
    std::cout << std::endl;
}

void ubuntu() {

}