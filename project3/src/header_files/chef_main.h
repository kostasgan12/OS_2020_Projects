#ifndef CHEF_MAIN_H
#define CHEF_MAIN_H

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

#include <unistd.h>

#include <semaphore.h>

#include "../header_files/chef_helper_functions.h"
#include "../header_files/common.h"

#define SEGMENTSIZE sizeof(salad_table_buffer_t)
#define SEGMENTPERM 0666 

using namespace std;

extern int numOfSlds;
extern int manTime;

#endif