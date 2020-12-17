#ifndef COMMON_MAIN_H
#define COMMON_MAIN_H

#include <semaphore.h>
#define BFSIZE 512

typedef struct
{
    char offered_vegetable[BFSIZE];
    sem_t occupied;             //check if table is occupied
    sem_t empty;                //check if table is empty
    int next_in;                //keep track of where to add the new vegetable 
    int next_out;               //keep track of which vegetable to take out
    sem_t chef_muting;          //pause chef
    sem_t saladmaker_1_muting;  //pause saladMaker
    sem_t saladmaker_2_Muting;  //pause saladMaker
    sem_t saladmaker_3_Muting;  //pause saladMaker
} salad_table_buffer_t;

#endif
