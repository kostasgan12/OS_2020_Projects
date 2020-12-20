#ifndef CHEF_HELPER_FUNCTIONS_H
#define CHEF_HELPER_FUNCTIONS_H

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
// extern int numOfChildren;

char findSaladMaker(int veg1, int veg2);
string findPickedVeg(int veg1, int veg2);

#endif