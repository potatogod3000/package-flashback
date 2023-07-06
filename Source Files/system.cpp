#include "system.h"
#include "os.h"

std::string name;

void operatingSystemCheck() {
    #if defined(__linux__)
    // REQUIRES /etc/os-release
        std::ifstream stream("/etc/os-release");
        std::string line;
        std::regex nameRegex("^NAME=\"(.*?)\"$");
        std::smatch match;

        while (std::getline(stream, line)) {
            if (std::regex_search(line, match, nameRegex)) {
                name = match[1].str();
                break;
            }
        }
        std::cout << name << std::endl;
        linuxSystem();

    #endif
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