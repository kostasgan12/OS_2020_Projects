#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <cassert>
#include <unistd.h>
#include <cstring>

#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>


using namespace std;

bool isNumeric(string str);

void list(char *name);
void printout(char *name);

#endif