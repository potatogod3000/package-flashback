#pragma once
#include <iostream>
#include <regex>
#include <cstring>
#include <algorithm>
#include <array>
#include <exception>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <ctime>
#include <climits>
// Unix Library for fork()
#include <sys/stat.h> // mkdir()

class Actions {
    public:
    void backupPackages(const char *listPackageCount, const char *listPackages, char **argv);
    void searchPackages(std::vector<std::string> packagesInstalled, char **argv);
    std::vector<std::string> storePackagesInstalled(const char *listPackages);
    void saveToFile(std::vector<std::string> packagesInstalled);
    const std::string currentDateTime();

    std::vector<std::string> fileCheck(char **argv);
    void restorePackages(std::string installPackagesCommand, std::vector<std::string> packagesInstalled, std::vector<std::string> packagesToRestore, char **argv);
    void installPackages(std::vector<std::string> packagesToRestore, std::string installPackagesCommand);
};