#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <fstream>

std::vector<std::string> fileCheck(char **argv);
void restorePackages(std::string installPackagesCommand, std::vector<std::string> packagesInstalled, std::vector<std::string> packagesToRestore, char **argv);
void installPackages(std::vector<std::string> packagesToRestore, std::string installPackagesCommand);