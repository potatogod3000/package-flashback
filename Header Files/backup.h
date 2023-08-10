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

class backup {
    void backupPackages(const char *listPackageCount, const char *listPackages, char **argv);
    std::vector<std::string> storePackagesInstalled(const char *listPackages);
    void searchPackages(std::vector<std::string> packagesInstalled, char **argv);
    void saveToFile(std::vector<std::string> packagesInstalled);
    const std::string currentDateTime();
};