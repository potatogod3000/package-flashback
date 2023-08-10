#pragma once
#include <iostream>
#include <fstream>
#include <regex>

void unsupportedSystem();
bool operatingSystemCheck();
std::string osName();
void setCommandsAndRedirect(bool check, std::string name, char operation, char **argv);