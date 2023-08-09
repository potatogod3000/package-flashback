#include "system.h"
#include "backup.h"
#include "restore.h"

const char *listPackageCount, *listPackages, *installPackagesCommand;

void unsupportedSystem() {
    std::vector<std::string> supportedOS = {"Arch Linux", "Debian GNU/Linux", "Fedora Linux", "Ubuntu"};
    std::cout << "\nSorry. Only ";
        for(int i = 0; i < supportedOS.size(); i++) {
            std::cout << supportedOS[i];
            if(i <= supportedOS.size() - 3) std::cout << ", ";
            else if(i == supportedOS.size() - 2) std::cout << " and ";
        }
    std::cout << " are supported." << std::endl;
}

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

void setCommands(bool check, std::string name, char **argv) {
    if(check) {
        if(name == "Arch Linux") {
            listPackageCount = "";
            listPackages = "";
            packages(listPackageCount, listPackages, argv);
        }
        else if(name == "Debian") {
            listPackageCount = "dpkg --list | wc --lines";
            listPackages = "";
            packages(listPackageCount, listPackages, argv);
        }
        else if(name == "Fedora Linux") {
            listPackageCount = "dnf list installed | awk 'NR!=1 {print}' | wc --lines";
            listPackages = "dnf list installed | awk 'NR!=1 {print $1}'";
            packages(listPackageCount, listPackages, argv);
        }
        else if(name == "Ubuntu") {
            listPackageCount = "";
            listPackages = "";
            packages(listPackageCount, listPackages, argv);
        }
    }
    else {
        unsupportedSystem();
    }
}

void installedPackages() {
    

    
}

void toBeInstalledPackages() {
    if(check) {
        if(name == "Arch Linux") {
            installPackagesCommand = "sudo pacman -S ";
            restorePackages(installPackagesCommand, storePackagesInstalled(listPackages), fileCheck(argv));
        }
        else if(name == "Debian") {
            installPackagesCommand = "sudo apt install ";
            restorePackages(installPackagesCommand, storePackagesInstalled(listPackages), fileCheck(argv));
        }
        else if(name == "Fedora Linux") {
            installPackagesCommand = "sudo dnf install ";
            restorePackages(installPackagesCommand, storePackagesInstalled(listPackages), fileCheck(argv));
        }
        else if(name == "Ubuntu") {
            installPackagesCommand = "sudo apt install ";
            restorePackages(installPackagesCommand, storePackagesInstalled(listPackages), fileCheck(argv));
        }
    }
    else {
        unsupportedSystem();
    }
}