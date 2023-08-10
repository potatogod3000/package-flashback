#include "system.h"
#include "backup.h"
#include "restore.h"

const char *listPackageCount, *listPackages;
std::string installPackagesCommand;

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
    std::string name, line;
    
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

    FILE *distroName;
    checkDir(packageFlashbackDir);

    if(!(distroName = fopen(distroNameFile.c_str(), "r"))) {
        std::ofstream distroTxtFile(distroNameFile);
        distroTxtFile << name;
        distroTxtFile.close();
    }

    return name;
}

void setCommandsAndRedirect(bool check, std::string name, char operation, char **argv) {
    if(check) {
        if(name == "Arch Linux") {
            listPackageCount = "pacman -Q | awk '{print $1}' | wc --lines";
            listPackages = "pacman -Q | awk '{print $1}'";
            installPackagesCommand = "pkexec pacman -S --noconfirm";
        }

        else if(name == "Fedora Linux") {
            listPackageCount = "dnf list installed | awk 'NR!=1 {print}' | wc --lines";
            listPackages = "dnf list installed | awk 'NR!=1 {print $1}'";
            installPackagesCommand = "pkexec dnf install --assumeyes";
        }

        else if(name == "Ubuntu" || name == "Debian") {
            listPackageCount = "dpkg --get-selections | grep -v \"deinstall\" | awk 'NR!=1 {print}' | wc --lines";
            listPackages = "dpkg --get-selections | grep -v \"deinstall\" | awk 'NR!=1 {print $1}'";
            installPackagesCommand = "pkexec apt install --assume-yes";
        }
    }

    else {
        unsupportedSystem();
    }


    if(operation == 'b') {
        backupPackages(listPackageCount, listPackages, argv);
    }

    else if(operation == 'r') {
        restorePackages(installPackagesCommand, storePackagesInstalled(listPackages), fileCheck(argv), argv);
    }
}

void checkDir(std::string fileLocationDir) {
    struct stat info;

    // Using sys/stat.h to see if the directory is already created
    if(stat(fileLocationDir.c_str(), &info) != 0) {
        mkdir(fileLocationDir.c_str(), 0777);    
    }
}