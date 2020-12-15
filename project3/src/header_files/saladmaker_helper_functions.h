#ifndef SALADMAKER_HELPER_FUNCTIONS_H
#define SALADMAKER_HELPER_FUNCTIONS_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <cassert>
#include <unistd.h>
#include <cstring>

#include "chef_main.h"

using namespace std;

bool isNumeric(string str);

void calculateChildrenAllocation(int **valuesRangeArray, int numOfGrandchilds, int lowestValue, int upperValue);

string convertToString(char *a, int size);
int extractNumOfPrimes(string a);

#endif