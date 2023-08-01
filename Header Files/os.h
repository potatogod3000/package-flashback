#pragma once
#include <iostream>
#include <regex>
#include <cstring>
#include <algorithm>
#include <array>
#include <exception>
#include <iomanip>
#include <fstream>
// Unix Library for fork()
#include <sys/stat.h> // mkdir()
/*
#include <unistd.h>
#include <sys/wait.h>
#include <cerrno>
*/

void packages(const char *listPackageCount, const char *listPackages, char **argv);
void searchPackages(std::vector<std::string> packagesInstalled, char **argv);
void savePackages(std::vector<std::string> packagesInstalled);