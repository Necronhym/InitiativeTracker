#ifndef GETFROMFILE_H
#define GETFROMFILE_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
//Fetches a string containing a substring from a file.
std::string GetFromFile(const char* string, const char* file);
//Converts string containing integers to integers.
int StringToInt(std::string string);
#endif
