#pragma once
#include <iostream>
#include <regex>
#include <cstring>
#include <algorithm>
#include <array>
#include <exception>
#include <iomanip>
/* Unix Library for fork()
#include <unistd.h>
#include <sys/wait.h>
#include <cerrno> */

void arch(char **argv);
void debian(char **argv);
void fedora(char **argv);
void ubuntu(char **argv);
