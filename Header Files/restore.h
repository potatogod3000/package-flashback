#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

std::vector<std::string> fileCheck(char **argv);
void restorePackages(const char *installPackagesCommand, std::vector<std::string> packagesInstalled, std::vector<std::string> packagesToRestore, char **argv);