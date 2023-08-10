#pragma once
#include <iostream>
#include <fstream>
#include <regex>

class system {
    public:
    const std::string xdgDataDir = getenv("HOME") + std::string("/.local/share");
    const std::string packageFlashbackDir = xdgDataDir + "/package-flashback";
    const std::string packageFlashbackFile = packageFlashbackDir + "/packagesInstalled.txt";
    const std::string distroNameFile = packageFlashbackDir + "/distroName.txt";

    void unsupportedSystem();
    bool operatingSystemCheck();
    std::string osName();
    void setCommandsAndRedirect(bool check, std::string name, char operation, char **argv);
    void checkDir(std::string fileLocationDir);
};