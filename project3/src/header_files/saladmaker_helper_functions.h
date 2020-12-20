#ifndef SALADMAKER_HELPER_FUNCTIONS_H
#define SALADMAKER_HELPER_FUNCTIONS_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <cassert>
#include <unistd.h>
#include <cstring>
#include <memory>

#include "chef_main.h"

using namespace std;

bool isNumeric(string str);

string convertToString(char *a, int size);

string getCurrentTime(time_t setTime, timeval setMilSec);
#endif