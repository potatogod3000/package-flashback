#include "system.h"
#include "os.h"

std::string name;

bool operatingSystemCheck() {
    std::cout << "|| Welcome to package-flashback ||\n\nChecking your operating system...\n\n";
    #if defined(__linux__)
        osName();
        return true;
    #else
        std::cout << "Sorry, this application is only supported in Linux-based operating systems." << std::endl;
        return false;
    #endif
}

void osName() {
    std::string line;
    // REQUIRES /etc/os-release
    std::ifstream stream("/etc/os-release");
    std::regex nameRegex("^NAME=\"(.*?)\"$");
    std::smatch match;

    while (std::getline(stream, line)) {
        if (std::regex_search(line, match, nameRegex)) {
            name = match[1].str();
            break;
        }
    }
    std::cout << "You are using " << name << ". ";
    linuxSystem();
}

void linuxSystem() {
    if (name == "Arch Linux")
        arch();
    else if (name == "Debian")
        debian();
    else if (name == "Fedora Linux")
        fedora();
    else if (name == "Ubuntu")
        ubuntu();
}