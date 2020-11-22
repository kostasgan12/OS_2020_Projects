#ifndef CHILD_HELPER_FUNCTIONS_H
#define CHILD_HELPER_FUNCTIONS_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <cassert>
#include <unistd.h>
#include <cstring>

#include "main.h"

using namespace std;

bool isNumeric(string str);

void calculateChildrenAllocation(int **  valuesRangeArray, int numOfGrandchilds, int lowestValue, int upperValue);

#endif