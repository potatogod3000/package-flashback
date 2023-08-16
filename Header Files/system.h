#pragma once
#include <iostream>
#include <fstream>
#include <regex>

#include "actions.h"

class System {
    public:
    const std::string xdgDataDir = getenv("HOME") + std::string("/.local/share");
    const std::string packageFlashbackDir = xdgDataDir + "/package-flashback";
    const std::string packageFlashbackFile = packageFlashbackDir + "/packagesInstalled.txt";
    const std::string distroNameFile = packageFlashbackDir + "/distroName.txt";

    Actions actions, backup, restore;

    void unsupportedSystem();
    bool operatingSystemCheck();
    std::string osName();
    void setCommandsAndRedirect(bool check, std::string name, char operation, char **argv);
    void checkDir(std::string fileLocationDir);
    std::vector<std::string> storePackagesInstalled(const char *listPackages);
};