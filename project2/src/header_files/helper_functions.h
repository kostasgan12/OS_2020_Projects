#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <cassert>
#include <unistd.h>
#include <cstring>
#include <memory>

#include "main.h"

using namespace std;

bool isNumeric(string str);
extern int numOfChildren;

void calculateChildrenAllocation(int **  valuesRangeArray, int arraySize, int lowestValue, int upperValue);
void calculateGrandchildrenAllocation(int **  valuesRangeArray, int arraySize, int lowestValue, int upperValue);

// template <std::size_t N>
// int myExecvp(const char* file, const char* const (&argv)[N]);


// int myExecvp(const char *file, const char *const argv[]);

string convertToString(char *a, int size);
int extractNumOfPrimes(string a);

#endif