#ifndef SALADMAKER_MAIN_H
#define SALADMAKER_MAIN_H

#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cmath>
#include <new>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <semaphore.h>

#include "../header_files/saladmaker_helper_functions.h"
#include "../header_files/common.h"

#define SEGMENTSIZE sizeof(salad_table_buffer_t)
#define SEGMENTPERM 0666

using namespace std;

extern int lowerTimeValue;
extern int UpperTimeValue;
extern int sharedMemoryId;
extern string missingVegetable;

#endif