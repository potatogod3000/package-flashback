#include "os.h"

int packagesInstalled;

void arch() {

}

void debian() {
    
}

void fedora() {
    std::string packages;
    std::array<char, 80> buffer;
    FILE * pipe = popen("dnf list installed | wc -l", "r");

    if(!pipe) {
        std::cerr << "Cannot access \"dnf\" package manager. Is this system immutable?" << std::endl;
    }
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        packages += buffer.data();
    }
    pclose(pipe);

    packages.erase(std::remove(packages.begin(), packages.end(), '\n'), packages.cend());
    packagesInstalled = std::stoi(packages);
    std::cout << "You have " << packagesInstalled << " packages installed currently in your system." << std::endl;
}

void ubuntu() {

}