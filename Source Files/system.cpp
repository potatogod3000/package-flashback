#include "system.h"
#include "os.h"

std::string name;
std::vector<std::string> supportedOS = {"Arch Linux", "Debian GNU/Linux", "Fedora Linux", "Ubuntu"};

bool operatingSystemCheck() {
    std::cout << "|| Welcome to package-flashback ||\n\nChecking your operating system... ";
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
    std::cout << "You are using " << name << ".\n\n";
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
    else {
        std::cout << "\nSorry. Only ";
        for(int i = 0; i < supportedOS.size(); i++) {
            std::cout << supportedOS[i];
            if(i <= supportedOS.size() - 3) std::cout << ", ";
            else if(i == supportedOS.size() - 2) std::cout << " and ";
        }
        std::cout << " are supported." << std::endl;
    }
}