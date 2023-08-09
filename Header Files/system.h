#pragma once
#include <iostream>
#include <fstream>
#include <regex>

void unsupportedSystem();
bool operatingSystemCheck();
std::string osName();
void setCommands(bool check, std::string name, char **argv);
void installedPackages();
void toBeInstalledPackages();