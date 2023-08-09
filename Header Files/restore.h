#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>

std::vector<std::string> fileCheck(char **argv);
void restorePackages(const char *installPackagesCommand, std::vector<std::string> packagesInstalled, std::vector<std::string> packagesToRestore);