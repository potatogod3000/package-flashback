#include "system.h"
#include "os.h"

std::vector<std::string> supportedOS = {"Arch Linux", "Debian GNU/Linux", "Fedora Linux", "Ubuntu"};

bool operatingSystemCheck() {
    std::cout << "Checking your operating system... ";
    #if defined(__linux__)
        return true;
    #else
        std::cout << "Sorry, this application is only supported in Linux-based operating systems." << std::endl;
        return false;
    #endif
}

std::string osName() {
    std::string name;
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
    return name;
}

void linuxSystem(bool check, std::string name, char **argv) {
    if(check) {
        if (name == "Arch Linux")
            arch(argv);
        else if (name == "Debian")
            debian(argv);
        else if (name == "Fedora Linux")
            fedora(argv);
        else if (name == "Ubuntu")
            ubuntu(argv);
    }
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