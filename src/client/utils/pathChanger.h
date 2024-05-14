#ifndef GAME_PATHCHANGER_H
#define GAME_PATHCHANGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#elif __APPLE__
#include <mach-o/dyld.h>
#endif


void setWorkingDirectoryToExecutablePath();


#endif //GAME_PATHCHANGER_H
