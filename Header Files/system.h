#pragma once
#include <iostream>
#include <fstream>
#include <regex>

bool operatingSystemCheck();
std::string osName();
void linuxSystem(bool check, std::string name, char **argv);